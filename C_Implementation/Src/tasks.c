/**
 * @file tasks.c
 * @brief Implementation of task management functions.
 *
 * This file contains the implementation of task initialization, scheduling,
 * and management for the embedded scheduler.
 *
 * @author Bilel
 * @date 2024-10-28
 */

#include "tasks.h"
#include "gpio.h"
#include "main.h"


extern TaskControlBlock tasks[TOTAL_TASKS];
extern uint8_t c_task;
extern uint32_t g_tick_count;
uint32_t psp_of_tasks[TOTAL_TASKS] = {IDLE_STACK_START ,TASK1_STACK_START , TASK2_STACK_START , TASK3_STACK_START , TASK4_STACK_START};
// Define task_handlers as an array of pointers to functions returning void
void (*task_handlers[TOTAL_TASKS])(void) = { idle_routine, task1_routine, task2_routine, task3_routine, task4_routine };
extern void trig_pendsv();

void task1_routine(void) {
  while (1)
  {
    /* code */
    toggle_gpio_pin(GPIO_PIN_D12);
    task_delay(2);
    //delay(10000);
  }
  
}

void task2_routine(void) {
  while (1)
  {
    /* code */
    toggle_gpio_pin(GPIO_PIN_D13);
    task_delay(4);
    //delay(20000);
  }
  
}

void task3_routine(void) {
  while (1)
  {
    /* code */
    toggle_gpio_pin(GPIO_PIN_D14);
    task_delay(6);
    //delay(30000);
  }
  
}

void task4_routine(void) {
  while (1)
  {
    /* code */
    toggle_gpio_pin(GPIO_PIN_D15);
    task_delay(8);
    //delay(40000);
  }
  
}

void idle_routine(void) {
  int idle = 0;
  while (1)
  {
    idle++;
  }
  
}




void init_tasks_stack(void) {

  for (int task=0 ; task< TOTAL_TASKS ; task++) {
    tasks[task].task_state = RUNNING;
    tasks[task].stack_pointer = psp_of_tasks[task];
    tasks[task].task_function = task_handlers[task];
  }
  uint32_t *PSP;


  //Stack frame : xPSR / PC / LR / General purpose registers R12 -> R0 / Scratch registers R11 -> R4
  for (int task=0 ; task < TOTAL_TASKS ; task++) {
    PSP = (uint32_t*)tasks[task].stack_pointer;

    PSP--;
    *PSP = xPSR; //0x00100000 T (thumb state) bit of PSR register

    PSP--;
    *PSP = tasks[task].task_function; //PC next instruction to execute is the task handler

    PSP--;
    *PSP = 0xFFFFFFFD; //LR

    for (int reg = 0 ; reg < 13 ; reg++) {
      PSP--;
      *PSP = 0;
    }

    tasks[task].stack_pointer = (uint32_t)PSP;
    
  }
}


__attribute__((naked)) void sched_stack_init(uint32_t stack_sched) {
  __asm volatile ("MSR MSP,R0");
  __asm volatile ("BX LR");
}

void task_delay(uint32_t delay_tick) {
  if ( c_task != 0 ) {
    tasks[c_task].remaining_ticks = g_tick_count + delay_tick;
    tasks[c_task].task_state = BLOCKED;
    trig_pendsv();
  }
}