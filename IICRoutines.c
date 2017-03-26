#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IICStart                0x00408000 // IIC Start Address (added)
#define MAX_BANKSPACE           65535
#define PAGE                    128

/* Initialize the IIC Controller */
void IIC_initialize(void){
    unsigned char *IICPtr = (unsigned char *)(IICStart);
    IICPtr[0x00 << 1] = 0x31;
    IICPtr[0x01 << 1] = 0x00;
    IICPtr[0x02 << 1] = 0x80;

    printf("\r\nIIC Controller Initialized");

}

void IIC_ReadByte(void){
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


    // write slave to transmit reg for reading
    IICPtr[0x03 << 1] = 0xA1; // Data written to memory address location
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

void IIC_ReadBytes(void){
    int i;
    int sr;
    int mask, masked_n, tip_bit, ack_bit;
    unsigned char *IICPtr = (unsigned char *)(IICStart), value;

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
    IICPtr[0x03 << 1] = 0xA1; // Data written to memory address location
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

    for(i = 0; i < 128; i++){

        // if last iteration, need to set sto bit and ACK bit
        if(i == 127){
            IICPtr[0x04 << 1] = 0x69; //RD, ACK = 1, STO, IACK
        }
        else{
            IICPtr[0x04 << 1] = 0x21; //RD, ACK = 0, IACK
        }

        // if not on the last iteration, check ack
        if(i < 127){
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
        printf( "\r\nValue Read: %.4x at address offset %i", value, i ) ;
    }
}

/*This is the UserRead functionality of the EEPROM, needs to be tested after successfully determining that the UserWrite works correctly
Place this function into the "IIC_UserRead" function (currently empty) in IICRoutines.c for testing
*/

void IIC_UserRead(unsigned int start, unsigned int bytes)
{
    unsigned int count, bytesLeft, w, w2, OffsetUpper, OffsetLower;
    int x, flag, w1;
	unsigned int value;

    int i;
    int sr;
    int mask, masked_n, tip_bit, ack_bit;
    unsigned char *IICPtr = (unsigned char *)(IICStart);

    //Set up count and bytesLeft
    count = start ;
    bytesLeft = bytes ;

    //Start the loop of death
    while(1)
    {
        if( count >= MAX_BANKSPACE )
        {
            flag = 0 ;
            x = 1 ;
            count = count - MAX_BANKSPACE ;
        }
        else
        {
            flag = 0 ;
            x = 0 ;
        }

        w = bytesLeft ;

        w1 = (int) (w / PAGE) ;   //Set up number of page loops
        w2 =  w % PAGE ;   //Set up the remaining loops

        //Page looping
        while( w1 > 0 )
        {
            if( (MAX_BANKSPACE - count) < PAGE )
            {
                w2 = MAX_BANKSPACE - count ;
                flag = 1 ;
                break ;
            }
            else
            {
                if( x == 1 )
                {
                    //Write Slave Address 1010100
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
                    IICPtr[0x03 << 1] = 0xA8;
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
                }
                else
                {
                    //Write Slave Address 1010000
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

                //Specify internal address upper byte based on count
                OffsetUpper = count >> 8 ;

                // specify the internal address
                // by writing each byte of the addr to the transmit reg
                IICPtr[0x03 << 1] = OffsetUpper;
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

                //Specify internal address upper byte based on count
                OffsetLower = count & 0x00ff ;

                // second byte of addr
                IICPtr[0x03 << 1] = OffsetLower;
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
                if( x == 1 )
                {
                    IICPtr[0x03 << 1] = 0xA9; // Slave 10101001
                    IICPtr[0x04 << 1] = 0x91; //STA, WR, IACK
                }
                else
                {
                    IICPtr[0x03 << 1] = 0xA1; // Slave 10100001
                    IICPtr[0x04 << 1] = 0x91; //STA, WR, IACK
                }

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

                    // if last iteration, need to set sto bit and ACK bit
                    if(i == 127){
                        IICPtr[0x04 << 1] = 0x69; //RD, ACK = 1, STO, IACK
                    }
                    else{
                        IICPtr[0x04 << 1] = 0x21; //RD, ACK = 0, IACK
                    }

                    // if not on the last iteration, check ack
                    if(i < 127){
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
                    printf( "\r\nValue Read: %.4x at address offset %i", value, count ) ;

                    count++ ;
                    bytesLeft-- ;
                }

                w1--;
            }
        }

        if( w2 != 0 )
        {
            if( x == 1 )
            {
                //Write Slave Address 1010100
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
                IICPtr[0x03 << 1] = 0xA8;
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
            }
            else
            {
                //Write Slave Address 1010000
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

            //Specify internal address upper byte based on count
            OffsetUpper = count >> 8 ;

            // specify the internal address
            // by writing each byte of the addr to the transmit reg
            IICPtr[0x03 << 1] = OffsetUpper;
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

            //Specify internal address upper byte based on count
            OffsetLower = count & 0x00ff ;

            // second byte of addr
            IICPtr[0x03 << 1] = OffsetLower;
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
            if( x == 1 )
            {
                IICPtr[0x03 << 1] = 0xA9; // Slave 10101001
                IICPtr[0x04 << 1] = 0x91; //STA, WR, IACK
            }
            else
            {
                IICPtr[0x03 << 1] = 0xA1; // Slave 10100001
                IICPtr[0x04 << 1] = 0x91; //STA, WR, IACK
            }

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

            while( w2 > 0 ) {
                // if last iteration, need to set sto bit and ACK bit
                if(w2 == 1){
                    IICPtr[0x04 << 1] = 0x69; //RD, ACK = 1, STO, IACK
                }
                else{
                    IICPtr[0x04 << 1] = 0x21; //RD, ACK = 0, IACK
                }

                // if not on the last iteration, check ack
                if(w2 > 1){
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
                printf( "\r\nValue Read: %.4x at address offset %i", value, count ) ;

                w2-- ;
                count++ ;
                bytesLeft-- ;
            }
        }

    if(flag == 1)
        continue;
    else
        break;
    }
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
    IICPtr[0x03 << 1] = 0x66; // Data written to memory address location
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
        IICPtr[0x03 << 1] = 0x11; //write data
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

void IIC_UserWrite(unsigned int start, unsigned int bytes)
{

    unsigned int count, bytesLeft, w, w2, OffsetUpper, OffsetLower;
    int x, flag, w1;

    int i;
    int sr;
    int mask, masked_n, tip_bit, ack_bit;
    unsigned char *IICPtr = (unsigned char *)(IICStart);

    //Set up count and bytesLeft
    count = start ;
    bytesLeft = bytes ;

    //Start the loop of death
    while(1)
    {
        if( count >= MAX_BANKSPACE )
        {
            flag = 0 ;
            x = 1 ;
            count = count - MAX_BANKSPACE ;
        }
        else
        {
            flag = 0 ;
            x = 0 ;
        }

        w = bytesLeft ;

        w1 = (int) (w / 128) ;   //Set up number of page loops
        w2 =  w % 128 ;   //Set up the remaining loops
        //Page looping
        while( w1 > 0 )
        {
            if( (MAX_BANKSPACE - count) < PAGE )
            {
                w2 = MAX_BANKSPACE - count ;
                flag = 1 ;
                break ;
            }
            else
            {
                if( x == 1 )
                {
                    //Write Slave Address 1010100
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
                    IICPtr[0x03 << 1] = 0xA8;
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
                }
                else
                {
                    //Write Slave Address 1010000
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

                //Specify internal address upper byte based on count
                OffsetUpper = count >> 8 ;

                // specify the internal address
                // by writing each byte of the addr to the transmit reg
                IICPtr[0x03 << 1] = OffsetUpper;
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

                //Specify internal address upper byte based on count
                OffsetLower = count & 0x00ff ;

                // second byte of addr
                IICPtr[0x03 << 1] = OffsetLower;
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
                    IICPtr[0x03 << 1] = 0x11; //write data
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

                w1--;
                bytesLeft = bytesLeft - PAGE ;
                count = count + PAGE ;
            }
        }

        if( w2 != 0 )
        {
            if( x == 1 )
            {
                //Write Slave Address 1010100
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
                IICPtr[0x03 << 1] = 0xA8;
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
            }
            else
            {
                //Write Slave Address 1010000
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

            //Specify internal address upper byte based on count
            OffsetUpper = count >> 8 ;

            // specify the internal address
            // by writing each byte of the addr to the transmit reg
            IICPtr[0x03 << 1] = OffsetUpper;
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

            //Specify internal address upper byte based on count
            OffsetLower = count & 0x00ff ;

            // second byte of addr
            IICPtr[0x03 << 1] = OffsetLower;
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
        }

        while( w2 > 0 ) {
            IICPtr[0x03 << 1] = 0x11; //write data
            // if last iteration, need to set sto bit
            if(w2 == 1){
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
            if(w2 > 1){
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

            w2-- ;
            count++;
            bytesLeft--;
        }

    if(flag == 1)
        continue;
    else
        break;
    }
}