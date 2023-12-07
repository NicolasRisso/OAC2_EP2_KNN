#include <stdio.h>
#include <math.h>
#include "knn.h"

DistanciaPonto Distancia(Ponto ponto1, Ponto ponto2){
    DistanciaPonto tmp;
    float distancia = 0;
    for (int i = 0; i < Lenght(ponto2.x); i++){
        distancia += (ponto1.x[i] - ponto2.x[i])*(ponto1.x[i] - ponto2.x[i]);
    }

    tmp.distancia = sqrt(distancia);
    tmp.classe = ponto2.classe;
    tmp.id = ponto2.id;

    return tmp;
}

float verificaClasse(DistanciaPonto distanciasPontos[],int k){
    int classeZero = 0, classeUm = 0, distClasseZero = 0, distClasseUm = 0;
    for( int i = 0; i<k;i++){
        if(distanciasPontos[i].classe == 1){
            classeUm++;
            distClasseUm += distanciasPontos[i].distancia;
        }else{
            classeZero++;
            distClasseZero += distanciasPontos[i].distancia;
        }
    }
    printf("Pedres: %d - %d\n", classeZero, classeUm);
    if(k%2 != 0 ) return classeUm > classeZero ? 1 : 0;
    else return distClasseZero > distClasseUm ? 1 : 0;
}

void KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes){
    DistanciaPonto distanciasPontos[tamanhoTestes][tamanhoPontos];
    
    for (int i = 0; i < tamanhoTestes; i++){
        for (int j = 0; j < tamanhoPontos; j++) distanciasPontos[i][j].distancia = distanciasPontos[i][j].classe = distanciasPontos[i][j].id = -1; //Definindo o array de distancias.
    }

    //Calculando todas as distâncias com relação à um ponto de teste.
    for (int i = 0; i < tamanhoTestes; i++){
        for (int j = 0; j < tamanhoPontos; j++){
            if (&pontos[j] == NULL) break;
            distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
        }
        bubbleSort(distanciasPontos[i], tamanhoPontos);
         //Implementar a observacao dos k pontos mais proximos
        testes[i].classe = verificaClasse(distanciasPontos[i],k);
    }

    for (int i = 0; i < tamanhoTestes; i++){
        printf("teste:%d classe: %.1f\n", i+1, testes[i].classe);
    }

    //Imprimindo
    for (int i = 0; i < tamanhoPontos; i++) {
        if (distanciasPontos[69][i].distancia == -1) break;
        printf("Distancia(%d | %d): ", i + 1, distanciasPontos[69][i].id);
        printf("%.4f, ", distanciasPontos[69][i].distancia);
        printf("%.0f\n", distanciasPontos[69][i].classe);
    }
}

int ordena(int k, float *xtrain, float *ytrain, float *xtest){
    int tamanho = 0;
    while (ytrain[tamanho]){
        tamanho++;
    }
    
    Ponto pontos[tamanho];
    Ponto teste;

    for (int i = 0; i < tamanho; i++){
        pontos[i].classe = ytrain[i];
        for (int j = 0; j < 8; j++){
            pontos[i].x[j] = xtrain[i * 8 + j];
        }
    }
    for (int i = 0; i < 8; i++){
        teste.x[i] = xtest[i];
    }
    return -1;
}