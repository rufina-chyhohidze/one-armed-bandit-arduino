#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "buttons.h"
#include <led.h>
//all lights up for 2 sec and then countdown pattern is as follows: you first light the 4 LEDs, then 3, 2, 1 and 0 
/*int main(){
  for(int i=4; i>-1;i--){
    enabledLed(i);
  }
  while (1)
  {
    for (int i=4; i>-1;i--){
      lightUpLed(i);
      _delay_ms(1000);
    }
    for (int i=4; i>-1;i--){
      lightDownLed(i);
      _delay_ms(1000);
    }
    break;//but after break it stops completely:(
   
  }
  return 0;

}
*/
 
 //defining LEDS here
#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED1 PB2
#define LED2 PB3
#define LED3 PB4
#define LED4 PB5 

//defining buttons here 
#define BUTTON_PORT PORTC
#define BUTTON_PIN PINC
#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3
#define BUTTON_DDR DDRC

//macros used to manage the state of LEDs on an AVR microcontroller
#define LED_ON(x) (LED_PORT &= ~_BV(x))
#define LED_OFF(x) (LED_PORT |= _BV(x))
#define LED_TOGGLE(x) (LED_PORT ^= _BV(x))

//macros for morse durations 
#define DOT_DURATION 200 // duration of a Morse dot
#define DASH_DURATION 600 // duration of a Morse dash
#define LETTER_GAP 800 // gap between letters

// Morse code array
const char* morse_code[] = {
    ".-",   // A //0 the index in an array
    "-...", // B //1 
    "-.-.", // C //2
    "-..",  // D //3 
    ".",    // E //4
    "..-.", // F //5
    "--.",  // G //6
    "....", // H //7
    "..",   // I //8
    ".---", // J //9
    "-.-",  // K //10
    ".-..", // L //11
    "--",   // M //12
    "-.",   // N //13
    "---",  // O //14
    ".--.", // P //15
    "--.-", // Q //16
    ".-.",  // R //17
    "...",  // S //18
    "-",    // T //19
    "..-",  // U //20
    "...-", // V //21
    ".--",  // W //22
    "-..-", // X //23
    "-.--", // Y //24
    "--.."  // Z //25
};
 
 //a specific function for duration of dots and dashes using defined previously LED's
void send_morse(const char* pattern) {
    while (*pattern) {
        if (*pattern == '.') {
            LED_ON(LED1);
            _delay_ms(DOT_DURATION);
            LED_OFF(LED1);
        } else if (*pattern == '-') {
            LED_ON(LED1);
            _delay_ms(DASH_DURATION);
            LED_OFF(LED1);
        }
        _delay_ms(DOT_DURATION); // gap between dots/dashes in a letter
        pattern++;
    }
    _delay_ms(LETTER_GAP); // gap between letters
}

void countdown_pattern() {
    //using function all leds on
    lightUpAllLeds();
    _delay_ms(2000);

    // 4, 3, 2, 1, 0
    for (int i = 4; i >= 0; --i) {
        if (i < 4) LED_OFF(PB5 - i);
        _delay_ms(1000);
    }
}

