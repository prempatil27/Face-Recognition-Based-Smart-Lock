# Face-Recognition-Based-Smart-Lock
Overview:
This project implements a smart lock system that uses face recognition, keypad password entry, and Bluetooth control to enhance security and convenience. The system integrates Python and Arduino for robust functionality.

Features:
1. Face Recognition: The Python code uses the DeepFace library to verify the user's face and send a signal to the Arduino to unlock the door.
2. Password Entry: An Arduino-based keypad allows for password entry to unlock the door.
3. Bluetooth Control: The lock can be controlled remotely via Bluetooth, providing additional flexibility.
4. Serial Communication: Enables communication between the Python script and Arduino to coordinate the locking mechanism.

Components:
Arduino Uno,
Keypad,
Bluetooth Module,
Solenoid Lock,
Relay Module,
LED.

Circuit Connections

1. Arduino Uno:
Connect the lock to pin 12.
Connect the LED to pin A0.
Connect the Bluetooth module to pins 2 (RX) and 3 (TX).
Keypad connections to pins 4-11.

2. Python Script:
Ensure the camera is connected and accessible via OpenCV.
Connect the Python script to Arduino via serial communication on COM9 at a baud rate of 9600.

Block Diagram Explanation: 
User: Initiates the lock operation via face recognition, keypad, or Bluetooth.
Input: The system takes inputs from three sources - camera (face recognition), keypad, and Bluetooth.
Face Recognition: Python script processes the camera input to verify the user's face.
Keypad: Users can enter a password via the keypad to unlock the door.
Bluetooth: Allows remote control of the lock via Bluetooth signals.
Microcontroller: Arduino Uno processes inputs from Python, keypad, and Bluetooth to control the solenoid lock.
Solenoid Lock: The locking mechanism is controlled by signals from the microcontroller.
