///********************************///
///* T5 - GAME COBRA DE BOLINHAS  *///
///* NOME JULIANO LEONARDO SOARES *///
///* MATRICULA: 201713854         *///
///********************************///

#include "tela5.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
///tamanho da janela
#define LARG 800
#define ALT 600
#define nmax_b_cobra 600
#define nmax_b_mira 200
///***********************///
///* definicao dos dados *///
///***********************///
/// define uma estrutura com a bolinha
typedef struct {
  circulo circ;     // coordenadas x e y do centro da bolinha
  ponto vel;        // velocidade em x e y
  cor c;            // cor da bola
  bool ativa;       // bolinha foi ativada
  bool operante;
  int id;
} bola;

typedef struct {
  char nomes[5];
  int pontuacaos;
}rarquivo;

/// define uma estrutura com o estado do jogo
typedef struct {
  bola bolinha[nmax_b_mira];       // a bolinha
  bola bolas_cobra[nmax_b_cobra];  // vetor de bolas da cobra e suas caracteristicas
  float tempo;                     // quanto falta pra acabar
  retangulo ret;                   // área válida
  int pontos;                      // numero de pontos
  circulo alvo;                    // circulo que segue o mouse
  double agora;                    // horario do inicio de um ciclo
  int forca;                       // com quanta forca a bolinha foi (será) solta
  int clic;                        // clics do mause para contar as bolinhas e aciona-las
  bool colidiu;
  float velocidade;
  bool sair;
  bool play;
  bool sobre;
  bool perdeu;
  int fase;
  bool bonus;
  bool perdida;
  int mult;
  int n_vezes;
  bool recordes;
  bool trocafase;
  int num_cores;
  int n_b_cobra;
} estado;


///**********************************///
///*  manutenção de estado do game  *///
///**********************************///
void altera_estado(estado *t);
///inicializaçõe do game
void inicializa_estado(estado *t);
void reinicia_fase(estado *t);
void inicializa_bolas_cobra(estado*t);
void inicializa_bolas_mira(estado *t);
void rand_cores(bola trocacor,estado *t);

///**********************///
///*  colisões no game  *///
///**********************///
/// declaracao de funcoes auxiliares
bool colisao_bola_cobra(bola b,bola central);
bool colisao_bola_cobra_posicao_ocp(bola b,bola frente,bola atras);
void colisao_bola_3oumais_colidiu(int k,estado*t);
void pontuacao(int n_bolas, estado *t);
void remover_da_cobra (int k, int direita, int esquerda ,estado *t);
void inserir_na_cobra (int k,bola nova,estado *t);

///*******************/
///* Desenho da tela */
///*******************/
/// função principal de desenho
void desenha_tela(estado *t);
/// declaracao de funcoes auxiliares de desenho
void desenha_canhao(estado *t);
void desenha_alvo(circulo c);
void desenha_bolas_no_carregador(estado *t);
void desenha_contorno(estado *t);
void desenha_bola(bola b);
void desenha_pontos(estado *t);
void desenha_pause();
void desenha_fase(estado *t);
void desenha_caminho();
void desenha_copyright();
void desenha_pontos_final(estado *t);
void desenha_pause2();
void desenha_somador_pont(int x, int m,estado *t);

///*******************************///
///* Desenho de aberturas do game*///
///*******************************///
/// declaracao de funcoes auxiliares de aberturas do jogo
void menu_inicial_do_game(estado *t);
void menu_final_do_game(estado *t);
void recordes(estado *t);
void sobre(estado *t);
void abertura(void);
void encerramento();

///***************************************///
///* Manutencao do estado do game        *///
///* e processamento de entradas do game *///
///***************************************///
void altera_alvo(estado *t);
void verifica_rato(estado *t);
void lanca_bolinha(estado *t);
void altera_bola(bola *pb, estado *pe);
void movimenta_bola(circulo *c, ponto *v, retangulo r);
void altera_bola_cobra(bola *pbc, estado *pe2);
void movimenta_bola_cobra(circulo *c,ponto *v, estado *t);

///************************///
///* Movimentação do game *///
///************************///
void movimenta_bola(circulo *c, ponto *v, retangulo r);

