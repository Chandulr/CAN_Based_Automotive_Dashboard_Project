
# CAN-Based Automotive Dashboard

## Project Overview
Developed a CAN-based automotive dashboard using Embedded C and PIC18F4580 microcontrollers. The system consists of three ECUs communicating through the CAN protocol to simulate an automotive instrument cluster.

## Technologies Used
- Embedded C
- PIC18F4580 Microcontroller
- CAN Protocol
- MPLAB X IDE
- XC8 Compiler

## Project Architecture

### ECU1 - Speed and Gear Control
- Reads vehicle speed using ADC.
- Handles gear selection using a matrix keypad.
- Transmits speed and gear information through CAN communication.

### ECU2 - Indicator and RPM Control
- Controls left and right indicators.
- Handles RPM-related functionality.
- Communicates vehicle information through CAN.

### ECU3 - Dashboard Display
- Receives vehicle parameters through CAN.
- Displays speed, gear, RPM and indicator status on CLCD.

## Project Structure
- ECU1 - Speed and gear control
- ECU2 - Indicator and RPM control
- ECU3 - Dashboard display

## Development Tools
- MPLAB X IDE
- XC8 Compiler
