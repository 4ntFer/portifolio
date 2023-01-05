#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "sequencial.h"
#include "Lista_s.h"
#include "Pessoa.h"
#include "sort.h"

int main(){
    int op=0, userN;
    double cpu_time_used;
    char fileName[BUFFER]="Leia a lista de um arquivo antes";
    char straux[BUFFER];
    Node listaSE;
    clock_t start, end;
    Pessoa userInfo;
    CnMn cont;

    while(op!=11){
        op=menuP1();
        if(op!=9&&strcmp(fileName,"Leia a lista de um arquivo antes")==0){
        printf("%s",fileName);
        }
        else if(op==0){
            printf("Informacoes do no: \n");
            insertInfo(&userInfo);

            start=clock();
            insertStartNode_s(&listaSE,&userInfo);

            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==1){
            printf("Informacoes do no: \n");
            insertInfo(&userInfo);

            printf("Lista sequencial: \n");
            start=clock();
            insertEndNode_s(&listaSE,&userInfo);

            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==2){
            printf("Informe a posicao da lista em que o no deve ser inserido: ");
            scanf("%d", &userN);
            getchar();
            printf("Informacoes do no: \n");
            insertInfo(&userInfo);
            system("cls");
            printf("Lista sequencial: \n");
            start=clock();
            insertNode_s(userN,&listaSE,&userInfo);
        
            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==3){
            printf("Lista sequencial:");
            start=clock();
            removeStartNode_s(&listaSE);

            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==4){
            printf("Lista sequencial");
            start=clock();
            removeEndNode_s(&listaSE);

            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==5){
            printf("Informe a posicao do no que deseja remover: ");
            scanf("%d", &userN);
            printf("Lista sequencial");
            start=clock();
            removeNode_s(userN,&listaSE);

            printf("Lista encadeada: \n");
            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==6){
            op=menuBusca();

            printf("Informe o RG a ser buscado: ");
            scanf("%s", straux);
            getchar();

            if(op==0){
                printf("No encontrado na lista sequencial: \n\n");
                start=clock();
                buscaSequencial_s(straux,&listaSE);

                end=clock();
                cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
                printf("Tempo de execucao: %f\n", cpu_time_used);
            }else{
                inicCnMn(&cont);
                printBuscaBinaria_s(straux,&listaSE,0,((listaSE.tamanho)-1),&cont);
                printCnMn(&cont);
            }
        }
        else if(op==7){
            printf("Impressao lista sequencial: \n");
            start=clock();
            imprimeLista_s(&listaSE);

            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==8){
            saveArq_s(&listaSE);
        }
        else if(op==9){
            if(strcmp(fileName,"Leia a lista de um arquivo antes")!=0){
                desaloca_s(&listaSE);
            }
            printf("Informe o arquivo no formato Nome,RG que deve ser lido: ");
            scanf("%s", fileName);
            getchar();

            printf("Lista sequencial: \n");
            //inicializando a lista sequencial
            start=clock();

            listaSE.tamanho=line_number_identify(fileName);
            listaSE.p=alocaLista_s(listaSE.tamanho);
            criaLista_s(fileName, &listaSE);
        
            end=clock();
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==10){
            op=menuSort();

            inicCnMn(&cont);
            start=clock();
            if(op==0){
                selectionSort_s(&listaSE, &cont);
            }else if(op==1){
                insertionSort_s(&listaSE, &cont);
            }else if(op==2){
                bubbleSort_s(&listaSE, &cont);
            }else if(op==3){
                shellSort_s(&listaSE, &cont);
            }else if(op==4){
                quickSort_s(&listaSE,0,listaSE.tamanho-1,&cont);
            }else if(op==5){
                mergeSort_s(&listaSE,0,listaSE.tamanho-1,&cont);  
            }
            end=clock();
            printCnMn(&cont);
            cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", cpu_time_used);
        }
        else if(op==11){
          desaloca_s(&listaSE);
          return 0;
        }

        getchar();
        getchar();
        system("cls");
    }

    return 0;
}