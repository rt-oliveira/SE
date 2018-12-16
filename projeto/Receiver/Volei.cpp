#include <Arduino.h>
#include "LedControl.h"
#include "Volei.h"

void Volei::iluminarLEDs() {
  digitalWrite(54, sets[0] >= 1);
  digitalWrite(55, sets[0] >= 2);
  digitalWrite(56, sets[0] >= 3);
  digitalWrite(62, sets[1] >= 1);
  digitalWrite(63, sets[1] >= 2);
  digitalWrite(64, sets[1] >= 3);
}

bool Volei::ganhouSetEqUm() {
  pontos_min = pontos1 >= p_set;
  diferenca = (short)pontos1 - (short)pontos2 >= 2;
  return pontos_min && diferenca;
}

bool Volei::ganhouSetEqDois() {
  pontos_min = pontos2 >= p_set;
  diferenca = (short)pontos2 - (short)pontos1 >= 2;
  return pontos_min && diferenca;
}

void Volei::ganhouJogo(short i,LedControl lc) {
  if (sets[i] == 3)
    situacao_jogo = i + 1;
  else {
    if (sets[0] + sets[1] == 4)
      p_set = 15;
    pontos1 = 0;
    pontos2 = 0;
    digitalWrite(58, LOW);
    digitalWrite(66, LOW);
    zerarDisplays(lc);
    iluminarLEDs();
  }
}

void Volei::Jogo(bool& t, int& comando,LedControl lc) {
  if (t) {
    switch (comando) {
      case 0x30CF:
        pontoUm(1,lc);
        break;
      case 0x18E7:
        pontoUm(-1,lc);
        break;
      case 0x7A85:
        pontoDois(1,lc);
        break;
      case 0x10EF:
        pontoDois(-1,lc);
        break;
    }
    t = false;
    comando = 0;
  }
}

void Volei::pontoUm(short val,LedControl lc) {
  if (val == 1) {
    pontos1++;
    lc.setDigit(0, 0, pontos1 / 10, false);
    lc.setDigit(0, 1, pontos1 % 10, false);
    digitalWrite(58, HIGH);
    digitalWrite(66, LOW);
    if (ganhouSetEqUm()) {
      delay(4000);
      sets[0]++;
      ganhouJogo(0,lc);
    }
    else
      iluminarLEDs();
  } else {
    if (pontos1 >= 1) {
      pontos1--;
      lc.setDigit(0, 0, pontos1 / 10, false);
      lc.setDigit(0, 1, pontos1 % 10, false);
      digitalWrite(58, LOW);
      digitalWrite(66, LOW);
    }
  }
}

void Volei::pontoDois(short val,LedControl lc) {
  if (val == 1) {
    pontos2++;
    lc.setDigit(0, 2, pontos2 / 10, false);
    lc.setDigit(0, 3, pontos2 % 10, false);
    digitalWrite(58, LOW);
    digitalWrite(66, HIGH);
    if (ganhouSetEqDois()) {
      delay(4000);
      sets[1]++;
      ganhouJogo(1,lc);
    }
    else
      iluminarLEDs();
  } else {
    if (pontos2 >= 1) {
      pontos2--;
      lc.setDigit(0, 2, pontos2 / 10, false);
      lc.setDigit(0, 3, pontos2 % 10, false);
      digitalWrite(58, LOW);
      digitalWrite(66, LOW);
    }
  }
}

Volei::Volei(LedControl l) {
  sets[0] = 0;
  sets[1] = 0;
  pontos1 = 0;
  pontos2 = 0;
  p_set = 25;
  situacao_jogo = 0;
  protocoloDisplay(l);
  Esporte::iniciarJogo(l);
}
