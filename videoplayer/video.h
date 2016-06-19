#ifndef VIDEO
#define VIDEO
#include <QDebug>
#include <QElapsedTimer>
#include "global.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavfilter/asrc_abuffer.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libpostproc/postprocess.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
}

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIOQ_SIZE (1 * 1024 * 1024)
#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

typedef struct VideoState {
    char            filename[1024];
    AVFormatContext *ic;
    int             videoStream, audioStream;
    AVStream        *audio_st;
    AVFrame         *audio_frame;
    PacketQueue     audioq;
    unsigned int    audio_buf_size;
    unsigned int    audio_buf_index;
    AVPacket        audio_pkt;
    uint8_t         *audio_pkt_data;
    int             audio_pkt_size;
    uint8_t         *audio_buf;
    uint8_t         *audio_buf1;
    DECLARE_ALIGNED(16,uint8_t,audio_buf2)[AVCODEC_MAX_AUDIO_FRAME_SIZE * 4];
    enum AVSampleFormat  audio_src_fmt;
    enum AVSampleFormat  audio_tgt_fmt;
    int             audio_src_channels;
    int             audio_tgt_channels;
    int64_t         audio_src_channel_layout;
    int64_t         audio_tgt_channel_layout;
    int             audio_src_freq;
    int             audio_tgt_freq;
    struct SwrContext *swr_ctx;
    SDL_Thread      *audioThread;
    volatile int             quit;
    double cur_time;
    double duration;
    double time_base;
} VideoState;

VideoState  *vs = NULL;
SDL_Surface *screen = NULL;

SDL_Thread *videoThread = NULL;
volatile bool Pause = 0;
volatile bool PlayIsEnd = 0;
AVFormatContext *pFormatCtx = NULL;
int videoStream = -1;
int audioStream = -1;
short volume = 128;
double video_duration = 0;
double video_cur_time = 0;
int video_frames = 0;
//void packet_queue_init(PacketQueue *q);
//int packet_queue_put(PacketQueue *q, AVPacket *pkt);
//int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);
//void packet_queue_flush(PacketQueue *q);
//int audio_decode_frame(VideoState *is);
//void audio_callback(void *userdata, Uint8 *stream, int len);
//int stream_component_open(VideoState *is/*, int stream_index*/);
//int audio_thread(void *arg);
//void setSource(const char *name);
//int openFile_and_getStream(const char *filename);
//void auto_scale(int dist_w,int dist_h,int *w,int *h);
//int video_thread(void *arg);

void packet_queue_init(PacketQueue *q)
{
    memset(q, 0, sizeof(PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
}

int packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
    AVPacketList *pkt1;

    pkt1 = (AVPacketList *)av_malloc(sizeof(AVPacketList));
    if (!pkt1) {
        return -1;
    }
    pkt1->pkt = *pkt;
    pkt1->next = NULL;

    SDL_LockMutex(q->mutex);

    if (!q->last_pkt) {
        q->first_pkt = pkt1;
    } else {
        q->last_pkt->next = pkt1;
    }

    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size;
    SDL_CondSignal(q->cond);
    SDL_UnlockMutex(q->mutex);
    return 0;
}

int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
    AVPacketList *pkt1;
    int ret;

    SDL_LockMutex(q->mutex);

    for(;;)
    {
        if(vs->quit)
        {
            ret = -1;
            break;
        }

        pkt1 = q->first_pkt;
        if (pkt1)
        {
            q->first_pkt = pkt1->next;
            if (!q->first_pkt)
            {
                q->last_pkt = NULL;
            }
            q->nb_packets--;
            q->size -= pkt1->pkt.size;
            *pkt = pkt1->pkt;

            av_free(pkt1);
            ret = 1;
            break;
        }
        else if (!block)
        {
            ret = 0;
            break;
        }
        else
        {
            SDL_CondWait(q->cond, q->mutex);
        }
    }

    SDL_UnlockMutex(q->mutex);

    return ret;
}

void packet_queue_flush(PacketQueue *q)
{
    AVPacketList *pkt, *pkt1;

    SDL_LockMutex(q->mutex);
    for (pkt = q->first_pkt; pkt != NULL; pkt = pkt1) {
        pkt1 = pkt->next;
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);
    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
}

