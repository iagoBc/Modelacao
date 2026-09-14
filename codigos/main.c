#include <stdio.h>
#include <stdlib.h>

#include "hidreletrica.h"
#include "central.h"
#include "arco.h"
#include "modelagem.h"
#include "arco.h"


// Função para ler os dados de entrada
void ler_dados(uint hidro_num, uint central_num, uint *arcos_num, Hidre *hidros, Central *centrais, Arco **arcos){
    for(uint i = 0; i < hidro_num; i++){            // Lê os dados das hidrelétricas
        scanf("%d %d %d", &hidros[i].capacidade, &hidros[i].eficiencia, &hidros[i].custo);
    }

    for(uint i = 0; i < central_num; i++){          // Lê os dados das centrais
        scanf("%d", &centrais[i].demanda);
    }

    int k = 0;
    for(uint i = 0; i < hidro_num + central_num; i++){          // Lê os dados dos arcos
        int n;
        scanf("%d", &n);
        *arcos_num += n;
        *arcos = realloc(*arcos, (*arcos_num) * sizeof(Arco));          // Realoca memória para os arcos

        for(uint j = 0; j < n; j++){            // Lê os dados de cada arco
            (*arcos)[k].origem = i + 1;
            scanf("%d %d %d", &(*arcos)[k].destino, &(*arcos)[k].capacidade, &(*arcos)[k].custo);
            k++;
        }
    }
}


int main(){
    uint h, l, r, n = 0;            // h = numero de hidreletricas, l = numero de centrais, r = vazao do rio, n = numero de arcos
    scanf("%d %d %d", &h, &l, &r);


    Hidre hidreletricas[h];
    Central centrais[l];
    Arco *arcos = NULL;
    
    ler_dados(h, l, &n, hidreletricas, centrais, &arcos);
    funcao_obj(h,l, n, hidreletricas, centrais, arcos);
    restricoes(h, l, n, r, hidreletricas, centrais, arcos);
}