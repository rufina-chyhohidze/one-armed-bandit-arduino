#include <util/delay.h>
#include <avr/io.h>
#include <led.h> 

#define LED_PIN 13 // Change this to the pin number connected to your LED

int main() {
  
  
  // Test dimming LED to 50% brightness for 3 seconds
  dimLed(LED_PIN, 50, 3000);
  
  // Test fading in LED from 0% to 100% brightness over 3 seconds
  fadeInLed(LED_PIN, 3000);
  
  // Test fading out LED from 100% to 0% brightness over 3 seconds
  fadeOutLed(LED_PIN, 3000);
  
  return 0;
}
