//JULIANO LEONARDO SOARES MATRICULA 201713854

/*3- Crie um programa que l� dois vetores de n�meros inteiros. O primeiro vetor deve ter 5
posi��es e o segundo 6 posi��es. Os valores lidos devem estar entre 0 e 9. O programa
ent�o deve fazer a impress�o dos valores armazenados em cada vetor e imprimir um
novo vetor C que ser� composto por A U B (uni�o de A e B), portanto este n�o dever�
apresentar valores que sejam comuns em ambos os vetores.
Exemplo de impress�o:
A = 1 5 7 8
B = 6 1 5 9 7
C = 1 5 7 8 6 9*/
#include <stdio.h>

int main()
{
   int v1[5], v2[6];
   int uniao[10];
   int i, j, k, m;
   int n=0;
   printf ("digite o vetor 1: ");
   for (i = 0; i <5; i++)
   {
        scanf ("%d/n", &v1[i]);//pega os vetores
        if(v1[i]<0 || v1[i]>9){
            i--;
        }
   }
   printf ("digite o vetor 2: ");
   for (j=0; j<6; j++){
     scanf ("%d/n", &v2[j]);
     if(v1[i]<0 || v1[i]>9){
        i--;
     }
   }
/*analisa o primeiro vetor*/
   for(i=0; i<5; i++)
   {
      for(j=0; j<5; j++)
      {
         if(v1[i]!=v2[j])
         {
            for(k=0;k<n;k++)
            {
               if(v1[i]==uniao[k])
               break;
            }
            if(k==n)
            {
               uniao[n]=v1[i];
               n++;
            }
         }
      }

   }
/*analisa o segundo vetor, descartando repeti��es dentro do uniao[]*/
   for(i=0; i<6; i++)
   {
      for(j=0; j<6; j++)
      {
         if(v1[i]!=v2[j])
         {
            for(k=0;k<n;k++)
            {
               if(v2[j]==uniao[k])
                 break;
            }
            if(k==n)
            {
               uniao[n]=v2[j];
               n++;
            }
         }
      }
   }
   printf("Seus elementos da uniao sao:\n");
   for(m=0;m<n;m++)
   {
      printf("%i\n", uniao[m]);
   }
   return 0;
}
