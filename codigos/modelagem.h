#ifndef __MODELAGEM_H__
#define __MODELAGEM_H__

#include <stdio.h>

#include "hidreletrica.h"
#include "central.h"
#include "arco.h"

typedef unsigned int uint;


void funcao_obj(uint hidros_num, uint central_num, uint arcos_num, Hidre *hidros, Central *centrais, Arco *arcos);
void restricoes(uint hidros_num, uint central_num, uint arcos_num, uint vazao_rio, Hidre *hidros, Central *centrais, Arco *arcos);


#endif