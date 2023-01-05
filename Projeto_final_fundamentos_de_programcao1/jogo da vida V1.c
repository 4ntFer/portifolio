#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ORG 'X'
#define VAZ '.'
#define TAM 101

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void limpaMatriz(char **m, int nL, int nC);
void inicBlinker(char **m, int nL, int nC);
void inicBloco(char **m, int nL, int nC);
void inicSapo(char **m, int nL, int nC);
void inicGlider(char **m, int nL, int nC);
void inicLWSS(char **m, int nL, int nC);
int vizinhos (char **m, int nL, int nC, int l, int c, int *nViz);
void jogaJogoVida(char **m, int nL, int nC, int ciclos);
void menuInicJogo(char **mat, int nL, int nC);
char **alocaMatriz(int l, int c);
void desalocaMatriz(char **m, int l);
void copiaMatriz(char **m, char **mCopia, int l, int c);
void imprimeMatriz(char **m, int l, int c);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

   char **mat;

   int nL = 20, nC = 20, ciclos; //ou fornecido pelo usuario

   mat = alocaMatriz(nL, nC);

   do
   {
      menuInicJogo(mat, nL, nC);
      printf("Digite o numero de ciclos:");
      scanf("%d", &ciclos);
      jogaJogoVida(mat, nL, nC, ciclos);
   } while (ciclos > __INT_MAX__ || ciclos < 0);

   //defina o numero de ciclos que o jogo vai rodar (def. pelo usuario ou constante)

   desalocaMatriz(mat, nL);
}

char **alocaMatriz(int l, int c)
{
   char **m;
   int i;

   m = (char **)malloc(l * sizeof(char *));
   for (i = 0; i < l; i++)
   {
      m[i] = (char *)malloc(c * sizeof(char));
   }
   return m;
}

void desalocaMatriz(char **m, int l)
{
   int i;

   for (i = 0; i < l; i++)
   {
      free(m[i]);
   }

   free(m);
}

void copiaMatriz(char **m, char **mCopia, int l, int c)
{

   int i, j;

   for (i = 0; i < l; i++)
   {
      for (j = 0; j < c; j++)
      {
         mCopia[i][j] = m[i][j];
      }
   }
}

void imprimeMatriz(char **m, int l, int c)
{
   int i, j;

   for (i = 0; i < l; i++)
   {
      for (j = 0; j < c; j++)
      {
         printf("%c ", m[i][j]);
      }
      printf("\n");
   }
}

void limpaMatriz(char **m, int nL, int nC)
{
   int i, j;
   for (i = 0; i < nL; i++)
      for (j = 0; j < nC; j++)
         m[i][j] = VAZ;
}

void inicBlinker(char **m, int nL, int nC)
{
   char padrao[1][3] = {{ORG, ORG, ORG}};
   int i, j, xInic = nL / 2, yInic = nC / 2;

   limpaMatriz(m, nL, nC);

   for (i = 0; i < 1; i++)
      for (j = 0; j < 3; j++)
         m[xInic + i][yInic + j] = padrao[i][j];
}

void inicBloco(char **m, int nL, int nC)
{
   char padrao[2][2] = {{ORG, ORG}, {ORG, ORG}};
   int i, j, xInic = nL / 2, yInic = nC / 2;

   limpaMatriz(m, nL, nC);

   for (i = 0; i < 2; i++)
      for (j = 0; j < 2; j++)
         m[xInic + i][yInic + j] = padrao[i][j];
}

void inicSapo(char **m, int nL, int nC)
{

   char padrao[2][4] = {{VAZ, ORG, ORG, ORG}, {ORG, ORG, ORG, VAZ}};
   int i, j, xInic = nL / 2, yInic = nC / 2;

   limpaMatriz(m, nL, nC);

   for (i = 0; i < 2; i++)
      for (j = 0; j < 4; j++)
         m[xInic + i][yInic + j] = padrao[i][j];
}

