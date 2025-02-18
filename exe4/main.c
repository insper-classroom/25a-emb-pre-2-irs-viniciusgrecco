#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
volatile int fall_red = 0;
volatile int fall_green = 0;
const int LED_RED = 4;
const int LED_GREEN = 6;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {
    if (gpio == BTN_PIN_R)
      fall_red = 1 ;
  }
  if (events == 0x8) {
    if (gpio == BTN_PIN_G)
      fall_green = 1;
  }
  
  
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_RED);
  gpio_init(LED_GREEN);
  gpio_set_dir(LED_RED,GPIO_OUT);
  gpio_set_dir(LED_GREEN,GPIO_OUT) ;

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

  while (true) {
    if (fall_green==1){
      if(gpio_get(LED_GREEN)==0){
        gpio_put(LED_GREEN,1);
      }else{
        gpio_put(LED_GREEN,0);
      }
      fall_green = 0;
    }
    if (fall_red == 1){
      if(gpio_get(LED_RED)==0){
        gpio_put(LED_RED,1);
      }else{
        gpio_put(LED_RED,0);
      }
      fall_red = 0;
    }

  }
}
