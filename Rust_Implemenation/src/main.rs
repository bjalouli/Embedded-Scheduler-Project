#![no_std]
#![no_main]

#[allow(unused)]
use panic_halt as _;

// For entry point and SysTick handler

mod gpio;
mod scheduler;
mod systick;
mod consts;
mod fault;

use crate::scheduler::*;
use crate::gpio::gpio_init;
use crate::systick::configure_systick;
use consts::{SCHEDULER_STACK_START , SYSTICK_TICK_RATE_HZ};
//use crate::fault::{enable_faults , trigger_hardfault};




#[no_mangle]
extern "C" fn main() -> ! {
    //enable_faults();
    gpio_init(); //gpio initialization
    init_scheduler_stack(SCHEDULER_STACK_START); //initialize MSP register with the address of scheduler stack start
    configure_systick(SYSTICK_TICK_RATE_HZ);  // HSI clock at 16 MHz and 1s tick rate

    init_tasks_stacks();
    switch_sp_to_psp();
    task1_routine();
    // Main loop
    loop {
        // Do nothing, SysTick handler will toggle the LED
    }
}





