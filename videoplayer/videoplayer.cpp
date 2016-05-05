#include "videoplayer.h"
#include "video.h"
//#include <QDesktopWidget>

VideoPlayer::VideoPlayer(QObject *parent, QWidget *window):QThread(parent)
{
    setObjectName(QStringLiteral("VideoPlayer"));
    Q_ASSERT(window);
    mainWindow = window;
    filename.clear();
    isOpened = false;
    isPlaying = false;
    playingNO = -1;
    play_cnt = 0;
    Stop = false;
    playMode = Cycle;

    volume = loadHistory("Video_Volume", 128).toInt();

    label.resize(SCREEN_WIDTH,SCREEN_HEIGHT);
    label.show();//TODO
    connect(&label, &Label::gestureActivated, this, &VideoPlayer::getGesture);

    Init();
    connect(this,SIGNAL(playEnd()),this,SLOT(replay()));
    start();

    timer = new QTimer();
    timer->setTimerType(Qt::VeryCoarseTimer);
    timer->start(3600000);
    connect(timer, &QTimer::timeout, this, &VideoPlayer::freeMem);

    audioPlayer = new AudioPlayer();
    connect(this,&VideoPlayer::stopAudioPlayer,audioPlayer,&AudioPlayer::stop);
    audioPlayer->setRobotId(RobotName);
    audioPlayer->startAudioPlayer();

    m_thread = new QThread(this);
    m_thread->start();
    moveToThread(m_thread);
//    QTimer::singleShot(5000,Qt::VeryCoarseTimer,[](){SDL_CloseAudio();});
    QStringList filters;
    filters<<"*.mkv"<<"*.mp4"<<"*.flv"<<"*.rm"<<"*.rmvb";
    QDir dir("./");
    QStringList filelist = dir.entryList(filters);
    dir.setPath("/video/");
    foreach(QString file, dir.entryList(filters))
    {
        filelist<<file.prepend(dir.absolutePath().append('/'));
    }
    setPlaylist(filelist);
    type = 0;
}

VideoPlayer::~VideoPlayer()
{
    m_thread->quit();
    stop();
    Stop = true;
    wait(100);
    SDL_Quit();
    delete m_thread;
    delete timer;
    delete audioPlayer;
}

void VideoPlayer::setSource(const char *name)
{
    vs->quit = 0;
    strcpy(vs->filename, name);
    filename = name;
}

void VideoPlayer::setSource(const QString &name)
{
    setSource(name.toLocal8Bit().data());
}

void VideoPlayer::setVolume(int vol)
{
    volume = vol;
    saveHistory(vol, "Video_Volume");
}

int VideoPlayer::Volume()
{
    return volume;
}

QString VideoPlayer::source() const
{
    return filename;
}

void VideoPlayer::Init()
{
    Init_all();
}

