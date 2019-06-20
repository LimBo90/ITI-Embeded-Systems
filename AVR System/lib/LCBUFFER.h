#ifndef _LCIRCBUFF_H_
#define __LCIRCBUFF_H_

#define LCBUFFER_BUFFER_SIZE 10

typedef struct {
    u8 buffer[LCIRC_BUFFER_SIZE];
    u8 head ;
    u8 tail;
    u8 full;
} CBuffer;


/// Reset the circular buffer to empty, head == tail
void LCBUFFER_reset(CBuffer* cbuf);

/// Put data into buffer, rejects new data if the buffer is full
/// Returns 0 on success, -1 if buffer is full
u8 LCBUFFER_put(CBuffer* cbuf, u8 data);

/// Put data into buffer, rejects new data if the buffer is full
/// Returns 0 on success, -1 if buffer is full
u8 LCBUFFER_putStr(CBuffer* cbuf, u8 * data);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
u8 LCBUFFER_get(CBuffer* cbuf, u8 * data);

/// Returns true if the buffer is empty
u8 LCBUFFER_empty(CBuffer* cbuf);

/// Returns true if the buffer is full
u8 LCBUFFER_full(CBuffer* cbuf);


#endif