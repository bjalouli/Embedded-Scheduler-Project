use cortex_m::peripheral::Peripherals;
use core::arch::asm;
use crate::gpio::toggle_gpio_d13;
use core::ptr;

use cortex_m_rt::exception;

#[allow(unused)]
pub fn enable_faults() {
    let mut cp = Peripherals::take().unwrap(); // Access core peripherals
    cp.SCB.enable(cortex_m::peripheral::scb::Exception::HardFault);
    cp.SCB.enable(cortex_m::peripheral::scb::Exception::MemoryManagement);
    cp.SCB.enable(cortex_m::peripheral::scb::Exception::BusFault);
    cp.SCB.enable(cortex_m::peripheral::scb::Exception::UsageFault);
}

#[allow(unused)]
#[inline(never)]
pub fn trigger_hardfault() {
    unsafe {
        ptr::read_volatile(0x3FFF_0000 as *const u32);
    }
}



#[exception]
unsafe fn HardFault(_ef: &cortex_m_rt::ExceptionFrame) -> ! {
    

    
    loop{
        toggle_gpio_d13();

        for _ in 0..500_000 {
            asm!("nop"); // Delay loop
        }
    }
}


// #[exception]
// fn MemoryManagement() {
//     // Handle memory management fault
//     loop {

//     }
// }

// // Bus Fault Handler
// #[exception]
// fn BusFault() {
//     // Handle bus fault
//     loop {

//     }
// }

// // Usage Fault Handler
// #[exception]
// fn UsageFault() {
//     // Handle usage fault
//     loop {

//     }
// }