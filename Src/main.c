/**
 * @file main.c
 * @brief Main entry point for the Embedded Scheduler Project.
 *
 * This file contains the main function, initializing tasks and hardware 
 * configurations required for the embedded scheduler. It sets up system 
 * peripherals, initializes the task scheduler, and starts the main loop.
 * 
 * @project Embedded Scheduler Project
 * @author Bilel JALOULI
 * @date 2024-10-28
 * @license MIT
 *
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include <stdint.h>
#include "../Inc/main.h"
#include "../Inc/gpio.h"
#include "../Inc/tasks.h"




TaskControlBlock tasks[TOTAL_TASKS];
uint8_t c_task = 1 ; //1st task - 0 is the idle task
uint32_t g_tick_count = 0;




int main(void)
{

  enable_faults();

  gpio_init();

  sched_stack_init(SCHEDULER_STACK_START);

  init_tasks_stack();

  systick_T_init(SYSTEM_TICK_RATE_HZ);

  switch_sp_to_psp();

  task1_routine();
	for(;;);
}


void increment_tick(void){
  g_tick_count++;
}


void check_blocked_tasks(void){
  for(int task = 0 ; task < TOTAL_TASKS ; task++){
    if ( tasks[task].task_state == BLOCKED) {
      if( tasks[task].remaining_ticks == g_tick_count ){
        tasks[task].task_state = RUNNING;
      }
    }
  }
}


uint32_t get_psp_value(void){
  return tasks[c_task].stack_pointer;
}

void set_psp_value(uint32_t task_psp){
  tasks[c_task].stack_pointer = task_psp;
}

void update_next_task(void) {
    uint8_t found_task = 0;

    for (int task = 0; task < TOTAL_TASKS; task++) {
        c_task = (c_task + 1) % TOTAL_TASKS;
        
        // Check if the selected task is running and is not the idle task
        if (tasks[c_task].task_state == RUNNING && c_task != 0) {
            found_task = 1;
            break;
        }
    }
    
    // If no running tasks were found, set to idle task
    if (!found_task) {
        c_task = 0;
    }
}

__attribute__((naked)) void switch_sp_to_psp(void)
{
	// Initialize PSP

	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL get_psp_value");
	__asm volatile ("MSR PSP, R0");
	__asm volatile ("POP {LR}");

	// Point SP to PSP
	__asm volatile ("MOV R0, #0x02");
	__asm volatile ("MSR CONTROL, R0");
	__asm volatile ("BX LR");
}

void systick_T_init(uint32_t tick) {
  uint32_t *SYST_RVR = (uint32_t*) 0xE000E014;
  uint32_t *SYST_CSR = (uint32_t*) 0xE000E010;

  uint32_t reload_value = (HSI_CLOCK_FREQUENCY_HZ / tick) -1 ;

    //clear the Reload register 24 bits  and then load the count 
        *SYST_RVR &= ~(0x00FFFFFF);
        *SYST_RVR |= reload_value;


    //configure the Control register , clock source enable systick exception and enable the counter 
        *SYST_CSR |=  7 << 0 ;
    
}



void enable_faults() {
  uint32_t *SHCSR = (uint32_t*)0xE000ED24;

  *SHCSR |= ( 7 << 16 ) ;  //mem , bus , usage faults

}

void trig_pendsv(){
  uint32_t *ICSR = (uint32_t*)0xE000ED04; // Interrupt control and status register
  *ICSR |= (1 << 28);
}

/************ HAndlers *************************** */
void SysTick_Handler(void) {
  increment_tick();
  check_blocked_tasks();
  trig_pendsv();
}

__attribute__((naked)) void PendSV_Handler() {
  __asm volatile("PUSH {LR}");
  __asm volatile("MRS R0,PSP");
  __asm volatile("STMDB R0!, {R4-R11}");
  __asm volatile ("BL set_psp_value");
  __asm volatile ("BL update_next_task");
  __asm volatile ("BL get_psp_value");
  __asm volatile ("LDMIA R0!, {R4-R11}");
  __asm volatile("MSR PSP,R0");
  __asm volatile ("POP {LR}");
  __asm volatile ("BX LR");
}

void HardFault_Handler(void) {
  while(1) {

  }
}

void MemManage_Handler(void) {
  while(1) {
    
  }
}

void BusFault_Handler(void) {
  while(1) {
    
  }
}

void UsageFault_Handler(void) {
  while(1) {
    
  }
}

