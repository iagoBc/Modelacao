#ifndef __HIDRELETRICA_H__
#define __HIDRELETRICA_H__

typedef unsigned int uint;

typedef struct{
    uint capacidade;         // Capacidade maxima de energia que a hidreletrica pode produzir
    uint eficiencia;         // Eficiencia da hidreletrica
    uint custo;              // Custo de producao de energia da hidreletrica
} Hidre;

#endif

