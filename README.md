
# union-find
##  Compilação

    cd src
    make
## Modo de uso

    cd bin
    ./unionfind algorithm input-file output-file
Os valores de algorithm podem ser:

 - `original`: Implementação naive.
 - `improved`: Implementação com delete constante.
 - `debug`: Vai rodar as duas implementações ao mesmo tempo e encerrar o programa na primeira divergência. 

## Entrada
O arquivo de entrada deve conter várias sequências da seguinte forma:

    add
    28
    add
    29
    union
    28 29
    delete
    28

## Teste

    cd test

Para gerar um arquivo de entrada:

    node generate_input.js  $edges  $nodes  $removed_nodes input_file
Para rodar os testes observando o tempo:

    ./run-time-tests.sh param_a_variar

`param_a_variar` pode ser `nodes`, `edges` ou `removed_nodes`

nodes -> varia de 1000 a 10000 de 1000 em 1000

edges -> varia de 1000 a 10000 de 1000 em 1000

removed_nodes -> varia de 500 a 5000 de 500 em 500

Enquanto um parâmetro varia, os outros permanecem constantes. Os valores constantes são:

nodes -> 10000

edges -> 1000

removed_nodes -> 500

./run-all-time-tests.sh roda o script acima 10 vezes (para ser usado dps n cálculo do tempo médio)

Da mesma forma, para testes de memória, tem:

    ./run-mem-tests.sh

e

    ./run-all-mem-tests.sh
 Já `node getMetrics.js` gera as planilhas com métricas de tempo e memória.
