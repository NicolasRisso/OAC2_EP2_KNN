#include <stdio.h>
#include <math.h>
#include "knn.h"
#include "utilidade.h"

DistanciaPonto Distancia(Ponto ponto1, Ponto ponto2){
    DistanciaPonto tmp;
    float distancia = 0;
    for (int i = 0; i < 8; i++){
        distancia += (ponto1.x[i] - ponto2.x[i])*(ponto1.x[i] - ponto2.x[i]);
    }

    tmp.distancia = sqrt(distancia);
    tmp.classe = ponto2.classe;

    return tmp;
}

void KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes){
    DistanciaPonto distanciasPontos[tamanhoPontos];
    for (int i = 0; i < tamanhoPontos; i++) distanciasPontos[i].distancia = -1; //Definindo o array de distancias.

    //Calculando todas as distâncias com relação à um ponto de teste.
    for (int i = 0; i < tamanhoPontos; i++){
        if (&pontos[i] == NULL) break;
        distanciasPontos[i] = Distancia(testes[0], pontos[i]);
    }

    bubbleSort(distanciasPontos, tamanhoPontos);

    //Implementar a observacao dos k pontos mais proximos

    //Imprimindo
    for (int i = 0; i < tamanhoPontos; i++) {
        if (distanciasPontos[i].distancia == -1) break;
        printf("Distancia(%d): ", i + 1);
        printf("%.4f, ", distanciasPontos[i].distancia);
        printf("%f\n", distanciasPontos[i].classe);
    }
}