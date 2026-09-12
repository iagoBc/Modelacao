#include <stdio.h>
#include <stdlib.h>
#include "hidreletrica.h"
#include "central.h"
#include "arco.h"
#include "modelagem.h"


void ler_dados(unsigned int hidro_num, unsigned int central_num, Hidro *hidros, Central *centrais){
    for(int i = 0; i < hidro_num; i++){
        scanf("%d %d %d", &hidros[i].capacidade, &hidros[i].eficiencia, &hidros[i].custo_producao);
    }

    for(int i = 0; i < central_num; i++){
        scanf("%d", &centrais[i].demanda);
    }

    for(int i = 0; i < hidro_num; i++){
        scanf("%d", &hidros[i].num_arcos);
        hidros[i].arcos = malloc(hidros[i].num_arcos * sizeof(Arco));
        for(int j = 0; j < hidros[i].num_arcos; j++){
            scanf("%d %d %d", &hidros[i].arcos[j].indice_c, &hidros[i].arcos[j].capacidade, &hidros[i].arcos[j].custo);
        }
    }
    
    for(int i = 0; i < central_num; i++){
        scanf("%d", &centrais[i].num_arcos);
        centrais[i].arcos = malloc(centrais[i].num_arcos * sizeof(Arco));
        for(int j = 0; j < centrais[i].num_arcos; j++){
            scanf("%d %d %d", &centrais[i].arcos[j].indice_c, &centrais[i].arcos[j].capacidade, &centrais[i].arcos[j].custo);
        }
    }
}



void imprimir_dados(unsigned int hidro_num, unsigned int central_num, unsigned int rio_V, Hidro *hidros, Central *centrais){
    printf("h=%d | l=%d | R=%d\n", hidro_num, central_num, rio_V);
    for(int i = 0; i < hidro_num; i++){   
        printf("M%d=%d | F%d=%d | C%d=%d\n", i+1, hidros[i].capacidade, i+1, hidros[i].eficiencia, i+1, hidros[i].custo_producao);
    }

    for(int i = 0; i < central_num; i++){
        printf("D%d=%d\n", i+1, centrais[i].demanda);
    }

    for(int i =0; i < hidro_num; i++){
        for(int j = 0; j < hidros[i].num_arcos; j++){
            printf("t(%d,%d)=%d | w(%d,%d)=%d | c(%d,%d)=%d\n", i+1, j+1, hidros[i].arcos[j].indice_c, i+1, j+1, hidros[i].arcos[j].capacidade, i+1, j+1, hidros[i].arcos[j].custo);
        }
    }

    for(int i =0; i < central_num; i++){
        for(int j = 0; j < centrais[i].num_arcos; j++){
            printf("t(%d,%d)=%d | w(%d,%d)=%d | c(%d,%d)=%d\n", hidro_num+i+1, j+1, centrais[i].arcos[j].indice_c, hidro_num+i+1, j+1, centrais[i].arcos[j].capacidade, hidro_num+i+1, j+1, centrais[i].arcos[j].custo);
        }
    }
}


int main(){
    unsigned int hidro_num, central_num, vazao_rio;
    scanf("%d %d %d", &hidro_num, &central_num, &vazao_rio);

    Hidro hidros[hidro_num];
    Central centrais[central_num];
    
    ler_dados(hidro_num, central_num, hidros, centrais);

    //imprimir_dados(hidro_num, central_num, rio_V, hidros, centrais);
    funcao_obj(hidro_num, hidros, centrais, central_num);
    restricoes(hidro_num, vazao_rio, hidros, centrais, central_num);
}