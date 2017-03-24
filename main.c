
int main (void) 
{
  char x, y, z ;
  unsigned int start, bytes ;
  
  IIC_initialize() ;
  
  printf( "\r\nSelect Device: (a)ADC (b)EEPROM\r\n" ) ;
  x = getchar() ;
  
  if( x == 0x61 )  {
    printf( "\r\nADC Selected" ) ;
    
    // Needs adding of test cases here
  }
  else if( x == 0x62 )  {
    printf( "\r\nEEPROM Selected" ) ;
    printf( "\r\nSelect Mode: (a)Read (b)Write\r\n" ) ;
    y = getchar() ;
    
    if( y == 0x61 )  {
      printf( "\r\nRead Selected" ) ;
      printf( "\r\nSelect Test: (a)Read Byte (b)Read Page (c)Read Other\r\n" ) ;
      z = getchar() ;
      
      if( z == 0x61 ) {
        printf( "\r\nRead Byte Selected" ) ;
        IIC_ReadByte() ;
      }
      else if( z == 0x62 )  {
        printf( "\r\nRead Page Selected" ) ;
        IIC_ReadBytes() ;
      }
      else if( z == 0x63 )  {
        printf( "\r\nSelect Starting Address\r\n" ) ;
        start = Get8HexDigits(0) ;
        printf( "\r\nSelect number of bytes to read in hex\r\n" ) ;
        bytes = Get8HexDigits(0) ; // Needs a better solution
        // Call Read Other function and send "start" and "bytes" parameters
      }  
      else
        printf( "\r\nError, your input was: %c", z ) ;
    }
    else if( y == 0x62 )  {
      printf( "\r\nWrite Selected" ) ;
      printf( "\r\nSelect Test: (a)Write Byte (b)Write Page (c)Write Other\r\n" ) ;
      z = getchar() ;
      
      if( z == 0x61 ) {
        printf( "\r\nWrite Byte Selected" ) ;
        IIC_WriteByte() ;
      }
      else if( z == 0x62 )  {
        printf( "\r\nWrite Page Selected" ) ;
        IIC_WriteBytes() ;
      }
      else if( z == 0x63 )  {
        printf( "\r\nSelect Starting Address\r\n" ) ;
        start = Get8HexDigits(0) ;
        printf( "\r\nSelect number of bytes to write in hex\r\n" ) ;
        bytes = Get8HexDigits(0) ; // Needs a better solution
        // Call Write Other function and send "start" and "bytes" parameters
      }
      else
        printf( "\r\nError, your input was: %c", z ) ;
    }
    else
      printf( "\r\nError, your input was: %c", y ) ;
  }
  else
    printf( "\r\nError, your input was: %c", x ) ;
  
  return 0 ;
}
  
