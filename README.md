# Embedded Scheduler Project

## Overview

This project is an embedded scheduler implemented in C for an ARM Cortex-M3/M4 microcontroller, specifically developed and tested on an STM32F4 microcontroller. The scheduler employs a **Round Robin scheduling algorithm**, ensuring each task receives a fair share of CPU time. It’s designed to handle basic multitasking by switching between tasks at regular intervals, leveraging the ARM Cortex-M's PendSV interrupt for context switching.

## Features

- **Round Robin Scheduling**: Implements time-slicing to provide fair CPU allocation to each task, ensuring that all tasks get a share of CPU time.

- **PendSV for Context Switching**: Uses the PendSV interrupt on ARM Cortex-M processors to enable efficient task switching. PendSV is triggered when a task's time slice ends, or it enters a blocked state, allowing the scheduler to select the next task.

- **SysTick Timer**: The SysTick timer is used to maintain the global tick count. It triggers periodic interrupts, updating the system tick and allowing the scheduler to track delays and manage task time slices accurately.

- **Task Delay**: Each task can specify idle periods using a delay function (`task_delay`). This feature allows tasks to release the CPU for a specified number of ticks, after which they are automatically rescheduled.

- **Tick Counting**: A global tick counter, updated by the SysTick handler, drives the scheduler. This counter ensures tasks run according to their time slice and tracks task delays.

- **Stack Frames**: Each task has its own stack frame, storing registers and execution state during context switching. The scheduler saves the current task’s stack pointer and loads the stack pointer of the next task, maintaining a seamless task execution.

## Task Scheduling
The scheduler is designed to manage four user tasks and an idle task. Each user task is responsible for toggling a user LED with a specified delay, demonstrating how the scheduler performs basic task management and timing control.

- **Idle Task**: Executes when no other tasks are scheduled to run, ensuring the system remains in a low-power, idle state.
- **User Tasks**: Each of the four tasks toggles an LED on the board, with each task configured to run after a specified delay. This setup simulates a time-slicing operation where each task is given CPU time based on the round-robin scheduling algorithm.
- **Flexible Design**: The scheduler implementation is flexible, allowing for easy addition of new tasks by configuring them in the TaskControlBlock structures, enabling scalable task management without major modifications.


## Requirements

- **Hardware**: ARM Cortex-M3 or M4 processor, tested on stm32f407g-disc1.
- **Software**: Developed from scratch in C for low-level control without any HAL dependencies. The Rust version utilizes the `cortex-m` crate for ARM Cortex-M peripheral access and the `stm32f4` crate for pin manipulation on the STM32F4.

- **Tools**: For the C implementation, `arm-none-eabi-gcc` is used for cross-compilation. The Rust version relies on `cargo` as the build system after setting the correct target in the config file. `OpenOCD` used for flashing and debugging on the ARM Cortex-M processor


## Project Structure
  - [Rust](C_Implementation/)
  - [C](Rust_Implemenation/)


## Building and Flashing

### Build the Project

#### For C
Run the following command under the `Debug` directory to build the C project:

```bash
make all
```

#### For RUST
Run the following command to build the Rust project:

```bash
cargo build --target thumbv7em-none-eabihf
```
### Build the Project

To flash the binary into your STM32 board, use the flash_device.sh script after ensuring that the openocd.cfg configuration file is present at the same directory level. 
Run the following command :

```
./flash_device.sh <path_to_binary>
```