#include "DebugMonitor.h"

/* Initialize the IIC Controller */
void IIC_initialize(void){
    unsigned char *IICPtr = (unsigned char *)(IICStart);
    IICPtr[0x00 << 1] = 0x31;
    IICPtr[0x01 << 1] = 0x00;

    printf("\r\nIIC Controller Initialized");

}

void IIC_WriteByte(void){
    int sr;
    int mask, masked_n, tip_bit, ack_bit;
    unsigned char *IICPtr = (unsigned char *)(IICStart);
    // check if TIP flag is negated
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    tip_bit = masked_n >> 1;

    while(tip_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        tip_bit = masked_n >> 1;
    }

    // Writing to the transmit reg
    IICPtr[0x03 << 1] = 0xA0;
    IICPtr[0x04 << 1] = 0x91;

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    ack_bit = masked_n >> 1;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 1;
    }

    // check tip flag
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    tip_bit = masked_n >> 1;

    while(tip_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        tip_bit = masked_n >> 1;
    }

    // specify the internal address
    // by writing each byte of the addr to the transmit reg
    IICPtr[0x03 << 1] = 0x00;
    IICPtr[0x04 << 1] = 0x11; // set WR, IACK

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    ack_bit = masked_n >> 1;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 1;
    }

    // check tip flag
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    tip_bit = masked_n >> 1;

    while(tip_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        tip_bit = masked_n >> 1;
    }

    // second byte of addr
    IICPtr[0x03 << 1] = 0x00;
    IICPtr[0x04 << 1] = 0x11; // set WR, IACK

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    ack_bit = masked_n >> 1;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 1;
    }

    // check tip flag
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    tip_bit = masked_n >> 1;

    while(tip_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        tip_bit = masked_n >> 1;
    }


    // write data to transmit reg
    IICPtr[0x03 << 1] = 0x55;
    IICPtr[0x04 << 1] = 0x51;

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 1;
    masked_n = sr & mask;
    ack_bit = masked_n >> 1;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 1;
    }
}