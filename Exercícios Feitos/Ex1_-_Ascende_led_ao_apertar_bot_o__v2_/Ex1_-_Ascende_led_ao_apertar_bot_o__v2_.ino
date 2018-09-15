#define PIN_BOTAO 7
#define PIN_LED 12

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BOTAO,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val=digitalRead(PIN_BOTAO);
  digitalWrite(PIN_LED,!val);  

}
