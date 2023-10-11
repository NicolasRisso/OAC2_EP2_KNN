#include <stdio.h>
#include <string.h>
#include "leitura.h"

void Leitura(Ponto matrizPonto[], int maxLinhas){

    FILE *xtrainFile, *ytrainFile;
    char xtrainFileName[] = "../data/xtrain.txt";
    char ytrainFileName[] = "../data/ytrain.txt";

    // Abra os arquivos para leitura
    xtrainFile = fopen(xtrainFileName, "r");
    ytrainFile = fopen(ytrainFileName, "r");

    if (xtrainFile == NULL || ytrainFile == NULL) {
        perror("Erro ao abrir um dos arquivos");
    }

    //Leitura do xtrain
    for (int numLinhas = 0; numLinhas < maxLinhas; numLinhas++){
        fscanf(xtrainFile, "%f,%f,%f,%f,%f,%f,%f,%f",
        &matrizPonto[numLinhas].x[0], &matrizPonto[numLinhas].x[1],
        &matrizPonto[numLinhas].x[2], &matrizPonto[numLinhas].x[3],
        &matrizPonto[numLinhas].x[4], &matrizPonto[numLinhas].x[5],
        &matrizPonto[numLinhas].x[6], &matrizPonto[numLinhas].x[7]);//Verifica se o arquivo 'xtrain.txt' ainda tem linhas e salva os floats.
    }

    //Leitura do ytrain
    char tmp[4];
    for (int i = 0; i < maxLinhas; i++){
        if (fgets(tmp, sizeof(tmp), ytrainFile) == NULL) break; //Para a leitura caso o arquivo tenha acabado.
        if (strlen(tmp) <= 1) //Evita a leitura repetida causada pelo \0.
            continue;
        sscanf(tmp, "%f", &matrizPonto[i].classe);
        fgetc(ytrainFile); //Para a leitura atual do fgets para que ele não leia o .0 do arquivo como um outro float.
    }

    // Feche os arquivos após a leitura
    fclose(xtrainFile);
    fclose(ytrainFile);
}