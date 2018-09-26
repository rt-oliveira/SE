/*
 * Exercício 3 - de 24/09/2018
 * É igual ao exercício 2, porém é versão reativa, pois a referida
 * não é reativa, pois tem chamada bloqueante.
 */

#define PIN_LED 9
#define PIN_BOTAO 7

bool apertei=false;
int v;
unsigned long tempo,tempoanterior;
int estado;

void setup() {
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BOTAO,INPUT);
  tempoanterior=0; 
  estado=LOW; 
}

void loop() {
  if(apertei)
    digitalWrite(PIN_LED,HIGH);
  else{
    v=digitalRead(PIN_BOTAO);
    if(!v)
      apertei=true;
    else{
      tempo=millis();
      if((tempo-tempoanterior)>=1000){
        tempoanterior=tempo;
        estado=!estado;
        digitalWrite(PIN_LED,estado);
      }
    }
  }
}
