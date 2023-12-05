float temp, desiredTemp;
float tempPreviousError = 0, tempError = 0;
float timePassed, time, previousTime;

//Proportional
float kp=8;
//Integral
float ki=1;
//derivative
float kd=100;

//Error element of each correction type
float PID_p = 0, PID_i = 0, PID_d = 0, PID_total = 0;
//PIN
int PIN;
void setupPID(int p){
    PIN = p;
    time = millis();
}
void setTemp(float desTemp){
  desiredTemp = desTemp;
}
void executePid(){   
    temp = read_temp();  
    //Proportional
    tempError = desiredTemp - temp;   
    PID_p = kp * tempError;

    //Calculate the integral part in +-3
    if(-3 < tempError && tempError < 3)
    {
      PID_i = PID_i + (ki * tempError);
    }
    //We calculate the speed change with derivative part
    previousTime = time;
    time = millis();
    timePassed = (time-previousTime)/1000;
    //Calculating derivative part
    PID_d = kd*((tempError-tempPreviousError)/timePassed);
    PID_total = PID_d + PID_p + PID_i;
    if(PID_total < 0)
    {    PID_total = 0;    }
    if(PID_total > 255)  
    {    PID_total = 255;  }
    lampPower((int)(PID_total*100/255));

    tempPreviousError = tempError;
    
}

