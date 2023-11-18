#include "Adafruit_Keypad.h"

const byte ROWS = 4; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 10, 9, 8}; //connect to the column pinouts of the keypad
char keyPressed = '0';
const String passcode = "123456";
String inputcode = "";

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  customKeypad.begin();
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(passcode == inputcode) startTimer();
  if(inputcode.length() >= 6) inputcode="";

  customKeypad.tick();
  
  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    keyPressed = (char)e.bit.KEY;
    Serial.print((char)e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.println(" pressed"); 
      inputcode += keyPressed;
    }
    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
    Serial.println(inputcode);
  }

  delay(10);
}

void startTimer() {
  for(int i=60; i>0; i--){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}

