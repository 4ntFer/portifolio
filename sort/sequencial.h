#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "Lista_s.h"
#include "Pessoa.h"

int line_number_identify(char fileName[]);
Pessoa** alocaLista_s(int tam);
void criaLista_s(char fileNasme[], Node* lista);
void verificaOpen_s(FILE** arq);
void desaloca_s(Node* lista);
void imprimeLista_s(Node* lista);
void insertEndNode_s(Node* lista, Pessoa* nodeinf);
void insertInfo(Pessoa* nodeinf);
void insertStartNode_s(Node* lista, Pessoa* nodeinf);
void insertNode_s(int n, Node* lista, Pessoa* nodeinf);
void removeStartNode_s(Node* lista);
void removeEndNode_s(Node* lista);
void removeNode_s(int n, Node* lista);
void buscaSequencial_s(char* rg, Node* lista);
int buscaBinaria_s(char* rg, Node* lista, int i, int f, CnMn* cont);
void saveArq_s(Node* lista);
void printBuscaBinaria_s(char* rg, Node* lista, int i, int f, CnMn* cont);
