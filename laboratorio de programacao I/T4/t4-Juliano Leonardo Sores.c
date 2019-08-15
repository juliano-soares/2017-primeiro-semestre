
/*/////////////////////////////////*
 * NOME: JULIANO LEONARDO SOARES   *
 * MATRICULA: 201713854            *
 *                                 *
 */////////////////////////////////*/
/*O programa se trata de um jogo do qual o mouse não pode ser atingido pelas bolinhas
vermelhas e o jogador deve lançar essas bolas para adquirir uma pontuação cada vez maior.
  Para a criação deste game foi usada uma struct para armazenhar todo estado do game
  Tambem foram criadas varias funções auxiliares para deixar o código mais simples e legivel
*/
#include "tela5.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//tamanho da janela
#define LARG 800
#define ALT 600

/***********************/
/* definicao dos dados */
/***********************/

// define uma estrutura com a bolinha
typedef struct {
  circulo circ;     // coordenadas x e y do centro da bolinha
  ponto vel;        // velocidade em x e y
  cor c;
  bool ativa;       // bolinha foi ativada
} bola;

// define uma estrutura com o estado do jogo
typedef struct {
  bola bolinha[25]; // as bolinhas
  float tempo;      // quanto falta pra acabar
  retangulo ret;    // Ã¡rea vÃ¡lida
  int pontos;       // numero de pontos
  circulo alvo;     // circulo que segue o mouse
  double agora;     // horario do inicio de um ciclo
  int forca;        // com quanta forca a bolinha foi (serÃ¡) solta
  int clic;         // clics do mause para contar as bolinhas e aciona-las
  int vida;         // inteiro para a vida do jogador
  bool colidiu;     // serve para indicar as colisões das bolinhas
  bool play;        // serve para indicar se o botão play foi acionado
  bool sobre;       // serve para indicar se o botão sobre foi acionado
  bool sair;        // serve para indicar se o botão sair foi acionado
  int fase;         // serve para indicar qual fase esta
  float tempop;     // serve para a função de pausar o jogo
} estado;

/**********************/
/* programa principal */
/**********************/