int audio_decode_frame(VideoState *is)
{
    int len1, len2, decoded_data_size;
    AVPacket *pkt = &is->audio_pkt;
    int got_frame = 0;
    int64_t dec_channel_layout;
    int wanted_nb_samples, resampled_data_size;

    vs->cur_time = pkt->pts*vs->time_base;

    for (;;) {
        while (is->audio_pkt_size > 0) {
            if (!is->audio_frame) {
                if (!(is->audio_frame = av_frame_alloc())) {
                    return AVERROR(ENOMEM);
                }
            } else
                av_frame_unref(is->audio_frame);

            len1 = avcodec_decode_audio4(is->audio_st->codec, is->audio_frame, &got_frame,  pkt);
            if (len1 < 0) {
                // error, skip the frame
                is->audio_pkt_size = 0;
                break;
            }

            is->audio_pkt_data += len1;
            is->audio_pkt_size -= len1;

            if (!got_frame)
                continue;

            decoded_data_size = av_samples_get_buffer_size(NULL,
                                                           is->audio_frame->channels,
                                                           is->audio_frame->nb_samples,
                                                           ( AVSampleFormat)is->audio_frame->format, 1);

            dec_channel_layout = (is->audio_frame->channel_layout && is->audio_frame->channels
                                  == av_get_channel_layout_nb_channels(is->audio_frame->channel_layout))
                    ? is->audio_frame->channel_layout
                    : av_get_default_channel_layout(is->audio_frame->channels);

            wanted_nb_samples =  is->audio_frame->nb_samples;

            //fprintf(stderr, "wanted_nb_samples = %d\n", wanted_nb_samples);

            if (is->audio_frame->format != is->audio_src_fmt ||
                    dec_channel_layout != is->audio_src_channel_layout ||
                    is->audio_frame->sample_rate != is->audio_src_freq ||
                    (wanted_nb_samples != is->audio_frame->nb_samples && !is->swr_ctx)) {
                if (is->swr_ctx) swr_free(&is->swr_ctx);
                is->swr_ctx = swr_alloc_set_opts(NULL,
                                                 is->audio_tgt_channel_layout,
                                                 is->audio_tgt_fmt,
                                                 is->audio_tgt_freq,
                                                 dec_channel_layout,
                                                 ( AVSampleFormat)is->audio_frame->format,
                                                 is->audio_frame->sample_rate,
                                                 0, NULL);
                if (!is->swr_ctx || swr_init(is->swr_ctx) < 0) {
                    fprintf(stderr, "swr_init() failed\n");
                    break;
                }
                is->audio_src_channel_layout = dec_channel_layout;
                is->audio_src_channels = is->audio_st->codec->channels;
                is->audio_src_freq = is->audio_st->codec->sample_rate;
                is->audio_src_fmt = is->audio_st->codec->sample_fmt;
            }
            if (is->swr_ctx) {
                // const uint8_t *in[] = { is->audio_frame->data[0] };
                const uint8_t **in = (const uint8_t **)is->audio_frame->extended_data;
                uint8_t *out[] = { is->audio_buf2 };
                if (wanted_nb_samples != is->audio_frame->nb_samples) {
                    if (swr_set_compensation(is->swr_ctx, (wanted_nb_samples - is->audio_frame->nb_samples)
                                             * is->audio_tgt_freq / is->audio_frame->sample_rate,
                                             wanted_nb_samples * is->audio_tgt_freq / is->audio_frame->sample_rate) < 0) {
                        fprintf(stderr, "swr_set_compensation() failed\n");
                        break;
                    }
                }

                len2 = swr_convert(is->swr_ctx, out,
                                   sizeof(is->audio_buf2)
                                   / is->audio_tgt_channels
                                   / av_get_bytes_per_sample(is->audio_tgt_fmt),
                                   in, is->audio_frame->nb_samples);
                if (len2 < 0) {
                    fprintf(stderr, "swr_convert() failed\n");
                    break;
                }
                if (len2 == (int)sizeof(is->audio_buf2) / is->audio_tgt_channels / av_get_bytes_per_sample(is->audio_tgt_fmt)) {
                    fprintf(stderr, "warning: audio buffer is probably too small\n");
                    swr_init(is->swr_ctx);
                }
                is->audio_buf = is->audio_buf2;
                resampled_data_size = len2 * is->audio_tgt_channels * av_get_bytes_per_sample(is->audio_tgt_fmt);
            } else {
                resampled_data_size = decoded_data_size;
                is->audio_buf = is->audio_frame->data[0];
            }
            // We have data, return it and come back for more later
            return resampled_data_size;
        }
        if (pkt->data) av_free_packet(pkt);
        memset(pkt, 0, sizeof(*pkt));
        if (is->quit) return -1;
        if (packet_queue_get(&is->audioq, pkt, 1) < 0) return -1;

        is->audio_pkt_data = pkt->data;
        is->audio_pkt_size = pkt->size;
    }
}

