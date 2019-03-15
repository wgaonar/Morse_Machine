/* Morse machine code
 * Wilmer Gaona Romero
 * 23 Feb 2019
 * twitter: @wgaonar
 * Cuernavaca, México
 */

#include"Letters.h" 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int dotPIN = A0;
const int dashPIN = A1;
const int spacePIN = A2;
const int resetPIN = A3;
const int dotLED = 8;
const int dashLED = 9;
const int spaceLED = 10;
const int buzzerPIN = 11;

int dotDURATION = 100, dashDURATION = 3 * dotDURATION, spaceDURATION = 1 * dotDURATION;
int dotSTATE, dashSTATE, spaceSTATE, resetSTATE;

int stateLCD = LOW;
String morseKEY,LETTER, WORD;

unsigned long previousMillis = 0; // will store last time LED was updated
// constants won't change:
const long interval = 1000; // interval at which to blink (milliseconds)

void setup() {
  // put your setup code here, to run once:

  pinMode(dotPIN,INPUT);
  pinMode(dashPIN,INPUT);
  pinMode(spacePIN,INPUT);
  pinMode(resetPIN,INPUT);
  pinMode(dotLED,OUTPUT);
  pinMode(dashLED,OUTPUT);
  pinMode(spaceLED,OUTPUT);
  pinMode(buzzerPIN,OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Morse Machine!");
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
  lcd.clear();
  
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the state of the push buttons for the dot, dash and space
  dotSTATE = digitalRead(dotPIN);
  dashSTATE = digitalRead(dashPIN);
  spaceSTATE = digitalRead(spacePIN);
  resetSTATE = digitalRead(resetPIN);

  // check if a pushbutton was pressed. If it is, the STATE = HIGH
  
  if (dotSTATE == HIGH) {
    // check if the state remains HIGH
    while (digitalRead(dotPIN) ==  HIGH) {
      delay(10);
    }
    // call the function dot to signal a dot on the LED
    dot();
  }
  
  if (dashSTATE == HIGH) {
    // check if the state remains HIGH
    while (digitalRead(dashPIN) ==  HIGH) {
      delay(10);
    }
    // At this point, the state should be LOW
    // call the function dash to signal a dash on the LED
    dash();
  }
  
  if (spaceSTATE == HIGH) {
    // check if the state remains HIGH
    while (digitalRead(spacePIN) ==  HIGH) {
      delay(10);
    }
    // At this point, the state should be LOW
    // call the function space to signal a space on the LED
    space();
  }
  
  if (resetSTATE == HIGH) {
    // check if the state remains HIGH
    previousMillis = millis();
    while (digitalRead(resetPIN) ==  HIGH) {
      delay(10);
      unsigned long currentMillis = millis();
      Serial.println(currentMillis - previousMillis);
//      // Check if the 2000ms interval for signaling a WORD reset has elapsed
      if (currentMillis - previousMillis >= interval) {
        // save the last time you erase the WORD
        previousMillis = currentMillis;
        morseKEY="";
        LETTER = "";
        WORD = "";
        lcd.clear();
      }
    }
    // Remove the last entered Morse Character
    if (morseKEY.length() > 0) {
      morseKEY.remove(morseKEY.length()-1);
    }
    lcd.home();
    for (int i = 0; i<=15; i++) {
      lcd.write(" ");
    }
    lcd.home();
    lcd.print(morseKEY);
  }

  if (morseKEY.equals(A)) {
    LETTER = "A";
    lcdPrintWord();
  }
  if (morseKEY.equals(B)) {
    LETTER = "B";
    lcdPrintWord();
  }
  if (morseKEY.equals(C)) {
    LETTER = "C";
    lcdPrintWord();
  }
  if (morseKEY.equals(D)) {
    LETTER = "D";
    lcdPrintWord();
  }
  if (morseKEY.equals(E)) {
    LETTER = "E";
    lcdPrintWord();
  }
  if (morseKEY.equals(F)) {
    LETTER = "F";
    lcdPrintWord();
  }
  if (morseKEY.equals(G)) {
    LETTER = "G";
    lcdPrintWord();
  }
  if (morseKEY.equals(H)) {
    LETTER = "H";
    lcdPrintWord();
  }
  if (morseKEY.equals(I)) {
    LETTER = "I";
    lcdPrintWord();
  }
  if (morseKEY.equals(J)) {
    LETTER = "J";
    lcdPrintWord();
  }
  if (morseKEY.equals(K)) {
    LETTER = "K";
    lcdPrintWord();
  }
  if (morseKEY.equals(L)) {
    LETTER = "L";
    lcdPrintWord();
  }
  if (morseKEY.equals(M)) {
    LETTER = "M";
    lcdPrintWord();
  }
  if (morseKEY.equals(N)) {
    LETTER = "N";
    lcdPrintWord();
  }
  if (morseKEY.equals(O)) {
    LETTER = "O";
    lcdPrintWord();
  }
  if (morseKEY.equals(P)) {
    LETTER = "P";
    lcdPrintWord();
  }
  if (morseKEY.equals(Q)) {
    LETTER = "Q";
    lcdPrintWord();
  }
  if (morseKEY.equals(R)) {
    LETTER = "R";
    lcdPrintWord();
  }
  if (morseKEY.equals(S)) {
    LETTER = "S";
    lcdPrintWord();
  }
}

// Functions for turning On and OFF the LEDs
void dot(){
  digitalWrite(dotLED,HIGH);
  digitalWrite(buzzerPIN,HIGH);
  delay(dotDURATION);
  digitalWrite(dotLED,LOW);
  digitalWrite(buzzerPIN,LOW);
  morseKEY += ".";
  lcdPrint();
}

void dash(){
  digitalWrite(dashLED,HIGH);
  digitalWrite(buzzerPIN,HIGH);
  delay(dashDURATION);
  digitalWrite(dashLED,LOW);
  digitalWrite(buzzerPIN,LOW);
  morseKEY += "-";
  lcdPrint();
}

void space(){
  digitalWrite(spaceLED,HIGH);
  delay(spaceDURATION);
  digitalWrite(spaceLED,LOW);
  morseKEY += "0";
  lcdPrint();
}

void lcdPrint(){
  lcd.clear();
  lcd.print(morseKEY);
  lcd.setCursor(0,1);
  lcd.print(WORD);
}

void lcdPrintWord(){
  lcd.setCursor(15, 0); // top right
  lcd.print(LETTER);
  delay(1000);
  lcd.clear();
  morseKEY = "";
  WORD += LETTER;
  lcd.setCursor(0, 1); // bottom left
  lcd.print(WORD);
}




