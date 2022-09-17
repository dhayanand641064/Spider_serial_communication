int tempTC74;
int main(){
  DDRB = (1<<5);
  uint8_t ubbr;
  int i = 0;
  unsigned char data1[] = "Fire";
  ubbr = 103;
  UBRR0L = (uint8_t)(ubbr & 0xFF);
  UBRR0H = (uint8_t)(ubbr >> 8);
  UCSR0C = 0x06;       
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  while(1){
    uint8_t data;
    i2c_start(0x9A);
    i2c_write(0x00);
    i2c_start(0x9B);
    data = i2c_readNak();
    i2c_stop(); 
    tempTC74 = data;
    if (tempTC74 > 50){
      PORTB = (1<<5);
      i = 0;
        while(data1[i] != 0) 
        {
          while (!( UCSR0A & (1<<UDRE0))); 
          UDR0 = data1[i];      
          i++;                          
        }
      }
    else{
      PORTB = 0;
      }

    }
}
void i2c_start(char address){
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  TWDR = address;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  }
unsigned char i2c_write( char data )
{   
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);

  while(!(TWCR & (1<<TWINT)));

}
unsigned char i2c_readNak()
{
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  
    return TWDR;

}
void i2c_stop()
{
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

}
  
