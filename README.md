# Arduino Uno + MPLAB SNAP DEBUGGER + MPLAB X/VS Code

## Overview
This project demonstrates how to program and debug an Arduino Uno (ATmega328P) using MPLAB X tools and the SNAP debugger, with Visual Studio Code as the main development environment.

Unlike the Arduino IDE, this setup uses low-level embedded C with direct register control, allowing real-time debugging and deeper understanding of the microcontroller.

---

## Features
- Embedded C programming (no Arduino libraries)
- USART communication (9600 baud)
- I2C communication with 16x2 LCD
- Debugging with MPLAB SNAP (breakpoints, step execution)
- VS Code integration with MPLAB tools

---

## Hardware
- Arduino Uno (ATmega328P)
- MPLAB SNAP Debugger (PG164100)
- I2C LCD (16x2, address 0x27)
- Jumper wires

---

## Software
- MPLAB X IDE
- XC8 Compiler (v3.x)
- Visual Studio Code
- MPLAB Extensions for VS Code

---

## Project Structure
LCD_Project/
│── main.c
│── .vscode/
│   ├── tasks.json
│   ├── launch.json

---

## Setup

### 1. Hardware Connections (SNAP → Arduino)
- TVDD → VCC  
- GND → GND  
- PGD → MISO  
- PGC → SCK  
- TAUX → RESET  
- TTDI → MOSI  

Note: The reset trace on the Arduino may need to be cut to prevent USB interference.

---

### 2. Open Project
- Open the project folder in VS Code
- Ensure MPLAB extensions are installed

---

### 3. Build
Run the build task in VS Code.

---

### 4. Debug
Press F5 to start debugging.

---

## Output

### Serial Output
Starting LCD + USART demo...
HELLO MARK displayed on LCD

### LCD Display
HELLO  
MARK  

---

## Troubleshooting

**avr/io.h not found**
- Wrong compiler selected (clang/gcc)
- Use XC8 via MPLAB tools

**program does not exist**
- Build failed or not run
- Build project before debugging

**Could not find task 'build'**
- tasks.json not configured correctly

**Port Issues**
- Close other apps using the Arduino (e.g., Arduino IDE)

---

## Author
Mark Anthony Masiclat
