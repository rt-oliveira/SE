#ifndef Volei_h
#define Volei_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Volei: public Esporte {
  public:
    Volei(LedControl);
    void Jogo(int);
  private:
    unsigned short sets[2];
    unsigned short pontos1, pontos2;
    bool pontos_min, diferenca;
    unsigned short p_set;
    // Procedimentos e Funções
    void iluminarLEDs();
    bool ganhouSetEqUm();
    bool ganhouSetEqDois();
    void ganhouJogo(short);
    void pontoMaisTime1();
    void pontoMaisTime2();
    void pontoMenosTime1();
    void pontoMenosTime2();
};

#endif
