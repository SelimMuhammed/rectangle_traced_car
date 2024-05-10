# rectangle_traced_car
The Car moves in a rectangle trace with different PWM and time delay using all Timers in only Normal Mode to achieve the sequence 
This Markdown file describes an embedded system application implemented in C language. The application controls a system with DC motors, LEDs, and buttons. Below is a breakdown of the code functionality:

## Directory Structure

The code is organized into several directories:
- **LIB**: Contains custom libraries for bit manipulation and standard types.
- **HAL**: Hardware Abstraction Layer for interfacing with hardware components like DC motors, buttons, and LEDs.
- **MCAL**: Microcontroller Abstraction Layer for low-level hardware control, including GPIO, external interrupts, and timers.
- **App**: Contains the main application code.

## Constants and Definitions

The code defines various constants and states used throughout the application, including:
- States for managing the program flow (INIT, START, STOP, etc.).
- Timer delay values for controlling timing operations.
- PWM signal parameters for motor control.

## Functions

### `Emergency_voidStop()`
- Stops the motor and resets state variables in case of an emergency stop button press.

### `SW_PWM()`
- Implements software-based PWM control for the DC motor.
- Adjusts the motor's duty cycle based on the current state (RECTANGLE_WIDTH, RECTANGLE_LENGTH, etc.).

### `DelaySec()`
- Handles timing operations using timer interrupts.
- Updates program states based on predefined delay intervals.

### `main()`
- Initializes hardware components (LEDs, motors, buttons, timers, and interrupts).
- Enters an infinite loop to continuously monitor button presses and update program states accordingly.
- Executes different actions based on the current state, such as motor control and LED status updates.

## Usage

To use the application:
1. Connect the hardware components (DC motors, LEDs, buttons) to the microcontroller.
2. Compile and upload the code to the microcontroller.
3. Press Push Button 1 to start the program.
4. The program will execute a predefined sequence of actions, including motor movements and LED indications.

## Conclusion

This embedded system application demonstrates the use of timers, interrupts, and GPIO manipulation for controlling hardware components. It provides a structured approach to managing system states and implementing timed operations.