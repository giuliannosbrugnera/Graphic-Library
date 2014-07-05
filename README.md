# Biblioteca Gráfica
## Projeto da disciplina de Computação Gráfica

Esta é uma biblioteca gráfica incrementada ao longo do semestre.

#### Instruções para compilação

```
$ make              # compila os arquivos
$ ./program         # executa o programa
$ make uninstall    # remove arquivos temporários e o executável
```

Alternativamente, você pode compilar usando o comando abaixo.

```
gcc main.c graphiclib.c -o program -lm -lX11
```

#### Lista mínima de funções para serem implementadas
##### A) Para o caso 2D

- [x] 1) uma estrutura com as dimensões mínimas e máximas de uma janela;
- [x] 2) uma estrutura com as dimensões mínimas e máximas de uma "viewport";
- [x] 3) uma estrutura para um ponto bidimensional;
- [x] 4) uma estrutura para um objeto bidimensional;
- [x] 5) uma estrutura para uma "look up table";
- [x] 6) uma função que converte coordenadas do SRU para o SRN;
- [x] 7) uma função que converte coordenadas do SRN para o SRD;
- [ ] 8) uma função que cria um buffer associado ao SRD;
- [x] 9) uma função que cria uma janela;
- [x] 10) uma função para traçado de segmentos de reta no SRD utilizando a abordagem incremental de funções;
- [x] 11) uma função para traçado de segmentos de reta no SRD utilizando o algoritmo do ponto médio;
- [ ] 12) uma função para preenchimento de um polígono (objeto 2D) no SRD (considerando as 3 abordagens discutidas);
- [ ] 13) funcões que realizam o deslocamento, rotação, escalonamento, cisalhamento e espelhamento na forma de operadores lineares considerando coordenadas homegêneas;
- [x] 14) funções para a conversão entre os sistemas de cores RGB e HSV e vice-versa;
- [x] 15) uma função para mapear o SRD no monitor para visualização (deve-se passar o SRD, matriz, e a "look up table");
- [x] 16) uma função que implementa a multiplicação de uma matriz por um vetor (já considerando coordenadas homogêneas, isto é, matrizes de tamanho 3 x 3 no caso bidimendional);
- [ ] 17) uma função que implementa a multiplicação de duas matrizes 3 x 3.

Obs: as funções do item 13 podem todas ser simplificadas com o uso da função do item 16, bastando passar a matriz correta
para a função.

##### B) Para o caso 3D

- [x] 1) uma estrutura para um ponto tridimensional;
- [x] 2) uma estrutura para uma face do objeto tridimensional;
- [ ] 3) uma estrutura para um objeto tridimensional;
- [ ] 4) uma função que dado dois vetores realize o produto vetorial entre eles;
- [ ] 5) uma função auxiliar para normalizar vetores (lembre-se que a base do observador deve ser ortonormal);
- [ ] 6) uma função que cria uma face de um objeto tridimensional (corresponde a aresta do objeto 2D);
- [ ] 7) uma função que realiza uma mudança de base entre bases ortonormais;
- [ ] 8) uma função que realiza uma projeção perspectiva na forma de uma transformação linear considerando coordenadas homegêneas;
- [ ] 9) uma função que implementa uma curva de Bèzier ou uma função que implementa uma B-Spline (escolha uma!);
- [ ] 10) funções que realizam o deslocamento, rotação, escalonamento, cisalhamento e espelhamento na forma de operadores lineares considerando coordenadas homegêneas no espaço tridimensional;
- [ ] 11) uma função para o algoritmo "z-buffer" (exercício opcional, pois provavelmente não teremos tempo hábil para discutir essa teoria em sala de aula);
- [ ] 12) uma função que implementa a multiplicação de uma matriz por um vetor (já considerando coordenadas homogêneas, isto é, matrizes de tamanho 4 x 4 no caso tridimendional);
- [ ] 13) uma função que implementa a multiplicação de duas matrizes 4 x 4.

Obs 01: as funções dos itens 7, 8 e 10, podem todas ser implementadas com a função do item 12;

Obs 02: a geração da base do observador seguindo os passos dados em sala de aula já garante que a base seja orientada
positivamente, isto é, seguindo a regra da mão direita. Contudo, se o aluno optar por uma forma diferente, deverá criar
uma função que verifique se a nova base é positiva, pois, caso contrário, os resultados não serão consistentes.

##### TO-DO

- [ ] Realizar verificações em geral de tamanhos de janelas;
- [ ] Estudar e implementar a mudança de base do SRN para o SRD (3D)
- [x] Função que multiplica uma matriz por um vetor (Retirar os Warnings) 
- [ ] Função que multiplica duas matrizes (Retirar os Warnings)
