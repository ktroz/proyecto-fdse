int FANPIN = 9;
int PUMPPIN = 10;
void changePwm(float percentage);
changePumpPwm(float percentage);
// PWM is the value between 0 and 100
void changePwm(float percentage){
  analogWrite(FANPIN,(int)(percentage*255/100));
}
void changePumpPwm(float percentage){
  analogWrite(PUMPPIN,(int)(percentage*255/100));
}


