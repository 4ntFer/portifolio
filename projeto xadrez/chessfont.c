#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

#define DIM_TAB 8
#define NLAYERS_TAB 4
#define TAB_FILE "inic_tab.csv"
#define BUFFLEN 128
#define VAZ '-'
#define WHI_LAYER 0
#define BLA_LAYER 1
#define MOV_LAYER 2
#define AUX_LAYER 3


typedef struct{
    char tab[NLAYERS_TAB][DIM_TAB][DIM_TAB]; /*Primeira camada para a visão do jogador com as peças maiusculas
    e segunda camada para o jogador de peças minusculas, terceira camada é auxiliar para mivimentação*/
    int dim;
    int layer;
    int checkmat;
} TAB;

void inicTab (TAB* jogo);
void imprimeMat (char mat[][DIM_TAB], int l);
int chMatVerify(TAB* jogo);
void viraTab (TAB* jogo, int original, int para);
void movimento(TAB* jogo, int vez, int linha, int coluna);
void peao (TAB* jogo, int vez, int linha, int coluna);
void torre (TAB* jogo, int vez, int linha, int coluna);
void cavalo (TAB* jogo, int vez, int linha, int coluna);
void bispo (TAB* jogo, int vez, int linha, int coluna);
void rei (TAB* jogo, int vez, int linha, int coluna);
int main(){
    TAB jogo;
    int linha, coluna, pvalida;
    
    jogo.checkmat=0;
    jogo.dim=DIM_TAB;
    jogo.layer=NLAYERS_TAB;

    inicTab(&jogo);

    

    while (chMatVerify(&jogo)!=1){
        imprimeMat(jogo.tab[WHI_LAYER],jogo.dim);

        printf("informe a posicao da peca que deseja mover: ");
        pvalida=0;
        while(pvalida==0){
            scanf("%d %d", &linha, &coluna);
            if(jogo.tab[WHI_LAYER][linha][coluna]>'Z'||jogo.tab[WHI_LAYER][linha][coluna]<'A'||linha<0||linha>=jogo.dim||coluna<0||coluna>=jogo.dim){
                printf("informe uma posicao valida!\n");
            }else{
                pvalida=1;
            }
        }
        movimento(&jogo, WHI_LAYER, linha, coluna);
            
        system("cls");
        if(chMatVerify(&jogo)!=1){
            imprimeMat(jogo.tab[WHI_LAYER],jogo.dim);

            printf("informe a posicao da peca que deseja mover: ");
            pvalida=0;
            while(pvalida==0){
                scanf("%d %d", &linha, &coluna);
                linha=(jogo.dim-1)-linha;
                coluna=(jogo.dim-1)-coluna;
                if(jogo.tab[BLA_LAYER][linha][coluna]>'z'||jogo.tab[BLA_LAYER][linha][coluna]<'a'||linha<0||linha>=jogo.dim||coluna<0||coluna>=jogo.dim){
                    printf("informe uma posicao valida!\n");
                }else{
                    pvalida=1;
                }
            }
            movimento(&jogo, BLA_LAYER, linha, coluna);
        }

        system("cls");
    }
    

    system("pause");
    return 0;
}
void inicTab (TAB* jogo){
    FILE* tab_patt;
    char line[BUFFLEN], *piece;
    int i=0, j;
    int i_l, j_l;

    tab_patt=fopen(TAB_FILE,"r");
    if(tab_patt==NULL){
        printf("Erro ao encontrar arquivos do jogo!");
        system("pause");
        exit(1);
    }

    while(fgets(line,BUFFLEN,tab_patt)){ //lê uma linha do aquivo por vêz (tem memoria)
        piece=strtok(line,","); //separa em tokiens (tem memoria)

        j=0;
        while(piece!=NULL){
            jogo->tab[WHI_LAYER][i][j]=*piece;
            j++;//coluna
            piece=strtok(NULL,",");
        }
        i++;// linha
    }

    viraTab(jogo, WHI_LAYER, BLA_LAYER);
    
    fclose(tab_patt);
}
void imprimeMat (char mat[][DIM_TAB], int l){
    int i=0, j=0;

    for(i=0;i<l;i++){ 
        printf("%d   ", i);
        for(j=0;j<l;j++){
            printf("%3c", mat[i][j]);
        }
        printf("\n\n");
    }
    printf("\n    ");
    for(j=0;j<l;j++){
        printf("%3d", j);
    }
    printf("\n\n");
}
void viraTab (TAB* jogo, int original, int para){
    int i, j;
    int i_l=0, j_l;

    for(i=(jogo->dim)-1;i>=0;i--){
        j_l=0;
        for(j=(jogo->dim)-1;j>=0;j--){
           jogo->tab[para][i][j]=jogo->tab[original][i_l][j_l];
           j_l++;
        }
        i_l++;
    }
}
int chMatVerify(TAB* jogo){
    int i, j, nR=0, nP=0;

    for(i=0;i<jogo->dim;i++){
        for(j=0;j<jogo->dim;j++){
            if(jogo->tab[WHI_LAYER][i][j]=='r'||jogo->tab[WHI_LAYER][i][j]=='R'){
                nR++;
            }
            if(jogo->tab[WHI_LAYER][i][j]!=VAZ){
                nP++;
            }
        }
    }
    if(nR==nP){
        return 1;
    }else if(nR!=2){
        return 1;
    }else{
        return 0;
    }
}
void movimento(TAB* jogo, int vez, int linha, int coluna){
    char piece;
    int i, j, aux, movL, movC, movValido=0;

    //limpa a camada de movimento
    for(i=0;i<jogo->dim;i++){
        for(j=0;j<jogo->dim;j++){
            jogo->tab[MOV_LAYER][i][j]=VAZ;
        }
    }
    //peça a peça para camada de mocimento na mesma posição do tabuleiro original
    piece=jogo->tab[vez][linha][coluna];
    jogo->tab[MOV_LAYER][linha][coluna]=jogo->tab[vez][linha][coluna];

    //identifica as peças

    /*A inversão dos tabuleiros é util porque assim só preciso
    desenvolver uma unica função com os movimentos de cada peça
    independente de ser maiuscula ou minuscula.*/
    if(piece=='p'||piece=='P'){
        peao(jogo,vez,linha,coluna);
    }else if(piece=='t'||piece=='T'){
        torre(jogo,vez,linha,coluna);
    }else if(piece=='c'||piece=='C'){
        cavalo(jogo,vez,linha,coluna);
    }else if(piece=='b'||piece=='B'){
        bispo(jogo,vez,linha,coluna);
    }else if(piece=='d'||piece=='D'){
        torre(jogo,vez,linha,coluna);
        bispo(jogo,vez,linha,coluna);
    }else if(piece=='r'||piece=='R'){
        rei(jogo,vez,linha,coluna);
    }
    
    /*se for a vez das peças minusculas então após marcar os movimentos possiveis
    inverte a camada de movimento antes de imprimir,
    o resultado disso é que no momento da impressão o tabuleiro não será invetido*/
    if(vez==BLA_LAYER){ 
        viraTab(jogo,MOV_LAYER, AUX_LAYER); 
        for(i=0;i<jogo->dim;i++){
            for(j=0;j<jogo->dim;j++){
                jogo->tab[MOV_LAYER][i][j]=jogo->tab[AUX_LAYER][i][j];
            }
        }
    }
    

    imprimeMat(jogo->tab[MOV_LAYER],jogo->dim);

    while(movValido==0){

        printf("Mover para: ");
        scanf("%d %d", &movL, &movC);

        if(vez==WHI_LAYER){
            if(movL>=0&&movL<jogo->dim&&movC>=0&&movC<jogo->dim&&(jogo->tab[MOV_LAYER][movL][movC]=='X'||(jogo->tab[MOV_LAYER][movL][movC]<'z'&&jogo->tab[vez][movL][movC]>'a'))){
                jogo->tab[vez][movL][movC]=piece;
                jogo->tab[vez][linha][coluna]=VAZ;
                movValido=1;
            }else{
                printf("informe um movemento valido!\n");
            }
        }else{
            if(movL>=0&&movL<jogo->dim&&movC>=0&&movC<jogo->dim&&(jogo->tab[MOV_LAYER][movL][movC]<'Z'&&jogo->tab[MOV_LAYER][movL][movC]>'A')){
                movL=(jogo->dim-1)-movL;
                movC=(jogo->dim-1)-movC;
                jogo->tab[vez][movL][movC]=piece;
                jogo->tab[vez][linha][coluna]=VAZ;
                movValido=1;
            }else{
                printf("informe um movemento valido!\n");
            }
        }
    }

    for(i=0;i<jogo->dim;i++){
        for(j=0;j<jogo->dim;j++){
            jogo->tab[MOV_LAYER][i][j]=VAZ;
        }
    }

    /*copia o tabuleiro da vez para o tabuleiro do jogador
    que não esta na vez*/
    if(vez==WHI_LAYER){ 
        viraTab(jogo,vez,BLA_LAYER);
    }else{
        viraTab(jogo,vez,WHI_LAYER);
    }
}
void peao (TAB* jogo, int vez, int linha, int coluna){
    int aux, i, j;
    aux=linha-1;
    for(i=coluna-1;i<=coluna+1;i+=2){
        if(i>=0&&i<jogo->dim&&aux>=0&&aux<jogo->dim){
            if(jogo->tab[vez][aux][i]!=VAZ){
                jogo->tab[MOV_LAYER][aux][i]=jogo->tab[vez][aux][i];
            }
        }
    }
    if(jogo->tab[vez][aux][coluna]==VAZ&&aux>=0&&aux<jogo->dim){
        jogo->tab[MOV_LAYER][aux][coluna]='X';
    }
}
void torre (TAB* jogo, int vez, int linha, int coluna){
    int i, obst=0;
    i=linha-1;

    while(i>=0 && obst==0){

        if(jogo->tab[vez][i][coluna]==VAZ){
            jogo->tab[MOV_LAYER][i][coluna]='X';
        }else{
            obst=1;
            jogo->tab[MOV_LAYER][i][coluna]=jogo->tab[vez][i][coluna];
        }

        i--;
    }

    obst=0;
    i=coluna-1;

    while(i>=0 && obst==0){

        if(jogo->tab[vez][linha][i]==VAZ){
            jogo->tab[MOV_LAYER][linha][i]='X';
        }else{
            obst=1;
            jogo->tab[MOV_LAYER][linha][i]=jogo->tab[vez][linha][i];
        }
        i--;
    }

    obst=0;
    i=linha+1;

    while(i<jogo->dim && obst==0){
        if(jogo->tab[vez][i][coluna]==VAZ){
            jogo->tab[MOV_LAYER][i][coluna]='X';
        }else{
            obst=1;
            jogo->tab[MOV_LAYER][i][coluna]=jogo->tab[vez][i][coluna];
        }
        i++;
    }

    obst=0;
    i=coluna+1;

    while(i<jogo->dim && obst==0){
        if(jogo->tab[vez][linha][i]==VAZ){
            jogo->tab[MOV_LAYER][linha][i]='X';
        }else{
            obst=1;
            jogo->tab[MOV_LAYER][linha][i]=jogo->tab[vez][linha][i];
        }
        i++;
    }

}
void cavalo (TAB* jogo, int vez, int linha, int coluna){
    int i, j;

    for(i=linha-2;i<=linha+2;i++){
        for(j=coluna-2;j<=coluna+2;j++){

            if(i>=0&&i<jogo->dim&&j>=0&&j<jogo->dim){

                if((j==coluna+1||j==coluna-1)&&(i==linha-2||i==linha+2)){
                    if(jogo->tab[vez][i][j]==VAZ){
                        jogo->tab[MOV_LAYER][i][j]='X'; 
                    }else{
                        jogo->tab[MOV_LAYER][i][j]=jogo->tab[vez][i][j];
                        //printf("(%d %d)", i, j);
                    }
                }

                if((j==coluna+2||j==coluna-2)&&(i==linha-1||i==linha+1)){
                    if(jogo->tab[vez][i][j]==VAZ){
                     jogo->tab[MOV_LAYER][i][j]='X'; 
                    }else{
                        jogo->tab[MOV_LAYER][i][j]=jogo->tab[vez][i][j];
                        //printf("%c", jogo->tab[vez][i][j]);
                    }
                }
                
            }

        }
    }
    
}
void bispo (TAB* jogo, int vez, int linha, int coluna){
    int i, j=0, obst=0;

    for(i=1;obst==0;i++){
        if(linha+i<jogo->dim&&coluna+i<jogo->dim){
            if(jogo->tab[vez][linha+i][coluna+i]==VAZ){
                jogo->tab[MOV_LAYER][linha+i][coluna+i]='X';
            }else{
                obst=1;
                jogo->tab[MOV_LAYER][linha+i][coluna+i]=jogo->tab[vez][linha+i][coluna+i];
            }
        }else{
            obst=1;
        }
    }

    obst=0;

    for(i=1;obst==0;i++){
        if(linha-i>=0&&coluna-i>=0){
            if(jogo->tab[vez][linha-i][coluna-i]==VAZ){
                jogo->tab[MOV_LAYER][linha-i][coluna-i]='X';
            }else{
                obst=1;
                jogo->tab[MOV_LAYER][linha-i][coluna-i]=jogo->tab[vez][linha-i][coluna-i];
            }
        }else{
            obst=1;
        }
    }
    
    obst=0;

    for(i=1;obst==0;i++){
        if(linha-i>=0&&coluna+i<jogo->dim){
            if(jogo->tab[vez][linha-i][coluna+i]==VAZ){
                jogo->tab[MOV_LAYER][linha-i][coluna+i]='X';
            }else{
                obst=1;
                jogo->tab[MOV_LAYER][linha-i][coluna+i]=jogo->tab[vez][linha-i][coluna+i];
            }
        }else{
            obst=1;
        }
    }
    
    obst=0;

    for(i=1;obst==0;i++){
        if(linha+i<jogo->dim&&coluna-i>=0){
            if(jogo->tab[vez][linha+i][coluna-i]==VAZ){
                jogo->tab[MOV_LAYER][linha+i][coluna-i]='X';
            }else{
                obst=1;
                jogo->tab[MOV_LAYER][linha+i][coluna-i]=jogo->tab[vez][linha+i][coluna-i];
            }
        }else{
            obst=1;
        }
    }
}
void rei (TAB* jogo, int vez, int linha, int coluna){
    int i, j;

    for(i=linha-1;i<=linha+1;i++){
        for(j=coluna-1;j<=coluna+1;j++){
            if(i>=0&&j>=0&&i<jogo->dim&&j<jogo->dim){
                if(jogo->tab[vez][i][j]==VAZ){
                    jogo->tab[MOV_LAYER][i][j]='X';
                }else{
                    jogo->tab[MOV_LAYER][i][j]=jogo->tab[vez][i][j];
                }
            }
        }
    }
}