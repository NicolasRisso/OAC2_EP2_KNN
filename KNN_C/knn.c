#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
    int classeZero = 0, classeUm = 0;
    for( int i = 0; i<k;i++){
        if((int)distanciasPontos[i].classe == 1){
            classeUm++;
        }else{
            classeZero++;
        }
    }
   // printf("Pedres: %d - %d\n", classeZero, classeUm);
    if(k%2 != 0 ) return classeUm > classeZero ? 1 : 0;
    else return distanciasPontos[0].classe;
}

double KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads){
    // Aloca dinamicamente memória para a matriz
    DistanciaPonto **distanciasPontos = (DistanciaPonto **)malloc(tamanhoTestes * sizeof(DistanciaPonto *));
    for (int i = 0; i < tamanhoTestes; i++) {
        distanciasPontos[i] = (DistanciaPonto *)malloc(tamanhoPontos * sizeof(DistanciaPonto));
    }

    // Inicializa a matriz
    for (int i = 0; i < tamanhoTestes; i++) {
        for (int j = 0; j < tamanhoPontos; j++) {
            distanciasPontos[i][j].distancia = distanciasPontos[i][j].classe = distanciasPontos[i][j].id = -1;
        }
    }

    //atualize aqui o num de threads
    omp_set_num_threads(nthreads);


    clock_t start_time = clock();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < tamanhoTestes; i++) {
        // Calculate distances for each test point
        for (int j = 0; j < tamanhoPontos; j++) {
            distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
        }
    }

    clock_t end_time = clock();

    //ATENCAO TIREI A PARTE DE ORDENAR PARA FACILITAR NA HORA DE MEDIR O TEMPO DO KNN!!!
    //COLOCAR DEVOLTA DPS
    //--------------------------------------------------------------------------------------------------
    for (int i = 0; i < tamanhoTestes; i++){ 
        qsort(distanciasPontos[i], tamanhoPontos, sizeof(struct DistanciaPonto), compararDistancias);
        //Implementar a observacao dos k pontos mais proximos
        testes[i].classe = verificaClasse(distanciasPontos[i],k);
    }

    for (int i = 0; i < tamanhoTestes; i++){
       printf("teste:%d classe: %.1f\n", i+1, testes[i].classe);
    }

    SaveYTest(testes);

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
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

double Mini_KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads, DistanciaPonto **distanciasPontos){
    //atualize aqui o num de threads
    omp_set_num_threads(nthreads);

    clock_t start_time = clock();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < tamanhoTestes; i++) {
        // Calculate distances for each test point
        for (int j = 0; j < tamanhoPontos; j++) {
            distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
        }
    }

    clock_t end_time = clock();

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void Chama_KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes, int nthreads, int max_threads, int passo){
    // Aloca dinamicamente memória para a matriz
    DistanciaPonto **distanciasPontos = (DistanciaPonto **)malloc(tamanhoTestes * sizeof(DistanciaPonto *));
    for (int i = 0; i < tamanhoTestes; i++) {
        distanciasPontos[i] = (DistanciaPonto *)malloc(tamanhoPontos * sizeof(DistanciaPonto));
    }
    // Inicializa a matriz
    for (int i = 0; i < tamanhoTestes; i++) {
        for (int j = 0; j < tamanhoPontos; j++) {
            distanciasPontos[i][j].distancia = distanciasPontos[i][j].classe = distanciasPontos[i][j].id = -1;
        }
    }
    double time = 0;
    for (int i = 1; i <= max_threads; i += passo){
        time = Mini_KNN(pontos, testes, k, tamanhoPontos, tamanhoTestes, i, distanciasPontos);
        printf("Tempo de Execucao(%d): %.3f\n", i, time);
    }
}