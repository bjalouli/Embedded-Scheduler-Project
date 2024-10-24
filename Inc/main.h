#define TASK_STACK    1024U
#define SCHED_STACK   1024U
#define RAM_S         0x20000000U
#define RAM_LEN       ( 128 * 1024 )
#define T1_S          ( RAM_S + RAM_LEN )    //Task1 stack entry address
#define T2_S          ( T1_S  - TASK_STACK )
#define T3_S          ( T2_S  - TASK_STACK )
#define T4_S          ( T3_S  - TASK_STACK )
#define SCHED_S       ( T4_S  - TASK_STACK ) //Scheduler stack entry address
#define TASKS         4

#define TICK_RATE     1U       //Systick timer tick in Hz = 1ms
#define HSI_CLOCK     16000000

// Define base addresses for peripherals
// #define RCC_BASE      0x40023800  // Base address for RCC
// #define GPIOD_BASE    0x40020C00  // Base address for GPIOD

// // Define offset for registers
// #define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30)) // AHB1 peripheral clock enable register
// #define GPIOD_MODER   (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) // GPIO port mode register
// #define GPIOD_ODR     (*(volatile uint32_t *)(GPIOD_BASE + 0x14)) // GPIO port output data register

// Define constants
// #define GPIO_PIN_D12 (1 << 12) 
// #define GPIO_PIN_D13 (1 << 13) 
// #define GPIO_PIN_D14 (1 << 14) 
// #define GPIO_PIN_D15 (1 << 15) 


#define xPSR           0x01000000U