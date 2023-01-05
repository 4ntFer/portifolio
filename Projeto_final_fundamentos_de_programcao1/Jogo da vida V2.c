#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ORG 'O'
#define VAZ '-'
#define TAM 101
#define BUFLEN 4096
#define INVADERS_LENGTH 2

typedef struct tab
{
    char nomeJogo[TAM]; //o nome do jogo deve ser relativo ao padrao de inicializacao. Por exemplo, JogoSapo ou JogoBloco
    int ciclosVida; // Define quanto cada jogo vai rodar (ciclos)
    int dim1, dim2; //dimensoes do tabuleiro linhas x colunas
    int tregua;
    char **m;       //Atenção! Essa matriz terá que ser alocada dinamicamente
                    //para que a funcao que inicializa possa funcionar
} Tab;

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void erroAlocacao();

void limpaMatriz(char **m, int nL, int nC);
void iniciaPadrao(char* nome, char** m, int xInic, int yInic);
int vizinhos (Tab *jogo, int l, int c, int *nViz);
void jogaJogoVida(Tab *jogo);
void injetaInv(char** aux, int invP);
int menuInicJogo(Tab *jogo);
char **alocaMatriz(int l, int c);
void desalocaMatriz(char **m, int l);
void copiaMatriz(char **m, char **mCopia, int l, int c);
void imprimeMatriz(char **m, int l, int c);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    srand(time(NULL));

    //var
    Tab jogo;
    int sair;
    
    jogo.dim1 = 25;
    jogo.dim2 = 25;

    //alg
    jogo.m = alocaMatriz(jogo.dim1, jogo.dim2);

    do{
        limpaMatriz(jogo.m,jogo.dim1,jogo.dim2);

        do{
            printf("Digite o numero de ciclos:");
            scanf("%d", &(jogo.ciclosVida));
        }while (jogo.ciclosVida > __INT_MAX__ || jogo.ciclosVida < 0);

        printf("\nLembre-se que caso coloque um numero negativo ou numero maior do que o de ciclos, isso nunca vai acontecer!\n");
        printf("Digite o numero de ciclos entre as chances de invasoes:");
        scanf("%d",&(jogo.tregua));

        sair = menuInicJogo(&jogo);
        if(!sair){
            jogaJogoVida(&jogo);
        }
    }while(!sair);

    desalocaMatriz(jogo.m,jogo.dim1);
}

void erroAlocacao(){
    printf("\nErro de alocacao de memoria!");
    exit(1);
}

char **alocaMatriz(int l, int c){
   char **m;
   int i;

   m = (char **)malloc(l * sizeof(char *));
   if (m==NULL) erroAlocacao();
   for (i = 0; i < l; i++){
      m[i] = (char *)malloc(c * sizeof(char));
      if (m[i]==NULL) erroAlocacao();
   }
   return m;
}

void desalocaMatriz(char **m, int l){
   int i;

   for (i = 0; i < l; i++){
      free(m[i]);
   }

   free(m);
}

void copiaMatriz(char **m, char **mCopia, int l, int c){

    int i, j;

    for (i = 0; i < l; i++){
        for (j = 0; j < c; j++){
            mCopia[i][j] = m[i][j];
        }
    }
}