int VideoPlayer::openFile_and_getStream()
{
    if( avformat_open_input(&pFormatCtx,vs->filename , NULL, NULL) != 0 )
    {
        qDebug()<<"Couldn't open"<<vs->filename;
        return ENOENT; // Couldn't open file
    }
    vs->ic = pFormatCtx;

    // Retrieve stream information
    if( avformat_find_stream_info(pFormatCtx, NULL) < 0 )
    {
        return -1; // Couldn't find stream information
    }

    // Dump information about file onto standard error
//    av_dump_format(pFormatCtx, 0, filename.toLatin1().data(), 0);

    videoStream = -1;
    audioStream = -1;
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
void VideoPlayer::wait_for_end()
{
    while(!vs->quit)
    {
        SDL_Delay(10);
        qApp->processEvents();
    }
    // Close the video file
    stop();
}

void VideoPlayer::addToPlaylist(const QString &file, int que)
{
    isOpened = false;
    if(que == -1)
        playlist<<file;
    else
        playlist.insert(que,file);
}

void VideoPlayer::removeFromPlaylist(const QString &file, int que)
{
    if(que == -1)
        playlist.removeLast();
    else
        playlist.removeOne(file);
}

void VideoPlayer::playNext(int n)
{
    if(! playlist.isEmpty())
    {
        if(isPlaying || isOpened)
            stop();
        playingNO += n;
        uint cnt = playlist.count();
        playingNO = (playingNO + cnt)%cnt;
        if(playingNO < 0)
            playingNO = 0;
        qDebug()<<"\n##\tplay Next: "<<playingNO<<playlist[playingNO];
        setSource(playlist[playingNO]);
        play();
    }
}

void VideoPlayer::playLast(int l)
{
    playNext(- l);
}

void VideoPlayer::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    if(cmd.type == SSDB_CTRL_VideoCtrl)
    {
        type = 0;
        switch (cmd.videoCtrl)
        {
        case Video_Play:
            if(isPlaying)
                stop();
            play();
            break;
        case Video_Pause:
            pause();
            break;
        case Video_ContinuePlay:
            pause();
            break;
        case Video_Stop:
            stop();
            break;
        case Video_PlayNext:
            playNext();
            break;
        case Video_PlayLast:
            playLast();
            break;
        case Video_SetPlayList:
            stop();
//            setPlaylist(cmd.msg.split(" ",QString::SkipEmptyParts));
            play();
            break;
        case Video_PlayList:
        {
            QString list = playlist.join(" ");
            emit returnMsg(list, (int)cmd.videoCtrl);
        }
            break;
        case Video_Info:
        {
            QString list("%1 %2");
            list = list.arg(filename.isEmpty() ? "NULL": filename).arg((int)(position()/duration()*100));
            emit returnMsg(list, (int)cmd.videoCtrl);
        }
            break;
        case Video_SetCyclePlay:
            setPlayMode(Cycle);
            if(! cmd.msg.isEmpty())
            {
                bool ok;
                int no = cmd.msg.toInt(&ok);
                if(ok)
                    play(no);
                else
                    play(playlist.indexOf(QRegExp(cmd.msg)));
            }
            break;
        case Video_SetSinglePlay:
            setPlayMode(Single);
            play(cmd.msg);
            break;
        case Video_SetSingleCyclePlay:
            setPlayMode(SingleCycle);
            play(cmd.msg);
            break;
        default:
            break;
        }
    }
}

// only for play emotion
int VideoPlayer::play(const QString &file, int type)
{
    this->type = type;
    return play(file);
}

double VideoPlayer::position() const
{
    return video_cur_time;
}

double VideoPlayer::duration() const
{
    return video_duration > 0.1 ? video_duration : -1;
}

void VideoPlayer::setPlayMode(VideoPlayer::PlayMode mode)
{
    playMode = mode;
    qDebug()<<"setPlayMode:"<<mode;
}

const QString &VideoPlayer::getPlayingFilename() const
{
    return filename;
}

void VideoPlayer::run()
{
//    qDebug()<<QThread::currentThread()<<QThread::thread()<<m_thread;
    while(! Stop)
    {
        if(PlayIsEnd)
        {
            PlayIsEnd = 0;
            qDebug()<<"play end:"<<filename;
//            msleep(100);
            emit playEnd();
        }
        msleep(20);
    }
}

void VideoPlayer::freeMem()
{
    qDebug()<<"freeMem";
    system("echo 1 > /proc/sys/vm/drop_caches");
}

void VideoPlayer::updateUI()
{
    mainWindow->repaint();
    label.hide();
}

void VideoPlayer::getGesture(int type)
{
    switch (type)
    {
    case 0:
        stop(true);
        emit changeWindows();
        break;
    default:
        break;
    }
}

Label &VideoPlayer::getLabel()
{
    return label;
}

bool VideoPlayer::IsOpened() const
{
    return isOpened;
}

VideoPlayer::PlayMode VideoPlayer::getPlayMode() const
{
    return playMode;
}

bool VideoPlayer::IsPause() const
{
    return Pause;
}

bool VideoPlayer::IsPlaying() const
{
    return isPlaying;
}

void VideoPlayer::setPlaylist(const QStringList &list)
{
    playlist = list;
}

const QStringList &VideoPlayer::getPlaylist() const
{
    return playlist;
}

