#ifndef Volei_h
#define Volei_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Volei: public Esporte {
  public:
    Volei(LedControl);
    void Jogo(int,LedControl);
  private:
    unsigned short sets[2];
    unsigned short pontos1, pontos2;
    bool pontos_min, diferenca;
    unsigned short p_set;
    // Procedimentos e Funções
    void iluminarLEDs();
    bool ganhouSetEqUm();
    bool ganhouSetEqDois();
    void ganhouJogo(short,LedControl);
    void pontoMaisTime1(LedControl);
    void pontoMaisTime2(LedControl);
    void pontoMenosTime1(LedControl);
    void pontoMenosTime2(LedControl);
};

#endif
