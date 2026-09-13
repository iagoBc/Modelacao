#include "modelagem.h"
typedef unsigned int uint;

// Função que imprime a função objetivo do modelo de programação linear
// Sum(Ci x Vi) + Sum(cij x eij)
// Ci = custo de producao da hidreletrica, Vi = vasao de agua da hidreletrica, cij = custo de transmissao do arco, eij = energia transmitida pelo arco
void funcao_obj(uint hidros_num, uint central_num, uint arcos_num, Hidre *hidros, Central *centrais, Arco *arcos){
    printf("min : ");
    for(uint i=0; i<hidros_num; i++){            // Sum(Ci x Vi)
        printf("%d*V%d + ", hidros[i].custo, i+1);
    }

    for(uint i =0; i < arcos_num; i++){          // Sum(cij x eij) | cij
        if(i == arcos_num-1){
            printf("%d*e%d_%d;\n", arcos[i].custo, i+1, arcos[i].destino);
            continue;
        }
            printf("%d*e%d_%d + ", arcos[i].custo, i+1, arcos[i].destino);
    }
}


// Função que imprime as restrições do modelo de programação linear
// Fi x Vi <= Mi | producao de energia da hidreletrica <= capacidade maxima da hidreletrica
// Vi <= R | vazao de agua da hidreletrica <= vazao do rio
// eij <= wij | energia transmitida pelo arco <= capacidade do arco
// sum(eij) = Fi x Vi | o que sai da hidreletrica
// sum(eij) - sum(eji) >= Di | o que chega na central - o que sai da central = a demanda da central
// Vi, eij >= 0 | energia produzida pela hidreletrica e energia transmitida pelo arco devem ser maior ou igual a 0
void restricoes(uint hidros_num, uint central_num, uint arcos_num, uint vazao_rio, Hidre *hidros, Central *centrais, Arco *arcos){
    for(uint i=0; i<hidros_num; i++){    
        printf("%d*V%d <= %d;\n", hidros[i].eficiencia, i+1, hidros[i].capacidade);         // Fi x Vi <= Mi | producao de energia da hidreletrica <= capacidade maxima da hidreletrica
        
        printf("V%d <= %d;\n", i+1, vazao_rio);         // Vi <= R | vazao de agua da hidreletrica <= vazao do rio
        
        printf("V%d >= 0;\n", i+1);         // Vi >= 0 | energia produzida pela hidreletrica deve ser maior ou igual a 0
    }

    for(uint i=0; i < arcos_num; i++){ 
            printf("e%d_%d <= %d;\n", i+1, arcos[i].destino, arcos[i].capacidade);         // eij <= wij | energia transmitida pelo arco <= capacidade do arco
 
            if(arcos[i].origem <= hidros_num) printf("e%d_%d = %d*V%d;\n", i+1, arcos[i].destino, hidros[i].eficiencia, i+1);          // sum(eij) = Fi x Vi | o que sai da hidreletrica

            printf("e%d_%d >= 0;\n", i+1, arcos[i].destino);         // eij >= 0 | energia transmitida pelo arco deve ser maior ou igual a 0
    }                                                                      
    
    for(uint i=0; i < central_num; i++){
        for(uint j=0; j < arcos_num; j++){
            if(arcos[j].destino == i+1) printf("+e%d_%d ", j+1, arcos[j].destino);   
        }

        for(uint j=0; j < arcos_num; j++){
            if(arcos[j].origem == hidros_num+i+1) printf("-e%d_%d ", j+1, arcos[j].destino);   
        }

        printf("= %d;\n", centrais[i].demanda);         // sum(eij) - sum(eji) >= Di | o que chega na central - o que sai da central = a demanda da central
    }
}

