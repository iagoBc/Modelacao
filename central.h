#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <stdio.h>
#include "arco.h"

typedef struct{
    int demanda;
    int vizinhos;
    int num_arcos;
    arco *arcos;
} central;

#endif