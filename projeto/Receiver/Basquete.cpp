#include <Arduino.h>
#include "LedControl.h"
#include "Basquete.h"

void Basquete::iluminarLEDs() {
  digitalWrite(54, faltas_periodo[0] >= 1);
  digitalWrite(55, faltas_periodo[0] >= 2);
  digitalWrite(56, faltas_periodo[0] >= 3);
  digitalWrite(57, faltas_periodo[0] >= 4);
  digitalWrite(62, faltas_periodo[1] >= 1);
  digitalWrite(63, faltas_periodo[1] >= 2);
  digitalWrite(64, faltas_periodo[1] >= 3);
  digitalWrite(65, faltas_periodo[1] >= 4);
}

void Basquete::Jogo(int comando) {
  switch (comando) {
    case 0x30CF: // 1
      Pontos(2, 0);
      break;
    case 0x18E7: // 2
      Pontos(3, 0);
      break;
    case 0x7A85: // 3
      Pontos(-2, 0);
      break;
    case 0x10EF: // 4
      Pontos(-3, 0);
      break;
    case 0x38C7: // 5
      Falta(0);
      break;
    case 0x5AA5: // 6
      Pontos(2, 1);
      break;
    case 0x42BD: // 7
      Pontos(3, 1);
      break;
    case 0x4AB5: // 8
      Pontos(-2, 1);
      break;
    case 0x52AD: // 9
      Pontos(-3, 1);
      break;
    case 0x6897: // 0
      Falta(1);
      break;
    case 0x906F: // Botão EQ
      if (periodo < 4) {
        periodo++;
        faltas_periodo[0] = 0;
        faltas_periodo[1] = 0;
        iluminarLEDs();
      }
      else {
        if (pontos[0] == pontos[1]) {
          periodo++;
          faltas_periodo[0] = 0;
          faltas_periodo[1] = 0;
          iluminarLEDs();
        }
        else if (pontos[0] > pontos[1])
          situacao_jogo = 1;
        else
          situacao_jogo = 2;
      }
      break;
  }
}

void Basquete::Pontos(short p, short i) {
  if (p >= 0)
    pontos[i] += p;
  else if (pontos[i] >= (-1 * p))
    pontos[i] += p;
  int t = pontos[i] % 100;
  (*lc).setDigit(0, (2 * i), t / 10, false);
  (*lc).setDigit(0, (2 * i) + 1, t % 10, false);
  digitalWrite(58 + (8 * i), pontos[i] >= 100);
}

void Basquete::Falta(short i) {
  if (faltas_periodo[i] >= 5) {
    for (int j = 0; j < 5; j++) {
      for (int k = (57 + (8 * i)); k >= (54 + (8 * i)); k--)
        digitalWrite(k, LOW);
      delay(200);
      for (int k = (57 + (8 * i)); k >= (54 + (8 * i)); k--)
        digitalWrite(k, HIGH);
      delay(200);
    }
  }
  else {
    faltas_periodo[i]++;
    iluminarLEDs();
  }
}


Basquete::Basquete(LedControl l) {
  lc=&l;
  pontos[0] = 0;
  pontos[1] = 0;
  faltas_periodo[0] = 0;
  faltas_periodo[1] = 0;
  situacao_jogo = 0;
  periodo = 1;
  protocoloDisplay();
  iluminarLEDs();
}
