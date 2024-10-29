/**
 * @file main.h
 * @brief Header file for the Embedded Scheduler Project.
 *
 * This file contains function prototypes and macro definitions for the main
 * module of the embedded scheduler.
 *
 * @author Bilel
 * @date 2024-10-28
 */

#define TASK_STACK_SIZE         1024U       // Stack size for each task in bytes
#define SCHEDULER_STACK_SIZE    1024U       // Stack size for the scheduler in bytes
#define RAM_START_ADDRESS       0x20000000U // Base address of RAM
#define RAM_TOTAL_SIZE          (128 * 1024) // Total RAM size in bytes

#define TASK1_STACK_START       (RAM_START_ADDRESS + RAM_TOTAL_SIZE) // Task 1 stack start address
#define TASK2_STACK_START       (TASK1_STACK_START - TASK_STACK_SIZE) // Task 2 stack start address
#define TASK3_STACK_START       (TASK2_STACK_START - TASK_STACK_SIZE) // Task 3 stack start address
#define TASK4_STACK_START       (TASK3_STACK_START - TASK_STACK_SIZE) // Task 4 stack start address
#define IDLE_STACK_START        (TASK4_STACK_START - TASK_STACK_SIZE) // Task 4 stack start address
#define SCHEDULER_STACK_START   (IDLE_STACK_START - SCHEDULER_STACK_SIZE) // Scheduler stack start address

#define TOTAL_TASKS             5           // Total number of tasks
#define SYSTEM_TICK_RATE_HZ     1U          // System tick rate in Hz (1ms tick)
#define HSI_CLOCK_FREQUENCY_HZ  16000000U    // HSI clock frequency in Hz


#define xPSR           0x01000000U

#define RUNNING        0x1
#define BLOCKED        0x0






/**
 * @brief Enables system fault handling.
 * 
 * This function configures the System Handler Control and State Register (SHCSR)
 * to enable memory management, bus, and usage fault exceptions. 
 * It modifies the appropriate bits in the SHCSR to activate fault handling 
 * for the specified fault types, allowing the system to respond to faults as 
 * needed.
 *
 * @note This function should be called during system initialization to ensure 
 *       fault handling is enabled before any tasks are executed.
 * 
 * @return None
 * 
 */
void enable_faults(void);

/**
 * @brief Initializes the SysTick timer to generate an interrupt at a specified interval.
 *
 * This function configures the SysTick timer to generate an interrupt every `tick` microseconds 
 * by setting up the reload value and enabling the counter. The SysTick counter is configured 
 * to use the processor clock source and enable the SysTick exception.
 *
 * @param tick Specifies the desired tick interval in microseconds. The reload value is calculated 
 *             based on the HSI clock frequency (e.g., 16 MHz) and the specified interval.
 * 
 * @details
 * - The reload value is calculated as `(HSI_CLOCK_FREQUENCY_HZ / tick) - 1`.
 * - The Reload Value Register (SYST_RVR) is cleared for the lower 24 bits, then the calculated 
 *   reload value is loaded.
 * - The Control and Status Register (SYST_CSR) is configured to enable the counter, the 
 *   clock source, and the SysTick exception.
 * 
 * @return None
 */
void systick_T_init(uint32_t);


/**
 * @brief Switches the stack pointer to the Process Stack Pointer (PSP).
 *
 * This function initializes the Process Stack Pointer (PSP) by calling an external function 
 * `get_psp_value` to retrieve the PSP base address. It then updates the stack pointer (SP) 
 * to point to PSP by configuring the CONTROL register.
 *
 * @details
 * - The function is declared with `__attribute__((naked))` to omit the typical function prologue 
 *   and epilogue, allowing for direct manipulation of the stack.
 * - The Link Register (LR) is saved and restored around the call to `get_psp_value`.
 * - `MSR PSP, R0` is used to set PSP to the value returned by `get_psp_value`.
 * - Finally, CONTROL register bit 1 is set to switch SP to PSP.
 * 
 * @note This function should be called only in the privileged mode to ensure proper access 
 *       to the CONTROL register.
 * 
 * @return None
 */
__attribute__((naked)) void switch_sp_to_psp(void);

/**
 * @brief Retrieves the current task's Process Stack Pointer (PSP) value.
 * 
 * This function returns the stack pointer value of the currently running task 
 * by accessing the `stack_pointer` field of the `tasks` array at the index of `c_task`.
 *
 * @param None
 * @return The current task's stack pointer (PSP) value as a 32-bit unsigned integer.
 *
 * @details
 * - This function is useful for managing context switching, as it provides access 
 *   to the PSP of the current task.
 * - It is typically called in the context of low-level task management routines 
 *   where stack manipulation is necessary.
 */
uint32_t get_psp_value(void);

/**
 * @brief Sets the Process Stack Pointer (PSP) value for the current task.
 * 
 * This function updates the `stack_pointer` field of the currently running task 
 * (indexed by `c_task`) with the specified `task_psp` value.
 *
 * @param task_psp The new stack pointer value to set for the current task.
 * @return None
 * @details
 * - Used to save the stack pointer for the active task during context switching.
 * - This function ensures that each task maintains its own stack pointer value, 
 *   allowing safe and independent task stack management.
 */
void set_psp_value(uint32_t task_psp);

/**
 * @brief Updates the current task to the next runnable task.
 *
 * This function increments the current task index (`c_task`) to point to the 
 * next task in a circular manner, skipping any tasks that are in a blocked state. 
 * If no tasks are in a runnable state, it defaults to the idle task (index 0).
 *
 * @details
 * - The function cycles through all tasks by incrementing the `c_task` index 
 *   within the bounds of `TOTAL_TASKS`.
 * - If a running task is found, it breaks out of the loop to set `c_task` to 
 *   the next runnable task. Otherwise, it falls back to the idle task.
 *
 * @note The idle task (task index 0) is chosen only when no other tasks are runnable.
 * 
 * @param None
 * @return None
 */
void update_next_task(void);

/**
 * @brief Increments the global tick count.
 *
 * This function increments the global tick counter `g_tick_count` by one,
 * which is typically used for tracking elapsed time in the system.
 *
 * @param None
 * @return None
 */
void increment_tick(void);

/**
 * @brief Triggers a PendSV interrupt.
 *
 * This function sets the PendSV (Pendable Service Interrupt) in the 
 * Interrupt Control and Status Register (ICSR) by writing to bit 28. 
 * This is typically used in a context-switching mechanism to request 
 * a context switch between tasks.
 *
 * @param None
 * @return None
 */
void trig_pendsv(void);

/**
 * @brief Checks the state of all tasks and updates blocked tasks.
 *
 * This function iterates through all tasks and checks if they are 
 * in the BLOCKED state. If a task's remaining_ticks matches the 
 * current tick count (g_tick_count), the task's state is updated 
 * to RUNNING, indicating that it is ready to execute again.
 *
 * This function is typically called during the task scheduling 
 * process to determine which blocked tasks can be unblocked.
 * 
 * @param None
 * @return None
 */
void check_blocked_tasks(void);

/**
 * @brief Represents a task in the task scheduler.
 * 
 * This structure contains all the necessary information to manage a task.
 * It includes the stack pointer,
 * the number of ticks remaining until the task can run again, the current
 * state of the task, and a pointer to the task's execution function.
 */
typedef struct
{
    uint32_t stack_pointer;      
    uint32_t remaining_ticks;         
    uint8_t task_state;           
    void (*task_function)(void); 
} TaskControlBlock;



