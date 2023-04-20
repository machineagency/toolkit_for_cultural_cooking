/*
hello! i'm danli, i wrote this firmware to operate my doufu maker!
any questions should be addressed to danlil at uw dot edu
 */
#include <OneWire.h>
#include <DallasTemperature.h>
// include the library code:
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
// Where the temperature sensor probe is connected.
#define ONE_WIRE_BUS 4 //need 4.7k pull-up to stablize data transfer

// Setup a OneWire instance to communicate with any devices.
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// define motor pin
int motorPin = 11;

// let's add 2 leds to indicate heater status
int ledON = 12; //red one!
int ledOFF = 13; //maybe a green one?

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledON, OUTPUT);
  pinMode(ledOFF, OUTPUT);
  pinMode(motorPin, OUTPUT);
  sensors.begin(); //start up the thermometer library
    // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // uncomment this line to save some power
//  lcd.setBacklight(LOW);
  // Print a message to the LCD.
  lcd.print("hello!");
}

void loop() {
  
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if (tempC < 85){ // lower bound for turning on the heater
    digitalWrite(motorPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("start adding coagulant");
    digitalWrite(ledON, HIGH);
    digitalWrite(ledOFF, LOW);
    delay(5000); // calibrated amount
    digitalWrite(relayPin, LOW);
    digitalWrite(motorPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("done!");
    digitalWrite(ledON, LOW);
    digitalWrite(ledOFF, HIGH);
    delay(100);

}
