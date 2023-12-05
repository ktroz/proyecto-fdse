// Definiendo rango de temperatura para activar ventilador
const float valueLOW = 25.0;
const float valueHIGH= 35.0;

// bandera para verificar el estado del ventilador
bool state = false; 

//Temperatura recibida 
float GetTemperature()
{
  return ;  
}

void setup() {
  pinMode(9, OUTPUT);  
}
 
void loop(){
  float currentTemperature = GetTemperature();

  if(state == false && currentTemperature > valueHIGH)
  {
      state = true;
      digitalWrite(9, HIGH);   // encender ventilador
  }
  if(state == true && currentTemperature < valueLOW)
  {
      state = false;
      digitalWrite(9, LOW);   // apagar ventilador
  }

 }