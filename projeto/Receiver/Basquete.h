#ifndef Basquete_h
#define Basquete_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Basquete: public Esporte {
  public:
    Basquete(LedControl);
    void Jogo(bool&,int&,LedControl);
  private:
    unsigned int pontos[2],faltas_periodo[2];
    unsigned short periodo;
    // Procedimentos e Funções
    void Pontos(short,short,LedControl);
    void Falta(short);
    void iluminarLEDs();
};

#endif