int VideoPlayer::play()
{
//    qDebug()<<QThread::currentThread()<<QThread::thread()<<m_thread;
    if(Pause)
    {
        pause();
        return 0;
    }
    msleep(50);
    play_cnt ++;
    if(! isOpened)
    {
        if(!playlist.isEmpty() && playingNO < 0)
        {
            setSource(playlist[0]);
            playingNO = 0;
        }
        label.show();
        mainWindow->hide();
//        label.activateWindow();
        isOpened = true;
        isPlaying = true;
        Pause = true;
        vs->quit = 0;

        if(openFile_and_getStream() != 0)
        {
            updateUI();
            return ENOENT;
        }
        qDebug()<<"##\tplay_cnt :"<<play_cnt<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if(videoStream >= 0)
        {
            videoThread = SDL_CreateThread(video_thread,NULL);
            if(videoThread == NULL)
            {
                printf("##ERROR\tvideoThread start failed");
                return -1;
            }
//            videothread.start();
        }
        msleep(50);
        if(audioStream >= 0)
        {
            vs->audioThread = SDL_CreateThread(audio_thread, vs);
            if (vs->audioThread == NULL)
            {
                av_free(vs);
                printf("##ERROR\taudioThread start failed");
                return -1;
            }
            emit stopAudioPlayer();
        }
    }
    Pause = false;
    SDL_PauseAudio(0);
    return 0;
}

int VideoPlayer::play(const QString &file)
{
    if(! QFile(file).exists())
    {
        qDebug()<<file<<"is not exist";
        return ENOENT;
    }
    stop();
    setSource(file);
    playingNO = 0;
    return play();
}

int VideoPlayer::play(int no)
{
    if(no < playlist.length() && no >= 0)
    {
        stop();
        playingNO = no;
        setSource(playlist[no]);
        return play();
    }
    return -1;
}

void VideoPlayer::silence(const bool &s)
{
    vs->quit = s;//stop audioThread
    SDL_PauseAudio(s);
}

void VideoPlayer::replay()
{
    if(type > 0)//表情播放
    {
        type = 0;
        emit replayEmotion();
        return;
    }
    msleep(100);
    switch (playMode)
    {
    case Cycle:
        playNext();
        break;
    case SingleCycle:
        play(filename);
        break;
    case Single:
        //播放完成后，触发播放表情
//        updateUI();
        emit replayEmotion();
        break;
    default:
        break;
    }
}

void VideoPlayer::pause()
{
    if(isOpened)
    {
        SDL_Event event;
        event.type = SDL_KEYDOWN;
        event.key.keysym.sym = SDLK_SPACE;
        SDL_PushEvent(&event);
        isPlaying = Pause;
        //    SDL_PauseAudio(1);
        audioPlayer->startAudioPlayer();
    }
}

void VideoPlayer::stop(bool repaint)
{
    QMutexLocker locker(&stopMutex);//加入互斥锁，防止重入
//    pause();
    if(isPlaying || isOpened)
    {
        isPlaying = false;
        vs->quit = 1;
//        msleep(100);

        if(audioStream >= 0)
        {
//            SDL_KillThread(vs->audioThread);
            SDL_WaitThread(vs->audioThread,NULL);
            audioPlayer->startAudioPlayer();
        }
//        videothread.stop();
        if(videoStream >= 0)
        {
//            SDL_KillThread(videoThread);
            SDL_WaitThread(videoThread,NULL);
        }
        if(pFormatCtx != NULL)
            avformat_close_input(&pFormatCtx);
    }
    Pause = 0;
    isOpened = false;

    if(repaint)
    {
        updateUI();
    }
}

