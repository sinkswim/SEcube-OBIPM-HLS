#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG 0   // Used in OBIPM interrupt controller. Use whenever useful to use std::cout.

// Useful defines for the TB
// Comment out the unecessary TBs
// #define WRITE_TEST  0
// #define READ_TEST   0
 #define INTERRUPT_TEST  0
#define CW_READ_TEST    "0x1002"
#define CW_WRITE_TEST   "0x1002"
// NOTE here we have two different defines since the
// in this scenario we have to simulate an interrupt rising during an
// ongoing transaction. Hence we need 1 CW for signaling the beginning and
// another for the end of a transaction.
#define CW_INTERRUPT_TEST_BEGIN "0x1001"
#define CW_INTERRUPT_TEST_END   "0x0001"
#define CLK_PERIOD  25
// --- end of tb related defines

#define NUM_IP 2   // NB: Hardcode this value before synthesizing.

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
