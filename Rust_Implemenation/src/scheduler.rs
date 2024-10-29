use core::{ptr , arch::asm};
use crate::consts::*;
use crate::gpio::{toggle_gpio_d12, toggle_gpio_d13 , toggle_gpio_d14 , toggle_gpio_d15 , delay};

static mut TASKS: [TaskControlBlock; NUM_TASKS] = [
    TaskControlBlock {psp_value: IDLE_T_STACK_START, block_count: 0, current_state: RUNNING, task_handler: idle_routine},
    TaskControlBlock {psp_value: TASK1_STACK_START, block_count: 0, current_state: RUNNING, task_handler: task1_routine},
    TaskControlBlock {psp_value: TASK2_STACK_START, block_count: 0, current_state: RUNNING, task_handler: task2_routine},
    TaskControlBlock {psp_value: TASK3_STACK_START, block_count: 0, current_state: RUNNING, task_handler: task3_routine},
    TaskControlBlock {psp_value: TASK4_STACK_START, block_count: 0, current_state: RUNNING, task_handler: task4_routine},
];


#[inline(always)]
pub fn init_scheduler_stack(stack_start_address: u32) {
    unsafe {
        asm!("MSR MSP, R0", in("r0") stack_start_address);
    }
}

#[inline(always)]
pub fn init_tasks_stacks() {
    unsafe {
        for task in 0..NUM_TASKS {
            let psp =  (TASKS[task].psp_value) as *mut u32; // Get mutable pointer to the task stack

            // Initialize the stack frame
            let mut psp_frame = psp.sub(1); // Point to the last position of the stack frame
            *psp_frame = INITIAL_X_PSR; // Set xPSR

            psp_frame = psp_frame.sub(1); // Move to the next position
            *psp_frame = (TASKS[task].task_handler) as u32; // Set the task handler

            psp_frame = psp_frame.sub(1); // Move to the next position
            *psp_frame = 0xFFFFFFFD; // Set LR

            // Initialize general purpose registers R12 to R0 with zero
            for _ in 0..13 {
                psp_frame = psp_frame.sub(1); // Move to the next position
                *psp_frame = 0; // Set register value to 0
            }

            TASKS[task].psp_value = psp_frame as u32; // Update the stack pointer for the task
        }
    }
}



pub unsafe fn get_psp_value() -> u32 {
    TASKS[C_TASK].psp_value
}

pub unsafe fn set_psp_value(task_psp: u32) {
    TASKS[C_TASK].psp_value = task_psp;
}

pub fn switch_sp_to_psp() {

    unsafe {
        asm!(
            "PUSH {{LR}}",
            options(nostack),
        );
    
        get_psp_value();
    
        //Move the PSP value from R0 to the Process Stack Pointer
        asm!(
            "MSR PSP, R0",
            options(nostack),
        );
    
        ///Restore the link register (LR) from the stack
        asm!(
            "POP {{LR}}",
            options(nostack),
        );
    
        ///SP to PSP by updating CONTROL register 
        asm!(
            "MOV R0, #0x02",
            "MSR CONTROL, R0",
            options(nostack),
        );
    
        asm!(
            "BX LR",
            options(nostack),
        );
    }
}

pub fn update_next_task() {
    unsafe {
        let mut found_task = false;
        for _ in 0..NUM_TASKS {
            C_TASK = (C_TASK + 1) % NUM_TASKS;
            
            // Check if the selected task is running and is not the idle task
            if TASKS[C_TASK].current_state == RUNNING && C_TASK != 0 {
                found_task = true;
                break;
            }
        }
        
        // If no running tasks were found, set to idle task
        if !found_task {
            C_TASK = 0;
        }
    }
    
}

pub fn task_delay(tick_to_delay: u32) {
    unsafe {
        if C_TASK != 0 {
            TASKS[C_TASK].block_count = GLOBAL_TICK_COUNT + tick_to_delay ;
            TASKS[C_TASK].current_state = BLOCKED;
            trig_pendsv();
        }
    }
}

pub fn trig_pendsv() {
    let icsr = 0xE000_ED04 as *mut u32;
    unsafe {
        ptr::write_volatile(icsr, ptr::read_volatile(icsr) | (1 << 28));
    }
}

pub fn check_blocked_tasks() {
    unsafe {
        for task in 0..NUM_TASKS {
            if TASKS[task].current_state == BLOCKED {
                if TASKS[task].block_count == GLOBAL_TICK_COUNT {
                    TASKS[task].current_state = RUNNING ;
                }
            }
        }
    }
}



pub fn task1_routine() -> () {
    loop {
        toggle_gpio_d12();
        task_delay(2);
    }
}
fn task2_routine() -> () {
    loop {
        toggle_gpio_d13();
        task_delay(4);
    }
}
fn task3_routine() -> () {
    loop {
        toggle_gpio_d14();
        task_delay(6);
    }
}
fn task4_routine() -> () {
    loop {
        toggle_gpio_d15();
        task_delay(8);
    }
}

fn idle_routine() -> () {
    loop {
        
    }
}