void audio_callback(void *userdata, Uint8 *stream, int len)
{
    VideoState *is = (VideoState *)userdata;
    int len1, audio_data_size;

    while (len > 0)
    {
        if (is->audio_buf_index >= is->audio_buf_size)
        {
            audio_data_size = audio_decode_frame(is);

            if(audio_data_size < 0) {
                /* silence */
                is->audio_buf_size = 1024;
                memset(is->audio_buf, 0, is->audio_buf_size);
            } else {
                is->audio_buf_size = audio_data_size;
            }
            is->audio_buf_index = 0;
        }

        len1 = is->audio_buf_size - is->audio_buf_index;
        if (len1 > len)
        {
            len1 = len;
        }

        if(vs->duration > 0 && vs->cur_time > vs->duration - 0.2)
        {
            if(vs->quit == 0)
                PlayIsEnd = 1;
            vs->quit = 1;
        }

//        memcpy(stream, (uint8_t *)is->audio_buf + is->audio_buf_index, len1);
        //set volume
        SDL_MixAudio(stream, (uint8_t *)is->audio_buf + is->audio_buf_index, len1, volume);
        len -= len1;
        stream += len1;
        is->audio_buf_index += len1;
    }
}

int stream_component_open(VideoState *is, int stream_index) {
    AVFormatContext *ic = is->ic;
    AVCodecContext *codecCtx;
    AVCodec *codec;
    SDL_AudioSpec wanted_spec, spec;
    int64_t wanted_channel_layout = 0;
    int wanted_nb_channels;
    const int next_nb_channels[] = {0, 0, 1 ,6, 2, 6, 4, 6};

    if (stream_index < 0 || stream_index >= (int)ic->nb_streams) {
        return -1;
    }

    codecCtx = ic->streams[stream_index]->codec;
    wanted_nb_channels = codecCtx->channels;
    if(!wanted_channel_layout || wanted_nb_channels != av_get_channel_layout_nb_channels(wanted_channel_layout)) {
        wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
        wanted_channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
    }

    wanted_spec.channels = av_get_channel_layout_nb_channels(wanted_channel_layout);
    wanted_spec.freq = codecCtx->sample_rate;
    if (wanted_spec.freq <= 0 || wanted_spec.channels <= 0) {
        fprintf(stderr, "Invalid sample rate or channel count!\n");
        return -1;
    }
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.silence = 0;
    wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = is;

    while(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
        fprintf(stderr, "SDL_OpenAudio (%d channels): %s\n", wanted_spec.channels, SDL_GetError());
        wanted_spec.channels = next_nb_channels[FFMIN(7, wanted_spec.channels)];
        if(!wanted_spec.channels) {
            fprintf(stderr, "No more channel combinations to tyu, audio open failed\n");
            return -1;
        }
        wanted_channel_layout = av_get_default_channel_layout(wanted_spec.channels);
    }

    if (spec.format != AUDIO_S16SYS) {
        fprintf(stderr, "SDL advised audio format %d is not supported!\n", spec.format);
        return -1;
    }
    if (spec.channels != wanted_spec.channels) {
        wanted_channel_layout = av_get_default_channel_layout(spec.channels);
        if (!wanted_channel_layout) {
            fprintf(stderr, "SDL advised channel count %d is not supported!\n", spec.channels);
            return -1;
        }
    }

//    fprintf(stderr, "%d: wanted_spec.format = %d\n", __LINE__, wanted_spec.format);
//    fprintf(stderr, "%d: wanted_spec.samples = %d\n", __LINE__, wanted_spec.samples);
//    fprintf(stderr, "%d: wanted_spec.channels = %d\n", __LINE__, wanted_spec.channels);
//    fprintf(stderr, "%d: wanted_spec.freq = %d\n", __LINE__, wanted_spec.freq);

//    fprintf(stderr, "%d: spec.format = %d\n", __LINE__, spec.format);
//    fprintf(stderr, "%d: spec.samples = %d\n", __LINE__, spec.samples);
//    fprintf(stderr, "%d: spec.channels = %d\n", __LINE__, spec.channels);
//    fprintf(stderr, "%d: spec.freq = %d\n", __LINE__, spec.freq);

    is->audio_src_fmt = is->audio_tgt_fmt = AV_SAMPLE_FMT_S16;
    is->audio_src_freq = is->audio_tgt_freq = spec.freq;
    is->audio_src_channel_layout = is->audio_tgt_channel_layout = wanted_channel_layout;
    is->audio_src_channels = is->audio_tgt_channels = spec.channels;

    codec = avcodec_find_decoder(codecCtx->codec_id);
    if (!codec || (avcodec_open2(codecCtx, codec, NULL) < 0)) {
        fprintf(stderr, "Unsupported codec!\n");
        return -1;
    }
    ic->streams[stream_index]->discard = AVDISCARD_DEFAULT;
    switch(codecCtx->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        is->audioStream = stream_index;
        is->audio_st = ic->streams[stream_index];
        is->audio_buf_size = 0;
        is->audio_buf_index = 0;
        memset(&is->audio_pkt, 0, sizeof(is->audio_pkt));
        packet_queue_init(&is->audioq);
        SDL_PauseAudio(0);
        break;
    default:
        break;
    }
    return 0;
}
/*
static void stream_component_close(VideoState *is, int stream_index) {
    AVFormatContext *oc = is->;
    AVCodecContext *avctx;

    if(stream_index < 0 || stream_index >= ic->nb_streams)	return;
    avctx = ic->streams[stream_index]->codec;

}
*/
QMutex audio_mutex;
int audio_thread(void *arg)
{
    QMutexLocker locker(&audio_mutex);
    VideoState *is = (VideoState *)arg;
    AVFormatContext *ic = NULL;
    AVPacket pkt1, *packet = &pkt1;
    int ret, i, audio_index = -1;

    is->audioStream=-1;

    if (avformat_open_input(&ic, is->filename, NULL, NULL) != 0) {
        return -1;
    }
    is->ic = ic;
    if (avformat_find_stream_info(ic, NULL) < 0) {
        return -1;
    }
//    av_dump_format(ic, 0, is->filename, 0);
    for (i=0; i<(int)ic->nb_streams; i++) {
        if (ic->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO && audio_index < 0) {
            audio_index=i;
            break;
        }
    }
    if (audio_index >= 0) {
        stream_component_open(is, audio_index);
        vs->time_base = av_q2d(ic->streams[audio_index]->time_base);
        vs->duration = ic->streams[audio_index]->duration*vs->time_base;
        vs->cur_time = 0;
        if(vs->duration < 0)
            vs->duration = video_duration;
    }
    if (is->audioStream < 0) {
        fprintf(stderr, "%s: could not open codecs\n", is->filename);
        goto fail;
    }
    while(Pause);//wait for Synchronization
    // main decode loop
    for(;;) {
        if(is->quit) break;
        if (is->audioq.size > MAX_AUDIOQ_SIZE) {
            SDL_Delay(10);
            continue;
        }
        ret = av_read_frame(is->ic, packet);
        if (ret < 0) {
            if(ret == AVERROR_EOF || avio_feof(is->ic->pb)) {
                break;
            }
            if(is->ic->pb && is->ic->pb->error) {
                break;
            }
            continue;
        }

        if (packet->stream_index == is->audioStream) {
            packet_queue_put(&is->audioq, packet);
        } else {
            av_free_packet(packet);
        }
    }

    while (!is->quit) {
        SDL_Delay(10);
    }

fail: {
        SDL_Event event;
        event.type = FF_QUIT_EVENT;
        event.user.data1 = is;
        SDL_PushEvent(&event);
    }
    SDL_CloseAudio();
    qDebug("audioThread --> return at : %0.3f/%0.3f",is->cur_time,is->duration);
    return 0;
}

