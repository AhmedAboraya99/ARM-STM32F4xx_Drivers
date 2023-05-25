# STM32F4xx EXTI Driver

This repository contains a driver for the external interrupt (EXTI) controller on the STM32F4xx microcontroller. The driver provides an interface for configuring and controlling the EXTI module, including setting interrupt triggers, enabling and disabling interrupts, and handling interrupt events.

The driver uses the following STM32F4xx standard peripheral drivers:
- STK (System Tick Timer)
- NVIC (Nested Vector Interrupt Controller)
- RCC (Reset and Clock Control)
- GPIO (General Purpose Input/Output)
- EXTI (External Interrupt Controller)

## Example Applications

The driver comes with two example applications to demonstrate how to use it:

### 1. Turn on LED using EXTI0 source with push button

This example demonstrates how to use the EXTI driver to turn on an LED when a push button connected to EXTI0 is pressed. The example uses the GPIO driver to control the LED and the push button, and the EXTI driver to handle the interrupt events.

### 2. Nested Interrupts using priority groups (PortA EXTI0, EXTI1)

This example demonstrates how to use the EXTI driver to handle nested interrupts from two sources: EXTI0 and EXTI1, both connected to GPIO pins on PortA. The example uses the NVIC driver to manage the priority of the interrupts, and the EXTI and GPIO drivers to handle the interrupt events.

## Contributing

If you find a bug or have a suggestion for improvement, please open an issue or submit a pull request. We welcome contributions from the community!

## Credits

This driver was developed by Ahmed Aboraya. and is based on the STM32F4xx standard peripheral drivers provided by STMicroelectronics.