// declaracao de funcoes auxiliares
void desenha_tela(estado *t);
void altera_estado(estado *t);
void abertura(estado *t);
void encerramento(estado *t);
bool acabou(estado *t);
void inicializa_estado(estado *t);
void lanca_bolinha(estado *t);
void altera_bola(bola *pb, estado *pe);
void altera_alvo(estado *t);
void verifica_rato(estado *t);
void prende_circulo_no_retangulo(circulo *c, retangulo r);
void movimenta_bola(circulo *c, ponto *v, retangulo r);
void desenha_contorno(estado *t);
void desenha_bola(bola b);
void desenha_alvo(circulo c);
void desenha_pontos(estado *t);
void desenha_tempo(estado *t);
void detecta_colisao(bola b, estado *a);
void reinicia(estado * t);
void desenha_contorno_final(estado *t);
void desenha_pontos_final(estado *t);
void desenha_vida(estado *t);
void desenha_pause(void);
void desenha_pause2(void);
void sobre(estado *t);
void desenha_copyright();
void efeito_inicial();
void efeito_final();
void desenha_fase(estado *t);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// funcao principal
int main()
{
  int i;//variavel usada nos laços de repetição
  estado mundo;
  mundo.sair=false;
  ponto pl;
  tamanho tam_tela = {LARG, ALT};
  tela_inicio(tam_tela);
  efeito_inicial();
  inicializa_estado(&mundo);
  while(mundo.play!=true){
    abertura(&mundo);
    pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
    if( pl.x>=300 &&  pl.x<=500 && pl.y>=140 && pl.y<=190 && tela_rato_apertado()){//caixa de play
      mundo.play=true;
    }if( pl.x>=300 &&  pl.x<=500 && pl.y>=200 && pl.y<=250 && tela_rato_apertado()){//caixa sobre
      mundo.sobre=true;
    }if( pl.x>=300 &&  pl.x<=500 && pl.y>=260 && pl.y<=310 && tela_rato_apertado()){// caixa sair
      mundo.sair=true;
      mundo.play=true;//serve para sair do laço e avança ate o fim e encerrar o programa
    }
    while( mundo.sobre==true){//se caixa sobre foi ativada entra no laço
      sobre(&mundo);//chama a tela sobre
      pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
      if( pl.x>=660 &&  pl.x<=700 && pl.y>=100 && pl.y<=140 && tela_rato_apertado()){//se clicou no x torna sobre para falso e sai do laço
        mundo.sobre=false;
      }
    }
  }
  inicializa_estado(&mundo);
  while( mundo.sair==false){
    while (mundo.vida!=0) {//enquanto vida diferente de zero ocorre as variações a seguir
      desenha_tela(&mundo);
      if(mundo.colidiu==true){// se ocorre a colisao o tempo retorna 60 e vida diminui
        reinicia(&mundo);
        mundo.vida-=1;
        mundo.tempo = 60;
      }
      if(tela_le_tecla()=='p'){//função pra entrar na tela pause
        do{
          desenha_pause2();
          mundo.agora=tela_agora();
        }while(tela_le_tecla()!='p');//clicar no p para sair do pause
      }
      if(acabou(&mundo)){//acabou o tempo aumenta a fase
        mundo.fase+=1;
      }if(mundo.vida>0 && acabou(&mundo)){// este serve para ver se tem vidas e tempo acabou se sim verifica qual fase esta e modifical algo no jogo afim de dificultalo
        mundo.ret.origem.x = 30;
        mundo.ret.origem.y = 20;
        mundo.ret.tam.l = LARG-60;
        mundo.ret.tam.h = ALT-80;
        if(mundo.fase%3==0){//fases multiplas de 3 o raio das bolinhas vermelhas aumenta
          reinicia(&mundo);
          mundo.tempo = 60;
          for(i=0; i<25;i++){
            mundo.bolinha[i].circ.raio+=5;
          }
        }
        if(mundo.fase%2==0 && !(mundo.fase%3==0)){//fases multiplas de 2 não multiplas de 3 o raio do alvo aumenta
          reinicia(&mundo);
          mundo.tempo = 60;
          mundo.alvo.raio+=5;
          if(mundo.fase%2==0 && mundo.fase%4==0){//fases multiplas de 4 modifica o tamanho da tela
            mundo.ret.origem.x = 100;
            mundo.ret.origem.y = 20;
            mundo.ret.tam.l = LARG-200;
            mundo.ret.tam.h = ALT-80;
          }
        }
        if(mundo.fase%2!=0 && !(mundo.fase%3==0)){//fase impares não multiplas de 3 muda o raio do alvo aumenta
          reinicia(&mundo);
          mundo.tempo = 60;
          mundo.alvo.raio+=5;
        }
      }
      altera_estado(&mundo);
    }
    reinicia(&mundo);
    while (mundo.sair!=true){//como mundo sair estara true apos morror todas as vidas entra neste laço
      encerramento(&mundo);
      pl = tela_pos_rato();// pl recebe a todo momento as coordenadas do mouse
      if( pl.x>=300 &&  pl.x<=500 && pl.y>=140 && pl.y<=190 && tela_rato_apertado()){// caixa para reiniciar o jogo
        mundo.play=true;
        inicializa_estado(&mundo);
        break;
      }if( pl.x>=300 &&  pl.x<=500 && pl.y>=200 && pl.y<=250 && tela_rato_apertado()){// caixa de sair
        mundo.sair=true;
      }
    }
  }
  efeito_final();
  tela_fim();
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************/
/* Manutencao do estado do jogo */
/********************************/
/* funcao principal de alteracao do estado do jogo */

// altera a posicao do que se mexe na tela, reage a acao do mouse
void altera_estado(estado *t)
{
  int i;
  double agora = tela_agora();
  double delta_t = agora - t->agora;
  t->agora = agora;
  altera_alvo(t);
  //altera o estado das 25 bolinhas em tela
  for(i=0; i<25; i++){
    altera_bola(&t->bolinha[i], t);
  }
  verifica_rato(t);
  t->tempo -= delta_t;
}

/* estado do alvo */
// faz o alvo acompanhar o rato, mas sem sair da casinha
void altera_alvo(estado *t)
{
  t->alvo.centro = tela_pos_rato();
  prende_circulo_no_retangulo(&t->alvo, t->ret);
}

// se o circulo esta fora do retangulo, recoloca-o dentro,
// na posicao mais proxima
void prende_circulo_no_retangulo(circulo *c, retangulo r)
{
  if (c->centro.x - c->raio < r.origem.x) {
    c->centro.x = r.origem.x + c->raio;
  }
  if (c->centro.y - c->raio < r.origem.y) {
    c->centro.y = r.origem.y + c->raio;
  }
  if (c->centro.x + c->raio > r.origem.x + r.tam.l) {
    c->centro.x = r.origem.x + r.tam.l - c->raio;
  }
  if (c->centro.y + c->raio > r.origem.y + r.tam.h) {
    c->centro.y = r.origem.y + r.tam.h - c->raio;
  }
}

/* estado da bolinha */
// atualiza o estado de uma bolinha e aproveita e calcula os pontos de sua movimentacao
void altera_bola(bola *pb, estado *pe)
{
  // bolinha inativa nao faz nada
  if (!pb->ativa) return;

  // altera a posicao
  movimenta_bola(&pb->circ, &pb->vel, pe->ret);

  // pontua a distancia percorrida
  pe->pontos += sqrt(pb->vel.x * pb->vel.x + pb->vel.y * pb->vel.y);
}

// movimenta um circulo no interior de um retangulo, de acordo com velocidade
// nao permite que o circulo saia do retÃ¢ngulo, ricocheteando:
// verifica o quanto o circulo ultrapassou os limites do retangulo
// em cada direcao, e calcula onde ele deveria estar, caso tivesse
// ricocheteado na parede do retangulo em vez de atravessÃ¡-la.
void movimenta_bola(circulo *c, ponto *v, retangulo r)
{
  // atualiza posiÃ§Ã£o com velocidade
  c->centro.x += v->x;
  c->centro.y += v->y;

  // ricocheteia - se saiu da tela, devolve o mesmo tanto e inverte a vel
  float d; // distancia que saiu da tela
  // por exemplo, na esquerda -- subtrai a coordenada mais a esquerda do
  // circulo da mais a esquerda do retangulo.
  // se der positivo, o circulo esta tal distancia a esquerda de r --
  // coloca ele o mesmo tanto a direita de r e inverte a velocidade em x
  d = r.origem.x - (c->centro.x - c->raio);
  if (d > 0) {
    c->centro.x += 2*d;
    v->x *= -1;
  }
  // na direita
  d = (r.origem.x + r.tam.l) - (c->centro.x + c->raio);
  if (d < 0) {
    c->centro.x += 2*d;
    v->x *= -1;
  }
  // em cima
  d = r.origem.y - (c->centro.y - c->raio);
  if (d > 0) {
    c->centro.y += 2*d;
    v->y *= -1;
  }
  // embaixo
  d = (r.origem.y + r.tam.h) - (c->centro.y + c->raio);
  if (d < 0) {
    c->centro.y += 2*d;
    v->y *= -1;
  }
}

/* processamento da entrada */
// o botao do mouse serve para liberar a bolinha.
// quanto mais tempo ele fica apertado, mais rapido ela vai
void verifica_rato(estado *t)
{
  // se o mouse ta apertado, aumenta a forca
  if (tela_rato_apertado()) {
    if(t->forca<15){
      t->forca++;
    }
  } else {
    // se o mouse ta solto e tem forca, foi solto agora
    if (t->forca > 0) {
      lanca_bolinha(t);
      t->forca = 0;
    }
  }
}

// lanca a bolinha em direcao ao alvo, com velocidade proporcional a forca
void lanca_bolinha(estado *t)
{
  // se a bolinha ja ta ativa, ignora
  int i;
  for(i=0; i<t->clic; i++){
    if (!t->bolinha[i].ativa){
        // calcula a direcao da bolinha -- direto para o alvo
        ponto dir;
        dir.x = t->alvo.centro.x - t->bolinha[i].circ.centro.x;
        dir.y = t->alvo.centro.y - t->bolinha[i].circ.centro.y;
        // transforma em um vetor unitario -- divide pela distancia
        float modulo;
        modulo = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir.x /= modulo;
        dir.y /= modulo;
        // a velocidade da bolinha sera proporcional a forca, na dir calculada
        t->bolinha[i].vel.x = dir.x * t->forca;
        t->bolinha[i].vel.y = dir.y * t->forca;
        // libera a bolinha, em cor de batalha
        t->bolinha[i].c = vermelho;
        t->bolinha[i].ativa = true;
    }
  }
  t->clic++;
  if(t->clic == 26) t->clic = 0;
}

/*******************/
/* Desenho da tela */
/*******************/
/* funcao principal do desenho da tela */
// Desenho de uma tela
// limpa a tela, desenha todos os elementos visuais de acordo com o estado,
// faz a tela ser mostrada
void desenha_tela(estado *t)
{
  int i;
  tela_limpa();

  desenha_pause();// desenha a frase pause no meio superior da tela
  desenha_vida(t);//desenha a vida do jogador
  desenha_contorno(t);
  desenha_tempo(t);
  desenha_pontos(t);
  desenha_fase(t);

  for(i=0; i<25; i++){
    desenha_bola(t->bolinha[i]);
    detecta_colisao(t->bolinha[i], t);
  }
  desenha_alvo(t->alvo);
  tela_atualiza();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* funcoes auxiliares para o desenho da tela */
// desenha a area central onde as bolinhas podem se moviemntar
void desenha_contorno(estado *t)
{
  tela_retangulo(t->ret, 5, azul, tela_cria_cor(0.50, 0.50, 0.50));
}

// desenha uma bola
void desenha_bola(bola b)
{
  tela_circulo(b.circ, 1, b.c, b.c);
}

// desenha o alvo
void desenha_alvo(circulo c)
{
  tela_circulo(c, 2, branco, amarelo);
  c.raio=5;
  tela_circulo(c, 2, branco, verde);
}

// desenha os pontos
void desenha_pontos(estado *t)
{
  // os pontos aparecem em verde, embaixo, a esquerda
  ponto p = { 35, ALT-55 };
  char s[20];
  sprintf(s, "%d", t->pontos);
  tela_texto_dir(p, 35, verde, s);
}

// desenha o tempo restante
void desenha_tempo(estado *t)
{
  // desenha a direita, embaixo
  ponto p = { LARG-50, ALT-55 };

  // prepara o texto
  char s[20];
  sprintf(s, "%.1f", t->tempo);

  // calcula o tamanho -- maior se for tempo inteiro
  int tam;
  if (t->tempo - floor(t->tempo) < 0.1) {
    tam = 50;
  } else {
    tam = 35;
  }

  // cor diferente quando tiver acabando o tempo
  cor c;
  c = t->tempo<10 ? vermelho : verde;

  // escreve
  tela_texto_esq(p, tam, c, s);
}

//desenha frase pause durante o jogo localizada no centro superior da tela
void desenha_pause()
{
  char pause[]="pause (p minusculo)";
  ponto p = { 400, 10 };
  tela_texto(p, 10, verde, pause);
}

//desenha frase fase durante o jogo localizada no canto esquerdo superior da tela
void desenha_fase(estado *t)
{
  char fase[]="fase";
  ponto p1 = { 40, 10 };
  tela_texto(p1, 10, vermelho, fase);
  // As fases aparecem em verde parte superior a esquerda
  ponto p = { 60, 2 };
  char s[20];
  sprintf(s, "%d", t->fase);
  tela_texto_dir(p, 15, vermelho, s);
}

//desenha palavra durante a pausa no jogo no centro da tela
void desenha_pause2()
{
  char pause[6]={'P','A','U','S','E'};
  ponto p = { 400, 300 };
  tela_texto(p, 50, branco, pause);
  tela_atualiza();
}

// função para desenhar a vida do jogador na tela
void desenha_vida(estado *t)/////////////////////**********************************************************************CORREÇÃO SIMBOLO
{
  int i;//variaver para os laços
  int x=320, y=575;//variaveis para as posiçoes das vidas
  char V[]="vida";//frase durante o jogo
  ponto p2 = { 400, 550 };
  tela_texto(p2, 15, laranja, V);
  if(t->vida!=0){// um if para cada estagio de vida para desenhar a quantidade certa de vida
    for(i=0; i<t->vida; i++){
      char s[]="❤";
      ponto p = { x, y };
      tela_texto(p, 50, vermelho, s);
      x+=40;
     }
  }
}
// desenha os pontos apos perder toda a vida ele aparece no menu encerramento
void desenha_pontos_final(estado *t)
{
  // os pontos aparecem em azul, meio
  ponto p = { 400, ALT-500 };
  char s[20];
  sprintf(s, "%d", t->pontos);
  tela_texto(p, 20, azul, s);
}

void desenha_copyright()
{
  // desenha mensagem de direitos autorais na parte central e inferior da tela no menu encerramento
  char copyright[]="Copyright 2017, Todos os direitos reservados";
  ponto pc = { 400, 550 };
  tela_texto(pc, 10, azul, copyright);
  char autor[]="JULIANO SOARES";
  ponto paut = { 400, 560 };
  tela_texto(paut, 10, azul, autor);
}
///*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/* funcoes complementares */
//inicializa todos os dados do jogo e seu estado
void inicializa_estado(estado *t)
{
  int i;
  t->clic = 0;
  t->ret.origem.x = 30;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-60;
  t->ret.tam.h = ALT-80;
  t->colidiu = false;
  t->play=false;
  t->sobre=false;
  t->vida = 5;
  t->fase=1;
  t->tempop=0;

  // inicializa a bolinha
  for(i=0; i<25; i++){
    t->bolinha[i].circ.centro.x = t->ret.origem.x + t->ret.tam.l/2;
    t->bolinha[i].circ.centro.y = t->ret.origem.y + t->ret.tam.h - 5 - 250;
    t->bolinha[i].circ.raio = 5;
    t->bolinha[i].vel.x = 0;
    t->bolinha[i].vel.y = 0;
    t->bolinha[i].c = azul;
    t->bolinha[i].ativa = false;
  }
  //inicializa o tempo e os pontos
  t->tempo = 60;/////////////////////////////////////////////////////////////////////////////////
  t->pontos = 0;
  //inicializa o alvo no mouse
  t->alvo.centro = tela_pos_rato();
  t->alvo.raio = 10;
  t->forca = 0;
  t->agora = tela_agora();
}

/*função para reiniciar todas as bolinhas devolta ao centro apos a morte do
jogador sem alterar o tempo ja consumido e os pontos ja ganhos e penaliza a
vida em menos vinte*/
void reinicia(estado *t)
{
  int i;
  t->clic = 1;
  t->ret.origem.x = 30;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-60;
  t->ret.tam.h = ALT-80;
  t->colidiu = false;
  t->play=false;
  t->sobre=false;
  t->sair=false;

  t->tempop=0;
  // inicializa a bolinha
  for(i=0; i<25; i++){
    t->bolinha[i].circ.centro.x = t->ret.origem.x + t->ret.tam.l/2;
    t->bolinha[i].circ.centro.y = t->ret.origem.y + t->ret.tam.h - 5 - 250;
    //t->bolinha[i].circ.raio = 5;
    t->bolinha[i].vel.x = 0;
    t->bolinha[i].vel.y = 0;
    t->bolinha[i].c = azul;
    t->bolinha[i].ativa = false;
  }
  // Nesta parte como pode ver o tempo e pontos não são alterados
  //t->tempo = 60;
  //t->pontos = 0;
  t->alvo.centro = tela_pos_rato();
  t->forca = 0;
  t->agora = tela_agora();
}

// animacao fantastica que aparece quando o jogo comeca
/* A função abertura foi usada como menu inicial do jogo */
void abertura(estado *t)
{
  tela_limpa();
  //quadrado maior delimita a localidade do jogo
  t->ret.origem.x = 20;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-40;
  t->ret.tam.h = ALT-40;
  tela_retangulo(t->ret, 5, branco, marrom);

  //desenha area clicavel de iniciar o jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 140;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50), tela_cria_cor(0.50, 0.50, 0.50));
  char iniciar[]="PLAY";//desenha a palavra
  ponto pR = { 400, 165 };
  tela_texto(pR, 35, azul, iniciar);

  //desenha area clicavel de informaçoes do jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 200;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50),tela_cria_cor(0.50, 0.50, 0.50));
  char sobre[]="SOBRE";//desenha a palavra
  ponto psob = { 400, 225 };
  tela_texto(psob, 35, azul, sobre);

  //desenha area clicavel de sair do jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 260;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50), tela_cria_cor(0.50, 0.50, 0.50));
  char sair[]="SAIR";//desenha a palavra
  ponto psair = { 400, 285 };
  tela_texto(psair, 35, azul, sair);

  desenha_copyright();//desenha frase de direitos autorais
  //correção para aparecer a bolinha do mouse nas aberturas e encerramento
  t->ret.origem.x = 20;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-40;
  t->ret.tam.h = ALT-40;
  altera_estado(t);//chama altera estado para póder mudar posição do mouse
  desenha_alvo(t->alvo);//desenha alvo no mouse

  tela_atualiza();
}

// animacao de despedida
/* A função encerramento foi usada como menu apos perder todas as vidas ou o
tempo acabar então ela aparece mostrando algumas funções */
void encerramento(estado *t)
{
  tela_limpa();
  t->alvo.raio = 10;// corrige o raio do alvo quando mudado nas fases
  // tela do fim do jogo
  //quadrado maior delimita a localidade do jogo quadrado maior marrom com linhas laterais brancas
  t->ret.origem.x = 20;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-40;
  t->ret.tam.h = ALT-40;
  tela_retangulo(t->ret, 5, branco, marrom);

  //desenha o score na parte superior e meio da tela
  desenha_pontos_final(t);
  ponto p = { 400, ALT-520 };
  char s[20]={'S','C','O','R','E'};//desenha a palavra
  tela_texto(p, 20, azul, s);

  //desenha a frase de fim na parte meio inferior
  //int tam = 35;
  char y[10]={'G','A','M','E',' ','O','V','E','R'};//desenha a palavra em posiçoes diferentes para dar um efeito
  ponto p2 = { 400, 525 };
  tela_texto(p2, 35, laranja, y);
  ponto p3 = { 400, 520 };
  tela_texto(p3, 35, azul, y);
  ponto p4 = { 400, 515 };
  tela_texto(p4, 35, verde, y);

  //desenha area clicavel de reiniciar o jogo, essa opção faz o jogador ter a possibilidade de voltar a jogar se desejar
  t->ret.origem.x = 300;
  t->ret.origem.y = 140;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50), tela_cria_cor(0.50, 0.50, 0.50));
  char reiniciar[10]={'R','E','I','N','C','I','A','R'};//desenha a palavra
  ponto pR = { 400, 165 };
  tela_texto(pR, 35, azul, reiniciar);

  //desenha area clicavel de sair do jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 200;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50),tela_cria_cor(0.50, 0.50, 0.50));
  char sair[]="SAIR";//desenha a palavra
  ponto psair = { 400, 225 };
  tela_texto(psair, 35, azul, sair);

  desenha_copyright();//desenha frase de direitos autorais
  //correção para aparecer a bolinha do mouse nas aberturas e encerramento
  t->ret.origem.x = 20;
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-40;
  t->ret.tam.h = ALT-40;
  altera_alvo(t);// altera a posição do alvo durante a tela encerramento
  desenha_alvo(t->alvo);//desenha alvo na nova posição
  tela_atualiza();
}

