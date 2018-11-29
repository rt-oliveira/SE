#include <IRremote.h>
#include "LedControl.h"
#include "Volei.h"
#include "Futebol.h"
#include "Basquete.h"

volatile IRrecv irrec(2);
volatile decode_results result;
LedControl lc = LedControl(10, 9, 8, 1);

int comando;
volatile bool tem_comando;
int pin_int;
Esporte* e = NULL;

void setup() {
  // Equipe 1
  pinMode(54, OUTPUT);
  pinMode(55, OUTPUT);
  pinMode(56, OUTPUT);
  pinMode(57, OUTPUT);
  pinMode(58, OUTPUT);
  // Equipe 2
  pinMode(62, OUTPUT);
  pinMode(63, OUTPUT);
  pinMode(64, OUTPUT);
  pinMode(65, OUTPUT);
  pinMode(66, OUTPUT);
  irrec.enableIRIn();
  tem_comando = false;
  pin_int = digitalPinToInterrupt(2);
  attachInterrupt(pin_int, LerIR, RISING);
}

void loop() {
  if (e != NULL && e->situacao_jogo != 0) {
    detachInterrupt(0);
    e->vitoria();
  }
  else {
    if (tem_comando) {
      detachInterrupt(pin_int);
      comando = result.value;
      if (e == NULL) {
        switch (comando) {
          case 0xA25D: // CH-
            e = new Volei(lc);
            break;
          case 0x629D: // CH
            e = new Futebol(lc);
            break;
          case 0xE21D: // CH+
            e = new Basquete(lc);
            break;
        }
        e->iniciarJogo();
      } else {
        e->Jogo(comando);
      }
      tem_comando = false;
      attachInterrupt(pin_int, LerIR, RISING);
    }
  }
}

void LerIR() {
  if (!tem_comando) {
    if (irrec.decode(&result)) {
      tem_comando = true;
      irrec.resume();
    }
  }
}
