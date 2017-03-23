
int main (void) 
{
  char x, y, z ;
  unsigned int start, bytes ;
  
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
      
      if( z == 0x61 )
        printf( "\r\nRead Byte Selected" ) ;
        // Call Read Byte function here
      else if( z == 0x62 )
        printf( "\r\nRead Page Selected" ) ;
        // Call Read Page function here
      else if( z == 0x63 )  {
        printf( "Select Starting Address" ) ;
        start = Get8HexDigits(0) ;
        printf( "Select number of bytes to read in hex" ) ;
        bytes = Get8HexDigits(0) ; // Needs a better solution
        // Call Read Other function and send "start" and "bytes" parameters
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
        start = Get8HexDigits(0) ;
        printf( "Select number of bytes to write in hex" ) ;
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
  