void imprimeMatriz(char **m, int l, int c){
    int i, j;

    for (i = 0; i < l; i++){
        for (j = 0; j < c; j++){
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

void limpaMatriz(char **m, int nL, int nC){
    int i, j;
    for (i = 0; i < nL; i++)
        for (j = 0; j < nC; j++)
            m[i][j] = VAZ;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void injetaInv(char** m, int invP){
    
    char invaders[INVADERS_LENGTH][BUFLEN] = {"./patterns/glider_invader.csv", "./patterns/block.csv"};

    int xInic = 0, yInic= 0;
    iniciaPadrao(invaders[invP],m,xInic,yInic);
}

void iniciaPadrao(char* nome, char** m, int xInic, int yInic){

    FILE *padrao;
    int i=0;
    char linha[BUFLEN], *num;

    padrao = fopen(nome, "r");
    if(padrao==NULL){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        printf("%s eh um arquivo invalido!\n", nome);
        system("pause");
        exit(1);
    }

    while(fgets(linha,BUFLEN,padrao)){
        num=strtok(linha,",");

        while(num!= NULL){
            m[yInic+i][xInic+atoi(num)-1] = ORG;
            num=strtok(NULL,",");
        }
        i++;
    }

    fclose(padrao);
}

int vizinhos (Tab *jogo, int l, int c, int *nViz){
    int i, j, viz=0;
    *nViz=0;
    for(i=l-1;i<=l+1;i++){/*i varia da coordenada horizontal da celula na matriz -1 até +1*/
        for(j=c-1;j<=c+1;j++){/*i varia da coordenada vertical da celula na matriz -1 até +1*/
            if((i>=0 && i<jogo->dim1)&&(j>=0&&j<jogo->dim2)){
                /*Se nc<i<0 ou nl<j<0 então as cordenadas estão
                fora da matriz*/
                viz+=jogo->m[i][j];
                (*nViz)++;
            }
        }
    }
    /*subtrai a celula central*/
    viz-=jogo->m[l][c];
    (*nViz)--;

    return viz; 
}

void jogaJogoVida(Tab *jogo){
    char **aux;
    int viz, k, i, j, nViz, invG, invP,podeInv=0;
    
    aux = alocaMatriz(jogo->dim1, jogo->dim2);
    copiaMatriz(jogo->m, aux, jogo->dim1, jogo->dim2);

    for (k = 0; k < jogo->ciclosVida; k++){

        for (i = 0; i < jogo->dim1; i++){
            for (j = 0; j < jogo->dim2; j++){
                viz=vizinhos(jogo,i,j,&nViz);
                if(jogo->m[i][j]==ORG){      
                    if(viz != 2*ORG + (nViz-2)*VAZ && viz != 3*ORG + (nViz-3)*VAZ){
                        aux[i][j]=VAZ;
                    }
                }else if(viz == 3*ORG + (nViz-3)*VAZ){
                    aux[i][j]=ORG;
                }
            }
        }

        podeInv++;

        if (podeInv == jogo->tregua){
            invG = rand()%10+1;

            if (invG < 3){
                invP=rand()%INVADERS_LENGTH;
                injetaInv(aux,invP);
            }
            podeInv = 0;
        }

        copiaMatriz(aux,jogo->m,jogo->dim1,jogo->dim2); 
        imprimeMatriz(aux,jogo->dim1,jogo->dim2);
        Sleep(50);

        if (k==(jogo->ciclosVida-1)){
            system("pause");
        }
        system("cls");
    }

    desalocaMatriz(aux, jogo->dim1);
}

int menuInicJogo(Tab *jogo){
    int opcao,xInic,yInic;
    
    printf("\nSelecione uma opcao:\n\n");

    printf("[1]Bloco\n");
    printf("[2]Blinker\n");
    printf("[3]Sapo\n");
    printf("[4]Glider\n");
    printf("[5]LWSS\n");
    printf("[Outro]Sair\n\n");

    printf("R:");

    xInic = jogo->dim2-7;
    yInic = jogo->dim1-7;

    scanf("%d", &opcao);
    switch (opcao){
        case 1:
            iniciaPadrao("./patterns/bloco.csv",jogo->m,xInic,yInic);
            break;
        case 2:
            iniciaPadrao("./patterns/blinker.csv",jogo->m,xInic,yInic);
            break;
        case 3:
            iniciaPadrao("./patterns/frog.csv",jogo->m,xInic,yInic);
            break;
        case 4:
            iniciaPadrao("./patterns/glider.csv",jogo->m,xInic,yInic);
            break;
        case 5:
            iniciaPadrao("./patterns/lwss.csv",jogo->m,xInic,yInic);
            break;
        default:
            printf("tchau bjos '3'");
            return 1;
    }

    imprimeMatriz(jogo->m, jogo->dim1, jogo->dim2);

    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");
    while (getchar() != '\n');
    getchar();

    return 0;
}
