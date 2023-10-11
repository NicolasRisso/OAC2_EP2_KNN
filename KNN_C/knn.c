#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar os pontos com x, y e classe
struct Ponto {
    float x;
    float y;
    float classe;
};

int main() {
    FILE *xtrainFile, *ytrainFile;
    char xtrainFileName[] = "xtrain.txt";
    char ytrainFileName[] = "ytrain.txt";

    // Abra os arquivos para leitura
    xtrainFile = fopen(xtrainFileName, "r");
    ytrainFile = fopen(ytrainFileName, "r");

    if (xtrainFile == NULL || ytrainFile == NULL) {
        perror("Erro ao abrir um dos arquivos");
        return 1;
    }

    int maxLinhas = 576; // Defina o tamanho máximo da matriz
    struct Ponto matrizPonto[maxLinhas * 4]; // Cada linha representa 4 pontos
    int numLinhas = 0;

    char classe[4];

    // Leia os dados dos arquivos e armazene na matriz de estruturas
    while (numLinhas < maxLinhas &&
        fscanf(xtrainFile, "%f,%f,%f,%f,%f,%f,%f,%f",
            &matrizPonto[numLinhas * 4].x, &matrizPonto[numLinhas * 4].y,
            &matrizPonto[numLinhas * 4 + 1].x, &matrizPonto[numLinhas * 4 + 1].y,
            &matrizPonto[numLinhas * 4 + 2].x, &matrizPonto[numLinhas * 4 + 2].y,
            &matrizPonto[numLinhas * 4 + 3].x, &matrizPonto[numLinhas * 4 + 3].y) != EOF &&
        fgets(classe, sizeof(classe), ytrainFile) != NULL) {
        printf("%d ", classe == "1.0\0");


        // Defina a classe para os quatro pontos na mesma linha
        // if (classe != 0){
        //     for (int i = 0; i < 4; i++){
        //         matrizPonto[numLinhas * 4 + i ].classe = 1;
        //     }
        // }else{
        //     for (int i = 0; i < 4; i++){
        //         matrizPonto[numLinhas * 4 + i ].classe = 0;
        //     }
        // }
        numLinhas++;
    }

    // Feche os arquivos após a leitura
    fclose(xtrainFile);
    fclose(ytrainFile);

    // Exiba os dados lidos
    for (int i = 0; i < numLinhas * 4; i++) {
        //printf("Ponto %d: x = %f, y = %f, classe = %d\n", i, matrizPonto[i].x, matrizPonto[i].y, matrizPonto[i].classe);
    }

    return 0;
}
