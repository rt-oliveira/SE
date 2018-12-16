#include <Arduino.h>
#include "LedControl.h"
#include "ContagemRegressiva.h"
#include <Wire.h>
#include <DS3231.h>

void ContagemRegressiva::Jogo(bool& r, int& comando, LedControl lc) {
  if (r) {
    int t = CaptarNumero(comando);
    if (!iniciou) {
      if (t == 0) {
        TZeroNIni(t, lc);
      } else if (t > 0) {
        TDifZeroNIni(t, lc);
      } else if (t == -3) {
        TrocaModo();
      }
    } else {
      switch (t) {
        case 1: // Parar contador
          funcionando = false;
          dt = clock.getDateTime();
          hrtc = dt.hour;
          mrtc = dt.minute;
          srtc = dt.second;
          break;
        case 2: // Retomar contador
          if (!funcionando) {
            funcionando = true;
            clock.setDateTime(2018, 1, 1, hrtc, mrtc, srtc);
          }
          break;
      }
    }
    r = false;
    comando = 0;
  } else {
    if (funcionando)
      mostrarTempo(lc);
  }
}

void ContagemRegressiva::TrocaModo() {
  if (modomin) {
    modomin = false;
    modoseg = true;
    iluminarEsq(HIGH);
    delay(300);
    iluminarEsq(LOW);
    delay(300);
  }
  else {
    modoseg = false;
    iniciou = true;
    iluminarDir(HIGH);
    delay(300);
    iluminarDir(LOW);
    delay(300);
    tempototal = (tmin * 60) + tseg;
    clock.setDateTime(2018, 1, 1, 0, 0, 0);
  }
}

void ContagemRegressiva::TZeroNIni(int t, LedControl lc) {
  if (modomin) {
    if (tmin < 10) {
      tmin = (tmin * 10) + t;
      mostrarTempo(lc);
    }
  } else {
    if (tseg < 10) {
      tseg = (tseg * 10) + t;
      mostrarTempo(lc);
    }
  }
}

void ContagemRegressiva::TDifZeroNIni(int t, LedControl lc) {
  if (modomin) {
    if (tmin < 10) {
      tmin = (tmin * 10) + t;
      mostrarTempo(lc);
    }
  } else {
    if (tseg == 0) {
      if (t < 6) {
        tseg = (tseg * 10) + t;
        mostrarTempo(lc);
      }
    } else {
      if (tseg < 10) {
        tseg = (tseg * 10) + t;
        mostrarTempo(lc);
      }
    }
  }
}

ContagemRegressiva::ContagemRegressiva(LedControl l) {
  tmin = 0;
  tseg = 0;
  situacao_jogo = 0;
  protocoloDisplay(l);
  iluminarTds(LOW);
  Esporte::iniciarJogo(l);
}

void ContagemRegressiva::mostrarTempo(LedControl lc) {
  if (!iniciou) {
    lc.setDigit(0, 0, tmin / 10, false);
    lc.setDigit(0, 1, tmin % 10, false);
    lc.setDigit(0, 2, tseg / 10, false);
    lc.setDigit(0, 3, tseg % 10, false);
  }
  else {
    dt = clock.getDateTime();
    hrtc = dt.hour;
    mrtc = dt.minute;
    srtc = dt.second;
    int tempodecorrido = (hrtc * 3600) + (mrtc * 60) + srtc;
    int temporestante = tempototal - tempodecorrido;
    int min_restante = temporestante / 60;
    int sec_restante = temporestante % 60;
    lc.setDigit(0, 0, min_restante  / 10, false);
    lc.setDigit(0, 1, min_restante  % 10, false);
    lc.setDigit(0, 2, sec_restante / 10, false);
    lc.setDigit(0, 3, sec_restante % 10, false);
    if (tempodecorrido == tempototal) {
      situacao_jogo = 3;
    }
  }
}

int ContagemRegressiva::CaptarNumero(int comando) {
  switch (comando) {
    case 0x30CF: // 1
      return 1;
    case 0x18E7: // 2
      return 2;
    case 0x7A85: // 3
      return 3;
    case 0x10EF: // 4
      return 4;
    case 0x38C7: // 5
      return 5;
    case 0x5AA5: // 6
      return 6;
    case 0x42BD: // 7
      return 7;
    case 0x4AB5: // 8
      return 8;
    case 0x52AD: // 9
      return 9;
    case 0x6897: // 0
      return 0;
    case 0x02FD: // Next
      return -3;
    default:     // Nada apertado
      return -1;
  }
}