int openFile_and_getStream(const char *filename)
{
    if( avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0 )
    {
        return 2; // Couldn't open file
    }
    vs->ic = pFormatCtx;

    // Retrieve stream information
    if( avformat_find_stream_info(pFormatCtx, NULL) < 0 )
    {
        return -1; // Couldn't find stream information
    }

    // Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, filename, 0);

    // Find the first video stream
    for(uint i=0; i < pFormatCtx->nb_streams; i++)
    {
        if(videoStream < 0 && pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
        if (audioStream < 0 && pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            audioStream=i;
            vs->audioStream = i;
        }
    }
    qDebug("videostream : %d; audiostream : %d",videoStream,audioStream);
    return 0;
}

void auto_scale(int dist_w,int dist_h,int *w,int *h)
{
    if(dist_w > 0 && dist_h > 0)
    {
        float aspect_ratio = (float)dist_w/dist_h;
        if(aspect_ratio > (float)*w/(*h))
        {
            *w = WINDOW_WIDTH;
            *h = WINDOW_WIDTH/aspect_ratio;
        }
        else
        {
            *h = WINDOW_HEIGHT;
            *w = WINDOW_HEIGHT*aspect_ratio;
        }
    }
}
QMutex video_mutex;
int video_thread(void *arg)
{
    QMutexLocker locker(&video_mutex);
    PlayIsEnd = 0;
    Q_UNUSED(arg);
    // Get a pointer to the codec context for the video stream
    AVCodecContext * pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    // Find the decoder for the video stream
    AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if( pCodec == NULL ) {
        fprintf(stderr, "Unsupported codec!\n");
        return -1; // Codec not found
    }

    // Open codec
    AVDictionary* optionsDict = NULL;
    if( avcodec_open2(pCodecCtx, pCodec, &optionsDict) < 0 )
    {
        return -1; // Could not open codec
    }

    // Allocate video frame
    AVFrame* pFrame = av_frame_alloc();
    if( pFrame == NULL ) {
        return -1;
    }

    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
    auto_scale(pCodecCtx->width, pCodecCtx->height, &width, &height);

    struct SwsContext* sws_ctx = sws_getContext(
                pCodecCtx->width,
                pCodecCtx->height,
                pCodecCtx->pix_fmt,
                pCodecCtx->width,
                pCodecCtx->height,
                AV_PIX_FMT_YUV420P,
                SWS_BICUBIC,
                NULL,
                NULL,
                NULL);

//    int numBytes = avpicture_get_size(
//                AV_PIX_FMT_YUV420P,
//                pCodecCtx->width,
//                pCodecCtx->height);
//    uint8_t* buffer = (uint8_t *)av_malloc( numBytes*sizeof(uint8_t) );

//    avpicture_fill((AVPicture *)pFrame, buffer, AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height);
//    av_free(buffer);

    // Read frames and save first five frames to disk
    float frame_rate = av_q2d(pFormatCtx->streams[videoStream]->r_frame_rate);
    double time_base = av_q2d(pFormatCtx->streams[videoStream]->time_base);
    video_duration = (double)pFormatCtx->duration/1e6;
    video_frames = pFormatCtx->streams[videoStream]->nb_frames;
    if(video_frames < 1 && frame_rate > 0 && video_duration > 0)
    {
        video_frames = frame_rate*video_duration - 1;
    }
    qDebug("size:%dx%d   fps:%0.3f   duration:%0.3lfs   frames:%d  code:%s",width,height,frame_rate,video_duration,video_frames, pCodec->name);

    //////////////////////////////////////////////////////

    // Make a screen to put our video
    SDL_Rect sdlRect{0, 0, (Uint16)width, (Uint16)height};
    sdlRect.x = (SCREEN_WIDTH - width)/2;
    sdlRect.y = (SCREEN_HEIGHT - height)/2;
//    sdlRect.w = SCREEN_WIDTH;
//    sdlRect.h = SCREEN_HEIGHT;

    if(!screen)
    {
        fprintf(stderr, "SDL: could not set video mode - exiting\n");
        exit(1);
    }

    // Allocate a place to put our YUV image on that screen
    SDL_Overlay * bmp = SDL_CreateYUVOverlay(pCodecCtx->width,
                                             pCodecCtx->height,
                                             SDL_YV12_OVERLAY,
                                             screen);
    // Read frames and save first five frames to disk
    AVPacket packet;
    SDL_Event event;
    volatile int play_over = 0;
    QElapsedTimer timer;
    video_cur_time = 0;
    double pauseTime = 0.0;
    while(Pause);//wait for Synchronization
    timer.start();
    while(! play_over)
    {
        if(!Pause)
        {
            if(av_read_frame(pFormatCtx, &packet)>=0)
            {
                // Is this a packet from the video stream?
                if(packet.stream_index==videoStream)
                {
//                    qDebug()<<packet.pts*time_base<<t.elapsed()<<fram++;

                    // Decode video frame
                    int frameFinished;
                    avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,&packet);
                    // Did we get a video frame?
                    if(frameFinished)
                    {
                        SDL_LockYUVOverlay(bmp);
                        AVPicture *pict = (AVPicture *)av_mallocz(sizeof(AVPicture));
                        pict->data[0] = bmp->pixels[0];
                        pict->data[1] = bmp->pixels[2];
                        pict->data[2] = bmp->pixels[1];

                        pict->linesize[0] = bmp->pitches[0];
                        pict->linesize[1] = bmp->pitches[2];
                        pict->linesize[2] = bmp->pitches[1];

                        // Convert the image into YUV format that SDL uses
                        if (pCodecCtx->pix_fmt == AV_PIX_FMT_YUV420P)
                        {
                            sws_scale(sws_ctx, pFrame->data, pFrame->linesize,
                                      0, pCodecCtx->height, pict->data, pict->linesize);
                        }
                        av_free(pict);
                        SDL_UnlockYUVOverlay(bmp);
                        SDL_DisplayYUVOverlay(bmp, &sdlRect);

                        video_cur_time = packet.dts*time_base;
                        while(video_cur_time > timer.elapsed()/1000.0 + pauseTime)
                        {
                            SDL_Delay(5);
                        }
//                        fprintf(stderr, "%0.3f/%0.3f\r",video_cur_time,video_duration);
                    }
                }
            }
            else
            {
                play_over = 1;
                Pause = 1;
                qDebug("#play over  at : %0.3f/%0.3f",video_cur_time,video_duration);
                break;
            }
            if(video_duration > 0 && video_cur_time > video_duration - 0.1)
            {
                qDebug("play over  at : %0.3f/%0.3f",video_cur_time,video_duration);
                break;
            }
            // Free the packet that was allocated by av_read_frame
            av_free_packet(&packet);
        }
        if(vs->quit > 0)
        {
            qDebug("stop  at : %0.3f/%0.3f",video_cur_time,video_duration);
            break;
        }
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                qDebug("x:%d y:%d",event.button.x, event.button.y);
            }
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    vs->quit = 1;
                    //            SDL_Quit();
                    qDebug()<<"quit :"<<Pause;
                    break;
                case SDLK_SPACE:
                    Pause = ! Pause;
                    SDL_PauseAudio(Pause);
                    if(Pause)
                    {
                        pauseTime += timer.elapsed()/1000.0;
                        timer.invalidate();
                    }
                    else
                        timer.start();
                    qDebug()<<"pause :"<<Pause;
                    break;
                case SDLK_UP:
                    volume += 10;
                    if(volume > 128)
                        volume =128;
                    qDebug()<<"volume :"<<volume;
                    break;
                case SDLK_DOWN:
                    volume -= 10;
                    if(volume < 0)
                        volume =0;
                    qDebug()<<"volume :"<<volume;
                    break;
                case SDLK_LEFT:
                    pauseTime -= 5;
                    break;
                case SDLK_RIGHT:
                    pauseTime += 5;
                    break;
                default:
                    break;
                }
            }
        }
    }
    if(vs->quit  == 0)
        PlayIsEnd = 1;
    vs->quit = 1;
