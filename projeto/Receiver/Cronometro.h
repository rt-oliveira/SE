#ifndef Cronometro_h
#define Cronometro_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Cronometro: public Esporte {
  public:
    Cronometro(LedControl);
    void Jogo(bool&,int&,LedControl);
    void iniciarJogo(LedControl);
    bool funcionando = true;
  private:
    unsigned short horas,minutos,segundos; 
    // Procedimentos e Funções
    void iluminarLEDs();
    void mostrarTempo(LedControl);
};

#endif
