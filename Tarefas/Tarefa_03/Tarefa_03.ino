#include <Servo.h>

/* Tarefa 03 - Construir uma aplicação que tenha dois sensores,
 *  dois atuadores e contato direto por GPIO e uso de registradores
 *  para conversão e comparação analógica.
 *  
 *  Componentes da aplicação: há um led, um botão, um joystick
 *  e um servo motor.
 *  
 *  Funcionamento da aplicação:  
 *  - O botão tem a função de ser o "on/off" da aplicação. 
 *  A aplicação começa desligada, ao apertar o botão, 
 *  e somente ao pressionar, troca o estado da aplicação 
 *  (se estava "ligada", "desliga", e vice-versa).
 *  
 * - Ao "ligar a aplicação", o servo motor girará de acordo com o
 * joystick, isto é, de acordo com o tanto que o joystick está inclinado
 * (em x e em y), o servo motor rotacionará mais ou menos, usando uma
 * amplitude de 0 a 180 graus de rotação.
 * 
 * - Além da rotação do servo motor, o led pode ficar aceso ou não.
 * Caso o ângulo de rotação que será feito no servo motor for maior que 
 * 90 graus, o led se acenderá, caso contrário, ele fica apagado.
 * 
 * - Continua funcionando como foi dito nos dois itens anteriores até
 * apertar novamente o botão, "desligando" a aplicação.
 */

Servo s;
int v,estado_anterior=1;
float vx=0,vy=0;
int soma;
bool on_off=false;

void testaOnOff(){
  v=PIND>>7; // Lendo o valor que está mapeado para o botão
  if(!v){
    if(estado_anterior)
      on_off=!on_off;
  }
  estado_anterior=v;
}

int lerAnalogico(int porta){
  ADMUX   = porta;              // para indicar porta analógica que será usada   
  ADMUX  |= (1 << REFS0);       // usa a voltagem pinada como referência
  ADCSRA |= (1 << ADEN);        // habilita o conversor analógico digital
  ADCSRA |= (1 << ADSC);        // começa a conversão
  while(ADCSRA & (1 << ADSC));  // espera terminar a conversão

  int v = ADCL;                 // pega os bits menos significativos
  v = (ADCH << 8) + v;          // soma com os bits mais significativos
  return v;
}

void setup ()
{
  DDRD &= ~(1<<7); // Isto signfica porta digital 7 servindo como entrada
  DDRB |= 1<<0; // Isto significa porta digital 8 servindo como saída
  s.attach(6);
  s.write(0);
}
 
void loop()
{
  testaOnOff();
  if(on_off){
    vx=lerAnalogico(5);
    vy=lerAnalogico(4);
    soma=map(vx+vy,0,2048,0,180);
    s.write(soma);
    if(soma>=90)
      PORTB |= 1 << 0; // Comando para fazer acender o led
    else
      PORTB &= ~(1 << 0); // Comando para deixar o led apagado
  }
}
