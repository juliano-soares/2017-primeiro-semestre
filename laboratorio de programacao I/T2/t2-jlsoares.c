// Nome: JULIANO LEONARDO SOARES Matricula: 201713854

/*Faça um programa que lê um valor, que pode ser 1 ou 2. Caso o valor lido seja 1, ele deve ler mais seis valores,
que representam duas datas. O programa deve então imprimir uma linha com o número de dias entre a primeira e a
segunda datas (pode ser negativo). Caso o primeiro valor lido seja 2, ele deve ler mais quatro valores, que
representam uma data e um número de dias, e deve imprimir uma linha com 3 valores que representam uma data que
fica o número de dias depois (ou antes, se o número de dias for negativo) da data informada.*/

#include<stdio.h>
#include<stdbool.h>

 // retorna true se o ano a for bissexto
bool bissexto(int a)
{
  if(a%4==0 && (a%400==0||a%100!=0)){//verifica se a variavel ano é bissexto e retorna true se bissexto e false se não é bissexto
    return true;
  }
  else{
    return false;
  }
}
  // retorna quantos dias tem no ano a
int dias_no_ano(int a)//recebe a variavel ano
{
  if(bissexto(a)){//envia a variavel ano para a função que identifica se o ano e bissexto ou não e recebe se é true ou false
    return 366;
  }
  else{
    return 365;
  }
}

  // retorna quantos dias se passaram desde o início do ano
  // exemplo: 2 de fevereiro retorna 33
int dia_do_ano(int dia, int mes, int ano)
{
  int soma=0,i,total=0, quant_de_dias, dia_do_ano;
  for(i=1;i < mes;i++){      //percorre o mes e diz quantos dias tem nele
    if(i==2){
      if(bissexto(ano)){
        quant_de_dias=29;
      }
      else{
        quant_de_dias=28;
      }
    }
    if(i>0 && i!=2 && i<=7){
      if(i%2==0){
        quant_de_dias=30;
      }
      else if(i%2!=0){
        quant_de_dias=31;
      }
    }
    if(i>=8 && i<=12){
      if(i%2==0){
        quant_de_dias=31;
      }
      else if(i%2!=0){
        quant_de_dias=30;
      }
    }
    soma = soma + quant_de_dias; //soma os dias dos meses
  }
  total=soma+dia; //somas os dias dos meses mais os dias recebidos
  return total;
}

  // retorna true se data for válida
bool data_valida(int dia, int mes, int ano)
{
  if( mes<1 || mes>12 ){//verifica se o mes esta no interva se não retorna data invalida
    return false;
  } else if(mes==2){//verifica para fevereiro se o dia esta correto
    if(bissexto(ano)){
      if(dia>0 && dia<30){//se bissexto o dia deve estar no intervalo 0<dia<30
        return true;
      }
    } else if(dia>0 && dia<29){//se não bissexto o dia deve estar no intervalo 0<dia<29
      return true;
    }
  } else if(mes>0 && mes<8 && mes!=2 ){//verifica o dia nos meses de 1 a 7 exceto fevereiro
    if(mes%2==0 && dia>0 && dia<31){//para meses pares o dia deve ficar no intervalo 0<dia<31
      return true;
    } else if(mes%2!=0 && dia>0 && dia<32){//para meses impares o dia deve ficar no intervalo 0<dia<32
      return true;
    }
  } else if(mes>7 && mes<13){//verifica o dia nos meses de 8 a 12
    if(mes%2==0 && dia>0 && dia<32){//para meses pares o dia deve ficar no intervalo 0<dia<32
      return true;
    } else if(mes%2!=0 && dia>0 && dia<31){//para meses impares o dia deve ficar no intervalo 0<dia<31
      return true;
    }
  }
  return false;
}
  // retorna nas referências uma data que é dd dias após a data d, m, a
  // dd pode ser negativo
  // retorna true se ok, false se d, m, a inválida
