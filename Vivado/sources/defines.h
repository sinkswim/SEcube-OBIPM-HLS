#ifndef DEFINES_H
#define DEFINES_H

#define NUM_IP 20	  // NB: Hardcode this value before synthesizing.
// LOG2 defines
#define NBITS2(n) ((n&2)?1:0)
#define NBITS4(n) ((n&(0xC))?(2+NBITS2(n>>2)):(NBITS2(n)))
#define NBITS8(n) ((n&0xF0)?(4+NBITS4(n>>4)):(NBITS4(n)))
#define NBITS16(n) ((n&0xFF00)?(8+NBITS8(n>>8)):(NBITS8(n)))
#define NBITS32(n) ((n&0xFFFF0000)?(16+NBITS16(n>>16)):(NBITS16(n)))
#define NBITS(n) (n==0?0:NBITS32(n)+1)
#define LOG NBITS(NUM_IP)
// --- end of LOG2 defines

#endif // DEFINES_H
