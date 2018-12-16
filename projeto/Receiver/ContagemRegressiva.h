#ifndef ContagemRegressiva_h
#define ContagemRegressiva_h

#include <Arduino.h>
#include "LedControl.h"
#include "Esporte.h"

class ContagemRegressiva: public Esporte {
  public:
    ContagemRegressiva(LedControl);
    void Jogo(bool&,int&,LedControl);
    void iniciarJogo();
    void mostrarTempo(LedControl);
    bool funcionando = true;
    bool iniciou = false;
  private:
    unsigned short tmin,tseg;
    unsigned short hrtc=0, mrtc=0, srtc=0;
    unsigned int tempototal;
    bool modomin = true, modoseg = false;
    // Procedimentos e Funções
    void iluminarLEDs();
    int CaptarNumero(int);
    void TZeroNIni(int,LedControl);
    void TDifZeroNIni(int,LedControl);
    void TrocaModo();
};

#endif
