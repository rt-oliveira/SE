#ifndef Futebol_h
#define Futebol_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class Futebol: public Esporte {
  public:
    Futebol(LedControl);
    void Jogo(bool&,int&,LedControl);
    void iniciarJogo();
  private:
    unsigned short gols[2],expulsos[2];
    /* 1 - 1º Tempo
     * 2 - 2º Tempo
     * 3 - Intervalo
     * 4 - Fim de Jogo
     */
    // Procedimentos e Funções
    void mostrarTempo(LedControl);
    void mudarTempo();
    void iluminarLEDs();
    void fimDeJogo();
    void gol(short,LedControl);
    void expulso(short);
    void tirarGol(short,LedControl);
};

#endif
