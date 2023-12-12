#include <time.h>
#include "utilidade.h"

#ifndef KNN_H
#define KNN_H

DistanciaPonto Distancia(Ponto ponto1, Ponto ponto2);
float verificaClasse(DistanciaPonto distanciasPontos[],int k);
double KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes);
int ordena(int k, float *xtrain, float *ytrain, float *xtest);
#endif