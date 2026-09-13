#ifndef __ARCO_H__
#define __ARCO_H__

#include <stdio.h>

typedef struct{
    int capacidade;     // Capacidade de transmissao do arco
    int custo;          // Custo de transmissao do arco
    int destino;        // Destino do arco
    int origem;         // Origem do arco
} Arco;

#endif