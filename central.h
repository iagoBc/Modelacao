#ifndef __CENTRAL_H__
#define __CENTRAL_H__

#include <stdio.h>
#include "arco.h"

typedef struct{
    int demanda;
    int num_arcos;
    Arco *arcos;
} Central;

#endif