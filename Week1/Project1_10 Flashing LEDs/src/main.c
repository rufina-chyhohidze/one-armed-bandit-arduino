#include <util/delay.h>
#include <avr/io.h>
#include <led.h> 

//THIS VERSION IS NOT WORKING 
int main()
{
    for ( int i = 0; i < 4; i++ )
    {
        enableMultipleLeds(i);
    }
    while (1)
    {
        for ( int i = 0; i < 4; i++ )
        {
            lightUpMultipleLeds(i);
            _delay_ms( 100 );
        }
        for ( int i = 0; i < 4; i++ )
        {
            lightDownMultipleLeds(i);
            _delay_ms( 100 );
        }
    }
    return 0;
}
/* THE FIRST WORKING VERSION WITH WAVE 
int main()
{
    for ( int i = 0; i < 4; i++ )
    {
        enabledLed(i);
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

*/
