/*NOME DO ALUNO: JULIANO LEONARDO SOARES
/*LEIA O PROGRAMA FOI CRIADO EM SISTEMA OPERACIONAL WINDOWNS ENTÃO PEDERÁ OCORRER ERROS SE FOR EXECUTADO EM OUTRO SITAMA OPERACIONAL*/
/*USADO O CodeBlocks*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#define STRTAM 60   //tamanho das linhas nos menus
#define tam 500      //quantidade de produtos no controle de estoque

void cria_menu_linha_cima()//-------------------FUNÇÃO PARA CRIAR AS LINHAS SUPERIORES NOS MENUS---------------------------//
{
    int i;
    printf("%c", 201);
    for(i=0; i<STRTAM; i++)
       printf("%c", 205);
    printf("%c\n", 187);
}

void cria_menu_linha_baixo(int tamx)//-------------------FUNÇÃO PARA CRIAR AS LINHAS INFERIORES NOS MENUS---------------------------//
{
    int i;
    printf("%c", 200);
    for(i=0; i<STRTAM; i++)
       printf("%c", 205);
    printf("%c\n", 188);
}

void cria_menu_item(int tamx, char str[])//---------------------FUNÇÃO QUE CRIA AS LINHA LATERAIS COM AS PALAVRAS------------------------------//
{
    int conta_letras=0;
    int i;
    for(i=0;i<tamx;i++){
        if(str[i]=='\0'){
            break;
        }
        else{
            conta_letras++;
        }
    }
    printf("%c", 186);
    printf("%s", str);
    while(conta_letras<tamx){
        printf("%c", 32);
        conta_letras++;
    }
    printf("%c\n", 186);
}

void monta_menu_principal()//--------------------------------FUNÇÃO IMPRIME MENU USANDO AS FUNÇÕES DE CRIAÇÃO DE LINHAS----------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"       __________GESTAO DE ESTOQUE__________");
    cria_menu_item(STRTAM,"");
    cria_menu_item(STRTAM,"1 - CADASTRAR PRODUTO");
    cria_menu_item(STRTAM,"2 - EXCLUIR PRODUTO");
    cria_menu_item(STRTAM,"3 - LISTAR PRODUTOS");
    cria_menu_item(STRTAM,"4 - SAIR");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_excluir()//--------------------------------FUNÇÃO IMPRIME MENU EXCLUIR USANDO AS FUNÇÕES DE CRIAÇÃO DE LINHAS----------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"       __________EXCLUIR PRODUTO__________");
    cria_menu_item(STRTAM,"");
    cria_menu_item(STRTAM,"COMO DESEJA EXCLUIR O PRODUTO");
    cria_menu_item(STRTAM,"1- EXCLUIR POR CODIGO");
    cria_menu_item(STRTAM,"PARA RETORNA AO MENU DIGITE QUALQUER TECLA");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_cadastro()//--------------------------------FUNÇÃO IMPRIME MENU CADASTRO USANDO AS FUNÇÕES DE CRIAÇÃO DE LINHAS----------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"       __________CADASTRO DE PRODUTO__________");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_M1()//--------------------------------FUNÇÃO IMPRIME MENU DE CONTINUAÇÃO OU NÃO-------------------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"DESEJA EXCLUIR UM NOVO PRODUTO SE SIM DIGITE 1?");
    cria_menu_item(STRTAM,"\tOU QUALQUER TECLA PARA SAIR");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_de_opcao()//------------------------------------FUNÇÃO IMPRIME MENU DE OPÇÃO-----------------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"        __________DIGITE A OPCAO__________");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_de_opcao_cadastro()//-------------------------------FUNÇÃO IMPRIME MENU DE CADASTRO------------------------------------------//
{
    cria_menu_linha_cima();
    cria_menu_item(STRTAM,"     __________ESCOLHA UMA OPCAO__________");
    cria_menu_item(STRTAM,"");
    cria_menu_item(STRTAM,"1 - SE DESEJA CADASTRAR UM NOVO PRODUTO");
    cria_menu_item(STRTAM,"SE DESEJA VOLTAR AO MENU DIGITE QUALQUER OUTRO VALOR");
    cria_menu_linha_baixo(STRTAM);
}

void monta_menu_lista()//-------------------IMPRIME CABEÇALHO DA FUNÇÃO LISTA------------------------------------------------------//
{
    int i;
    for(i=0; i<62; i++){
       printf("%c", 205);
    }
    printf("\n");
    printf("\t\t__________PRODUTOS__________\n");
}

void monta_menu_lista_baixo()//---------------IMPRIME RODAPE DA FUNÇÃO LISTA------------------------------------------------------//
{
   int i;
    for(i=0; i<62; i++){
       printf("%c", 205);
    }
    printf("\n");
}

typedef struct estoque//------------------------------------------ESTRUTURA DE DADOS PARA O PROJETO----------------------------------//
{
    int vet_codigo_prod;//----------CODIGO DOS PRODUTOS---------//
    char vet_nome_prod[50];
    int vet_quantidade_prod;
    int vet_quantidade_min_prod;//----------QUANTIDADE EM ESTOQUE MINIMA-----------//
    float vet_preco_prod;
    int ativo;//-------------------------SERVE PARA VERIFICAR SE JA EXISTE O CADASTRO OU NÃO----------------------------//
}estoque;
struct estoque cadastro[tam];

void cadastra_produto()//------------------------------------------MENU PARA CADASTRAR PRODUTOS--------------------------------------//
{
    system("cls");
    char nome[50];
    int codigo=1,quantidade,quantidade_min;
    float preco;
    int opcao;
    int i, teste, NOK;
    monta_menu_cadastro();//----------ABRE MENU----//
    do{
        printf("DIGITE O NOME DO PRODUTO: ");//--LE O NOME DO PRODUTO--------------------------------------------//
        scanf(" %s", nome);
        do{//-------------------------------------LE A QUANTIDADE--------------------------------------------//
            teste=0;//----------COLOCA O TESTE PARA FICAR NO LUPE ATE QUE SEJA CORRETO PORTANTO SE = 0 CORRETO SE = 1 ERRADO E FAZ O DO WHILE NOVAMENTE--------//
            printf("DIGITE A QUANTIDADE DE PRODUTO: ");
            scanf(" %d", &quantidade);
            if (quantidade<0)//------------NÃO ACEITA QUANTIDADES NEGATIVAS E MUDA O TESTE PARA 1--------//
            {
                printf ("ERRO - quantidade invalido\n");
                teste=1;
            }
        }while (teste==1);
        do{//--------------------------------QUANTIDADE MINIMA----------------------------------------//
            teste=0;//----------COLOCA O TESTE PARA FICAR NO DO WHILE ATE QUE SEJA CORRETO PORTANTO SE = 0 CORRETO SE = 1 ERRADO E FAZ O DO WHILE NOVAMENTE--------//
            printf("DIGITE A QUANTIDADE MINIMA DO PRODUTO: ");
            scanf("%d", &quantidade_min);
            if(quantidade_min<0){//---------NAO ACEITA QUANTIDADE MINIMA NEGATIVA--------//
                printf ("ERRO - quantidade minima invalida\n");
                teste=1;
            }
        }while (teste==1);
        do{//----------------------------------------PREÇO------------------------------------------------//
            teste=0;//----------COLOCA O TESTE PARA FICAR NO DO WHILE ATE QUE SEJA CORRETO PORTANTO SE = 0 CORRETO SE = 1 ERRADO E FAZ O DO WHILE NOVAMENTE--------//
            printf("DIGITE O PRECO DO PRODUTO: ");
            scanf(" %f", &preco);
            if (preco<0){//------------NÃO ACEITA PRECO NEGATIVO E MUDA O TESTE PARA 1--------//
                teste = 1;
            }
            break;
        }while (teste==1);
        printf("\n");//----------------------INSERE NA STRUCT OS DADOS------------------------------------------------//
        for(i=0; i<tam; i++){
            if(cadastro[i].ativo==0){
                cadastro[i].vet_codigo_prod = codigo;
                cadastro[i].vet_quantidade_prod = quantidade;
                cadastro[i].vet_quantidade_min_prod = quantidade_min;
                cadastro[i].vet_preco_prod = preco;
                strcpy(cadastro[i].vet_nome_prod, nome);
                cadastro[i].ativo=1;
                break;
            }
        }
        monta_menu_de_opcao_cadastro();//----PERGUNTA SE DESEJA CONTINUAR CADASTRANDO------------------------------------------------//
        scanf("%d", &opcao);
        codigo=codigo+1;
    }while (opcao == 1);
}
//---------------------------------------------FUNÇÃO LISTAR PRODUTOS----------------------------------------------------------------------------//
int listar()
{
    int i;
    system("cls");
    printf("\n LISTA DE PRODUTOS\n");
    monta_menu_lista();//--------MONTA O CABEÇALHO DA LISTA-----------//
    for(i=0;i<tam;i++){
        if(cadastro[i].ativo==1){//-----------VERIFICA SE O CADASTRO É ATIVO SE SIM IMPRIME SE NÃO NAO IMPRIME ATE O FOR ACABAR-----//
            printf("CODIGO: %d  NOME: %s  QUANT.: %d  QUANT. MIN.: %d  PRECO: R$ %.2f \n", cadastro[i].vet_codigo_prod, cadastro[i].vet_nome_prod, cadastro[i].vet_quantidade_prod, cadastro[i].vet_quantidade_min_prod, cadastro[i].vet_preco_prod);
        }
    }
    monta_menu_lista_baixo();//------------------------------MONTA O RODAPE DA LISTA-------------------/
}

void exclui_produto()//------------------------------------------------FUNÇÃO EXCLUIR-----------------------------------------------------//
{
    char nome[50];
    int codigo,opcao,i, teste;
    listar();
    monta_menu_excluir();//-----------MONTA O MENU EXCLUIR------//
    printf("\nDIGITE A OPCAO\n");
    scanf("%d", &opcao);//-----------PERGUNTA SE DESEJA EXCLUIR ALGO-----//
    switch(opcao){
        case 1:{
            printf("\nDIGITE O CODIGO A SER REMOVIDO\n");
            scanf("%d", &codigo);//---------------PEDE QUAL ITEM IRA SER REMOVIDO---------//
            for(i=0; i<tam; i++){
                if(cadastro[i].vet_codigo_prod==codigo){//------------PROCURA NA STRUCT E COMPARA SE FOR IGUAL MUDA A OPÇÃO ATIVO PARA 0 PARA NÃO SER IMPRIMIDO NA FUNÇÃO LISTA-------------//
                    cadastro[i].ativo=0;
                    printf("CODIGO EXCLUIDO COM SUCESSSO");
                }
                else{ teste = 0;
                }
            }
            if(teste == 0){
                printf("\nCODIGO NAO ENCONTRADO\n");
            }
        }
        default:
            break;
    }
}

int main(void)//--------------------------------------------------INICIO-------------------------------------------------------------------//
{
    int op;
    do{
        monta_menu_principal();
        printf("\n\n");
        monta_menu_de_opcao();
        scanf("%d",&op);
             switch(op){
                 case 1:{
                    cadastra_produto();
                    break;
                 }
                 case 2:{
                    exclui_produto();
                    break;
                 }
                 case 3:{
                    listar();
                 break;
                 }
            }
    }while(op!=4);
}