///*******************///
///* Arquivo do game *///
///*******************///
void fechar_arquivo(FILE *arquivo);
bool abre_arquivo(char modo, char caminho[30]);
void listar();
void compara_pontuacao(estado *t,rarquivo *s);

/// funcao principal
int main()
{
  int i,contaux=0;//variavel usada nos laços de repetição
  rarquivo score;
  estado mundo;

  srand(time(NULL));
  mundo.sair=false;
  ponto pl;
  tamanho tam_tela = {LARG, ALT};
  tela_inicio(tam_tela);
  abertura();
  inicializa_estado(&mundo);
  while(mundo.play!=true){
    menu_inicial_do_game(&mundo);
    pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
    if( pl.x>=300 &&  pl.x<=500 && pl.y>=140 && pl.y<=190 && tela_rato_apertado()){//caixa de play
      mundo.play=true;
    }if( pl.x>=300 &&  pl.x<=500 && pl.y>=200 && pl.y<=250 && tela_rato_apertado()){//caixa sobre
      mundo.sobre=true;
    }if( pl.x>=300 &&  pl.x<=500 && pl.y>=260 && pl.y<=310 && tela_rato_apertado()){// caixa sair
      mundo.sair=true;
      mundo.play=true;//serve para sair do laço e avança ate o fim e encerrar o programa
    }if( pl.x>=300 &&  pl.x<=500 && pl.y>=320 && pl.y<=370 && tela_rato_apertado()){// caixa sair
      mundo.recordes=true;
    }
    while( mundo.sobre==true){//se caixa sobre foi ativada entra no laço
      sobre(&mundo);//chama a tela sobre
      pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
      if( pl.x>=660 &&  pl.x<=700 && pl.y>=100 && pl.y<=140 && tela_rato_apertado()){//se clicou no x torna sobre para falso e sai do laço
        mundo.sobre=false;
      }
    }while( mundo.recordes==true){//se caixa recordes foi ativada entra no laço
      recordes(&mundo);//chama a tela recordes
      pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
      if( pl.x>=660 &&  pl.x<=700 && pl.y>=100 && pl.y<=140 && tela_rato_apertado()){//se clicou no x torna sobre para falso e sai do laço
        mundo.recordes=false;
      }
    }
  }
  inicializa_estado(&mundo);
  inicializa_bolas_mira(&mundo);
  while( mundo.sair==false){
    while (mundo.perdeu!=true) {
      //inicializa_bolas_mira(&mundo);
      desenha_tela(&mundo);
      if(tela_le_tecla()=='p'){//função pra entrar na tela pause
        do{
          desenha_pause2();
          mundo.agora=tela_agora();
        }while(tela_le_tecla()!='p');//clicar no p para sair do pause
      }
      if( mundo.bolas_cobra[0].circ.centro.x==LARG-150 && mundo.bolas_cobra[0].circ.centro.y==ALT-159)mundo.perdeu=true;
      //printf("%f **** %f\n",mundo.bolas_cobra[0].circ.centro.x,mundo.bolas_cobra[0].circ.centro.y);
      if(mundo.trocafase==true){
        reinicia_fase(&mundo);
      }for(i=0;i<nmax_b_mira;i++){
        if(!&mundo.bolinha[i].operante)contaux++;
      }if(contaux>=1){
        inicializa_bolas_mira(&mundo);
      }
      contaux=0;
      altera_estado(&mundo);
    }
    compara_pontuacao(&mundo, &score);
    inicializa_estado(&mundo);
    while (mundo.sair!=true){//como mundo sair estara true apos morror todas as vidas entra neste laço
      menu_final_do_game(&mundo);
      pl = tela_pos_rato();// pl recebe a todo momento as coordenadas do mouse
      if( pl.x>=300 &&  pl.x<=500 && pl.y>=140 && pl.y<=190 && tela_rato_apertado()){// caixa para reiniciar o jogo
        mundo.play=true;
        inicializa_estado(&mundo);
        inicializa_bolas_mira(&mundo);
        break;
      }if( pl.x>=300 &&  pl.x<=500 && pl.y>=200 && pl.y<=250 && tela_rato_apertado()){// caixa de sair
        mundo.sair=true;
      }if( pl.x>=300 &&  pl.x<=500 && pl.y>=260 && pl.y<=310 && tela_rato_apertado()){// caixa sair
        mundo.recordes=true;
      }while( mundo.recordes==true){//se caixa sobre foi ativada entra no laço
        recordes(&mundo);//chama a tela sobre
        pl = tela_pos_rato();// recebe a posição do mouse para verificar se clicou em uma opção
        if( pl.x>=660 &&  pl.x<=700 && pl.y>=100 && pl.y<=140 && tela_rato_apertado()){//se clicou no x torna sobre para falso e sai do laço
          mundo.recordes=false;
        }
      }
    }
  }
  encerramento();
  tela_fim();
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///* funcao principal de alteracao do estado do jogo *///
// altera a posicao do que se mexe na tela, reage a acao do mouse
void altera_estado(estado *t)
{
  int i;
  double agora = tela_agora();
  double delta_t = agora - t->agora;
  t->agora = agora;

  altera_alvo(t);
  //altera o estado das 25 bolinhas em tela
  for(i=0; i<nmax_b_mira; i++){
    altera_bola(&t->bolinha[i], t);
  }
  for(i=0; i<nmax_b_cobra; i++){
    altera_bola_cobra(&t->bolas_cobra[i], t);
  }

  verifica_rato(t);
  t->tempo -= delta_t;
}

///******************************************************** estados das bolinhas ****************************************************************************/
///************************************************** funcao auxiliar de movimentacao ***********************************************************************/
void altera_bola(bola *pb, estado *pe)/// atualiza o estado de uma bolinha e aproveita e calcula os pontos de sua movimentacao
{
  /// bolinha inativa nao faz nada
  if (!pb->ativa) return;
  if (!pb->operante) return;
  /// altera a posicao
  movimenta_bola(&pb->circ, &pb->vel, pe->ret);
}

void movimenta_bola(circulo *c, ponto *v, retangulo r)/// altera a movimentação da bola lançada
{
  /// atualiza posição com velocidade
  c->centro.x += v->x;
  c->centro.y += v->y;
}

void altera_bola_cobra(bola *pbc, estado *pe2)/// atualiza o estado da bolas na cobra para movimentação
{
  movimenta_bola_cobra(&pbc->circ,&pbc->vel,&pe2);
}

void movimenta_bola_cobra(circulo *c,ponto *v, estado *t)///movimenta as bolinhas pelo caminho
{
  /// atualiza posição com velocidade
  if(c->centro.x<=LARG-75 && c->centro.y==50)c->centro.x += t->velocidade;
  if(c->centro.x>=LARG-75 && c->centro.y<=ALT-75)c->centro.y += t->velocidade;
  if(c->centro.y>=ALT-75 && c->centro.x>=73)c->centro.x -= t->velocidade;
  if(c->centro.y>=125 && c->centro.x<=73)c->centro.y -= t->velocidade;
  if(c->centro.y==125 && c->centro.x<=LARG-150)c->centro.x += t->velocidade;
  if(c->centro.y<=ALT-160 && c->centro.x==LARG-150 && c->centro.y>=124)c->centro.y += t->velocidade;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///**************************************************************processamento de entradas ******************************************************************/
void verifica_rato(estado *t)///verifica as condições do mouse
{
  // se o mouse ta apertado, aumenta a forca
  if (tela_rato_apertado()) {
    t->forca=5;////////////////////////////força atira
  } else {
    // se o mouse ta solto e tem forca, foi solto agora
    if (t->forca > 0) {
      lanca_bolinha(t);
      t->forca = 0;
    }
  }
}

void altera_alvo(estado *t)///estado do alvo
{
  t->alvo.centro = tela_pos_rato();
}

void lanca_bolinha(estado *t)/// lanca a bolinha em direcao ao alvo
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
      t->bolinha[i].ativa = true;
    }
  }
  t->clic++;
  if(t->clic == nmax_b_mira+1) t->clic = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///****************************************************************inicializações do game********************************************************************/
