#pragma once
#include "Lista_s.h"
#include "Pessoa.h"

void selectionSort_s(Node* lista, CnMn* cont);
void insertionSort_s(Node* lista, CnMn* cont);
void mergeSort_s(Node* lista, int inicio, int fim, CnMn* cont);
void merge_s(Node* lista, int inicio, int mid, int fim, CnMn* cont);
void quickSort_s(Node* lista, int inicio, int fim, CnMn* cont);
void trade(Node* lista, int a, int b);
void shellSort_s(Node* lista, CnMn* cont);
void bubbleSort_s(Node* lista, CnMn* cont);
void inicCnMn(CnMn* cont);
void printCnMn(CnMn* cont);