int counter = 0;

void pulsoVentilador(int * pwm, int pinNumber);
// PWM is the value between 0 and 100
void pulsoVentilador(int * pwm, int pinNumber){
  while(counter < 255){
    if(counter < *pwm){
      digitalWrite(pinNumber,HIGH);
    }else{
      digitalWrite(pinNumber,LOW);
    }
    counter++;
  }
  counter = 0;
}


