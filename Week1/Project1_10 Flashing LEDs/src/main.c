#include <util/delay.h>
#include <avr/io.h>

#define NUMBER_OF_LEDS 4 //Define is a "preprocessor directive". It ensures that every NUMBER_OF_LEDS will be replaced by 4 in the following code

void enabled(int lednumber)//C has no classes; functions can be included directly in the .c file.
{
  if (lednumber <0 || lednumber>NUMBER_OF_LEDS-1)return;
  DDRB |=(1<<(PB2+lednumber));
}
void lightUpLed ( int lednumber )    //Note: enabled LEDs light up immediately ( 0 = on )
{
  if (lednumber<0||lednumber>NUMBER_OF_LEDS-1)return;
  PORTB &=~(1<<(PB2+lednumber));
}
void lightDownLed ( int lednumber )
{
  if(lednumber<0||lednumber>3)return;
  PORTB |=(1<<(PB2+lednumber));
}
int main()
{
    for ( int i = 0; i < 4; i++ )
    {
        enableLed(i);
    }
    while (1)
    {
        for ( int i = 0; i < 4; i++ )
        {
            lightUpLed(i);
            _delay_ms( 100 );
        }
        for ( int i = 0; i < 4; i++ )
        {
            lightDownLed(i);
            _delay_ms( 100 );
        }
    }
    return 0;
}