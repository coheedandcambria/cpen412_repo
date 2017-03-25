#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IICStart                0x00408000 // IIC Start Address (added)

// IIC Prototypes
void IIC_initialize(void);
void IIC_WriteByte(void);
void IIC_WriteBytes(void);
void IIC_UserWrite( unsigned long start, unsigned long bytes );
void IIC_ReadByte(void);
void IIC_ReadBytes(void) ;
void IIC_UserRead( unsigned long start, unsigned long bytes );

void IICController (void)
{
  char x, y, z ;
  unsigned long start, bytes ;

  IIC_initialize() ;

  printf( "\r\nSelect Device: (a)ADC (b)EEPROM" ) ;
  x = getchar() ;

  if( x == 0x61 )  {
    printf( "\r\nADC Selected" ) ;

    // Needs adding of test cases here
  }
  else if( x == 0x62 )  {
    printf( "\r\nEEPROM Selected" ) ;
    printf( "\r\nSelect Mode: (a)Read (b)Write" ) ;
    y = getchar() ;

    if( y == 0x61 )  {
      printf( "\r\nRead Selected" ) ;
      printf( "\r\nSelect Test: (a)Read Byte (b)Read Page (c)Read Other" ) ;
      z = getchar() ;

      if( z == 0x61 )   {
        printf( "\r\nRead Byte Selected" ) ;
        IIC_ReadByte() ;
      }
      else if( z == 0x62 )  {
        printf( "\r\nRead Page Selected" ) ;
        IIC_ReadBytes();
       }
      else if( z == 0x63 )  {
        printf( "Select Starting Address in hex" ) ;
        scanf( "%.4x", &start ) ;
        printf( "Select number of bytes to read" ) ;
        scanf( "%d", &bytes ) ; // Needs a better solution
        printf( "Address %.4x   Bytes %d", start, bytes );
        IIC_UserRead( start, bytes );
      }
      else
        printf( "\r\nError, your input was: %c", z ) ;
    }
    else if( y == 0x62 )  {
      printf( "\r\nWrite Selected" ) ;
      printf( "\r\nSelect Test: (a)Write Byte (b)Write Page (c)Write Other" ) ;
      z = getchar() ;

      if( z == 0x61 )
        IIC_WriteByte() ;
      else if( z == 0x62 )
        IIC_WriteBytes() ;
      else if( z == 0x63 )  {
        printf( "Select Starting Address" ) ;
        scanf( "%.4x", &start ) ;
        printf( "Select number of bytes to write in hex" ) ;
        scanf( "%d", &bytes ) ; // Needs a better solution

        printf( "Address %.4x   Bytes %d", start, bytes );
        IIC_UserWrite( start, bytes );
      }
      else
        printf( "\r\nError, your input was: %c", z ) ;
    }
    else
      printf( "\r\nError, your input was: %c", y ) ;
  }
  else
    printf( "\r\nError, your input was: %c", x ) ;
}