#include <stdio.h>
#include <string.h>
#include "sequencial.h"
#include "Lista_s.h"
#include "Pessoa.h"

int line_number_identify(char fileName[]){
   FILE* arq;
   int i=0;
    char line[BUFFER];
    char* result;

   arq=fopen(fileName,"rt");
   verificaOpen_s(&arq);

    while(!feof(arq)){
        if(fgets(line,BUFFER,arq)!=NULL){
            i++;
        }
    }

    fclose(arq);

    return i;
}

Pessoa** alocaLista_s(int tam){
    Pessoa **p;

    p=(Pessoa**)malloc(tam*sizeof(Pessoa*));

    if(p==NULL){
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    return p;
}

void criaLista_s(char fileName[], Node* lista){
    FILE* arq;
    int i;
    char line[BUFFER];
    char *nome, *rg;

    arq=fopen(fileName,"rt");

    verificaOpen_s(&arq);

    for(i=0;i<(lista->tamanho);i++){
        if(fgets(line,BUFFER,arq)==NULL){
            printf("ERRO AO LER O ARQUIVO!");
            getchar();
            exit(1);
        }

        nome=strtok(line,",");
        rg=strtok(NULL,"\n");

        lista->p[i]=(Pessoa*)malloc(sizeof(Pessoa));
        
        strcpy(lista->p[i]->nome,nome);
        strcpy(lista->p[i]->rg,rg);

        if(nome==NULL || rg==NULL){
            printf("ERRO NA LINHA %d", (i+1));
            exit(1);
        }
    }

    fclose(arq);
}

void verificaOpen_s(FILE** arq){
    if(arq==NULL){
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }
}

void desaloca_s(Node* lista){
    int i;

    for(i=0;i<lista->tamanho;i++){
        free(lista->p[i]);
    }

    free(lista->p);
}

void imprimeLista_s(Node* lista){
    int i;
    for(i=0;i<lista->tamanho;i++){
        printf("Nome: %s\nRG: %s\n\n", lista->p[i]->nome,lista->p[i]->rg);
    }
}

void insertEndNode_s(Node* lista, Pessoa* nodeinf){
    int Cn=0, Mn=0;
    (lista->tamanho)++;
    lista->p=(Pessoa**)realloc(lista->p,(lista->tamanho)*sizeof(Pessoa*));
    if(lista->p==NULL){
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    lista->p[(lista->tamanho)-1]=(Pessoa*)malloc(sizeof(Pessoa));
    if(lista->p[(lista->tamanho)-1]==NULL){
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    strcpy(lista->p[(lista->tamanho)-1]->nome,nodeinf->nome);
    strcpy(lista->p[(lista->tamanho)-1]->rg,nodeinf->rg);

    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void insertInfo(Pessoa* nodeinf){
    char info[BUFFER];
    
    printf("informe o Nome: ");
    scanf("%s", info);
    getchar();
    strcpy(nodeinf->nome,info);
    
    printf("informe o RG: ");
    scanf("%s", info);
    getchar();
    strcpy(nodeinf->rg,info);
}

void insertStartNode_s(Node* lista, Pessoa* nodeinf){
    int i, Cn=0, Mn=0;

    (lista->tamanho)++;
    lista->p=(Pessoa**)realloc(lista->p,(lista->tamanho)*sizeof(Pessoa*));
    if(lista->p==NULL){
        printf("Erro na alocacao!");
        getchar();
        exit(1);
    }

    for(i=lista->tamanho-1;i>0;i--){
        lista->p[i]=lista->p[i-1];
        Mn++;
    }

    lista->p[0]=(Pessoa*)malloc(sizeof(Pessoa));
    if(lista->p[0]==NULL){
        printf("Erro na alocacao!");
        getchar();
        exit(1);
    }
    strcpy(lista->p[0]->nome,nodeinf->nome);
    strcpy(lista->p[0]->rg,nodeinf->rg);
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void insertNode_s(int n, Node* lista, Pessoa* nodeinf){
    int i, Cn=0, Mn=0;

    if(n>lista->tamanho){
        printf("informe uma posicao valida!");
        exit(1);
    }

    (lista->tamanho)++;
    lista->p=(Pessoa**)realloc(lista->p,(lista->tamanho)*sizeof(Pessoa*));
    if(lista->p==NULL){
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    for(i=(lista->tamanho)-1;i>=n;i--){
        lista->p[i]=lista->p[i-1];
        Mn++;
    }

    lista->p[n-1]=(Pessoa*)malloc(sizeof(Pessoa));
    if(lista->p[(lista->tamanho)-1]==NULL){
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }
    strcpy(lista->p[n-1]->nome,nodeinf->nome);
    strcpy(lista->p[n-1]->rg,nodeinf->rg);
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void removeEndNode_s(Node* lista){
    int i, Cn=0, Mn=0;
    free(lista->p[(lista->tamanho)-1]);
    (lista->tamanho)--;
    lista->p=(Pessoa**)realloc(lista->p,((lista->tamanho)-1)*sizeof(Pessoa*));
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void removeStartNode_s(Node* lista){
    int i, Cn=0, Mn=0;
    
    free(lista->p[0]);

    for(i=0;i<(lista->tamanho)-1;i++){
        lista->p[i]=lista->p[i+1];
        Mn++;
    }

    (lista->tamanho)--;
    lista->p=(Pessoa**)realloc(lista->p,(lista->tamanho)*sizeof(Pessoa*));
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void removeNode_s(int n, Node* lista){
    int i, Cn=0, Mn=0;

    n--;
    if(n<0||n>(lista->tamanho-1)){
        printf("posicao invalida!");
        exit(1);
    }
    free(lista->p[n]);

    for(i=n;i<(lista->tamanho)-1;i++){
        lista->p[i]=lista->p[i+1];
        Mn++;
    }

    (lista->tamanho)--;
    lista->p=(Pessoa**)realloc(lista->p,(lista->tamanho)*sizeof(Pessoa*));
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void buscaSequencial_s(char rg[], Node* lista){
    int i, flag=0, Cn=0, Mn=0;

    for(i=0;i<lista->tamanho&&flag!=1;i++){
        if(strcmp(lista->p[i]->rg, rg)==0){
            printf("Elm. num. (%d)\n", i+1);
            printf("Nome: %s\nRG: %s\n",lista->p[i]->nome,lista->p[i]->rg);
            flag=1;
        }
        Cn++;
    }
    if(flag==0){
        printf("RG não encontrado!");
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void saveArq_s(Node* lista){
    FILE *arq;
    int i=0;
    char line[BUFFER];
    char *result;
    char newarq[BUFFER];
    printf("\nInsira o nome do novo arquivo:\n");
    scanf("%s", newarq);
    arq=fopen(newarq, "w+");

    if(arq==NULL){
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }

    for (i=0;i<((lista->tamanho));i++){
        if(i==(lista->tamanho)-1){
        fprintf(arq,"%s,%s",lista->p[i]->nome,lista->p[i]->rg);
        }else{
            fprintf(arq,"%s,%s\n",lista->p[i]->nome,lista->p[i]->rg);
        }
    }

    fclose(arq);
}

int buscaBinaria_s(char* rg, Node* lista, int i, int f, CnMn* cont){
    int m, p=-1;

    m=(i+f)/2;
    if(i<f){
        if((atoi(lista->p[m]->rg)==atoi(rg))){
            cont->Cn++;
            return m; 
        }else if(atoi(lista->p[m]->rg)>atoi(rg)){
            cont->Cn=cont->Cn+2;
            p=buscaBinaria_s(rg,lista,0,m-1,cont);
        }else if(atoi(lista->p[i]->rg)<atoi(rg)){
            p=buscaBinaria_s(rg,lista,m+1,f,cont);
        }
    }else if((atoi(lista->p[m]->rg)==atoi(rg))){
        cont->Cn++;
        return m;
    }
    
    return p;
}

void printBuscaBinaria_s(char* rg, Node* lista, int i, int f, CnMn* cont){
    int p;

    p=buscaBinaria_s(rg,lista,0,lista->tamanho-1,cont);

    if(p!=-1){
        printf("Elm. num. (%d)\n", p+1);
        printf("Nome: %s\nRG: %s\n",lista->p[p]->nome,lista->p[p]->rg);
    }else{
        printf("RG nao encontrado!");
    }
}