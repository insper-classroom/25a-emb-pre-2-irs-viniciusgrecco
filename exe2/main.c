#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_RED = 28;
const int LED_RED = 4;
volatile int fall = 0;
volatile int rise = 0;

void btn_callback(uint gpio, uint32_t events){
  if (events == 0x4){
    fall = 1;
  } else if (events == 0x8){
    rise = 1;
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_RED);
  gpio_set_dir(BTN_RED,GPIO_IN);
  gpio_pull_up(BTN_RED);

  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);


  gpio_set_irq_enabled_with_callback(BTN_RED,GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);


  while (true) {
    if(fall==1){
      gpio_put(LED_RED,1);
      fall = 0;
    }
    if (rise==1){
      gpio_put(LED_RED,0);
      rise = 0;
    }
  }
}