void inicGlider(char **m, int nL, int nC)
{
   char padrao[3][3] = {{ORG, ORG, ORG}, {ORG, VAZ, VAZ}, {VAZ, ORG, VAZ}};
   int i, j, xInic, yInic;

   limpaMatriz(m, nL, nC);

   xInic = nL - 4;
   yInic = nC - 4;

   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         m[xInic + i][yInic + j] = padrao[i][j];
}

void inicLWSS(char **m, int nL, int nC)
{
   char padrao[4][5] = {{VAZ, ORG, VAZ, VAZ, ORG}, {ORG, VAZ, VAZ, VAZ, VAZ}, {ORG, VAZ, VAZ, VAZ, ORG}, {ORG, ORG, ORG, ORG, VAZ}};
   int i, j, xInic, yInic;

   limpaMatriz(m, nL, nC);

   xInic = 7;
   yInic = 7;

   for (i = 0; i < 4; i++)
      for (j = 0; j < 5; j++)
         m[xInic + i][yInic + j] = padrao[i][j];
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int vizinhos (char **m, int nL, int nC, int l, int c, int *nViz){
    int i, j, viz=0;
    *nViz=0;
    for(i=l-1;i<=l+1;i++){/*i varia da coordenada horizontal da celula na matriz -1 até +1*/
        for(j=c-1;j<=c+1;j++){/*i varia da coordenada vertical da celula na matriz -1 até +1*/
            if((i>=0 && i<nL)&&(j>=0&&j<nC)){
                /*Se nc<i<0 ou nl<j<0 então as cordenadas estão
                fora da matriz*/
                viz+=m[i][j];
                (*nViz)++;
            }
        }
    }
    /*subtrai a celula central*/
    viz-=m[l][c];
    (*nViz)--;

    return viz; 
}

void jogaJogoVida(char **m, int nL, int nC, int ciclos)
{
   char **aux;
   int viz, k, i, j, nViz;

   aux = alocaMatriz(nL, nC);   
   copiaMatriz(m,aux,nL, nC);//matriz que devera ser usada para atualizar cada jogada
   ////laco de repeticao para jogar TOTAL DE CICLOS
   
   for (k = 0; k < ciclos; k++){
      for (i = 0; i < nL; i++){
         viz=0;
         nViz=0;
         for (j = 0; j < nC; j++){
            /*
               j=0 nao verifica lateral esquerda;
               j=nC-1 nao verifica lateral direita;
               i=1 - Não verificar a parte de cima;
               i=nL-1 - Não verificar a parte de baixo;
            */

            viz=vizinhos(m,nL,nC,i,j,&nViz);
            
            if(m[i][j]==ORG){      
               if(viz != 2*ORG + (nViz-2)*VAZ && viz != 3*ORG + (nViz-3)*VAZ){
                  aux[i][j]=VAZ;
               }
            }else if(viz == 3*ORG + (nViz-3)*VAZ){
               aux[i][j]=ORG;
            }
      
         }
      }
   
      copiaMatriz(aux,m,nL, nC); //implemente uma funcao que copia uma matriz em out
      imprimeMatriz(aux,nL,nC);
      Sleep(100);
      system("cls");
   }

   ////fim do laco de repeticao para jogar TOTAL DE CICLOS

   desalocaMatriz(aux, nL);
}

void menuInicJogo(char **mat, int nL, int nC)
{
   int opcao;

   printf("\n\t[1]Bloco\n");
   printf("\t[2]Blinker\n");
   printf("\t[3]Sapo\n");
   printf("\t[4]Glider\n");
   printf("\t[5]LWSS\n");
   printf("\t[Outro]Sair\n");
   scanf("%d", &opcao);
   switch (opcao)
   {
   case 1:
      inicBloco(mat, nL, nC);
      break;
   case 2:
      inicBlinker(mat, nL, nC);
      break;
   case 3:
      inicSapo(mat, nL, nC);
      break;
   case 4:
      inicGlider(mat, nL, nC);
      break;
   case 5:
      inicLWSS(mat, nL, nC);
      break;
   default:
      printf("tchau bjos");
      exit(1);
   }

   imprimeMatriz(mat, nL, nC);

   printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");
   while (getchar() != '\n')
      ;
   getchar();
}
