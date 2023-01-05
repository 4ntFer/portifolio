#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"Pessoa.h"

int menuP1(){
    int p=-1;

   
    printf("0 Inserir no no inicio da lista\n");

    printf("1 Inserir no no fim da lista\n");

    printf("2 Inserir no na posicao n da lista\n");

    printf("3 Retirar no do inicio da lista\n");

    printf("4 Retirar no do fim da lista\n");

    printf("5 Retirar no da posicao n da lista\n");

    printf("6 Procurar no por RG\n");

    printf("7 Imprimir lista\n");

    printf("8 Salvar a lista em um arquivo\n");

    printf("9 Ler a lista de um arquivo\n");

    printf("10 Ordenar a lista\n");

    printf("11 Sair\n");

    while(p>11||p<0){
        scanf("%d",&p);
    }

    system("cls");
    
    return p;
}

void indica(){
    printf(">>> ");
}

int menuBusca(){
    int p=-1;

    
    printf("0 Busca Sequencial\n");
    printf("1 Busca Binaria\n");

    while(p>1||p<0){
        scanf("%d",&p);
    }

    return p;
}

int menuSort(){
    int p=-1;
 
    printf("0 Selection Sort\n");
    printf("1 Insertion-Sort\n");
    printf("2 Bubble-Sort\n");
    printf("3 Shell-Sort\n");
    printf("4 Quick-Sort\n");
    printf("5 Merge Sort\n");

    while(p>5||p<0){
        scanf("%d",&p);
    }
    
    system("cls");

    return p;
}


