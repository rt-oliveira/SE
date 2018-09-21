/*Exercício do dia 19/09/2018
 * - Piscar o led a cada 1 segundo
 * - Ao apertar o botão, deixar o LED aceso para sempre
 */


#define PIN_LED 9
#define PIN_BOTAO 7

bool apertei=false;
int v;

void setup() {
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BOTAO,INPUT);  
}

void loop() {
  if(apertei)
    digitalWrite(PIN_LED,HIGH);
  else{
    v=digitalRead(PIN_BOTAO);
    if(!v)
      apertei=true;
    else{
      digitalWrite(PIN_LED,HIGH);
      delay(1000);
      digitalWrite(PIN_LED,LOW); 
      delay(1000);
    }
  }
}
