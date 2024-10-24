#include "tasks.h"
#include "gpio.h"

void T1_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d12();
  }
  
}

void T2_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d13();
  }
  
}

void T3_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d14();
  }
  
}

void T4_Handler(void) {
  while (1)
  {
    /* code */
    toggle_gpio_d15();
  }
  
}