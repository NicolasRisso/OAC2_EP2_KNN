#ifndef STRUCTS_H
#define STRUCTS_H

struct Ponto {
    float x[8];  //x, y, z, w, u, v, s, t
    float classe;
};
typedef struct Ponto Ponto;

struct DistanciaPonto
{
    float distancia;
    float classe;
};
typedef struct DistanciaPonto DistanciaPonto;

#endif