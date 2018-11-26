#ifndef Futebol_h
#define Futebol_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Futebol: public Esporte {
  public:
    Futebol(LedControl);
    void Jogo(int,LedControl);
    void iniciarJogo(LedControl);
    void mostrarTempo(LedControl);
  private:
    unsigned short gols[2],expulsos[2];
    /* 1 - 1º Tempo
     * 2 - 2º Tempo
     * 3 - Intervalo
     * 4 - Fim de Jogo
     */
    // Procedimentos e Funções
    void mudarTempo();
    void iluminarLEDs();
    void fimDeJogo();
    void gol(short,LedControl);
    void expulso(short);
    void tirarGol(short,LedControl);
};

#endif
