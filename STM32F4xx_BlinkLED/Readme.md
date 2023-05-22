# STM32F4xx Blink LED Example Project

This repository contains a simple example project for the STM32F4xx microcontroller family,
 which blinks an LED using the RCC, GPIO, and SysTick drivers.

## Getting Started

To get started with this project, you will need:

- An STM32F4xx microcontroller board
- A toolchain such as Keil, STM32Cube or eclipse software development IDEs installed on your machine

Once you have all the necessary tools, you can clone this repository to your local machine and open the project in your development environment.

## Project Structure

The project is structured as follows:

- **Drivers**: This example project uses the following STM32F4xx MCAL drivers:
- RCC (Reset and Clock Control)
- GPIO (General Purpose Input/Output)
- SysTick (System Timer) 

These drivers provide an abstracted interface to the hardware peripherals of the microcontroller, allowing the code to interact with them more easily.

- **Inc**: This directory contains the project header files, including the RCC, GPIO and SysTick driver header files.

- **Src**: This directory contains the project source files. The main.c and other soucre program files contains the code for the project.

## How to Use

To use this project, you can simply build and flash the code to your STM32F4xx board. The LED connected to pin PA0 should start blinking at a frequency of 1Hz.