///inicialização e restart do game
void inicializa_estado(estado *t)///inicializa todas funções do game
{

  t->clic = 0;
  t->ret.origem.x = 0;
  t->ret.origem.y = 0;
  t->ret.tam.l = LARG;
  t->ret.tam.h = ALT;
  t->velocidade = 1;
  t->play=false;
  t->sobre=false;
  t->recordes=false;
  t->perdeu=false;
  t->trocafase=false;
  t->fase=1;
  t->mult=0;
  t->n_vezes=0;
  t->num_cores=3;
  t->n_b_cobra= 20;
  inicializa_bolas_cobra(t);
  //inicializa_bolas_mira(t);

  t->pontos = 0;
  t->alvo.centro = tela_pos_rato();
  t->alvo.raio = 10;
  t->forca = 0;
  t->agora = tela_agora();
}

void reinicia_fase(estado *t)///reinicia a inicialização sem modificar algumas coisas
{
  t->clic = 1;
  t->ret.origem.x = 0;
  t->ret.origem.y = 0;
  t->ret.tam.l = LARG;
  t->ret.tam.h = ALT;
  t->velocidade = 1;
  t->play=false;
  t->sobre=false;
  t->recordes=false;
  t->perdeu=false;
  t->trocafase=false;
  t->fase+=1;
  t->mult=0;
  t->n_vezes=0;
  t->num_cores+=1;
  t->n_b_cobra+=10;
  if(t->num_cores>9){
    t->num_cores=9;
  }

  inicializa_bolas_cobra(t);
  inicializa_bolas_mira(t);
  t->alvo.centro = tela_pos_rato();
  t->alvo.raio = 10;
  t->forca = 0;
  t->agora = tela_agora();
}

