# Aluno: Rafael Teixeira de Oliveira
## Tarefa 06 - Pré-Projeto Escrito
---
### Descrição do Projeto Final da disciplina
O Projeto Final da disciplina de Software Embarcado consistirá em construir um placar eletrônico.

Esta ideia de construir um placar eletrônico teve inspiração nos jogos de vôlei, pois funcionará da seguinte maneira:

- Haverão pequenos LEDs  (3 para cada equipe) que servirão para marcar a quantidade de "sets" que cada equipe ganhou na partida, além de ajudar a indicar em qual "set" a partida está.
	- Inicialmente todos esses pequenos LEDs começarão desligados, e a medida que os "sets" vão passando, eles vão sendo ligados, de acordo com a quantidade que cada equipe tem.
- Além disso, haverão outros 2 LEDs (1 para cada equipe), que serão de um tamanho maior que esses últimos falados, além de serem de cor diferente dos também últimos citados. 
	- Estes 2 LEDs terão a função de mostrar com que equipe está a posse da bola, isto é, qual equipe fará o saque.
- Contando com isto tudo, para mostrar, realmente, como está o placar daquele "set" do jogo, haverão 2 displays de 7 segmentos de 2 dígitos cada (1 relativo a cada equipe do jogo).
	- Eles mostrarão a pontuação de cada equipe dentro do set.
- A pontuação será mostrada desta maneira, mas para poder registrar a pontuação das equipes, é necessário haver algum sensor, para que, ao acontecer uma determinada condição, a pontuação de uma das equipes seja aumentada, ou diminuída, dependendo do caso.
	- Considerando isso, haverão 4 botões (2 para cada equipe), que serão os responsáveis por fazer com que a pontuação das equipes mude.
		- A cada vez que for apertado o botão 1 de alguma das equipes, e somente ao pressionar, a pontuação da mesma será incrementada.
			- Se apertar o botão 1 da equipe 1, a pontuação da equipe 1 aumentará, e assim vale para o botão 1 da equipe 2.
		- Porém, podem haver casos em que seja necessário diminuir a pontuação das equipes, devido a algum motivo, que muitas vezes chega no tocante da regra do jogo.
			- Para poder diminuir a pontuação das equipes, será preciso pressionar o botão 2 da equipe correspondente. Somente ao pressionar, a pontuação daquela equipe será decrementada.
	- Com esse esquema, já será possível registrar a pontuação de um jogo de vôlei, mostrando quem está ganhando, quem está com mais "sets", entre outros detalhes.
- Contudo, para facilitar a tarefa de quem está registrando a pontuação do jogo, os botões ficarão independentes do resto do placar.
	- Isto é, o placar eletrônico terá duas partes:
		- Uma parte será a parte de exibição do placar, onde estarão os dados do jogo.
		- E outra parte, que será formada pelos botões, onde a partir deles, a pontuação das equipes será alterada.
	- Os comandos dos botões serão enviados via rádiofrequência para a outra parte do placar, que captará esses comandos, e irá tratá-los em forma de ações na pontuação.
- Quando uma das equipes atingir o necessário para vencer o "set", isto é, atingir pelo menos 25 pontos, e ter pelo menos 2 pontos de diferença para a outra equipe, o placar fica "congelado" por alguns segundos, de modo que seja possível anotar o resultado do "set". 
	- Depois disso, liga-se um dos LEDs desligados daquela equipe, para indicar um "set" ganho, e "zera" a pontuação das equipes, configurando os displays para exibirem o dígito 0.
		- Caso a partida chegue ao 5º "set", o mesmo é feito sendo que agora a pontuação mínima é 15 pontos, mas o critério da diferença se mantém.
	- Se, em algum momento da partida, uma das equipes ganhar 3 "sets", ela é dita a vencedora do jogo. 
		- Quando isso acontecer:
			- "Congela" placar por alguns segundos;
			- Liga o último LED desligado da equipe vencedora;
			- O lado vencedor terá seus LEDs e seu display piscando para sempre, para indicar a vitória, enquanto que o lado perdedor fica com os mesmos desativados, desligados para sempre.
		- Além disso, tudo o que vier dos botões, a partir deste momento, passará a ser ignorado.

---
### Componentes que serão usados no Projeto Final da disciplina

- 6 LEDs de tamanho menor ("mini-LED");
- 2 LEDs de tamanho maior que os citados acima (tamanho "normal");
- 2 Displays de 7 segmentos, de 2 dígitos cada;
- 1 Transmissor de rádiofrequência, para mandar os comandos disparados pelos botões para a outra parte do placar;
- 1 Receptor de rádiofrequência, que ficará na parte de exibição do placar, para receber os comandos dos botões, e atuar nos dados das equipes no jogo;
- 2 Arduinos Uno, que funcionarão 1 em cada parte do placar eletrônico;
- 1 Circuito integrado especializado em displays, que servirá para administrar os comandos de exibição de dígitos nos displays de 7 segmentos;
- 4 Botões, que servirão de "gatilho" para "disparar" os comandos de incrementar e decrementar placar das equipes ao serem pressionados. 
