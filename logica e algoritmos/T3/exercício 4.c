// JULIANO LEONARDO SOARES MATRICULA 201713854
/*4- Faça um programa que preenche uma matriz M[3][4] com valores aleatórios de 0 à 10
(use função pronta rand). Após, realiza a impressão de uma matriz que terá como
elementos a soma de todos os elementos anteriores à posição equivalente da matriz
M. Exemplo:
    1 3 9 2                 1 4  13 15
M = 2 6 2 4 será impresso: 17 23 25 29
    7 4 5 6                36 40 45 51 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define lin 3
#define col 4
int main(void)
{
   int matriz [lin][col], matriz2 [lin][col]={0},aux=0;
   int i, j;
   printf("matriz a\n");
   for (i = 0; i <lin; i++)
   {
      for (j = 0; j <col; j++)
      {
         srand(time(NULL));//PREENCHE A MATRIZ A
         _sleep(800);
         matriz[i][j]=rand()%9+1;
         printf("%2d",matriz[i][j]);
      }
   printf("\n");
   }
   for (i = 0; i <lin; i++)
   {
     for (j = 0; j <col; j++) //INSERE OS VALORES NA NOVA MATRIZ COM AJUDA DO AUXILIAR
     {
        aux= matriz [i][j] + aux;
        matriz2 [i][j]=aux;
     }
   }
   printf("a nova matriz e:\n"); // IMPRIME A NOVA MATRIZ
   for (i = 0; i <lin; i++)
   {
     for (j = 0; j <col; j++)
     {
        printf("%2d  ",matriz2[i][j]);
     }
   printf("\n");
   }
}
