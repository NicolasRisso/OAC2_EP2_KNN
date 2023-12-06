#include <stdio.h>
#include <string.h>
#include "leitura.h"
#include "utilidade.h"

void EscreverX(Ponto matrizPonto[], FILE *file, int maxLinhas){
    for (int numLinhas = 0; numLinhas < maxLinhas; numLinhas++){
        fscanf(file, "%f,%f,%f,%f,%f,%f,%f,%f",
        &matrizPonto[numLinhas].x[0], &matrizPonto[numLinhas].x[1],
        &matrizPonto[numLinhas].x[2], &matrizPonto[numLinhas].x[3],
        &matrizPonto[numLinhas].x[4], &matrizPonto[numLinhas].x[5],
        &matrizPonto[numLinhas].x[6], &matrizPonto[numLinhas].x[7]);//Verifica se o arquivo 'xtrain.txt' ainda tem linhas e salva os floats.
    }
}

void EscreverY(Ponto matrizPonto[], FILE *file, int maxLinhas){
    char tmp[4];
    for (int i = 0; i < maxLinhas; i++){
        if (fgets(tmp, sizeof(tmp), file) == NULL) break; //Para a leitura caso o arquivo tenha acabado.
        if (strlen(tmp) <= 1) //Evita a leitura repetida causada pelo \0.
            continue;
        sscanf(tmp, "%f", &matrizPonto[i].classe);
        matrizPonto[i].id = i + 1;
        fgetc(file); //Para a leitura atual do fgets para que ele não leia o .0 do arquivo como um outro float.
    }
}

void LeituraTrain(Ponto matrizPonto[], char xtrainFileName[], char ytrainFileName[]){

    int maxLinhas = CountFileLines(xtrainFileName);

    FILE *xtrainFile, *ytrainFile;

    xtrainFile = fopen(xtrainFileName, "r");
    ytrainFile = fopen(ytrainFileName, "r");

    if (xtrainFile == NULL) perror("Erro ao abrir o arquivo do xtrain");
    if (ytrainFile == NULL) perror("Erro ao abrir o arquivo do ytrain");

    //Leitura do xtrain
    EscreverX(matrizPonto, xtrainFile, maxLinhas);

    //Leitura do ytrain
    EscreverY(matrizPonto, ytrainFile, maxLinhas);

    // Feche os arquivos após a leitura
    fclose(xtrainFile);
    fclose(ytrainFile);
}

void LeituraTest(Ponto matrizPonto[], int maxLinhas){
    FILE *xtestFile;
    char xtestFileName[] = "../data/xtest.txt";

    xtestFile = fopen(xtestFileName, "r");
    if (xtestFile == NULL) perror("Erro ao abrir um dos arquivos");

    //Escreve as coordenadas do arquivo xtest
    EscreverX(matrizPonto, xtestFile, maxLinhas);

    //Define todas as classes do test como indeterminadas.
    for (int i = 0; i < maxLinhas; i++){
        matrizPonto[i].classe = -1;
        matrizPonto[i].id = -1;
    }
}