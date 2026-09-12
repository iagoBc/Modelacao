#ifndef __MODELAGEM_H__
#define __MODELAGEM_H__

#include "hidreletrica.h"
#include "central.h"


void funcao_obj(int hidros_num, Hidro *hidros, Central *centrais, int central_num);
void restricoes(int hidros_num, int vazao_rio, Hidro *hidros, Central *centrais, int central_num);


#endif