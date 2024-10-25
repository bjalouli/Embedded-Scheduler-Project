#include "tasks.h"
#include "gpio.h"

void T1_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d12();
    delay(100000);
  }
  
}

void T2_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d13();
    delay(100000);
  }
  
}

void T3_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d14();
    delay(100000);
  }
  
}

void T4_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d15();
    delay(100000);
  }
  
}