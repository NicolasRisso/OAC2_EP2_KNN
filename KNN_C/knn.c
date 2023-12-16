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
    float distClasseZero = 0, distClasseUm = 0;
    for( int i = 0; i<k;i++){
        if((int)distanciasPontos[i].classe == 1){
            classeUm++;
            distClasseUm += distanciasPontos[i].distancia;
        }else{
            classeZero++;
            distClasseZero += distanciasPontos[i].distancia;
        }
    }
   // printf("Pedres: %d - %d\n", classeZero, classeUm);
    if(k%2 != 0 ) return classeUm > classeZero ? 1 : 0;
    else return distClasseZero > distClasseUm ? 1 : 0;
}

double KNN(Ponto pontos[], Ponto testes[], int k, int tamanhoPontos, int tamanhoTestes){
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
    omp_set_num_threads(1);


    clock_t start_time = clock();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < tamanhoTestes; i++) {
        // Calculate distances for each test point
        for (int j = 0; j < tamanhoPontos; j++) {
            distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
        }
    }




    // #pragma omp parallel for schedule(dynamic)
    // for (int i = 0; i < tamanhoTestes; i++) {
    //     // Calculate start and end indices for each thread
    //     int thread_id = omp_get_thread_num();
    //     int chunk_size = (tamanhoPontos + omp_get_num_threads() - 1) / omp_get_num_threads();
    //     int start = omp_get_thread_num() * chunk_size;
    //     int end = (omp_get_thread_num() + 1) * chunk_size;
    //     if (end > tamanhoPontos) {
    //         end = tamanhoPontos;
    //     }

    //     // Calculate distances for the assigned range
    //     for (int j = start; j < end; j++) {
    //         if (&pontos[j] == NULL) break;
    //         distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
    //     }
    // }

    // // Combine results after the parallel section
    // for (int i = 0; i < tamanhoTestes; i++) {
    //     for (int j = 0; j < tamanhoPontos; j++) {
    //         // Combine results from all threads
    //         for (int t = 0; t < omp_get_num_threads(); t++) {
    //             DistanciaPonto tmp = privateDistanciasPontos[t][i][j];
    //             if (tmp.distancia != -1){
    //                 distanciasPontos[i][j] = privateDistanciasPontos[t][i][j];
    //             } else continue;
    //         }
    //     }
    // }

    //Calculando todas as distâncias com relação à um ponto de teste.
    // for (int i = 0; i < tamanhoTestes; i++){
    //     for (int j = 0; j < tamanhoPontos; j++){
    //         if (&pontos[j] == NULL) break;
    //         distanciasPontos[i][j] = Distancia(testes[i], pontos[j]);
    //     //    printf("iteração: %d,classe: %f ---  distancia: %f, linha: %d\n",j,distanciasPontos[i][j].classe, distanciasPontos[i][j].distancia, distanciasPontos[i][j].id);
    //     }
    //      // Ordenar as distâncias para o ponto de teste atual usando qsort
    // }

    clock_t end_time = clock();

    for (int i = 0; i < tamanhoTestes; i++){ 
        qsort(distanciasPontos[i], tamanhoPontos, sizeof(struct DistanciaPonto), compararDistancias);
        //Implementar a observacao dos k pontos mais proximos
        testes[i].classe = verificaClasse(distanciasPontos[i],k);
    }

    for (int i = 0; i < tamanhoTestes; i++){
        printf("teste:%d classe: %.1f\n", i+1, testes[i].classe);
    }

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // //Imprimindo
    // for (int i = 0; i < tamanhoPontos; i++) {
    //     if (distanciasPontos[0][i].distancia == -1) break;
    //     printf("Distancia(%d | %d): ", i + 1, distanciasPontos[0][i].id);
    //     printf("%.4f, ", distanciasPontos[0][i].distancia);
    //     printf("%.0f\n", distanciasPontos[0][i].classe);
    // }
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