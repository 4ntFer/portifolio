#pragma once
#include "Pessoa.h"

typedef struct Node{
    Pessoa** p;
    int tamanho;
}Node;

typedef struct CnMn{
    int Cn;
    int Mn;
}CnMn;