bool data_apos(int dia, int mes, int ano, int dd, int *d2, int *m2, int *a2)//dd = diferença de dias
{
  int diasdomes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//vetor para ver quantos dias tem cada mes
  if (bissexto(ano)) {
    diasdomes[1]=29;// se ano bissexto troca para 29 o vetor na posição 1 que representa fevereiro
  }
  if(data_valida(dia, mes, ano)){
    dia=dia+dd;// pega o dia mais o diferença de dias para somar ou subtrair
    if ( dia>diasdomes[mes-1] ){
      while ( dia>diasdomes[mes-1] ){//vai retirando os dias e aumentando o mes
        dia = dia - diasdomes[mes-1];
        mes++;
        if ( mes>12 ) {
          ano++;//incrementa o ano e retorna o mes devolta para janeiro
          mes=1;
        }
      }
    } else if ( dia<=0 ){//para subtrair dias da data
      while ( dia<=0 ) {
        dia = dia + diasdomes[mes-2];// vai somando os dias e decrentando o mes
        mes--;
        if ( mes<1 ) {
          ano--;    //retorna para o ano anterior e coloca as datas para o ultimo dia do ano
          dia=31;
          mes=12;
        }
      }
    }
    *d2=dia;
    *m2=mes;
    *a2=ano;
    return true;
  } else {
    return false;
  }
}

// função que soma os dias entre dois anos
//essa função recebe os anos e soma os dias entre elas
int soma_as_datas(int ano1, int ano2){
  int i, soma_dias=0;
  for(i=ano1+1; i<ano2; i++){
    soma_dias = soma_dias + dias_no_ano(i);//é usada nessa parte a função dias_no_ano que retorna os dias para somar inclusive se for bissexto
  }
  return soma_dias;
}

  // retorna na referência o número de dias desde d1m1a2 até d2m2a2
  // retorna true se ok, false se alguma data inválida
bool dias_entre(int d1, int m1, int a1, int d2, int m2, int a2, int *dd)
{
  int soma, dia_a_somar, dias_a_subtrair, resultado;
  if ( data_valida(d1,m1,a1) && data_valida(d2,m2,a2) ){ //envias as variaveis para verificar se as datas são validas, se sim continua a função se não retorna true
    if (a1<a2){ //compara os anos
      resultado = (dias_no_ano(a1) - dia_do_ano(d1,m1,a1)) + soma_as_datas(a1,a2) + dia_do_ano(d2,m2,a2);//o resultado é o os dias entre o 1º e o 2º e subtrai os dias ja iniciados do 1º e soma os dias do 2º.
    } else if (a2<a1){//compara os anos
      resultado = -( (dias_no_ano(a2) - dia_do_ano(d2,m2,a2)) + soma_as_datas(a2,a1) + dia_do_ano(d1,m1,a1) );//inverte o sinal caso a1>a2
    } else if(a1==a2 && m1==m2){//compara os anos
      resultado=d1-d2; //se mes e ano igual so soma ou subtrai os dias
    }
    else {//se for mesmo ano mas meses diferente so subtrai os dias
      resultado = dia_do_ano(d2,m2,a2) - dia_do_ano(d1,m1,a1);
    }
    *dd = resultado;
    return true;
  }
  else {
    return false;
  }
}

int main(void)
{
  while(true){
    int opcao; //variavel para o switch
    int dia1,mes1,ano1,dia2,mes2,ano2; //variaveis para o caso 1
    int dia, mes, ano, dif, d2, m2, a2; //variaveis para o caso 2: dif=diferença de dias
    bool ok;//variavel booleana para verificar se data e valida
    printf("escolha uma opcao: \n1:Quantos dias tem entre datas \n2:Diferenca de dias \n\n");
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
      scanf("%d %d %d", &dia1, &mes1, &ano1);
      scanf("%d %d %d", &dia2, &mes2, &ano2);
      ok = dias_entre(dia1, mes1, ano1, dia2, mes2, ano2, &dif);//envia variaveis para a função, o ok serve para ver se retorna data valida ou não
      if(ok){
        printf("%d\n", dif);
      }
      else {
        printf("x\n");
        return 0;
      }
      break;
      case 2:
      scanf("%d %d %d", &dia, &mes, &ano);
      scanf("%d", &dif);
      ok=data_apos(dia, mes, ano, dif, &d2, &m2, &a2);//envia variaveis para a função, o ok serve para ver se retorna data valida ou não
      if(ok){
        printf("%d %d %d\n", d2, m2, a2);
      }
      else {
        printf("x\n");
        return 0;
      }
      break;
    }
  }
}
