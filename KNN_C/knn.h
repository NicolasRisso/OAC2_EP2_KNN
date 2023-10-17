#include "leitura.h"
#include "utilidade.h"

#ifndef KNN_H
#define KNN_H

DistanciaPonto Distancia(Ponto ponto1, Ponto ponto2);
void KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes);
float verificaClasse(DistanciaPonto distanciasPontos[],int k);
#endif