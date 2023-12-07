#include "leitura.h"

#ifndef UTILIDADE_H
#define UTILIDADE_H

void PrintArray(Ponto lista[], int max);
int CountFileLines(char filePath[]);
void bubbleSort(DistanciaPonto distancias[], int n);
int ContarCol(char nomeArquivo[]);
int Lenght(float array[]);
void alocarEspaco(Ponto *ponto, int numColunas);

#endif