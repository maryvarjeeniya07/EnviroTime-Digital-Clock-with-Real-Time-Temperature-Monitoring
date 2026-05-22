#ifndef _DEFINES_H_
#define _DEFINES_H_

#include "type.h"


/******** BIT MACROS ********/

#define setbit(word,bitpos) \
        (word |= (1<<(bitpos)))

#define clrbit(word,bitpos) \
        (word &= ~(1<<(bitpos)))

#define togglebit(word,bitpos) \
        (word ^= (1<<(bitpos)))

#define readbit(word,bitpos) \
        ((word>>(bitpos))&1)

#define writebit(word,bitpos,bitval) \
        word=((word&(~(1<<(bitpos)))) | (bitval<<(bitpos)))



/******** MULTI BIT MACROS ********/

#define writebyte(word,startbit,byteval) \
        word=((word&(~(255<<(startbit)))) | (byteval<<(startbit)))

#define writenibble(word,startbit,nibbleval) \
        word=((word&(~(15<<(startbit)))) | (nibbleval<<(startbit)))

#define readnibble(word,startbit) \
        ((word>>(startbit))&15)

#define readbyte(word,startbit) \
        ((word>>(startbit))&255)




#endif