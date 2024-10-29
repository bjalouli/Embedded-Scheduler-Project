pub const TASK_STACK_SIZE: usize = 1024; // Stack size for each task
pub const SCHEDULER_STACK_SIZE: usize = 1024; // Stack size for the scheduler
pub const RAM_START_ADDR: u32 = 0x2000_0000; // Start address of RAM
pub const RAM_SIZE_BYTES: u32 = 128 * 1024; // RAM size in bytes

// Calculate each task's stack start address
pub const TASK1_STACK_START: u32 = RAM_START_ADDR + RAM_SIZE_BYTES; 
pub const TASK2_STACK_START: u32 = TASK1_STACK_START - TASK_STACK_SIZE as u32;
pub const TASK3_STACK_START: u32 = TASK2_STACK_START - TASK_STACK_SIZE as u32;
pub const TASK4_STACK_START: u32 = TASK3_STACK_START - TASK_STACK_SIZE as u32;
pub const IDLE_T_STACK_START: u32 = TASK4_STACK_START - TASK_STACK_SIZE as u32;
pub const SCHEDULER_STACK_START: u32 = IDLE_T_STACK_START - SCHEDULER_STACK_SIZE as u32;

pub const HSI_CLOCK_FREQ_HZ: u32 = 16_000_000;  // High-Speed Internal clock frequency in Hz
pub const SYSTICK_TICK_RATE_HZ: u32 = 1; // SysTick timer rate in Hz (1 ms)

pub const NUM_TASKS: usize = 5; // Number of tasks
pub const INITIAL_X_PSR: u32 = 0x01000000; // Initial Program Status Register value with Thumb state bit set

pub const RUNNING:u8        = 0x1;
#[allow(unused)]
pub const BLOCKED:u8        = 0x0;

pub static mut GLOBAL_TICK_COUNT: u32 = 0 ;


pub struct TaskControlBlock {
    pub psp_value: u32,                   // Process stack pointer value
    pub block_count: u32,                 // Block counter
    pub current_state: u8,                // Current state of the task
    pub task_handler: fn(),        // Task handler function pointer
}

pub static mut C_TASK:usize = 1;


