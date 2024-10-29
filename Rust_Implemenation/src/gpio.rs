use stm32f4::stm32f407;

pub fn gpio_init() {
    let dp = stm32f407::Peripherals::take().unwrap();

    // Enable the GPIOD clock (for the LED)
    dp.RCC.ahb1enr.modify(|_, w| w.gpioden().enabled());

    // Set GPIOD12 and GPIOD13 as output
    dp.GPIOD.moder.modify(
        |_, w| w.moder12().output().moder13().output().moder14().output().moder15().output());
}

pub fn toggle_gpio_d12() {
    let dp = unsafe { stm32f407::Peripherals::steal() };

    // Toggle GPIOD12 (LED)
    if dp.GPIOD.odr.read().odr12().bit_is_set() {
        dp.GPIOD.bsrr.write(|w| w.br12().set_bit()); // Turn off
    } else {
        dp.GPIOD.bsrr.write(|w| w.bs12().set_bit()); // Turn on
    }
}

pub fn toggle_gpio_d13() {
    let dp = unsafe { stm32f407::Peripherals::steal() };

    // Toggle GPIOD12 (LED)
    if dp.GPIOD.odr.read().odr13().bit_is_set() {
        dp.GPIOD.bsrr.write(|w| w.br13().set_bit()); // Turn off
    } else {
        dp.GPIOD.bsrr.write(|w| w.bs13().set_bit()); // Turn on
    }
}

pub fn toggle_gpio_d14() {
    let dp = unsafe { stm32f407::Peripherals::steal() };

    // Toggle GPIOD12 (LED)
    if dp.GPIOD.odr.read().odr14().bit_is_set() {
        dp.GPIOD.bsrr.write(|w| w.br14().set_bit()); // Turn off
    } else {
        dp.GPIOD.bsrr.write(|w| w.bs14().set_bit()); // Turn on
    }
}

pub fn toggle_gpio_d15() {
    let dp = unsafe { stm32f407::Peripherals::steal() };

    // Toggle GPIOD12 (LED)
    if dp.GPIOD.odr.read().odr15().bit_is_set() {
        dp.GPIOD.bsrr.write(|w| w.br15().set_bit()); // Turn off
    } else {
        dp.GPIOD.bsrr.write(|w| w.bs15().set_bit()); // Turn on
    }
}

pub fn delay(mut count: u32) {
    while count != 0 {
        count -= 1 ;
    }
}
