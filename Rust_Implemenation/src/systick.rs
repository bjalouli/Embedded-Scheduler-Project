use cortex_m::peripheral::syst::SystClkSource;
use cortex_m::peripheral::Peripherals;
use crate::{get_psp_value, update_next_task};
use cortex_m_rt::exception;
use crate::consts::{HSI_CLOCK_FREQ_HZ , GLOBAL_TICK_COUNT};
use crate::scheduler::{set_psp_value , trig_pendsv , check_blocked_tasks};
use core::arch::asm;


pub fn configure_systick(tick_rate: u32) {
    let mut cp = Peripherals::take().unwrap(); // Access core peripherals

    let reload_value = HSI_CLOCK_FREQ_HZ / tick_rate - 1;
    cp.SYST.set_clock_source(SystClkSource::Core);
    cp.SYST.set_reload(reload_value);
    cp.SYST.clear_current();
    cp.SYST.enable_counter();
    cp.SYST.enable_interrupt();
}

#[exception]
fn SysTick() {
    unsafe {
        GLOBAL_TICK_COUNT += 1;
        check_blocked_tasks();
        trig_pendsv();
    }
    

}

#[exception]
fn PendSV() {
    unsafe {
        
        asm!("PUSH {{LR}}", options(nostack, preserves_flags));
        // Get the current PSP value 
        let mut psp_value: u32;
        asm!("MRS {0}, PSP", out(reg) psp_value);

        // Store registers R4-R11 on the stack using the PSP
        asm!("STMDB {0}!, {{R4-R11}}", inout(reg) psp_value);
        set_psp_value(psp_value);
        update_next_task();
        let mut next_psp_value = get_psp_value();

        // Restore registers R4-R11 from the PSP stack (LDMIA R0!, {R4-R11})
        asm!("LDMIA {0}!, {{R4-R11}}", inout(reg) next_psp_value);
        asm!("MSR PSP, {0}", in(reg) next_psp_value);
        asm!("POP {{LR}}", options(nostack, preserves_flags));

        asm!(
            "MOV LR, {0}",    // Move 0xFFFFFFFD into LR
            "BX LR",          /// Return from the handler (BX LR)
            in(reg) 0xFFFFFFFD as u32,
            options(noreturn)
        );
        
        
    }
}

