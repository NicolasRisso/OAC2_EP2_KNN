#include "leitura.h"

#ifndef UTILIDADE_H
#define UTILIDADE_H

void PrintArray(Ponto lista[], int max);
int CountFileLines(char filePath[]);
int ContarCol(char nomeArquivo[]);
int Lenght(float array[]);
int LenghtPonto(Ponto array[]);
void alocarEspaco(Ponto *ponto, int numColunas);
int compararDistancias(const void *a, const void *b);
void SaveYTest(Ponto testes[]);
#endif