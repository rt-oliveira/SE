#define PIN_BOTAO 7

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(PIN_BOTAO,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val=digitalRead(PIN_BOTAO);
  digitalWrite(LED_BUILTIN,!val);  

}
