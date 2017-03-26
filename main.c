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

long Get8HexDigits(char *CheckSumPtr);
long Get4HexDigits(char *CheckSumPtr);
long Get2HexDigits(char *CheckSumPtr);
char xtod(long c);

void IICController (void)
{
  char x, y, z ;
  unsigned long start, bytes;

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
        //printf( "Address %.4x   Bytes %d", start, bytes );
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
        printf( "\r\nSelect Starting Address\r\n" ) ;
        start = Get8HexDigits(0);
        printf( "\r\nSelect number of bytes to write in hex" ) ;
        scanf( "\r\n%d", &bytes ) ;

        printf( "\r\nAddress %.4x   Bytes %d", start, bytes );
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

char xtod(long c)
{
    if ((char)(c) <= (char)('9'))
        return c - (char)(0x30);    // 0 - 9 = 0x30 - 0x39 so convert to number by sutracting 0x30
    else if((char)(c) > (char)('F'))    // assume lower case
        return c - (char)(0x57);    // a-f = 0x61-66 so needs to be converted to 0x0A - 0x0F so subtract 0x57
    else
        return c - (char)(0x37);    // A-F = 0x41-46 so needs to be converted to 0x0A - 0x0F so subtract 0x37
}

long Get2HexDigits(char *CheckSumPtr)
{
    register long i = (xtod(_getch()) << 4) | (xtod(_getch()));

    if(CheckSumPtr)
        *CheckSumPtr += i ;

    return i ;
}

long Get4HexDigits(char *CheckSumPtr)
{
    return (Get2HexDigits(CheckSumPtr) << 8) | (Get2HexDigits(CheckSumPtr));
}

long Get6HexDigits(char *CheckSumPtr)
{
    return (Get4HexDigits(CheckSumPtr) << 8) | (Get2HexDigits(CheckSumPtr));
}

long Get8HexDigits(char *CheckSumPtr)
{
    return (Get4HexDigits(CheckSumPtr) << 16) | (Get4HexDigits(CheckSumPtr));
}