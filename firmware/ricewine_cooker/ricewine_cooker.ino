/*
hello! i'm danli, i wrote this firmware to operate my slow cooker!
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

// define relay pin
int relayPin = 7;

// define motor pin
int motorPin = 11;

// let's add 2 leds to indicate heater status
int ledON = 12; //red one!
int ledOFF = 13; //maybe a green one?

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledON, OUTPUT);
  pinMode(ledOFF, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
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
  if (tempC < 29){ // lower bound for turning on the heater
    digitalWrite(relayPin, HIGH);
    analogWrite(motorPin, 63);
    // the motor draws a lot of current, so I pwm'ed it to have just enough amount of turbulance
    lcd.setCursor(0, 0);
    lcd.print("heater on!");
    digitalWrite(ledON, HIGH);
    digitalWrite(ledOFF, LOW);
    delay(100);
  }
  if (tempC >= 31){ // upper bound for turning off the heater
    lcd.setCursor(0, 0);
    digitalWrite(relayPin, LOW);
    digitalWrite(motorPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("heater off...");
    digitalWrite(ledON, LOW);
    digitalWrite(ledOFF, HIGH);
    delay(100);
  }
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  delay(2000); //read temp only per 2 seconds
}
