#include "modelagem.h"


void funcao_obj(int hidros_num, hidro *hidros, central *centrais, int central_num){
    printf("min : ");
    for(int i=0; i<hidros_num; i++){
        printf("%d*V%d + ", hidros[i].custo_producao, i+1);
    }

    for(int i =0; i < hidros_num; i++){
        for(int j = 0; j < hidros[i].num_arcos; j++){
            printf("%d*e%d_%d + ", hidros[i].arcos[j].custo, i+1, hidros[i].arcos[j].indice_c);
        }
    }

   for(int i =0; i < central_num; i++){
       for(int j = 0; j < centrais[i].num_arcos; j++){
           if(j == centrais[i].num_arcos-1){
               printf("%d*e%d_%d", centrais[i].arcos[j].custo, hidros_num+i+1, centrais[i].arcos[j].indice_c);
               continue;
           }
           printf("%d*e%d_%d + ", centrais[i].arcos[j].custo, hidros_num+i+1, centrais[i].arcos[j].indice_c);
       }
   }
    printf(";\n");
}


void restricoes(int hidros_num, int vazao_rio, hidro *hidros, central *centrais, int central_num){
    for(int i=0; i<hidros_num; i++){    // Fi x Vi <= Mi -> producao de energia da hidreletrica <= capacidade maxima da hidreletrica
        printf("%d*V%d <= %d;\n", hidros[i].eficiencia, i+1, hidros[i].capacidade);
    }

    for(int i=0; i<hidros_num; i++){    // Vi <= R -> vazao de agua da hidreletrica <= vazao do rio
        printf("V%d <= %d;\n", i+1, vazao_rio);
    }

    for(int i=0; i<hidros_num; i++){    // eij <= wij -> energia que sai da hidreletrica <= capacidade do arco
        for(int j=0; j<hidros[i].num_arcos; j++){
            printf("e%d_%d <= %d;\n", i+1, hidros[i].arcos[j].indice_c, hidros[i].arcos[j].capacidade);
        }
    }

    for(int i=0; i<central_num; i++){   // eij <= wij -> energia que sai da central <= capacidade do arco
        for(int j=0; j<centrais[i].num_arcos; j++){
            printf("e%d_%d <= %d;\n", hidros_num+i+1, centrais[i].arcos[j].indice_c, centrais[i].arcos[j].capacidade);
        }
    }

    for(int i=0; i<hidros_num; i++){   // sum(eij) = Fi x Vi -> o que sai da hidreletrica 
        for(int j=0; j<hidros[i].num_arcos; j++){
            printf("e%d_%d = %d*V%d;\n", i+1, hidros[i].arcos[j].indice_c, hidros[i].eficiencia, i+1);
        }
    }


}
