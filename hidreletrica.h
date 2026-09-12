#ifndef __HIDRELETRICA__
#define __HIDRELETRICA__

#include <stdio.h>
#include "arco.h"

typedef struct{
    int capacidade;
    int eficiencia;
    int custo_producao;
    int num_arcos;
    arco *arcos;
} hidro;

#endif

