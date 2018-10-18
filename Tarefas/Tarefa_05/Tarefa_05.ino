#include <Servo.h>

Servo s;
int v, estado_anterior = 1;
float vx = 0, vy = 0;
int soma;
bool on_off = false;
unsigned long c;

ISR(TIMER2_OVF_vect)        // rotina de interrupção
{
  if (on_off) {
    c++;
  }
}

void testaOnOff() {
  v = PIND >> 7; // Lendo o valor que está mapeado para o botão
  if (!v) {
    if (estado_anterior) {
      if (on_off) {
        if (c >= 125000) {
          on_off = !on_off;
          c = 0;
        }
      }
      else {
        on_off = !on_off;
      }
    }
  }
  estado_anterior = v;
}

int lerAnalogico(int porta) {
  ADMUX   = porta;              // para indicar porta analógica que será usada
  ADMUX  |= (1 << REFS0);       // usa a voltagem pinada como referência
  ADCSRA |= (1 << ADEN);        // habilita o conversor analógico digital
  ADCSRA |= (1 << ADSC);        // começa a conversão
  while (ADCSRA & (1 << ADSC)); // espera terminar a conversão

  int v = ADCL;                 // pega os bits menos significativos
  v = (ADCH << 8) + v;          // soma com os bits mais significativos
  return v;
}

void setup ()
{
  cli();
  DDRD &= ~(1 << 7); // Isto signfica porta digital 7 servindo como entrada
  DDRB |= 1 << 0; // Isto significa porta digital 8 servindo como saída
  TCCR2A = 0b0;
  TCCR2B = 1 << CS21; // Modo Normal e Prescaler em 8
  TIMSK2 = 0b1;       // Habilita interrupção por overflow
  TCNT2 = 0;          // Reseta o TCNT2
  s.attach(4);
  s.write(0);
  sei();
  c = 0;
}

void loop()
{
  testaOnOff();
  if (on_off) {
    vx = lerAnalogico(5);
    vy = lerAnalogico(4);
    soma = map(vx + vy, 0, 2048, 0, 180);
    s.write(soma);
    if (soma >= 90)
      PORTB |= 1 << 0; // Comando para fazer acender o led
    else
      PORTB &= ~(1 << 0); // Comando para deixar o led apagado
  }
}