/*
VideoThread::VideoThread()
{
    play_stop = false;
    play_over = false;
}

VideoThread::~VideoThread()
{
    vs->quit = 1;
    play_stop = 1;
    msleep(50);
    wait();
}

void VideoThread::stop()
{
    play_stop = 1;
    quit();
    msleep(100);
    if(isRunning())
        terminate();
    wait();
}

double VideoThread::position()
{
    return video_cur_time;
}

double VideoThread::duration()
{
    return video_duration;
}

void VideoThread::run()
{
    play_stop = 0;
    play_over = 0;
    PlayIsEnd = 0;
    // Get a pointer to the codec context for the video stream
    AVCodecContext * pCodecCtx = pFormatCtx->streams[videoStream]->codec;

    // Find the decoder for the video stream
    AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if( pCodec == NULL ) {
        fprintf(stderr, "Unsupported codec!\n");
        play_stop = 1; // Codec not found
    }

    // Open codec
    AVDictionary* optionsDict = NULL;
    if( avcodec_open2(pCodecCtx, pCodec, &optionsDict) < 0 )
    {
        play_stop = 1; // Could not open codec
    }

    // Allocate video frame
    AVFrame* pFrame = av_frame_alloc();
    if( pFrame == NULL ) {
        play_stop = 1;
    }

    int width=SCREEN_WIDTH, height = SCREEN_HEIGHT;
    auto_scale(pCodecCtx->width, pCodecCtx->height, &width, &height);
    qDebug("width = %d, height = %d",width,height);
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

    int numBytes = avpicture_get_size(
                AV_PIX_FMT_YUV420P,
                pCodecCtx->width,
                pCodecCtx->height);
    uint8_t* buffer = (uint8_t *)av_malloc( numBytes*sizeof(uint8_t) );

    avpicture_fill((AVPicture *)pFrame, buffer, AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height);

    // Read frames and save first five frames to disk
    float frame_rate = av_q2d(pFormatCtx->streams[videoStream]->r_frame_rate);
    double time_base = av_q2d(pFormatCtx->streams[videoStream]->time_base);
    video_duration = (double)pFormatCtx->duration/1e6;
    qDebug()<<frame_rate<<video_duration<<pFormatCtx->streams[videoStream]->nb_frames;

    //////////////////////////////////////////////////////

    // Make a screen to put our video
    SDL_Rect sdlRect;
    sdlRect.x = 0;
    sdlRect.y = 0;
    //    width = pCodecCtx->width;
    //    height = pCodecCtx->height;
    sdlRect.w = width;
    sdlRect.h = height;

#ifndef __DARWIN__
//    fprintf(stderr,"%s\tline:%d\n",__FILE__,__LINE__);
    screen = SDL_SetVideoMode(width, height, 0, 0);
#else
    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 24, 0);
#endif
//    fprintf(stderr,"%s\tline:%d\n",__FILE__,__LINE__);
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
    QElapsedTimer timer;
    video_cur_time = 0;
    while(Pause);//wait for Synchronization
    timer.start();
    while(! play_over && !play_stop)
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
                        AVPicture *pict;
                        pict = new AVPicture;
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
                        SDL_UnlockYUVOverlay(bmp);
                        SDL_DisplayYUVOverlay(bmp, &sdlRect);

                        video_cur_time = packet.dts*time_base;
                        while(video_cur_time>timer.elapsed()/1000.0)
                            SDL_Delay(2);
                        //                        fprintf(stderr, "%0.3f/%0.3f\r",video_cur_time,video_duration);
                    }
                }
            }
            //            else
            //            {
            //                play_over = 1;
            //                Pause = 1;
            //                qDebug()<<"play_over";
            //                break;
            //            }
            if(video_duration > 0 && video_cur_time > video_duration - 0.1)
            {
                qDebug("play over  at : %0.3f/%0.3f",video_cur_time,video_duration);
                break;
            }
        }
        if(vs->quit)
            break;
        // Free the packet that was allocated by av_read_frame
        av_free_packet(&packet);
        if(SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //        case SDL_KEYUP:
                vs->quit = 1;
                SDL_Quit();
                qDebug()<<"quit :"<<Pause;
                break;
            case SDLK_SPACE:
                Pause = ! Pause;
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
            default:
                break;
            }
    }
    if(vs->quit  == 0)
        PlayIsEnd = 1;
    vs->quit = 1;
    SDL_FreeYUVOverlay(bmp);
    SDL_FreeSurface(screen);
    // Free the YUV frame
    av_frame_free(&pFrame);
    av_free(buffer);

    // Close the codec
    avcodec_close(pCodecCtx);
    //    SDL_Quit();
    qDebug("videoThread --> return  at : %0.3f/%0.3f",video_cur_time,video_duration);
//    return 0;
}
*/
