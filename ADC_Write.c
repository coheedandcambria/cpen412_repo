void ADC_Write(void){
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
    IICPtr[0x04 << 1] = 0x91; // lines 20 and 21 might need to be flipped since they specified that
															// the address is sent after the start condition

		IICPtr[0x03 << 1] = 0x92; // 10010010
    
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

    // transmit the control byte through the transmit register (0x00)
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


    while(1){
        IICPtr[0x03 << 1] = 0x55; //write data
        // if last iteration, need to set sto bit
        /*if(i == 127){
            IICPtr[0x04 << 1] = 0x51;
        }
        else{
            IICPtr[0x04 << 1] = 0x11;
        }*/
				
		IICPtr[0x04 << 1] = 0x11;

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

		// check tip
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
    
