#ifndef __MODELAGEM_H__
#define __MODELAGEM_H__

#include "hidreletrica.h"
#include "central.h"

void funcao_obj(int hidros_num, hidro *hidros, central *centrais, int central_num);
void restricoes(int hidros_num, int vazao_rio, hidro *hidros, central *centrais, int central_num);


#endif