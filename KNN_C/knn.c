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
    DistanciaPonto distanciasPontos[tamanhoTestes][tamanhoPontos];
    
    for (int i = 0; i < tamanhoTestes; i++){
        for (int j = 0; j < tamanhoPontos; j++) distanciasPontos[i][j].distancia = -1; //Definindo o array de distancias.
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
        if (distanciasPontos[3][i].distancia == -1) break;
        printf("Distancia(%d): ", i + 1);
        printf("%.4f, ", distanciasPontos[3][i].distancia);
        printf("%.0f\n", distanciasPontos[3][i].classe);
    }
}

float verificaClasse(DistanciaPonto distanciasPontos[],int k){
    int classeZero = 0;
    int classeUm = 0;
    int distClasseZero = 0;
    int distClasseUm = 0;
    for( int i = 0; i<k;i++){
        if(distanciasPontos[i].classe == 1){
            classeUm++;
            distClasseUm += distanciasPontos[i].distancia;
        }else{
            classeZero++;
            distClasseZero += distanciasPontos[i].distancia;
        }
    }
    if(k%2 != 0 ){
        if( classeUm > classeZero){
            return 1.0;
        }else{
            return 0.0;
        }
    }else{
        if(distClasseZero > distClasseUm ){
            return 1;
        }
        else{
            return 0;
        }
    }
}