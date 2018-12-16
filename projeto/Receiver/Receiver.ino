#include <IRremote.h>
#include "LedControl.h"
#include "Volei.h"
#include "Futebol.h"
#include "Basquete.h"
#include "Cronometro.h"
#include "ContagemRegressiva.h"

volatile IRrecv irrec(2);
volatile decode_results result;
LedControl lc = LedControl(10, 9, 8, 1);

int comando;
bool tem_comando;
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
  irrec.blink13(true);
  tem_comando = false;
  EICRB = (1 << ISC41) || (1 << ISC40);
  EIMSK |= 1 << INT4;
}

void loop() {
  if (e == NULL) {
    e = Inicializacao();
  }
  else {
    if (e->situacao_jogo != 0) {
      e->vitoria(lc);
    } else {
      e->Jogo(tem_comando, comando, lc);
    }
  }
}

ISR(INT4_vect) {
  sei();
  if (!tem_comando) {
    if (irrec.decode(&result)) {
      tem_comando = true;
      comando = result.value;
      irrec.resume();
    }
  }
}

Esporte* Inicializacao() {
  if (tem_comando) {
    switch (comando) {
      case 0xA25D: // CH-
        return new Volei(lc);
      case 0x629D: // CH
        return new Futebol(lc);
      case 0xE21D: // CH+
        return new Basquete(lc);
      case 0xC23D: // Play/Pause
        return new Cronometro(lc);
      case 0x906F: // EQ
        return new ContagemRegressiva(lc);
    }
    tem_comando = false;
  }
  else {
    return NULL;
  }
}
