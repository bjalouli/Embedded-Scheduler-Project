// #define TASK_STACK    1024U
// #define SCHED_STACK   1024U
// #define RAM_S         0x20000000U
// #define RAM_LEN       ( 128 * 1024 )
// #define T1_S          ( RAM_S + RAM_LEN )    //Task1 stack entry address
// #define T2_S          ( T1_S  - TASK_STACK )
// #define T3_S          ( T2_S  - TASK_STACK )
// #define T4_S          ( T3_S  - TASK_STACK )
// #define SCHED_S       ( T4_S  - TASK_STACK ) //Scheduler stack entry address
// #define TASKS         4

// #define TICK_RATE     1U       //Systick timer tick in Hz = 1ms
// #define HSI_CLOCK     16000000

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


#define TASK_STACK_SIZE         1024U       // Stack size for each task in bytes
#define SCHEDULER_STACK_SIZE    1024U       // Stack size for the scheduler in bytes
#define RAM_START_ADDRESS       0x20000000U // Base address of RAM
#define RAM_TOTAL_SIZE          (128 * 1024) // Total RAM size in bytes

#define TASK1_STACK_START       (RAM_START_ADDRESS + RAM_TOTAL_SIZE) // Task 1 stack start address
#define TASK2_STACK_START       (TASK1_STACK_START - TASK_STACK_SIZE) // Task 2 stack start address
#define TASK3_STACK_START       (TASK2_STACK_START - TASK_STACK_SIZE) // Task 3 stack start address
#define TASK4_STACK_START       (TASK3_STACK_START - TASK_STACK_SIZE) // Task 4 stack start address
#define SCHEDULER_STACK_START   (TASK4_STACK_START - SCHEDULER_STACK_SIZE) // Scheduler stack start address

#define TOTAL_TASKS             4           // Total number of tasks
#define SYSTEM_TICK_RATE_HZ     1U          // System tick rate in Hz (1ms tick)
#define HSI_CLOCK_FREQUENCY_HZ  16000000    // HSI clock frequency in Hz


#define xPSR           0x01000000U

#define RUNNING        0x1
#define BLOCKED        0x0


void systick_T_init(uint32_t);
__attribute__((naked)) void sched_stack_init(uint32_t);
void init_tasks_stack(void);

__attribute__((naked)) void switch_sp_to_psp(void);
uint32_t get_psp_value(void);
void enable_faults(void);
void set_psp_value(uint32_t task_psp);
void update_next_task(void);

typedef struct
{
    uint32_t stack_pointer;      
    uint32_t delay_count;         
    uint8_t task_state;           
    void (*task_function)(void); 
} TaskControlBlock;