void inicializa_bolas_cobra(estado*t)/// inicialização das bolinhas do caminho
{
  int i,aux=0;
  for(i=0; i<nmax_b_cobra; i++){
    t->bolas_cobra[i].circ.centro.x =aux;
    t->bolas_cobra[i].circ.centro.y = 50;
    t->bolas_cobra[i].circ.raio = 14;
    t->bolas_cobra[i].vel.x = t->velocidade;
    t->bolas_cobra[i].vel.y = t->velocidade;
    t->bolas_cobra[i].id=i;
    if(i<t->n_b_cobra){
      t->bolas_cobra[i].c = 1 + ( rand() % t->num_cores);
      t->bolas_cobra[i].ativa = true;
    }if(i>=t->n_b_cobra){
      t->bolas_cobra[i].c = transparente;
      t->bolas_cobra[i].ativa = false;
    }
    aux-=28;
  }
}

void inicializa_bolas_mira(estado *t)/// inicialização das bolinhas para lançamento
{
  int i;
  for(i=0; i<nmax_b_mira; i++){
    t->bolinha[i].circ.centro.x = LARG/2;
    t->bolinha[i].circ.centro.y = ALT/2;
    t->bolinha[i].circ.raio = 14;
    t->bolinha[i].vel.x = 0;
    t->bolinha[i].vel.y = 0;
    t->bolinha[i].c = 1 + ( rand() % t->num_cores );
    t->bolinha[i].ativa = false;
    t->bolinha[i].operante = true;
  }
}

