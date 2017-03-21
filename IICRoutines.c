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
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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
    IICPtr[0x03 << 1] = 0x00; // may need to update to be based on user input address
    IICPtr[0x04 << 1] = 0x11; // set WR, IACK

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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
    IICPtr[0x03 << 1] = 0x00; // may need to update to be based on user input address
    IICPtr[0x04 << 1] = 0x11; // set WR, IACK

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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
    IICPtr[0x03 << 1] = 0x55; // Data written to memory address location
    IICPtr[0x04 << 1] = 0x51; //STO, WR, IACK

    // check ack
    sr = IICPtr[0x04 << 1];
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
    }
}

void IIC_WriteBytes(void){
    int i;
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
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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
    mask = 1 << 7;
    masked_n = sr & mask;
    ack_bit = masked_n >> 7;

    while(ack_bit != 0){
        sr = IICPtr[0x04 << 1];
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;
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

    for(i = 0; i < 128; i++){
        IICPtr[0x03 << 1] = 0x55; //write data
        // if last iteration, need to set sto bit
        if(i == 127){
            IICPtr[0x04 << 1] = 0x51;
        }
        else{
            IICPtr[0x04 << 1] = 0x11;
        }

        // check ack (done in every iteration of loop)
        sr = IICPtr[0x04 << 1];
        mask = 1 << 7;
        masked_n = sr & mask;
        ack_bit = masked_n >> 7;

        while(ack_bit != 0){
            sr = IICPtr[0x04 << 1];
            masked_n = sr & mask;
            ack_bit = masked_n >> 7;
        }

        // if not on the last iteration, check tip
        if(i < 127){
            sr = IICPtr[0x04 << 1];
            mask = 1 << 1;
            masked_n = sr & mask;
            tip_bit = masked_n >> 1;

            while(tip_bit != 0){
                sr = IICPtr[0x04 << 1];
                masked_n = sr & mask;
                tip_bit = masked_n >> 1;
            }
        }
    }
}
