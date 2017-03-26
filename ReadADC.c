void ReadADC(void){
    int sr;
    int mask, masked_n, tip_bit, ack_bit;
    unsigned int value ;
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
    IICPtr[0x03 << 1] = 0x92;
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

    // specify the control byte
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

    // write slave to transmit reg for reading
    IICPtr[0x03 << 1] = 0x93; // Data written to memory address location
    IICPtr[0x04 << 1] = 0x91; //STA, WR, IACK

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

    //Read from reg
    IICPtr[0x04 << 1] = 0x69; //RD, ACK = 1, STO, IACK

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

    //Store transmit register value into variable and print
    value = IICPtr[0x03 << 1] ;
    printf( "\r\nValue Read: %.4x", value ) ;
}