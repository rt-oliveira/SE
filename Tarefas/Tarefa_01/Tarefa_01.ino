#define PIN_LED 9
#define PIN_BOTAO1 4
#define PIN_BOTAO2 7

int v1,v2;
int est_b1,est_b2;
unsigned long inst_b1,inst_b2,tempo;
unsigned int tempo_piscar;
int estado;
bool apertou1=false,apertou2=false;

void setup() {
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BOTAO1,INPUT);
  pinMode(PIN_BOTAO2,INPUT);
  
  est_b1=1;
  est_b2=1; 
  tempo_piscar=1000;
  estado=LOW;
  tempo=0;
}

void loop() {
  v1=digitalRead(PIN_BOTAO1);
  if(!v1){
    if(est_b1){
      if(tempo_piscar>=40)
        tempo_piscar-=20;
      apertou1=true;
      inst_b1=millis();
    }
  }
  v2=digitalRead(PIN_BOTAO2);
  if(!v2){
    if(est_b2){
      tempo_piscar+=20;
      apertou2=true;
      inst_b2=millis();
    }
  }
  if(apertou1 && apertou2){
    if(inst_b1>inst_b2){
      if((inst_b1-inst_b2)<=500)
        while(1);
    }else{
      if((inst_b2-inst_b1)<=500)
        while(1);
    }
  }
  est_b1=v1;
  est_b2=v2;
  if((millis()-tempo)>=tempo_piscar){
    tempo=millis();
    estado=!estado;
    digitalWrite(PIN_LED,estado);
  }
}
