
#include "LSTD_TYPES.h"
#include "LCIRCBUFF.h"

/// Reset the circular buffer to empty, head == tail
void LCBUFFER_reset(CBuffer* cbuf){
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = 0;
}

/// Put data into buffer, rejects new data if the buffer is full
/// Returns 1 on success, 0 if buffer is full
u8  LCBUFFER_put(CBuffer* cbuf, u8 data){
    u8 r = 0;

    if(!LCIRCBUFF_full(cbuf))
    {
        cbuf->buffer[cbuf->head] = data;
        cbuf->head = (cbuf->head + 1) % LCIRC_BUFFER_SIZE;
        cbuf->full = (cbuf->head == cbuf->tail);
        r = 1;
    }
    return r;
}



u8 LCBUFFER_putStr(CBuffer* cbuf, u8 * data){
    u8 r = 0;
    do{
        if(!LCIRCBUFF_put(cbuf, *data)){
            r = 1;
            break;
        }
        data++;
    }while(*data != '\0');
    return r;
}
/// Retrieve a value from the buffer
/// Returns 1 on success, 0 if the buffer is empty
u8 LCBUFFER_get(CBuffer* cbuf, u8 * data){
    int r = 0;

    if(!LCIRCBUFF_empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->full = 0;
        cbuf->tail = (cbuf->tail + 1) % LCIRC_BUFFER_SIZE;

        r = 1;
    }

    return r;
}

/// Returns true if the buffer is empty
u8 LCBUFFER_empty(CBuffer* cbuf){
    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

/// Returns true if the buffer is full
u8 LCBUFFER_full(CBuffer* cbuf){
    return cbuf->full;
}