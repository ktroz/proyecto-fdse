#include <Wire.h>

#define I2C_SLAVE_ADDR 0x0A
//
byte[5] buffer;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
    // Configure I2C to run in slave mode with the defined address
    Wire.begin(I2C_SLAVE_ADDR);
    // Configure the handler for received I2C data
    Wire.onReceive(i2c_received_handler);
    // Configure the handler for request of data via I2C
    Wire.onRequest(i2c_request_handler);     
    // Setup the serial port to operate at 56.6kbps
    Serial.begin(56600);
}

void i2c_request_handler(){
    Wire.write((byte*) &byte[1], sizeof(float));
}

void i2c_received_handler(int count){
    Wire.readBytes(buffer,5);
    Serial.println("%c,%f",buffer[0],&buffer[1]);
}