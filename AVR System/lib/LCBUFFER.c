
#include "LSTD_TYPES.h"
#include "LCBUFFER.h"

/**
 * Reset the circular buffer to empty, head == tail
 */
void LCBUFFER_voidReset(CBuffer* cbuf){
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = 0;
}

/**
 * Put data into buffer, rejects new data if the buffer is full
 * Returns 1 on success, 0 if buffer is full
 */
u8  LCBUFFER_u8Put(CBuffer* cbuf, u8 data){
    u8 r = 0;

    if(!LCBUFFER_u8Full(cbuf))
    {
        cbuf->buffer[cbuf->head] = data;
        cbuf->head = (cbuf->head + 1) % LCBUFFER_BUFFER_SIZE;
        cbuf->full = (cbuf->head == cbuf->tail);
        r = 1;
    }
    return r;
}


/**
 * Sends a string into buffer, if buffer is full returns 0
 */
u8 LCBUFFER_u8PutStr(CBuffer* cbuf, u8 * data){
    u8 r = 1;
    do{
        if(!LCBUFFER_u8Put(cbuf, *data)){
            r = 0;
            break;
        }
        data++;
    }while(*data != '\0');
    return r;
}

/// Retrieve a value from the buffer
/// Returns 1 on success, 0 if the buffer is empty
u8 LCBUFFER_u8Get(CBuffer* cbuf, u8 * data){
    int r = 0;

    if(!LCBUFFER_u8Empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->full = 0;
        cbuf->tail = (cbuf->tail + 1) % LCBUFFER_BUFFER_SIZE;

        r = 1;
    }

    return r;
}

/// Returns true if the buffer is empty
u8 LCBUFFER_u8Empty(CBuffer* cbuf){
    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

/// Returns true if the buffer is full
u8 LCBUFFER_u8Full(CBuffer* cbuf){
    return cbuf->full;
}
