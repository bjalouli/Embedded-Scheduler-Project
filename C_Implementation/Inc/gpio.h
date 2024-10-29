/**
 * @file gpio.h
 * @brief Header file for GPIO control functions.
 *
 * This file contains function prototypes for GPIO initialization and manipulation.
 *
 * @author Bilel
 * @date 2024-10-28
 */

#include <stdint.h>

#define GPIO_PIN_D12 (1 << 12) 
#define GPIO_PIN_D13 (1 << 13) 
#define GPIO_PIN_D14 (1 << 14) 
#define GPIO_PIN_D15 (1 << 15) 
#define RCC_BASE      0x40023800  // Base address for RCC
#define GPIOD_BASE    0x40020C00  // Base address for GPIOD

// Define offset for registers
#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30)) // AHB1 peripheral clock enable register
#define GPIOD_MODER   (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) // GPIO port mode register
#define GPIOD_ODR     (*(volatile uint32_t *)(GPIOD_BASE + 0x14)) // GPIO port output data register

/**
 * @brief Initializes the GPIO port D.
 *
 * This function configures GPIO port D to enable the clock and set pins D12, 
 * D13, D14, and D15 as output. The initialization steps include:
 * 
 * 1. Enabling the clock for GPIOD by setting the appropriate bit in the 
 *    RCC_AHB1ENR register.
 * 2. Configuring the mode of the specified pins to output by clearing the 
 *    relevant bits in the GPIOD_MODER register and setting them to output mode.
 *
 * The output mode allows these pins to drive external devices or LEDs.
 * 
 * @param None
 * @return None
 * 
 */
void gpio_init(void);

/**
 * @brief Toggles the state of the specified GPIO pin.
 * 
 * This function toggles the output state of a specified pin on the GPIOD port 
 * by performing an XOR operation on the Output Data Register (ODR).
 *
 * @param pin The GPIO pin to toggle. Typically defined as a bitmask 
 *        corresponding to the desired pin (e.g., `GPIO_PIN_D12`).
 *
 * @details
 * - Uses XOR to toggle the specified pin by modifying the corresponding bit 
 *   in the GPIOD Output Data Register (GPIOD_ODR).
 * - This function assumes that the specified pin is already configured as an output.
 * 
 * @return None
 */
void toggle_gpio_pin(uint32_t pin);


//void delay(uint32_t);


