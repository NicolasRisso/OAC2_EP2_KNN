#include <stdio.h>
#include <math.h>
#include "knn.h"

int Distancia(Ponto ponto1, Ponto ponto2){
    float distancia = 0;
    for (int i = 0; i < 8; i++){
        distancia += (ponto1.x[i] - ponto2.x[i])*(ponto1.x[i] - ponto2.x[i]);
    }
    return sqrt(distancia);
}