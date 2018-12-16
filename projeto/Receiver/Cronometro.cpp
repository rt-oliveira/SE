#include <Arduino.h>
#include "LedControl.h"
#include "Cronometro.h"
#include <Wire.h>
#include <DS3231.h>

void Cronometro::iluminarLEDs() {
  digitalWrite(54, horas >= 1);
  digitalWrite(55, horas >= 2);
  digitalWrite(56, horas >= 3);
  digitalWrite(57, horas >= 4);
  digitalWrite(65, horas >= 5);
  digitalWrite(64, horas >= 6);
  digitalWrite(63, horas >= 7);
  digitalWrite(62, horas >= 8);
  digitalWrite(58, horas >= 9);
  digitalWrite(66, horas >= 10);
}

void Cronometro::Jogo(bool& t, int& comando,LedControl lc) {
  if (t) {
    switch (comando) {
      case 0x30CF: // Parar cronômetro
        funcionando = false;
        break;
      case 0x18E7: // Retomar cronômetro
        if (!funcionando) {
          funcionando = true;
          clock.setDateTime(2018, 1, 1, horas, minutos, segundos);
        }
        break;
      case 0x7A85: // Resetar cronômetro
        clock.setDateTime(2018, 1, 1, 0, 0, 0);
        mostrarTempo(lc);
        break;
    }
    t = false;
    comando = 0;
  }
  else {
    if (funcionando)
      mostrarTempo(lc);
  }
}

Cronometro::Cronometro(LedControl l) {
  situacao_jogo = 0;
  protocoloDisplay(l);
  iluminarLEDs();
  Esporte::iniciarJogo(l);
}

void Cronometro::mostrarTempo(LedControl lc) {
  dt = clock.getDateTime();
  horas    = dt.hour;
  minutos  = dt.minute;
  segundos = dt.second;
  lc.setDigit(0, 0, minutos  / 10, false);
  lc.setDigit(0, 1, minutos  % 10, false);
  lc.setDigit(0, 2, segundos / 10, false);
  lc.setDigit(0, 3, segundos % 10, false);
  iluminarLEDs();
}