void rand_cores(bola trocacor,estado *t)///função rand para as cores
{
   int i, cont=0;
   for(i=0;i<nmax_b_cobra;i++){
     if(trocacor.c==t->bolas_cobra[i].c)cont++;
   }
   if(cont == 0){
     trocacor.c = 1 + ( rand() % t->num_cores );
     rand_cores(trocacor,t);
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///****************************************************************colisôes do jogo**************************************************************************/
bool colisao_bola_cobra(bola b,bola central)///verifica se a bolinha colidiu em umaa bola da cobra
{//recebe 1° bola do canhão 2° bola da cobra
  if(sqrt( pow(b.circ.centro.x - central.circ.centro.x, 2)+pow(b.circ.centro.y - central.circ.centro.y, 2)) <= central.circ.raio + b.circ.raio){
    printf("entrou no colidiu\n");
    return 1;
  }
  return 0;
}

bool colisao_bola_cobra_posicao_ocp(bola b,bola frente,bola atras)///verifica a posição que ira inserir na cobra a bolinha
{
  float Dfrente,Datras;
  if(b.ativa==true){
    Dfrente = sqrt( pow(b.circ.centro.x - frente.circ.centro.x, 2)+pow(b.circ.centro.y - frente.circ.centro.y, 2));
    Datras = sqrt( pow(b.circ.centro.x - atras.circ.centro.x, 2)+pow(b.circ.centro.y - atras.circ.centro.y, 2));
    if(frente.ativa && atras.ativa){
      if(Dfrente>=Datras){
        return 0;
      }if(Dfrente<Datras){
        return 1;
      }
    }
    if(!atras.ativa){
      return 1;
    }if(!frente.ativa){
      return 0;
    }
  }
  return -1;
}

void colisao_bola_3oumais_colidiu(int k,estado*t)///verifica se são 3 cores ou + que colidiu
{
  int i;
  int SOMA;
  int contD=0,contE=0;
  for(i=k; t->bolas_cobra[k].c==t->bolas_cobra[i].c;i++){
   if(t->bolas_cobra[i].c==t->bolas_cobra[i+1].c && t->bolas_cobra[i+1].ativa)contE++;
   printf("esquerda------%d\n\n", contE);
  }for(i=k; t->bolas_cobra[k].c==t->bolas_cobra[i].c;i--){
   if(t->bolas_cobra[i].c==t->bolas_cobra[i-1].c && t->bolas_cobra[i-1].ativa)contD++;
   printf("direita-----%d\n\n", contD);
  }
  if(contD+contE+1>=3){
    remover_da_cobra (k,contD,contE,t);
    SOMA = contD+contE+1;
    pontuacao(SOMA,t);
  }if(contD+contE+1<3){
    t->bonus=false;
  }
}

void pontuacao(int n_bolas, estado *t)/// multiplica as pontuações e modifica na struct
{
  if(t->bonus==false && t->perdida==false){
    t->pontos+=n_bolas * 10;
    t->n_vezes=n_bolas;
    t->mult=10;
  }
  if(t->bonus==true && t->perdida==false){
    t->pontos+=n_bolas * 15;
    t->n_vezes=n_bolas;
    t->mult=15;
  }if(t->perdida==true){
    t->pontos-=n_bolas * 7;
    t->n_vezes=n_bolas;
    t->mult=7;
    if(t->pontos<=0)t->pontos=0;
  }
  t->bonus=false;
  t->perdida=false;
}

void remover_da_cobra (int k, int direita, int esquerda ,estado *t)///se colidiu e formou 3 cores ou mais remove as bolas da cobra
{
 int i, j;
 for (i=0;i<=k+esquerda; i++);
 for (i=0;i<=k-direita; i++);
 for(j=k-direita; t->bolas_cobra[j].ativa ; j++){
   t->bolas_cobra[j].c = t->bolas_cobra[j+esquerda+direita+1].c;
   t->bolas_cobra[j].ativa = t->bolas_cobra[j+esquerda+direita+1].ativa;
 }
 t->bonus=true;
 colisao_bola_3oumais_colidiu(k-direita-1,t);
}

void inserir_na_cobra (int k,bola nova,estado *t)///se colidiu insere a bolinha que colidiu na cobra e verifica se formou um conjunto com 3 cores
{///recebe o numero da bola colidida e o estado do game
  int i, j;
  for (i=0;t->bolas_cobra[i].ativa; i++);
  for(j=i; j>=k ; j--){
    t->bolas_cobra[j+1].c = t->bolas_cobra[j].c;
    t->bolas_cobra[j+1].ativa = t->bolas_cobra[j].ativa;
  }
  t->bolas_cobra[k].c = nova.c;
  t->bolas_cobra[k].ativa = nova.ativa;
  colisao_bola_3oumais_colidiu(k,t);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///****************************************************************desenhos do jogo**************************************************************************/
///* funcao principal do desenho da tela *///
/// Desenho de uma tela
/// limpa a tela, desenha todos os elementos visuais de acordo com o estado,
/// faz a tela ser mostrada
void desenha_tela(estado *t)
{
  int i,j,contfase=0;
  tela_limpa();
  desenha_contorno(t);
  desenha_caminho();
  desenha_canhao(t);
  desenha_pontos(t);
  desenha_pause();// desenha a frase pause no meio superior da tela
  desenha_fase(t);
  desenha_somador_pont(t->n_vezes,t->mult,t);
  for(i=nmax_b_cobra; i>-1; i--){
    if(t->bolas_cobra[i].ativa){
      desenha_bola(t->bolas_cobra[i]);
    }
  }
  desenha_bolas_no_carregador(t);
  for(i=0;i<nmax_b_mira;i++){
    for(j=0;j<nmax_b_cobra;j++){
      if(colisao_bola_cobra(t->bolinha[i],t->bolas_cobra[j])==1 && t->bolas_cobra[j].c!=transparente){
        if(colisao_bola_cobra_posicao_ocp(t->bolinha[i],t->bolas_cobra[j+1],t->bolas_cobra[j-1])==1){
          inserir_na_cobra (j+1,t->bolinha[i],t);
        }if(colisao_bola_cobra_posicao_ocp(t->bolinha[i],t->bolas_cobra[j+1],t->bolas_cobra[j-1])==0){
          inserir_na_cobra (j-1,t->bolinha[i],t);
        }if(colisao_bola_cobra_posicao_ocp(t->bolinha[i],t->bolas_cobra[j+1],t->bolas_cobra[j-1])==-1){
          inserir_na_cobra (j,t->bolinha[i],t);
        }if(t->bolas_cobra[j].ativa){
          t->bolinha[i].circ.centro.x=-200;
          t->bolinha[i].circ.centro.y=-200;
          t->bolinha[i].operante=false;
        }if(!t->bolas_cobra[j].ativa){
          t->bolinha[i].circ.centro.x=-200;
          t->bolinha[i].circ.centro.y=-200;
          t->bolinha[i].operante=false;
        }
      }
      if(t->bolinha[i].circ.centro.x<-30 && t->bolinha[i].operante==true){
        t->bolinha[i].operante=false;
        t->perdida=true;
        pontuacao(1,t);
      }
      if(t->bolinha[i].circ.centro.x>LARG+30 && t->bolinha[i].operante==true){
        t->bolinha[i].operante=false;
        t->perdida=true;
        pontuacao(1,t);
      }
      if(t->bolinha[i].circ.centro.y>ALT+30 && t->bolinha[i].operante==true){
        t->bolinha[i].operante=false;
        t->perdida=true;
        pontuacao(1,t);
      }
      if(t->bolinha[i].circ.centro.y<-30 && t->bolinha[i].operante==true){
        t->bolinha[i].operante=false;
        t->perdida=true;
        pontuacao(1,t);

      }
    }
  }
  for(j=0;j<nmax_b_cobra;j++){
    if(t->bolas_cobra[j].c==transparente)contfase++;
    if(contfase == nmax_b_cobra)t->trocafase = true;
  }if(t->trocafase == true){
    //ContaBonusDist();///****************************************
  }
  desenha_alvo(t->alvo);
  tela_atualiza();
}

///* funcoes auxiliares para o desenho da tela *///
void desenha_canhao(estado *t)///desenha o canhão///////->>>>>>>>>>correção tamanho do canhão<<<<<<<<<<<<<<<<<////////////
{
  circulo ccanhao= {LARG/2,ALT/2,20};
  tela_circulo(ccanhao, 2, preto, tela_cria_cor(0.34, 0.428, 0.188));
  ponto dir;
  dir.x = t->alvo.centro.x;
  dir.y = t->alvo.centro.y;
  ponto pCANOX = { dir.x,dir.y};
  ponto pCANOY = { LARG/2, ALT/2 };
  tela_linha(pCANOX, pCANOY, 10, preto);

}

void desenha_alvo(circulo c)///desenha a mira no local do mouse
{
  tela_circulo(c, 2, preto, transparente);
}

void desenha_bolas_no_carregador(estado *t)///desenha a bolinha de espera para avançar para a ponta do canhão
{
   int i;
   for(i=nmax_b_mira; i>=0; i--){
     desenha_bola(t->bolinha[i]);
   }for(i=nmax_b_mira; i>=0; i--){
     desenha_bola(t->bolinha[i]);
   }
}

void desenha_contorno(estado *t)/// desenha a area branca na tela
{
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50),tela_cria_cor(0.50, 0.50, 0.50));
}

void desenha_bola(bola b)/// desenha uma bola
{
  tela_circulo(b.circ, 1, b.c, b.c);
}

void desenha_pontos(estado *t)/// desenha os pontos
{
  // os pontos aparecem em verde, embaixo, a esquerda
  ponto p = { 35, ALT-55 };
  char s[20];
  sprintf(s, "%d", t->pontos);
  tela_texto_dir(p, 35, verde, s);
}

void desenha_pause()///desenha frase pause durante o jogo localizada no centro superior da tela
{
  char pause[]="pause (p minusculo)";
  ponto p = { 400, 10 };
  tela_texto(p, 10, verde, pause);
}

void desenha_fase(estado *t)///desenha frase fase durante o jogo localizada no canto esquerdo superior da tela
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

void desenha_caminho()///desenha o caminho
{
  ponto p1X = { 0, 50 };
  ponto p1Y = { LARG-75, 50 };
  tela_linha(p1X, p1Y, 5, preto);
  ponto p2X = { LARG-75, 48 };
  ponto p2Y = { LARG-75, ALT-73 };
  tela_linha(p2X, p2Y, 5, preto);
  ponto p3X = { 73, ALT-75 };
  ponto p3Y = { LARG-75, ALT-75 };
  tela_linha(p3X, p3Y, 5, preto);
  ponto p4X = { 75, 125 };
  ponto p4Y = { 75, ALT-75 };
  tela_linha(p4X, p4Y, 5, preto);
  ponto p5X = { 72, 125 };
  ponto p5Y = { LARG-150, 125 };
  tela_linha(p5X, p5Y, 5, preto);
  ponto p6X = { LARG-150, ALT-175 };
  ponto p6Y = { LARG-150, 122 };
  tela_linha(p6X, p6Y, 5, preto);
  circulo c_caminho= {LARG-150,ALT-160,15};
  tela_circulo(c_caminho, 5, preto, transparente);
}

void desenha_copyright()/// desenha a frase na parte inferior dos menus iniciar e final
{
  // desenha mensagem de direitos autorais na parte central e inferior da tela no menu encerramento
  char copyright[]="Copyright 2017, Todos os direitos reservados";
  ponto pc = { 400, 550 };
  tela_texto(pc, 10, azul, copyright);
  char autor[]="JULIANO SOARES";
  ponto paut = { 400, 560 };
  tela_texto(paut, 10, azul, autor);
}

void desenha_pontos_final(estado *t)/// desenha a pontuação adquirida pelo jogador no fim de jogo
{
  // os pontos aparecem em azul, meio
  ponto p = { 400, ALT-500 };
  char s[20];
  sprintf(s, "%d", t->pontos);
  tela_texto(p, 20, azul, s);
}

void desenha_pause2()///desenha palavra durante a pausa no jogo no centro da tela
{
  char pause[6]={'P','A','U','S','E'};
  ponto p = { 400, 300 };
  tela_texto(p, 50, preto, pause);
  tela_atualiza();
}

void  desenha_somador_pont(int x, int m,estado *t)/// desenha o multiplicador
{
  if(t->mult==7){
    ponto g = { 200, ALT-40 };
    char s[20];
    sprintf(s, "- %d X %d", x, m);
    tela_texto(g, 35, azul, s);
  }else{
    ponto g = { 200, ALT-40 };
    char s[20];
    sprintf(s, "+ %d X %d", x, m);
    tela_texto(g, 35, azul, s);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///****************************************************************aberturas e menus do jogo*****************************************************************/
///mostra o menu inicial do game
///mostra o menu do final do game
///mostra o menu de recordes do game
///mostra o menu de instruções do  game
///função de termino do game
///animações de inicio e fim do game
void menu_inicial_do_game(estado *t)///menu inicial com areas clicaveis
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

  //desenha area clicavel de recordes do jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 320;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50),tela_cria_cor(0.50, 0.50, 0.50));
  char pontosR[]="RECORDES";//desenha a palavra
  ponto pREC = { 400, 345 };
  tela_texto(pREC, 35, azul, pontosR);

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

void menu_final_do_game(estado *t)///menu final com areas clicaveis
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
  char s[]="SCORE";//desenha a palavra
  tela_texto(p, 20, azul, s);

  //desenha a frase de fim na parte meio inferior
  //int tam = 35;
  char y[]="GAME OVER";//desenha a palavra em posiçoes diferentes para dar um efeito
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
  char reiniciar[]="REINICIAR";//desenha a palavra
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

    //desenha area clicavel de recordes do jogo
  t->ret.origem.x = 300;
  t->ret.origem.y = 260;
  t->ret.tam.l = 200;
  t->ret.tam.h = 50;
  tela_retangulo(t->ret, 5, tela_cria_cor(0.50, 0.50, 0.50),tela_cria_cor(0.50, 0.50, 0.50));
  char pontosR[]="RECORDES";//desenha a palavra
  ponto pREC = { 400, 285 };
  tela_texto(pREC, 35, azul, pontosR);

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

void recordes(estado *t)///menu recordes
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
  listar();
  desenha_copyright();//desenha frase de direitos autorais
  //correção para aparecer a bolinha do mouse nas aberturas e encerramento
  altera_estado(t);//chama altera estado para póder mudar posição do mouse
  desenha_alvo(t->alvo);//desenha alvo no mouse
  tela_atualiza();
}

void sobre(estado *t)///menu de informações e instruções do jogo
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
  char tx3[]="->Não as bolinhas do cominho chegarem ao fim;";
  ponto ptx3 = { 110, 140 };
  tela_texto_dir(ptx3, 15, preto, tx3);
  char tx4[]="Instruções:";
  ponto ptx4 = { 110, 175 };
  tela_texto_dir(ptx4, 15, azul, tx4);
  char tx5[]="->O mouse movimenta todo o jogo;";
  ponto ptx5 = { 110, 190 };
  tela_texto_dir(ptx5, 15, preto, tx5);
  char tx6[]="->O canhão é a origem da saida das outras bolinhas;";
  ponto ptx6 = { 110, 205 };
  tela_texto_dir(ptx6, 15, preto, tx6);
  char tx7[]="->A pontuação aumenta conforme o numero de bolas é destruido;";
  ponto ptx7 = { 110, 220 };
  tela_texto_dir(ptx7, 15, preto, tx7);
  char tx8[]="->Quanto mais longe do fim destruir todas bolinhas ganha mais bonus;";
  ponto ptx8 = { 110, 235 };
  tela_texto_dir(ptx8, 15, preto, tx8);
  desenha_copyright();//desenha frase de direitos autorais
  //correção para aparecer a bolinha do mouse nas aberturas e encerramento
  altera_estado(t);//chama altera estado para póder mudar posição do mouse
  desenha_alvo(t->alvo);//desenha alvo no mouse
  tela_atualiza();
}

void abertura(void)/// animação fantastica que aparece quando o jogo começa
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
      x[j]=rand() % LARG;
      y[j]=rand() % ALT;
      circulo c={ x[j],y[j],rr};
      tela_circulo(c, 5,j, j);
    }
    tela_texto(p, t, vermelho, inicial);
    if(t<50)t+=5;
    i++;
    tela_atualiza();
  }
}

