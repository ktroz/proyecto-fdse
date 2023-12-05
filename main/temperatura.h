#define VAREF 2.7273

int vdiff1;
int vdiff2;


float read_temp(void);

float read_temp(void) {
  // Temperature of the first LM35
  int vplus1 = analogRead(0);
  int vminus1 = analogRead(1);
  // Temperature of the second LM35
  int vplus2 = analogRead(2);
  int vminus2 = analogRead(3);
  // Calculate the difference. when V+ is smaller than V- we have negative temp
  vdiff1 = vplus1 - vminus1;
  vdiff2 = vplus2 - vminus2;
  float temp = ((vdiff1+vdiff2)/2) * VAREF / 10.24f;
  return temp;
}