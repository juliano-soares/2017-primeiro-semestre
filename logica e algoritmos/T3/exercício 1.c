//JULIANO LEONARDO SOARES MATRICULA 201713854
//1- Escreva um programa que lê um vetor de 7 elementos. Cada valor deve ser um
//número entre 0 e 9. Após o programa deve dizer se os M dígitos do vetor representam
//ou não um número palíndromo (número igual lido de trás para frente).
//Exemplos de palíndromos:
//Vetor = {1, 2, 3, 4, 3, 2, 1}.
//Vetor = {9, 8, 4, 2, 2, 4, 8, 9}.
#include<stdio.h>

void main(void)
{
   int v1[7];
   int i, j, palindromo;
   printf("Para comparar uma sequencia de 7 numeros e dizer se e um palindromo:\n");
   for (i=0; i<7; i++) {
      printf("Informe o %2d\xa7. elemento de 7: ", (i+1));
      scanf("%d", &v1[i]);
      if(v1[i]<0 || v1[i]>10){
         printf("numero não permitido\n digite um numero entre 0 e 9:\n");
         i--;
      }
   }

   i = 0; // posicoes iniciais do vetor
   j = 6; // posicoes finais do vetor
   palindromo = 1; // flag que indicara se o vetor eh palindromo ou nao
   while ((i < j) && (palindromo == 1)) {
     if (v1[i] != v1[j])
        palindromo = 0; // nao eh palindromo
     else {
       i = i + 1;
       j = j - 1;
     }
   }

   if (palindromo == 1){
      printf("\nOs elementos do vetor formam um palindromo.");
   }
   else {
      printf("\nOs elementos do vetor \"nao\" formam um palindromo.");
   }
}
