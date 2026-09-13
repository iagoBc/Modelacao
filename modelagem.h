#ifndef __MODELAGEM_H__
#define __MODELAGEM_H__

#include "hidreletrica.h"
#include "central.h"
#include "arco.h"

void funcao_obj(unsigned int hidros_num, unsigned int central_num, unsigned int arcos_num, Hidre *hidros, Central *centrais, Arco *arcos);
void restricoes(unsigned int hidros_num, unsigned int central_num, unsigned int arcos_num, unsigned int vazao_rio, Hidre *hidros, Central *centrais, Arco *arcos);


#endif