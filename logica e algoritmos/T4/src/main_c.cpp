                ///////////////////////////////////
                //----JULIANO LEONARDO SOARES----//
                //----------201713854------------//
                //----------T4-DAMAS-------------//
                ///////////////////////////////////
                //FUNÇOES IMPLEMENTADAS
                  //CRIAÇÃO DO TABULEIRO
                  //CRIAÇÃO DAS PEÇAS
                  //CRIAÇÃO DO QUADRADO DE MOVIMENTO

#include "GL/glut.h"
#include "GL/freeglut_ext.h" //callback da wheel do mouse.


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "gl_canvas2d.h"
#define DIM_TELA 800
#define DIM_TELA_Y 600



//variaveis globais
int pos_quadradoX = 0;
int pos_quadradoY = 0;
int posicao_x = 0;
int posicao_y = 0;
int player_1=1;
int player_2=1;
int selecionado_2=0;
int tecla_liberada=1;
int selecao=0;

struct peca {
   int x, y;
   int id;
   int cor;
};

void desenha_quadrado()//arrumar a posição, ver o if
{
    int x;
    color(1,0,0);
    for(x=0; x<=5; x++) {
       rect(pos_quadradoX-x+5, pos_quadradoY-x+5, pos_quadradoX+70+x, pos_quadradoY+70+x);
    }
}

void desenha_pecas_player_1()
{
    int a=0, i=0;
    float x_c=37.5, y_c=37.5, raio = 35.5;
    for(a=0; a<2; a++) {
        for(i=0; i<4; i++) {
            color(1,1,1);//branco
            circleFill( x_c, y_c, raio, 100);
            player_1+=1;
            x_c+=150;
        }
        x_c=112.5;
        y_c+=75;
    }
    x_c=37,5;
    y_c=187.5;
    for(i=0; i<4; i++) {
        color(1,1,1);//preto
        circleFill( x_c, y_c, raio, 100);
        player_1+=1;
        x_c+=150;
    }

}

void desenha_pecas_player_2()
{
    int a=0, i=0, id=0;
    float x_c=112.5, y_c=562.5, raio = 35.5;
    int inp_x=7, inp_y=1;
    for(a=0; a<2; a++) {
        for(i=0; i<4; i++) {
            color(0,0,0);//preto
            circleFill( x_c, y_c, raio, 100);
            player_2+1;
            x_c+=150;
        }
        x_c=37.5;
        y_c+=-75;
    }
    x_c=112,5;
    y_c=412.5;
    for(i=0; i<4; i++) {
        color(0,0,0);//preto
        circleFill( x_c, y_c, raio, 100);
        x_c+=150;
    }
}

void qudrados_azuis()//desenha os quadrados azuis
{
    color(0, 0, 1);
    rectFill(0, 0, 600, 600);
}

void quadrados_verdes()//desenha os quadrados verdes
{
    int a, i, x1=0, x2=75, y1=0, y2=75;
    color(0.5, 0.5, 0); //colocar em função
    for(a=0; a<4; a++) {
        for(i=0; i<4; i++) {
            rectFill(x1, y1, x2, y2);
            x1+=150;
            x2+=150;
        }
        x1=0;
        x2=75;
        y1+=150;
        y2+=150;
    }
    x1=75;
    x2=150;
    y1=75;
    y2=150;
    for(a=0; a<4; a++) {
        for(i=0; i<4; i++) {
            rectFill(x1, y1, x2, y2);
            x1+=150;
            x2+=150;
        }
        x1=75;
        x2=150;
        y1+=150;
        y2+=150;
    }
}

void area_tabuleiro()//delimita a area do tabuleiro
{
    color(0, 0, 0);//preto
    line(0, 0, 0, 600);
    line(0, 0, 600, 0);
    line(600, 0, 600, 600);
    line(0, 600, 600, 600);
}

void textos_menus1()//faz textos no jogo
{
    color(0, 0.5, 1);//"azul"
    text(610,570,"DAMAS");
    color(0, 0, 0);//preto
    text(610,590,"<==Player 2");
    text(610,10,"<==Player 1");
}

void preenche_de_branco()//preenche fundo de branco
{
  color(1,1,1);//branco
  rectFill(0, 0, 800, 600);
}
//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
void render()
{

    clear(0,0,0);
    //preenche tudo de branco
    preenche_de_branco();
    //texto
    textos_menus1();
    //quadrados bege
    qudrados_azuis();
    //quadrados marrom
    quadrados_verdes();
    //área do tabuleiro
    area_tabuleiro();
    //peças player 1
    desenha_pecas_player_1();
    //peças player 2
    desenha_pecas_player_2();
    //desenha o quadrado
    desenha_quadrado();
    //desenha a pecça no novo lugar
}
//move o quadrado de selecao
void MoveQuadrado(int x, int y, int direcao)//direcao == 1, incrementa, direcao == 0 decrementa
{
    int g_x=1,g_y=1;
    if((pos_quadradoX + x < 600) && (pos_quadradoX + x >= 0) && y==0) {
        pos_quadradoX += x;
        if(g_x < 8 && direcao == 0) {
            g_x++;
        }
        if(g_x >= 0 && direcao == 1) {
            g_x--;
        }
        if(direcao==0){
            posicao_y+=1;
        }if(direcao==1){
            posicao_y-=1;
        }if(direcao==2){
            posicao_x+=1;
        }if(direcao==3){
            posicao_x-=1;
        }
    }
    if((pos_quadradoY + y < 600) && (pos_quadradoY + y >= 0) && x==0) {
        pos_quadradoY += y;
        if(g_y < 8 && direcao == 2) {
            g_y++;
        }
        if(g_y >= 0 && direcao == 3) {
            g_y--;
        }
        if(direcao==0){
            posicao_y+=1;
        }if(direcao==1){
            posicao_y-=1;
        }if(direcao==2){
            posicao_x+=1;
        }if(direcao==3){
            posicao_x-=1;
        }
    }
    desenha_quadrado();
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   switch(key)
   {
      case 27: //finaliza programa
	     exit(0);
        break;
	  case 201: //seta para cima
        MoveQuadrado(0, 75 ,0);
        break;
	  case 203: //seta para a baixo
        MoveQuadrado(0 , -75 ,1);
        break;
	  case 202: //seta para direita
        MoveQuadrado(75 , 0 , 2);
        break;
      case 200: //seta para esquerda
        MoveQuadrado(-75, 0,3);
        break;
      case 32:

          break;
   }
}
//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   y = DIM_TELA - y;
}

int main(void)
{
   initCanvas(DIM_TELA, DIM_TELA_Y, "Titulo da Janela: Canvas 2D");
   runCanvas();

}

