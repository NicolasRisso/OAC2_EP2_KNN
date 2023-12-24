#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main() {

    int tamanho = 0;
    char xtrainFileName[50];
    char ytrainFileName[50];
    char xtestFileName[] = "../data/xtest.txt";

    printf("Qual o tamanho do arquivo que deseja utilizar como entrada(100, 500, 1000...)? ");
    scanf("%d", &tamanho);
    if (tamanho == 100 || tamanho == 500 || tamanho == 1000 || tamanho == 10000 || tamanho == 100000 || tamanho == 200000 || tamanho == 500000 || tamanho == 1000000){
        sprintf(xtrainFileName, "../data/xtrain%d.txt", tamanho);
        sprintf(ytrainFileName, "../data/ytrain%d.txt", tamanho);
    }else{
        sprintf(xtrainFileName, "../data/xtrain.txt", tamanho);
        sprintf(ytrainFileName, "../data/ytrain.txt", tamanho);
    }

    int numCol = ContarCol(xtrainFileName);

    int maxLinhas = CountFileLines(xtrainFileName);
    Ponto *pontos = (Ponto *)malloc(maxLinhas * sizeof(Ponto));
    for (int i = 0; i < maxLinhas; i++) {
        // Supondo que você deseja alocar dinamicamente para o membro 'x'
        pontos[i].x = (float *)malloc(sizeof(float) * 8);
        // Inicializa outros membros
        pontos[i].classe = 0.0;
        pontos[i].id = i + 1;  // Atribui um ID fictício
    }

    int maxLinhasTestes = CountFileLines(xtestFileName);
    Ponto *testes = (Ponto *)malloc(maxLinhas * sizeof(Ponto));
    for (int i = 0; i < maxLinhas; i++) {
        // Supondo que você deseja alocar dinamicamente para o membro 'x'
        pontos[i].x = (float *)malloc(sizeof(float) * numCol);
        // Inicializa outros membros
        pontos[i].classe = 0.0;
        pontos[i].id = i + 1;  // Atribui um ID fictício
    }

    LeituraTrain(pontos, xtrainFileName, ytrainFileName);
    LeituraTest(testes, xtestFileName);

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    int k = 1;
    int numThreads = 1;
    int maxThreads = 1;
    int passo = 1;

    printf("Digite o numero do k: ");
    scanf("%d", &k);
    printf("Digite o numero de Threads: ");
    scanf("%d", &numThreads);

    if (numThreads <= 0) {
        printf("Executando multiplos KNNs.\nDigite o maximo de threads que deseja utilizar: ");
        scanf("%d", &maxThreads);
        printf("Digite o passo das threads: ");
        scanf("%d", &passo);
        numThreads = 2;
        Chama_KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, numThreads, maxThreads, passo);
    }else{
        double time = KNN(pontos, testes, k, maxLinhas, maxLinhasTestes, numThreads);
        printf("Tempo de Execucao: %.3fs\n", time);
    }

    //PrintArray(pontos, maxLinhas);
    //PrintArray(testes, maxLinhasTestes);

    //int tmp = ordena(3, xtrain, ytrain, xtest);

    return 0;
}