void encerramento(void)/// animação de despedida
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
      x[j]=rand() % LARG;
      y[j]=rand() % ALT;
      circulo c={ x[j],y[j],rr};
      tela_circulo(c, 5,j, j);
    }
    tela_texto(p, t, vermelho, inicial);
    if(t<50)t+=5;
    i++;
    tela_atualiza();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///****************************************************************arquivos do game*****************************************************************/
///
void compara_pontuacao(estado *t,rarquivo *s)
{

}

void listar()
{
  FILE *arquivo;
  char nome[5];
  int pontosscore;
  //arquivo = abre_arquivo('l', "recordes.txt");
  while(!feof(arquivo)){
    fscanf(arquivo, "%s %d", &nome, &pontosscore);
    printf("%s %d", nome, pontosscore);
  }
  fechar_arquivo(arquivo);
}

bool abre_arquivo(char modo, char caminho[30])
{
  FILE *arquivo;
  switch(modo){
    case 'g':
      arquivo =fopen(caminho, "w+");
      break;
    case 'l':
      arquivo = fopen(caminho, "r+");
      break;
  }
  if(!arquivo){
    printf("não foi possivel abrir o arquivo");
    exit(0);
  }
  return arquivo;
}

void fechar_arquivo(FILE *arquivo)
{
  fclose(arquivo);
}

//void compara_recordes
