# Reaction Time Game Using Arduino UNO

This project is a multiplayer reaction time game built using Arduino UNO, push buttons, and a 128x64 OLED display. Players compete to see who reacts the fastest when the “GO!!!” signal appears.

## Features

- Supports 3 players with individual buttons  
- Countdown timer before game starts  
- Displays reaction times on the OLED screen  
- Shows the winner based on fastest reaction  
- Reset and replay functionality with the start button  

## Hardware Required

- Arduino UNO  
- 128x64 OLED Display (SSD1306)  
- 4 Push buttons (1 Start + 3 Player buttons)  
- Connecting wires  
- Breadboard (optional)  

## Wiring

- Start button connected to digital pin 2  
- Player 1 button connected to digital pin 3  
- Player 2 button connected to digital pin 4  
- Player 3 button connected to digital pin 5  
- OLED connected via I2C (SDA, SCL pins)

## How to Run

1. Install the **Adafruit GFX** and **Adafruit SSD1306** libraries in Arduino IDE.  
2. Connect the hardware as described above.  
3. Open the `ReactionTimeGame.ino` sketch in Arduino IDE.  
4. Upload the sketch to your Arduino UNO.  
5. Press the **START** button to begin the countdown.  
6. When “GO!!!” appears on the OLED, players press their buttons as quickly as possible.  
7. Reaction times and the winner are displayed.  
8. Press **START** again to reset and replay.