void sobre(estado *t)/////////////*****************
{
  tela_limpa();
  t->ret.origem.x = 20;//desenha retangulo marrom
  t->ret.origem.y = 20;
  t->ret.tam.l = LARG-40;
  t->ret.tam.h = ALT-40;
  tela_retangulo(t->ret, 5, branco, marrom);
  t->ret.origem.x = 100;//desenha retangulo branco
  t->ret.origem.y = 100;
  t->ret.tam.l = LARG-200;
  t->ret.tam.h = ALT-200;
  tela_retangulo(t->ret, 5, preto, branco);
  char x[2]="X";// desenha o x para fecha o sobre
  ponto px = { 680, 118 };
  tela_texto(px, 30, preto, x);
  // desenha mensagem de direitos autorais na parte central e inferior da tela no menu abertura
  char tx1[]="Objetivos do jogo:";
  ponto ptx1 = { 110, 110 };
  tela_texto_dir(ptx1, 15, azul, tx1);
  char tx2[]="->Fazer a maior pontuação possivel;";
  ponto ptx2 = { 110, 125 };
  tela_texto_dir(ptx2, 15, preto, tx2);
  char tx3[]="->Não  ser tocado pelas bolinhas vermelhas;";
  ponto ptx3 = { 110, 140 };
  tela_texto_dir(ptx3, 15, preto, tx3);
  char tx4[]="Instruções:";
  ponto ptx4 = { 110, 175 };
  tela_texto_dir(ptx4, 15, azul, tx4);
  char tx5[]="->O mouse movimenta todo o jogo;";
  ponto ptx5 = { 110, 190 };
  tela_texto_dir(ptx5, 15, preto, tx5);
  char tx6[]="->A bolinha azul é a origem da saida das outras bolinhas;";
  ponto ptx6 = { 110, 205 };
  tela_texto_dir(ptx6, 15, preto, tx6);
  char tx7[]="->A pontuação aumenta conforme a distância percorida pelas bolas vermelhas;";
  ponto ptx7 = { 110, 220 };
  tela_texto_dir(ptx7, 15, preto, tx7);
  desenha_copyright();//desenha frase de direitos autorais
  //correção para aparecer a bolinha do mouse nas aberturas e encerramento
  altera_estado(t);//chama altera estado para póder mudar posição do mouse
  desenha_alvo(t->alvo);//desenha alvo no mouse
  tela_atualiza();
}

