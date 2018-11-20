# Alterações no Projeto Final da disciplina

1. Projeto Final da disciplina de Software Embarcado continuará sendo construir um placar eletrônico, porém este placar eletrônico não será restrito a jogos de vôlei. Com ele será possível marcar o placar de jogos de vôlei, basquete e futebol.
2. Haverão pequenos LEDs (4 para cada equipe, ao invés de 3 para cada equipe) que servirão para:
	- Mostrar a quantidade de "sets" que cada equipe ganhou, caso esteja em um jogo de vôlei;
	- Mostrar a quantidade de jogadores expulsos na partida, caso esteja em um jogo de futebol, ou;
	- Mostrar a quantidade de faltas coletivas que a equipe já fez no período, caso esteja em um jogo de basquete.
	- Inicialmente todos esses pequenos LEDs começarão desligados, e a medida que os eventos vão acontecendo, eles vão sendo ligados.
3. Além disso, haverão outros 2 LEDs (1 para cada equipe), que serão de um tamanho maior que esses últimos falados, além de serem de cor diferente dos também últimos citados. 
	- Estes 2 LEDs terão a função de:
		- Mostrar com que equipe está a posse da bola, isto é, qual equipe fará o saque, caso esteja em um jogo de vôlei, ou;
		- Mostrar se uma equipe já marcou 100 ou mais pontos, caso esteja em um jogo de basquete.
4. Contando com isto tudo, para mostrar, realmente, como está o placar do jogo, haverão 2 displays de 7 segmentos de 2 dígitos cada (1 relativo a cada equipe do jogo).
	- Eles mostrarão a pontuação de cada equipe.
5. Ao invés de usar 4 botões, que seriam usados para aumentar ou diminuir as pontuações das equipes nos jogos, será usado um controle remoto para tal.
	- Dependendo do jogo que esteja querendo marcar o placar, os botões do controle remoto terão diferentes funções.
	- Antes de marcar o placar do jogo que queira marcar, será preciso antes escolher qual esporte quer marcar placar (vôlei, futebol ou basquete).
	- O placar eletrônico continua a ter duas partes:
		- Uma parte será a parte de exibição do placar, onde estarão os dados do jogo.
		- E outra parte, que é basicamente o controle remoto, onde, a partir dele, a pontuação das equipes será alterada, além de registrar eventos que farão iluminar os LEDs.
		- Por estar usando um controle remoto, os comandos serão enviados via infravermelho para a outra parte do placar, que será a responsável por tratar os comandos com as devidas ações.
6. O funcionamento nos jogos de vôlei não mudou.
7. Quando se vai marcar o placar de um jogo de basquete:
	1. O trâmite de aumento e redução de placar é simples;
		1. Quando uma equipe tiver 100 ou mais pontos , o LED amarelo respectivo fica aceso.
	2. Quando for registrada uma falta de uma equipe, um dos LEDs da equipe acende.
	3. Caso seja a 5ª falta da equipe naquele período, os LEDs piscam, indicando que já estourou o limite de faltas.
	4. Quando um período termina, e começa outro, ao apertar um determinado botão do controle remoto, os LEDs vermelhos desligam, indicando novo período começando, e sem faltas para as duas equipes (regra do esporte).
	5. Quando chega no 4º e último período, ao apertar esse mesmo botão do controle, duas possibilidades de acontecimentos:
		1. Caso alguma equipe esteja na frente, o trâmite de vitória já dito na versão 1 do Projeto segue acontecendo.
		2. Caso o placar esteja empatado, o jogo continua (pois oficialmente não há empate no basquete, caso aconteça há prorrogações quantas vezes forem até que alguém termine na frente), fazendo o processo de troca de período já dito no sub-item iv deste item. E este processo pode se repetir quantas vezes forem necessárias.
8. Quando se vai marcar o placar de um jogo de futebol:
	1. O trâmite de aumento e redução de placar é simples;
	2. Quando um jogador da equipe for expulso, um dos LEDs vermelhos acende.
		1. Caso este seja o 5º jogador expulso da mesma equipe, o jogo acaba, e a outra equipe é declarada vencedora, com o protocolo de vitória já dito, que é o mesmo do vôlei e do basquete.
	3. Além disso, há um relógio, que ajudará a mostrar o tempo da partida. De 5 em 5 minutos, o placar mostrará o tempo da partida durante 5 segundos, depois volta a mostrar a quantidade de gols de cada time.
	4. Ao apertar um determinado botão do controle remoto:
		1. Caso esteja no 1º tempo, o placar em "modo de intervalo";
		2. Caso esteja "no intervalo", volta o jogo, começando a contar o 2º tempo;
		3. E caso esteja no 2º tempo, acaba o jogo. Caso alguém esteja na frente, faz-se o mesmo protocolo de vitória; caso termine empatado, os LEDs das duas equipes piscam para sempre, e o placar fica inalterado.
9. Componentes que estão sendo usados:
	- 1 Arduino Mega;
  	- 8 LEDs pequenos vermelhos;
  	- 2 LEDs "normais" (ou grandes) amarelos;
  	- 1 Controle Remoto
  	- 2 Displays de 7 segmentos, de 2 dígitos cada;
  	- 1 CI especializado em displays;
  	- 1 Receptor de Infravermelho;
  	- 1 RTC (Real Time Clock).
 ---
 # Próximos passos do Projeto Final
 
 - [x] Adicionar RTC para mostrar tempo de uma partida de futebol.
