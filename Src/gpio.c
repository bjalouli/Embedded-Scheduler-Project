#include "gpio.h"


void gpio_init(void) {
    // Step 1: Enable the clock for GPIOD
    RCC_AHB1ENR |= (1 << 3); // Bit 3 corresponds to GPIOD

    // Step 2: Set D12, D13, D14, and D15 as output (00: Input, 01: Output)
    GPIOD_MODER &= ~((0x3 << (12 * 2)) | (0x3 << (13 * 2)) | (0x3 << (14 * 2)) | (0x3 << (15 * 2))); // Clear mode bits for D12, D13, D14, D15
    GPIOD_MODER |= ((0x1 << (12 * 2)) | (0x1 << (13 * 2)) | (0x1 << (14 * 2)) | (0x1 << (15 * 2)));  // Set mode to output (01)
}

void toggle_gpio_d12(void) {
    GPIOD_ODR ^= GPIO_PIN_D12; // Toggle D12 using XOR
}

void toggle_gpio_d13(void) {
    GPIOD_ODR ^= GPIO_PIN_D13; // Toggle D12 using XOR
}

void toggle_gpio_d14(void) {
    GPIOD_ODR ^= GPIO_PIN_D14; // Toggle D12 using XOR
}

void toggle_gpio_d15(void) {
    GPIOD_ODR ^= GPIO_PIN_D15; // Toggle D12 using XOR
}

void delay(volatile uint32_t count) { //TODO remplace with timer
    while (count--) {
    }
}