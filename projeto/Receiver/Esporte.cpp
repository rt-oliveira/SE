#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

void Esporte::zerarDisplays() {
  (*lc).setDigit(0, 0, 0, false);
  (*lc).setDigit(0, 1, 0, false);
  (*lc).setDigit(0, 2, 0, false);
  (*lc).setDigit(0, 3, 0, false);
}

void Esporte::iniciarJogo() {
  iluminarTds(HIGH);
  (*lc).clearDisplay(0);
  delay(500);
  (*lc).setDigit(0, 0, 8, false);
  (*lc).setDigit(0, 1, 8, false);
  (*lc).setDigit(0, 2, 8, false);
  (*lc).setDigit(0, 3, 8, false);
  delay(1000);
  zerarDisplays();
  iluminarTds(LOW);
  tempo = 1;
  clock.begin();
  clock.setDateTime(2018, 1, 1, 0, 0, 0);
}

void Esporte::protocoloDisplay() {
  (*lc).shutdown(0, false); // Habilita o display
  (*lc).setIntensity(0, 10); // Luminosidade (0 a 15)
  zerarDisplays();
}

void Esporte::vitoria() {
  iluminarTds(LOW);
  if (situacao_jogo == 1) {
    (*lc).clearDisplay(0);
    while (1) {
      iluminarEsq(HIGH);
      (*lc).setDigit(0, 0, 8, false);
      (*lc).setDigit(0, 1, 8, false);
      delay(1000);
      iluminarEsq(LOW);
      (*lc).clearDisplay(0);
      delay(1000);
    }
  } else if (situacao_jogo == 2) {
    (*lc).clearDisplay(0);
    while (1) {
      iluminarDir(HIGH);
      (*lc).setDigit(0, 2, 8, false);
      (*lc).setDigit(0, 3, 8, false);
      delay(1000);
      iluminarDir(LOW);
      (*lc).clearDisplay(0);
      delay(1000);
    }
  } else {
    iluminarTds(LOW);
    delay(1000);
    iluminarTds(HIGH);
    delay(1000);
  }
}

void Esporte::iluminarTds(int v) {
  for (int i = 58; i >= 54; i--)
    digitalWrite(i, v);
  for (int i = 66; i >= 62; i--)
    digitalWrite(i, v);
}

void Esporte::iluminarEsq(int v) {
  for (int i = 58; i >= 54; i--)
    digitalWrite(i, v);
}

void Esporte::iluminarDir(int v) {
  for (int i = 66; i >= 62; i--)
    digitalWrite(i, v);
}
