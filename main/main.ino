#include <Wire.h>
#include "ventilador.h"

// Constants
#define I2C_SLAVE_ADDR 0x0A
//Components pin
#define VENTILATOR_PIN 9
// Digital 2 is Pin 2 in UNO
#define ZXPIN 2
// Digital 3 is Pin 3 in UNO
#define TRIAC 3
#define VAREF 2.7273

// Global variables
float time = 0;
float temp = 0;
volatile bool flag = false;
int pdelay = 0;
int inc = 1;
//Ventilator
int pwm = 0;

// Prototypes
void i2c_received_handler(int count);
void i2c_request_handler(int count);
void turnLampOn(void);
float read_temp(void);
float read_avg_temp(int count);
/**
* Setup the Arduino
*/
void setup(void){
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

	// Setup board led
    pinMode(VENTILATOR_PIN,OUTPUT);
}

/**
* Handles data requests received via the I2C bus
* It will immediately reply with the power stored
*/
void i2c_request_handler(){
	temp = read_temp();
	Wire.write((byte*) &temp, sizeof(float));
}

/**
* Handles received data via the I2C bus.
* Data is stored in local variable power.
*/
void i2c_received_handler(int count){
	float f;
	byte *fp;
	if(count != 4) return;
	fp = (byte*)&f;
	for(byte i = 0; i < count; ++i)
		fp[i] = (byte)Wire.read();
	time = f;
}

void turnLampOn(){
	// Turn sentinel LED on
	digitalWrite(13, HIGH);
	// Send a 10us pulse to the TRIAC
	digitalWrite(TRIAC, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIAC, LOW);
}

void zxhandle(){
	flag = true;
	// TRIAC automatically shuts down on ZX
	digitalWrite(TRIAC, LOW);
	digitalWrite(13, LOW);

	delayMicroseconds(time);

	if(time > 0) turnLampOn();
}

float read_temp(void){
	// The actual temperature
	int vplus = analogRead(0);
	// The reference temperature value, i.e. 0 C
	int vminus = analogRead(1);
	// Calculate the difference. when V+ is smaller than V- we have negative temp
	int vdiff = vplus - vminus;
	float temp = vdiff * VAREF / 10.24f;
return temp;
}

void loop(){
	pulsoVentilador(&pwm,VENTILATOR_PIN);
}