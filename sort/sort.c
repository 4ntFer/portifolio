#include "Lista_s.h"
#include "Pessoa.h"
#include <stdlib.h>
#include <stdio.h>
#include "sequencial.h"
#include "sort.h"
#include <time.h>

void selectionSort_s(Node* lista, CnMn* cont){
    Pessoa *aux;
    int i, j, k;

    
    for(i=0;i<lista->tamanho;i++){
        k=i;
        for(j=i+1;j<lista->tamanho;j++){
            if(atoi(lista->p[k]->rg)>atoi(lista->p[j]->rg)){
                k=j;
            }
            cont->Cn++;
        }
        if(i!=k){
            aux=lista->p[i];
            lista->p[i]=lista->p[k];
            lista->p[k]=aux;
        }
        cont->Mn++;
    }
}

void insertionSort_s(Node* lista, CnMn* cont){
    int i, j, k, flag;
    Pessoa *aux;
    
    for(i=1;i<lista->tamanho;i++){
        flag=1;
        for(j=i;j>0&&flag==1;j--){
            cont->Cn++;
            if(atoi(lista->p[i]->rg)<atoi(lista->p[j]->rg)){
                trade(lista,i,j);
                cont->Mn=cont->Mn+2;
            }else{
                flag=0;
            }
        }    
    }
}

void mergeSort_s(Node* lista, int inicio, int fim, CnMn* cont){
    int mid;
    
    if(inicio<fim){
        mid=(inicio+fim)/2;
        mergeSort_s(lista,inicio,mid,cont);
        mergeSort_s(lista,mid+1,fim,cont);
        merge_s(lista,inicio,mid,fim,cont);
    }
}

void merge_s(Node* lista, int inicio, int mid, int fim, CnMn* cont){
    int i=0,tam=fim-inicio+1, leftTop, rightTop;
    Pessoa **v;
    
    v=(Pessoa**)malloc(tam*sizeof(Pessoa*));

    /*separa os indices da sublista que será ordenada
    dividindo ela em duas pilhas a partir da lista original.*/
    leftTop=inicio;
    rightTop=mid+1;

    /*Se o elemento da pilha da esquerda é menor que da direita,
    então esse elemento é inserido no vetor v, e vice-versa.*/
    while(leftTop<=mid&&rightTop<=fim){
        cont->Cn++;
        if(atoi(lista->p[leftTop]->rg)<atoi(lista->p[rightTop]->rg)){
            v[i]=lista->p[leftTop];
            leftTop++;
            cont->Mn++;
        }else{
            v[i]=lista->p[rightTop];
            rightTop++;
            cont->Mn++;
        }
        i++;
    }

    /*se não foram usados todos os elementos de uma das pilhas,
    então os elementos que faltam são inseridos. Isso aconteceria
    caso uma das pilhas tivesse todos os elementos menores que o primeiro
    elemento da outra pilha.*/
    while(leftTop<=mid){
        v[i]=lista->p[leftTop];
        leftTop++;
        i++;
        cont->Mn++;
    }

    while(rightTop<=fim){
        v[i]=lista->p[rightTop];
        rightTop++;
        i++;
        cont->Mn++;
    }

    /*Ao final desse processo temos a sublista no vetor que foi alocado no
    inicio da função.*/
    
    /*substituindo a sub-lista não ordenada, pela sub-lista ordenada na lista principal.*/
    for(i=0;i<tam;i++){
        lista->p[inicio+i]=v[i];
    }
    
    free(v);
}

void quickSort_s(Node* lista, int inicio, int fim, CnMn* cont){
    int i=inicio, j=fim;
    Pessoa* pivo;

    //define como pivo o elemento no meio da lista
    pivo=lista->p[(inicio+fim+1)/2];

    /*i e j são as variaveis responsaveis por apontar duas posições
    da lista, elas para de se mover quando é encontrado um elemento
    que deveria estar do outro lado do pivo. Como tenho dois elementos do lado errado,
    então troco estes de posição um com o outro. Se for encontrado um elemento mal
    posicionado somente de um lado da lista, então este deve trocar de posição com
    o proprio pivo, como se esse avançasse encurtando uma das sub-listas.
    Esse processo se repete até que i e j se cruzem.*/
    while(i<=j){

        /*Procura um elemento maior que o pivô, mas que esta à esquerda dele.*/
        while(atoi(pivo->rg)>atoi(lista->p[i]->rg)){
            i++;
            cont->Cn++;
        }
        /*Procura um elemento menor que o pivô, mas que esta à direita dele.*/
        while(atoi(pivo->rg)<atoi(lista->p[j]->rg)){
            j--;
            cont->Cn++;
        }

        /*Se i e j não se cruzaram, então troca i com j.*/
        if(i<=j){
            trade(lista,i,j);
            cont->Mn++;
            i++;
            j--;
        }
    }

    /*j = posicão do pivo -1;
      i = posicão do pivo +1.*/
    if(j>inicio){
        quickSort_s(lista,inicio,j,cont);
    }
    if(i<fim){ 
        quickSort_s(lista,i,fim,cont);
    }
}

void trade(Node* lista, int a, int b){
   Pessoa* aux;

   aux=lista->p[b];
   lista->p[b]=lista->p[a];
   lista->p[a]=aux;
}

void shellSort_s(Node* lista, CnMn* cont){
    int h, flag, i, j, k;
    Pessoa* aux;

    for(h=1;h<lista->tamanho;(h=h*3+1));

    while(h>0){
        for(i=h;i<lista->tamanho;i=i+h){
            flag=1;
            for(j=i;j>0&&flag;j=j-h){
                cont->Cn++;
                if(atoi(lista->p[i]->rg)<atoi(lista->p[j]->rg)){
                    trade(lista,i,j);
                    cont->Mn+2;
                
                }else{
                    flag=0;
                }
            }
        }
        h=h/3;
    }
}

void bubbleSort_s(Node* lista, CnMn* cont){
    int flag=1, k;

    for(int j=0;(j<(lista->tamanho)-1)&&flag;j++){
        k=0;
        for(int i=0;i<(lista->tamanho)-1;i++){
            cont->Cn++;
            if(atoi(lista->p[i]->rg)>atoi(lista->p[i+1]->rg)){
                trade(lista,i,i+1);
                k++;
                cont->Mn=cont->Mn+2;
            }
        }
        if(k==0){
            flag=0;
        }
    }
}

void inicCnMn(CnMn* cont){
    cont->Cn=0;
    cont->Mn=0;
}

void printCnMn(CnMn* cont){
    printf("\nC(n): %d\nM(n): %d\n", cont->Cn, cont->Mn);
}