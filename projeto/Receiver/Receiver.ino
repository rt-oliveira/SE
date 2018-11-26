#include <IRremote.h>
#include "LedControl.h"
#include "Volei.h"
#include "Futebol.h"
#include "Basquete.h"

volatile IRrecv irrec(2);
volatile decode_results result;
LedControl lc = LedControl(10, 9, 8, 1);

int comando;
bool ja_roda = false;
Volei v(lc);
Futebol f(lc);
Basquete b(lc);
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
  attachInterrupt(digitalPinToInterrupt(2), LerIR, CHANGE);
}

void loop() {
  if (e != NULL && e->situacao_jogo != 0) {
    detachInterrupt(0);
    e->vitoria(lc);
  }
}

void LerIR() {
  sei();
  if (irrec.decode(&result) && !ja_roda) {
    ja_roda = true;
    comando = result.value;
    if (e == NULL) {
      switch (comando) {
        case 0xA25D:
          e = &v;
          break;
        case 0x629D:
          e = &f;
          break;
        case 0xE21D:
          e = &b;
          break;
      }
      e->iniciarJogo(lc);
    } else {
      e->Jogo(comando, lc);
    }
    irrec.resume();
    ja_roda = false;
  }
}
