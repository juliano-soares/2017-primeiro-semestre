//nome: JULIANO LEONARDO SOARES matricula:201713854 professor:BENHUR STEIN
//Programa sobre coordenadas dentro de uma casa com areas restritas aonde deve mostrar a localidade e se é retrito o local ou não apartir das coordenadas.
#include<stdio.h>
#include <stdbool.h>
main()
{
  float d, x, y;
  bool corredor = true, inHOME = false, origem = false;//devido eu colocar a area do corredor grande devo deixar ativada e desativar nas area onde nao e corredor
  printf("Digite a coordenada x: ");
  scanf("%f", &x);
  printf("Digite a coordenada y: ");
  scanf("%f", &y);

  float b1,c1,d1,r1;//compara a distancia do individuo com o primeiro ap
  b1 = x - 10;
  c1 = y - 8.5;
  d1 = (b1*b1) + (c1*c1);
  r1 = 100;

  float b2,c2,d2,r2;//compara a distancia do individuo com o segundo ap
  b2 = x - 13;
  c2 = y - -11;
  d2 = (b2*b2) + (c2*c2);
  r2 = 100;

  float b3,c3,d3,r3;//compara a distancia do individuo da origem
  b3 = x;
  c3 = y;
  d3 = (b3*b3) + (c1*c1);
  r3 = 4;

//nesta parte eu começo verificando as ares onde ha restrições devido a proximidade dos ap
  if (x < 7 && x > -1 && y < 12 && y > 6.5) { // verifica a distancia do ap1
    corredor = false;// desativa a localização corredor
    inHOME = true;//indica que esta dentro de casa
    if(d1<=r1){
      printf("nOK, lavanderia, perto ap");
    }
    else {
      printf("OK, lavanderia");
    }
  }
  if (x<7 && x>2 && y<6.5 && y>5){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, lavanderia, comodo proibido, perto ap");
  }
  if (x<=2 && x>=-9 && y>=1 && y<=6.5){//verifica na area do comodo (elevador escadas) se ele não esta na origem e perto do ap
    inHOME = true;//indica que esta dentro de casa
    corredor = false;// desativa a localização corredor
    if(d2<=r2){
      printf("NOK, elevador escadas, perto ap");
    }
    if(d3<=r3){
      printf("OK, elevador escadas na origem");
    }
    else{
      printf("NOK, elevador escadas, comodo proibido");
    }
  }
  if (x<13 && x>5 && y<2 && y>-2){// verifica as area distantes de AP
    inHOME = true;//indica que esta dentro de casa
    if(d1 <= r1 || d2 <= r2 ){//verifica se esta perto do AP1 e/ou perto do AP2
      printf("NOK, sala de reunioes 02, perto ap1");
    }
    else{
      printf("OK, sala de reunioes 02,Parte livre");
    }
  }
  if (x<4 && x>=2 && y<=5 && y>=2){// verifica as area distantes de AP
    if(d1<=r1){
      printf("NOK, banheiro 4, perto ap1");
    }
    else{
      printf("OK, banheiro 4, comodo livre");
    }
    inHOME = true;//indica que esta dentro de casa
  }
  if (x<=5 && x>=-13 && y<=-1 && y>=-11){// verifica as area distantes de AP2
    inHOME = true;//indica que esta dentro de casa
    if(d2<=r2){
      printf("NOK, sala, perto ap2");
    }
    else{
      printf("OK, sala, comodo livre");
    }
  }
  if (x<=13 && x>5 && y<=-2 && y>=-11){//verifica se na area da sala ele esta perto do AP2
    inHOME = true;//indica que esta dentro de casa
    if(d2<=r2){
      printf("NOK, sala, perto ap2");
    }
    else{
      printf("OK, sala, comodo livre");
    }
  }
// esta parte so detecta se o individuo esta em um comodo pribido pois não ha restrições

  if (x<-13 && x>=-18 && y<=1 && y>=-5){
    printf("NOK, escritorio, comodo proibido");
    inHOME = true;//indica que esta dentro de casa
    corredor = false;// desativa a localização corredor
  }
  if (x<=-21 && x>=-26 && y<=14 && y>8){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, quarto 02, comodo proibido");
  }
  if (x<=-16 && x>=-21 && y<=14 && y>=8){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, quarto 03, comodo proibido");
  }
  if (x<=-13.5 && x>-16 && y<=10 && y>=8){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, quarto 03, comodo proibido");
  }
  if (x<=-11 && x>-13.5 && y<=10 && y>=8){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, quarto 04, comodo proibido");
  }
  if (x<=-6 && x>-11 && y<=14 && y>=8){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, quarto 04, comodo proibido");
  }
  if (x<=13 && x>=7 && y<=12 && y>5){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, cozinha, comodo proibido perto AP");
  }
  if (x<=13 && x>=4 && y<=5 && y>=2){
    inHOME = true;//indica que esta dentro de casa
    printf("NOK, sala de reunioes 1, comodo proibido perto ap");
  }
//esta parte so compara se o individuo esta em uma das partes permitidas
  if (x<-18 && x>=-26 && y<=1 && y>=-5){
    corredor = false;// desativa a localização corredor
    inHOME = true;//indica que esta dentro de casa
    printf("OK, quarto 01, comodo livre");
  }
  if (x<=-19.5 && x>=-24.5 && y<-5 && y>=-6){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, sacada, comodo livre");
  }
  if (x<=-21.5 && x>=-26.5 && y<=4 && y>=1){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, banheiro 3, comodo livre");
  }
  if (x<-21.5 && x>-26.5 && y<=6 && y>4){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, banheiro 2, comodo livre");
  }
  if (x<-21.5 && x>-26.5 && y<=8 && y>6){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, banheiro 1, comodo livre");
  }
  if (x<=-12 && x>=-21.5 && y<=6 && y>=3){
    corredor = false;// desativa a localização corredor
    inHOME = true;//indica que esta dentro de casa
    printf("OK, closet, comodo livre");
  }
  if (x<=-13.5 && x>=-16 && y<=14 && y>=10){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, banheiro 5, comodo livre");
  }
  if (x<=-11 && x>-13.5 && y<=14 && y>10){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, banheiro 6, comodo livre");
  }
  if (x<=-1 && x>-6 && y<=14 && y>=8){
    inHOME = true;//indica que esta dentro de casa
    printf("OK, dependencia dos empregados, comodo livre");
  }
  if (x<=2 && x>=-21.5 && y<8 && y>-1){
    inHOME = true;//indica que esta dentro de casa
    if (corredor == true){
     printf("OK, corredores:");
    }
  }
  if (x<5 && x>2 && y>-1 && y<2){
    inHOME = true;//indica que esta dentro de casa
    if(d1<=r1){
      printf("NOK, corredor, perto ap1");
    }
    else{
      printf("OK, corredor, comodo livre");
    }
  }
  if (inHOME == false){//indica se esta fora de casa
    printf("O individuo esta FORA DE CASA!!!");
  }
}
