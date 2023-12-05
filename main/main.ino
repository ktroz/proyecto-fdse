#include <Wire.h>
#include "ventilador.h"
#include "foco.h"
#include "temperatura.h"
#include "i2c.h"

// Constants
#define I2C_SLAVE_ADDR 0x0A
//Components pin
#define VENTILATOR_PIN 9
// Digital 2 is Pin 2 in UNO
#define ZXPIN 2
// Digital 3 is Pin 3 in UNO
#define TRIAC 3
  
// Global variables
volatile bool flag = false;
int pdelay = 0;
int inc = 1;
//Ventilator 0-255
int pwm = 0;
//Lamp
float triacDelay = 0;
//Temperature sensor
float temp = 0;
float temp2 = 0;
// I2C Data
char cmd;
float value;
bool send = false;

// Prototypes
void i2c_received_handler(int count);
void i2c_request_handler(int count);
void turnLampOn(void);
float read_temp(void);
float read_avg_temp(int count);
/**
* Setup the Arduino
*/
void setup(void) {
  pinMode(ZXPIN, INPUT);
  // digitalPinToInterrupt may not work, so we choose directly the
  // interrupt number. It is Zero for pin 2 on Arduino UNO
  // attachInterrupt(digitalPinToInterrupt(ZXPIN), zxhandle, RISING);
  analogReference(EXTERNAL);
  attachInterrupt(0, zxhandle, RISING);
  // Setup output (triac) pin
  pinMode(TRIAC, OUTPUT);
  // Configure I2C to run in slave mode with the defined address
  Wire.begin(I2C_SLAVE_ADDR);
  // Configure the handler for received I2C data
  Wire.onReceive(i2c_received_handler);
  // Configure the handler for request of data via I2C
  Wire.onRequest(i2c_request_handler);

  // Setup the serial port to operate at 56.6kbps
  Serial.begin(56600);

  // Setup board
  pinMode(VENTILATOR_PIN, OUTPUT);
  //Setup components
  setupLamp(TRIAC);
}

/**
* Handles data requests received via the I2C bus
* It will immediately reply with the power stored
*/
void i2c_request_handler() {
  Wire.write((byte *)&value, sizeof(float));
}

/**
* Handles received data via the I2C bus.
* Data is stored in local variable power.
*/
void i2c_received_handler(int count) {
  cmd = (char)Wire.read();
  byte *fp;
  if (count != 4) return;
  fp = (byte *)&value;
  for (byte i = 0; i < count; ++i)
    fp[i] = (byte)Wire.read();
  if (cmd == 'a'){
    value = value+1;
  }
  else if (cmd == 'b'){
    value = value+2;
  }
}



void loop() {
  //changePwm(&pwm);
}