#ifndef Esporte_h
#define Esporte_h

#include <Arduino.h>
#include "LedControl.h"
#include <Wire.h>
#include <DS3231.h>

class Esporte {
  public:
    unsigned short situacao_jogo;
    /* 0 significa jogo acontecendo.
      Diferente de 0 significa jogo finalizado:
      1 - Vitória da Equipe 1
      2 - Vitória da Equipe 2
      3 - Empate */
    void iniciarJogo();
    void vitoria();
    virtual void Jogo(int);
  protected:
    unsigned short tempo;
    DS3231 clock;
    RTCDateTime dt;
    LedControl* lc;
    void zerarDisplays();
    void protocoloDisplay();
    void iluminarTds(int);
    void iluminarEsq(int);
    void iluminarDir(int);
};

#endif