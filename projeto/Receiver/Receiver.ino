#include <IRremote.h>
#include "LedControl.h"

IRrecv irrec(11);
decode_results result;

int comando;
unsigned short sets[2], pontos1, pontos2;
bool pontos_min, diferenca;
unsigned short p_set, situacao_jogo;
/* 0 significa jogo acontecendo.
   Diferente de 0 significa jogo finalizado:
   1 - Vitória da Equipe 1
   2 - Vitória da Equipe 2*/
// Ordem: DIN, CLK e LOAD. Do LedControl.
LedControl lc = LedControl(9, 8, 7, 1);

void configurarPortas() {
  // Equipe 1
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  // Equipe 2
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(4, OUTPUT);
}

void setup() {
  configurarPortas();
  sets[0] = 0;
  sets[1] = 0;
  pontos1 = 0;
  pontos2 = 0;
  p_set = 25;
  situacao_jogo = 0;
  lc.shutdown(0, false); // Habilita o display
  lc.setIntensity(0, 10); // Luminosidade (0 a 15)
  zerarDisplays();
  iluminarLEDs();
  irrec.enableIRIn();
}

void loop() {
  if (situacao_jogo == 0) {
    if (irrec.decode(&result)) {
      comando = result.value;
      switch (comando) {
        case 0x30CF:
          pontos1++;
          lc.setDigit(0, 0, pontos1 / 10, false);
          lc.setDigit(0, 1, pontos1 % 10, false);
          digitalWrite(5, HIGH);
          digitalWrite(4, LOW);
          if (ganhouSetEqUm()) {
            delay(4000);
            sets[0]++;
            ganhouJogo(0);
          }
          else
            iluminarLEDs();
          break;
        case 0x18E7:
          if (pontos1 >= 1) {
            pontos1--;
            lc.setDigit(0, 0, pontos1 / 10, false);
            lc.setDigit(0, 1, pontos1 % 10, false);
            digitalWrite(5, LOW);
            digitalWrite(4, LOW);
          }
          break;
        case 0x7A85:
          pontos2++;
          lc.setDigit(0, 2, pontos2 / 10, false);
          lc.setDigit(0, 3, pontos2 % 10, false);
          digitalWrite(5, LOW);
          digitalWrite(4, HIGH);
          if (ganhouSetEqDois()) {
            delay(4000);
            sets[1]++;
            ganhouJogo(1);
          }
          else
            iluminarLEDs();
          break;
        case 0x10EF:
          if (pontos2 >= 1) {
            pontos2--;
            lc.setDigit(0, 2, pontos2 / 10, false);
            lc.setDigit(0, 3, pontos2 % 10, false);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
          }
          break;
      }
      irrec.resume();
    }
  } else {
    for (int i = 19; i >= 14; i--)
      digitalWrite(i, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    vitoria();
  }
}

bool ganhouSetEqUm() {
  pontos_min = pontos1 >= p_set;
  diferenca = (short)pontos1 - (short)pontos2 >= 2;
  return pontos_min && diferenca;
}

bool ganhouSetEqDois() {
  pontos_min = pontos2 >= p_set;
  diferenca = (short)pontos2 - (short)pontos1 >= 2;
  return pontos_min && diferenca;
}

void ganhouJogo(short i) {
  if (sets[i] == 3)
    situacao_jogo = i + 1;
  else {
    if (sets[0] + sets[1] == 4)
      p_set = 15;
    pontos1 = 0;
    pontos2 = 0;
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    zerarDisplays();
    iluminarLEDs();
  }
}

void vitoria() {
  if (situacao_jogo == 1) {
    lc.clearDisplay(0);
    while (1) {
      for (int i = 16; i >= 14; i--)
        digitalWrite(i, HIGH);
      digitalWrite(5, HIGH);
      lc.setDigit(0, 0, 8, false);
      lc.setDigit(0, 1, 8, false);
      delay(1000);
      for (int i = 16; i >= 14; i--)
        digitalWrite(i, LOW);
      digitalWrite(5, LOW);
      lc.clearDisplay(0);
      delay(1000);
    }
  } else {
    lc.clearDisplay(0);
    while (1) {
      for (int i = 19; i >= 17; i--)
        digitalWrite(i, HIGH);
      digitalWrite(4, HIGH);
      lc.setDigit(0, 2, 8, false);
      lc.setDigit(0, 3, 8, false);
      delay(1000);
      for (int i = 19; i >= 17; i--)
        digitalWrite(i, LOW);
      digitalWrite(4, LOW);
      lc.clearDisplay(0);
      delay(1000);
    }
  }
}

void zerarDisplays() {
  lc.setDigit(0, 0, 0, false);
  lc.setDigit(0, 1, 0, false);
  lc.setDigit(0, 2, 0, false);
  lc.setDigit(0, 3, 0, false);
}

void iluminarLEDs() {
  digitalWrite(14, sets[0] >= 1);
  digitalWrite(15, sets[0] >= 2);
  digitalWrite(16, sets[0] >= 3);
  digitalWrite(19, sets[1] >= 1);
  digitalWrite(18, sets[1] >= 2);
  digitalWrite(17, sets[1] >= 3);
}
