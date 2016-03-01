#ifndef _BUFFER_H_INCLUDED
#define _BUFFER_H_INCLUDED

#ifdef  __cplusplus
extern "C" {
#endif

struct buffer_s;

struct buffer_s* ox_buffer_new(int buffer_size);
void ox_buffer_delete(struct buffer_s* self);
void ox_buffer_adjustto_head(struct buffer_s* self);
void ox_buffer_init(struct buffer_s* self);

int ox_buffer_getwritepos(struct buffer_s* self);
int ox_buffer_getreadpos(struct buffer_s* self);

void ox_buffer_addwritepos(struct buffer_s* self, int value);
void ox_buffer_addreadpos(struct buffer_s* self, int value);

int ox_buffer_getreadvalidcount(struct buffer_s* self);
int ox_buffer_getwritevalidcount(struct buffer_s* self);
int ox_buffer_getsize(struct buffer_s* self);

char* ox_buffer_getwriteptr(struct buffer_s* self);
char* ox_buffer_getreadptr(struct buffer_s* self);

int ox_buffer_write(struct buffer_s* self, const char* data, int len);

#ifdef  __cplusplus
}
#endif

#endif
