#include <Arduino.h>
#include "LedControl.h"
#include "Futebol.h"
#include <Wire.h>
#include <DS3231.h>

void Futebol::iluminarLEDs() {
  digitalWrite(54, expulsos[0] >= 1);
  digitalWrite(55, expulsos[0] >= 2);
  digitalWrite(56, expulsos[0] >= 3);
  digitalWrite(57, expulsos[0] >= 4);
  digitalWrite(62, expulsos[1] >= 1);
  digitalWrite(63, expulsos[1] >= 2);
  digitalWrite(64, expulsos[1] >= 3);
  digitalWrite(65, expulsos[1] >= 4);
}

void Futebol::Jogo(int comando) {
  switch (comando) {
    case 0x30CF: // 1
      if (tempo <= 2)  gol(0);
      break;
    case 0x18E7: // 2
      if (tempo <= 2)  tirarGol(0);
      break;
    case 0x7A85: // 3
      if (tempo <= 2)  expulso(0);
      break;
    case 0x10EF: // 4
      if (tempo <= 2)  gol(1);
      break;
    case 0x38C7: // 5
      if (tempo <= 2)  tirarGol(1);
      break;
    case 0x5AA5: // 6
      if (tempo <= 2)  expulso(1);
      break;
    case 0xC23D: // Play/Pause
      if (tempo <= 2)  mostrarTempo();
      break;
    case 0x906F: // Botão EQ
      mudarTempo();
      break;
  }
}

void Futebol::mudarTempo() {
  if (tempo == 1) {
    iluminarTds(HIGH);
    delay(300);
    iluminarTds(LOW);
    delay(300);
    tempo = 3;
  } else if (tempo == 3) {
    iluminarTds(HIGH);
    delay(300);
    iluminarTds(LOW);
    delay(300);
    tempo = 2;
    clock.setDateTime(2018, 1, 1, 1, 0, 0);
  } else if (tempo == 2) {
    tempo = 4;
    fimDeJogo();
  }
  iluminarLEDs();
}

void Futebol::tirarGol(short i) {
  if (gols[i] >= 1) {
    gols[i]--;
    (*lc).setDigit(0, (2 * i), gols[i] / 10, false);
    (*lc).setDigit(0, (2 * i) + 1, gols[i] % 10, false);
  }
}

void Futebol::gol(short i) {
  gols[i]++;
  for (int j = 0; j <= 5; j++) {
    if (i == 0) {
      iluminarEsq(HIGH);
      delay(200);
      iluminarEsq(LOW);
      delay(200);
    }
    else {
      iluminarDir(HIGH);
      delay(200);
      iluminarDir(LOW);
      delay(200);
    }
  }
  (*lc).setDigit(0, (2 * i), gols[i] / 10, false);
  (*lc).setDigit(0, (2 * i) + 1, gols[i] % 10, false);
  iluminarLEDs();
}

void Futebol::expulso(short i) {
  expulsos[i]++;
  if (expulsos[i] == 5)
    situacao_jogo = (2 - i);
  else
    iluminarLEDs();
}

void Futebol::fimDeJogo() {
  if (gols[0] > gols[1])
    situacao_jogo = 1;
  else if (gols[1] > gols[0])
    situacao_jogo = 2;
  else
    situacao_jogo = 3;
}

Futebol::Futebol(LedControl l) {
  lc=&l;
  gols[0] = 0;
  gols[1] = 0;
  expulsos[0] = 0;
  expulsos[1] = 0;
  situacao_jogo = 0;
  protocoloDisplay();
  iluminarLEDs();
}

void Futebol::mostrarTempo() {
  short mins = clock.getDateTime().minute;
  short secs;
  iluminarTds(HIGH);
  (*lc).setDigit(0, 0, mins / 10, false);
  (*lc).setDigit(0, 1, mins % 10, false);
  for (int j = 0; j <= 5; j++) {
    secs = clock.getDateTime().second;
    (*lc).setDigit(0, 2, secs / 10, false);
    (*lc).setDigit(0, 3, secs % 10, false);
    delay(1000);
  }
  iluminarTds(LOW);
  iluminarLEDs();
  (*lc).setDigit(0, 0, gols[0] / 10, false);
  (*lc).setDigit(0, 1, gols[0] % 10, false);
  (*lc).setDigit(0, 2, gols[1] / 10, false);
  (*lc).setDigit(0, 3, gols[1] % 10, false);
}
