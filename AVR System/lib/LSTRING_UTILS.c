
#include "LSTD_TYPES.h"
#include "LSTRING_UTILS.h"

void numberToString(u64 i, u8 b[]){
    u8* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    u64 shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = '0' + (i%10);
        i = i/10;
    }while(i);
}
