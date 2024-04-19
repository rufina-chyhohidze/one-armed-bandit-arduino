#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

int main(){
  initUSART();
  printf ("Hello World\n");
  return 0;
}
