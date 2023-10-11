#include "leitura.h"

#ifndef UTILIDADE_H
#define UTILIDADE_H

struct DistanciaPonto
{
    float distancia;
    float classe;
};
typedef struct DistanciaPonto DistanciaPonto;

void PrintArray(Ponto lista[], int max);
int CountFileLines(char filePath[]);
void bubbleSort(DistanciaPonto distancias[], int n);

#endif