# Flight Attitude HUD Simulation

A real-time fighter-style flight attitude simulation written in C using the Raylib graphics library.

This project simulates a simplified aircraft Head-Up Display (HUD) including an artificial horizon, pitch ladder, altitude display, and real-time attitude dynamics. The goal of the project is to demonstrate concepts from flight dynamics, control systems, and real-time rendering using low-level C programming.

---

## Features

- Artificial horizon rendering
- Pitch ladder visualization
- Flight path marker
- 360° roll and pitch dynamics
- Inverted flight control behavior
- Dynamic altitude simulation
- Real-time keyboard interaction
- Fighter-style HUD interface

---

## Controls

W → Pitch Up  
S → Pitch Down  
A → Roll Left  
D → Roll Right  
ESC → Exit Simulation

---

## Technologies Used

- C
- Raylib graphics library
- Real-time simulation loop
- Basic flight dynamics modeling

---

## Concepts Demonstrated

This project demonstrates several engineering and software concepts:

- Flight attitude representation
- Artificial horizon visualization
- Coordinate transformations
- Real-time simulation loops
- Basic control system behavior
- Interactive graphics rendering

---

## Build

Compile using GCC:

gcc main.c -o sim -IC:/raylib/include -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

---

## Run

./sim

---

## Project Goal

The purpose of this project is to build a simplified simulation of a fighter aircraft HUD while practicing systems-level programming, real-time graphics, and flight attitude visualization.

---

## Future Improvements

Possible extensions include:

- Airspeed indicator
- Heading indicator
- G-force indicator
- Sky / ground rendering
- Improved aircraft physics
- Joystick or gamepad support

---

## Author

Oguz Mermer  
Computer Engineering Student
