int TRIAC;
extern float triacDelay;
//prototypes

void turnLampOn();
void zxhandle();
void setupLamp(int t);

void setupLamp(int t){
  TRIAC = t;
}
void changeDelayTime(float t){
  triacDelay = t;
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
		// TRIAC automatically shuts down on ZX
	digitalWrite(TRIAC, LOW);
	digitalWrite(13, LOW);

	delayMicroseconds(triacDelay);

	if(triacDelay > 0) turnLampOn();
}