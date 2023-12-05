int FANPIN = 9;
void changePwm(int * pwm);
// PWM is the value between 0 and 100
void changePwm(int * pwm){
  analogWrite(FANPIN,*pwm);
}


