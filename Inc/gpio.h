#include <stdint.h>

#define GPIO_PIN_D12 (1 << 12) 
#define GPIO_PIN_D13 (1 << 13) 
#define GPIO_PIN_D14 (1 << 14) 
#define GPIO_PIN_D15 (1 << 15) 


void gpio_init(void);

void toggle_gpio_d12(void);

void toggle_gpio_d13(void);

void toggle_gpio_d14(void);

void toggle_gpio_d15(void);

#define RCC_BASE      0x40023800  // Base address for RCC
#define GPIOD_BASE    0x40020C00  // Base address for GPIOD

// Define offset for registers
#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30)) // AHB1 peripheral clock enable register
#define GPIOD_MODER   (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) // GPIO port mode register
#define GPIOD_ODR     (*(volatile uint32_t *)(GPIOD_BASE + 0x14)) // GPIO port output data register
