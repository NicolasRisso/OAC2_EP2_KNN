#include <stdio.h>

int main() {
    // Abra o arquivo ytrain.txt para leitura
    FILE *file_ytrain = fopen("ytrain.txt", "r");

    if (!file_ytrain) {
        printf("Erro ao abrir o arquivo ytrain.txt.\n");
        return 1;
    }

    char linha[1024]; // Suponha um tamanho máximo para a linha
    float valor = -1;

    // Ler cada linha do arquivo e imprimir o conteúdo
    while (fgets(linha, sizeof(linha), file_ytrain) != NULL) {
        sscanf(linha, "%f", &valor);
        printf("%d ", (int)valor);
    }

    fclose(file_ytrain);

    return 0;
}