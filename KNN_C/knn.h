#include <time.h>
#include <omp.h>
#include "utilidade.h"

#ifndef KNN_H
#define KNN_H

DistanciaPonto Distancia(Ponto ponto1, Ponto ponto2);
float verificaClasse(DistanciaPonto distanciasPontos[],int k);
double KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads);
int ordena(int k, float *xtrain, float *ytrain, float *xtest);
double Mini_KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads, DistanciaPonto **distanciasPontos);
void Chama_KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads, int max_threads, int passo);
#endif