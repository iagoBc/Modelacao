#ifndef __ARCO_H__
#define __ARCO_H__

typedef unsigned int uint;

typedef struct{
    uint capacidade;     // Capacidade de transmissao do arco
    uint custo;          // Custo de transmissao do arco
    uint destino;        // Destino do arco
    uint origem;         // Origem do arco
} Arco;

#endif