//    qDebug()<<pFormatCtx<<pCodecCtx;
    SDL_FreeYUVOverlay(bmp);
    SDL_FreeSurface(screen);
    // Free the YUV frame
    av_frame_free(&pFrame);

    // Close the codec
    if(pFormatCtx != NULL)
    {
        avcodec_close(pCodecCtx);
    }
    qDebug("videoThread --> return  at : %0.3f/%0.3f",video_cur_time,video_duration);
    return 0;
}
void Init_all(void)
{
    // ffmpeg
    // Register all formats and codecs
    av_register_all();
    avformat_network_init();
    vs = (VideoState *)av_mallocz(sizeof(VideoState));

    // SDL init
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    //hide cursor
    SDL_ShowCursor(0);
#ifndef __DARWIN__
//    fprintf(stderr,"%s\tline:%d\n",__FILE__,__LINE__);
/// SDL_SetVideoMode()会刷新屏幕导致开始播放时黑屏，放在初始化防止每次开始播放时都黑屏
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
#else
    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 24, 0);
#endif
//    fprintf(stderr,"%s\tline:%d\n",__FILE__,__LINE__);
}

int Play(void)
{
    if(audioStream != -1)
    {
        vs->audioThread = SDL_CreateThread(audio_thread, vs);
        if (!vs->audioThread)
        {
            av_free(vs);
            return -1;
        }
    }
    //    SDL_WaitThread(vs->parse_tid,&s);

    if(videoStream != -1)
    {
        videoThread = SDL_CreateThread(video_thread,NULL);
        if(!videoThread)
        {
            return -1;
        }
    }
    return 0;
}

#endif // VIDEO