// função que verifica a colisão de uma bolinha com o mouse
void detecta_colisao(bola b, estado *a)
{
  //foi usada a função de distancia entre dois pontos e compara com a soma dos raios do alvo + bolas para verificar se ocorreu uma colisão
  if(b.ativa==true){
    if(sqrt( pow(b.circ.centro.x - a->alvo.centro.x, 2)+pow(b.circ.centro.y - a->alvo.centro.y, 2)) <= a->alvo.raio + b.circ.raio){
      a->colidiu = true;
    }
  }
  return;
}

// o jogo terminou?
bool acabou(estado *t)
{
  return t->tempo <= 0;
}

void efeito_inicial(circulo c)
{

  int i=0, j;
  srand(time(NULL));
  int x[25],y[25];
  float rr=25,t=1;
  ponto p = { 400, 300 };
  char inicial[]="BOLINHAS O GAME";
    while(i!=200){
    j=tela_cria_cor(rand() % 2, rand() % 2, rand() % 2);
    tela_limpa();
    for(j=0;j<25;j++){
      x[j]=rand() % 800;
      y[j]=rand() % 600;
      circulo c={ x[j],y[j],rr};
      tela_circulo(c, 5,j, j);
    }
    tela_texto(p, t, vermelho, inicial);
    if(t<50)t+=5;
    i++;
    tela_atualiza();
  }
}

void efeito_final(circulo c)
{
  int i=0, j;
  srand(time(NULL));
  int x[25]={rand() % 100},
      y[25]={rand() % 100};
  float rr=25,t=1;
  ponto p = { 400, 300 };
  char inicial[]="OBRIGADO POR JOGAR";
  while(i!=200){
    j=tela_cria_cor(rand() % 2, rand() % 2, rand() % 2);
    tela_limpa();
    for(j=0;j<25;j++){
      x[j]=rand() % 1000;
      y[j]=rand() % 1000;
      circulo c={ x[j],y[j],rr};
      tela_circulo(c, 5,j, j);
    }
    tela_texto(p, t, vermelho, inicial);
    if(t<50)t+=5;
    i++;
    tela_atualiza();
  }
}

/* acabou, Ã© sÃ³ isso */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
