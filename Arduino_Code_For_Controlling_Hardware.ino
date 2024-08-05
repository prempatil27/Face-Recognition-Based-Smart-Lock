#include <SoftwareSerial.h>  // Include the SoftwareSerial library for Bluetooth communication
#include <Keypad.h>  // Include the Keypad library

#define lock 12  // Define the pin for the solenoid lock
#define led A0  // Define the pin for the LED

// Initialize the SoftwareSerial for Bluetooth
SoftwareSerial Bluetooth(2, 3);  // RX | TX

// Function to check if a character is present in a string
int check(String string, char c);

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  Bluetooth.begin(9600);  // Start Bluetooth communication at 9600 baud rate

  pinMode(lock, OUTPUT);  // Set the lock pin as output
  pinMode(led, OUTPUT);  // Set the LED pin as output
  digitalWrite(lock, HIGH);  // Set the lock to locked position
  analogWrite(led, 0);  // Turn off the LED
}

String str = "";  // String to store Bluetooth data
bool send = false;  // Flag to indicate if data should be sent
char flag = ' ';  // Character to store Bluetooth command

// Define the keypad layout
const byte ROWS = 4;  // Four rows
const byte COLS = 4;  // Four columns

const char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

const byte rowPins[ROWS] = {11, 10, 9, 8};  // Connect to the row pinouts of the keypad
const byte colPins[COLS] = {7, 6, 5, 4};  // Connect to the column pinouts of the keypad

// Create an object of keypad
const Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
const String pwd = "111";  // Define the correct password
char key = ' ';  // Character to store the key pressed
String pass = "";  // String to store the entered password
bool getPass = false;  // Flag to indicate if password is being entered

void loop() {
  char key = keypad.getKey();  // Read the key from the keypad
  if (key) {
    if (getPass) {
      if (key == 'C') {
        if (pwd == pass) {
          pass = "";
          digitalWrite(lock, LOW);  // Unlock the lock
          delay(200);
        }
        analogWrite(led, 0);  // Turn off the LED
        getPass = false;
      } else pass += (String) key;  // Append the key to the password
    }
    if (key == 'A' && getPass == false) {
      analogWrite(led, 150);  // Turn on the LED
      getPass = true;  // Start entering the password
    }
    if (key == 'D' && getPass == false) digitalWrite(lock, HIGH);  // Lock the lock
  }

  // Bluetooth part
  if (Bluetooth.available()) {
    flag = Bluetooth.read();
    if(flag == '?') {
      send = true;
    } else {
      str += (String) flag;
    }
  }
  if (send) {
    if(check(str, '0')) {
      digitalWrite(lock, LOW);  // Unlock the lock
    } else if (check(str, '1')) {
      digitalWrite(lock, HIGH);  // Lock the lock
    }
    str = "";
    send = false;
  }

  // Python serial communication part
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(lock, LOW);  // Unlock the lock
      delay(200);
    }
  }
  delay(50);
}

// Function to check if a character is present in a string
int check(String string, char c) {
  int isPresent = 0;
  for (int i = 0; i < string.length(); i++) {
    if (string[i] == c) {
      isPresent = 1;
      break;
    }
  }
  return isPresent;
}
