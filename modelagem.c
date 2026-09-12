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

    for(int i=0; i<central_num; i++){   // sum(eij) - sum(eji) = Di -> o que entra e sai da central deve ser igual a demanda da central
        for(int j=0; j<hidros_num; j++){
            for(int k=0; k<hidros[j].num_arcos; k++){
                if(hidros[j].arcos[k].indice_c == i+1){
                    printf("+e%d_%d ", j+1, hidros[j].arcos[k].indice_c);
                }
            }
        }

        for(int j=0; j<central_num; j++){
            if(j == i) continue;
            for(int k=0; k<centrais[j].num_arcos; k++){
                if(centrais[j].arcos[k].indice_c == i+1){
                    printf("+e%d_%d ", hidros_num+j+1, centrais[j].arcos[k].indice_c);
                }
            }
        }

        for(int j=0; j<centrais[i].num_arcos; j++){ // energia que sai da central
            if(j == centrais[i].num_arcos-1){
                printf("-e%d_%d ", hidros_num+i+1, centrais[i].arcos[j].indice_c);
                continue;
            }
            printf("-e%d_%d ", hidros_num+i+1, centrais[i].arcos[j].indice_c);
        }

        printf("= %d;\n", centrais[i].demanda);
    }

    for(int i=0; i<hidros_num; i++){    // Vi >= 0 -> energia produzida pela hidreletrica deve ser maior ou igual a 0
        printf("V%d >= 0;\n", i+1);
    }

    for(int i=0; i<hidros_num; i++){    // eij >= 0 -> energia que sai da hidreletrica deve ser maior ou igual a 0
        for(int j=0; j<hidros[i].num_arcos; j++){
            printf("e%d_%d >= 0;\n", i+1, hidros[i].arcos[j].indice_c);
        }
    }     
                                                                               
    for(int i=0; i<central_num; i++){   // eij >= 0 -> energia que sai da central deve ser maior ou igual a 0
        for(int j=0; j<centrais[i].num_arcos; j++){
            printf("e%d_%d >= 0;\n", hidros_num+i+1, centrais[i].arcos[j].indice_c);
        }
    }                                                                                     
}

