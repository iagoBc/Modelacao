# Produção e transmissão de energia por programação linear

Implementação, em C99, de um gerador de modelos de programação linear para uma
rede de energia formada por hidrelétricas, centrais elétricas e arcos de
transmissão.

O programa lê uma instância pela entrada padrão e escreve, na saída padrão, um
modelo no formato aceito pelo [lp_solve](http://lpsolve.sourceforge.net/5.5/lp-format.htm).
A resolução do modelo (solução ótima ou detecção de inviabilidade) é feita pelo
`lp_solve`, não pelo programa em C.

## Problema

O objetivo é determinar:

- a vazão utilizada por cada hidrelétrica;
- a energia transmitida em cada arco da rede;
- uma distribuição que atenda exatamente à demanda de todas as centrais;
- a operação de menor custo total de produção e transmissão.

O modelo respeita:

- a capacidade máxima de produção de cada hidrelétrica;
- a vazão máxima disponível no rio;
- a capacidade de cada arco de transmissão;
- a conservação da energia produzida;
- o atendimento da demanda das centrais;
- a não negatividade das variáveis.

## Modelo matemático

### Parâmetros

- `h`: número de hidrelétricas;
- `l`: número de centrais;
- `R`: vazão máxima disponível no rio;
- `Mᵢ`: capacidade máxima de produção da hidrelétrica `i`;
- `Fᵢ`: eficiência da hidrelétrica `i`;
- `Cᵢ`: custo por unidade de vazão da hidrelétrica `i`;
- `Dₖ`: demanda da central `k`;
- `wₐ`: capacidade do arco `a`;
- `cₐ`: custo de transmissão por unidade de energia no arco `a`.

As hidrelétricas ocupam os vértices globais `1` a `h`. As centrais ocupam os
vértices globais `h + 1` a `h + l`, mas o destino dos arcos é informado usando o
índice local da central, entre `1` e `l`.

### Variáveis

- `Vᵢ ≥ 0`: vazão utilizada pela hidrelétrica `i`;
- `eₐ ≥ 0`: energia transmitida pelo arco `a`.

A produção da hidrelétrica `i` é `Fᵢ Vᵢ`.

### Função objetivo

Minimizar:

```text
Z = Σ(Cᵢ Vᵢ) + Σ(cₐ eₐ)
```

### Restrições geradas

Para cada hidrelétrica:

```text
Fᵢ Vᵢ ≤ Mᵢ
Vᵢ ≤ R
Σ eₐ = Fᵢ Vᵢ          (arcos que saem da hidrelétrica)
Vᵢ ≥ 0
```

Para cada arco:

```text
eₐ ≤ wₐ
eₐ ≥ 0
```

Para cada central `k`:

```text
energia que chega - energia que sai = Dₖ
```

Como os custos são não negativos, a igualdade no atendimento da demanda não
altera a solução ótima: uma solução com excedente poderia ser reduzida até
atender exatamente à demanda.

## Requisitos

- GCC com suporte a C99;
- GNU Make;
- [lp_solve](http://lpsolve.sourceforge.net/5.5/), para resolver os arquivos
  gerados.

## Compilação

Na raiz do projeto:

```bash
make
```

Isso compila os fontes em `codigos/` com `gcc -Wall -g -std=c99` e gera o
executável `energia`.

Para remover apenas os arquivos objeto:

```bash
make clean
```

Para remover os objetos e o executável:

```bash
make purge
```

## Formato da entrada

A entrada é lida pela entrada padrão nesta ordem:

1. Uma linha com `h l R`.
2. `h` linhas, uma para cada hidrelétrica, com:
   ```text
   Mᵢ Fᵢ Cᵢ
   ```
3. `l` linhas, uma para cada central, contendo:
   ```text
   Dₖ
   ```
4. Para cada um dos `h + l` vértices, na ordem das hidrelétricas e depois das
   centrais:
   - um inteiro `n`, indicando o número de arcos de saída;
   - `n` linhas com:
     ```text
     destino capacidade custo
     ```

O campo `destino` é o índice local da central de destino (`1` a `l`). A origem
é determinada automaticamente pelo vértice que está sendo lido.

Exemplo de entrada:

```text
2 2 10
100 20 2
50 10 1
50
80
1
1 200 1
1
2 100 2
1
2 100 1
0
```

## Uso

O programa gera o modelo na saída padrão. É possível redirecioná-lo para um
arquivo `.lp` e então passá-lo ao `lp_solve`:

```bash
./energia < exemplos/viavel1.txt > exemplos/viavel1_gerado.lp
lp_solve exemplos/viavel1_gerado.lp
```

Para a instância viável fornecida, a solução ótima esperada é:

```text
Value of objective function: 223.00000000

V1     4
V2     5
e1_1   80
e2_2   50
e3_2   30
```

Isso corresponde a custo:

```text
2(4) + 1(5) + 1(80) + 2(50) + 1(30) = 223
```

Também há uma instância inviável:

```bash
./energia < exemplos/D_alto.txt > exemplos/inviavel_D_gerado.lp
lp_solve exemplos/inviavel_D_gerado.lp
```

Nesse caso, o `lp_solve` informa:

```text
This problem is infeasible
```

Uma instância pode ser inviável quando a produção máxima não é suficiente para
as demandas ou quando as capacidades dos arcos impedem que energia suficiente
chegue a alguma central.

## Organização do projeto

```text
.
├── codigos/
│   ├── arco.h           # Estrutura dos arcos
│   ├── central.h        # Estrutura das centrais
│   ├── hidreletrica.h   # Estrutura das hidrelétricas
│   ├── main.c           # Leitura da entrada e ponto de entrada
│   ├── modelagem.c      # Geração da função objetivo e restrições
│   └── modelagem.h      # Declarações da geração do modelo
├── exemplos/             # Instâncias e saídas de referência
├── makefile
└── Modelagem.pdf         # Relatório da modelagem
```

## Referências

- [Documentação do formato do lp_solve](http://lpsolve.sourceforge.net/5.5/lp-format.htm)
- MATOUŠEK, J.; GÄRTNER, B. *Understanding and Using Linear Programming*.
- UNIVERSIDADE FEDERAL DO PARANÁ. *CI1238/INFO7070 — Otimização: Primeiro
  Trabalho Prático*.