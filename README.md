# Mandelbrot — Infraestrutura de Software (Implementação 2)

Programa em C que gera o conjunto de Mandelbrot em quatro implementações — Serial, OpenMP e duas versões com Pthreads — e compara o tempo de execução entre elas.

## Compilação

```
make
```

Remove os artefatos gerados pela compilação:

```
make clean
```

## Execução

```
./mandelbrot [largura] [altura] [max_iteracoes] [num_threads]
```

Exemplo:

```
./mandelbrot 800 600 1000 4
```

- `largura`, `altura`: dimensões da imagem, em pixels (inteiros positivos).
- `max_iteracoes`: número máximo de iterações por ponto.
- `num_threads`: número de threads usado nas implementações OpenMP e Pthreads.

Uma única execução roda as quatro implementações (Serial, OpenMP, Pthreads1, Pthreads2), nessa ordem, e gera todas as saídas descritas abaixo.

## Saídas

- `mandelbrot_grp_serial.pgm`
- `mandelbrot_grp_openmp.pgm`
- `mandelbrot_grp_pthreads1.pgm`
- `mandelbrot_grp_pthreads2.pgm`

Cada arquivo contém apenas os valores de intensidade de cada pixel (sem cabeçalho de formato), um valor por pixel separado por espaço, uma linha do arquivo por linha da imagem. A intensidade é proporcional ao número de iterações, normalizada entre 0 e 255. As quatro implementações produzem arquivos idênticos entre si.

- `times.txt`: tempo de execução (em segundos) de cada uma das quatro implementações.

## Estrutura do projeto

| Arquivo | Responsabilidade |
|---|---|
| `mandelbrot.c` | `main`: leitura e validação dos argumentos, alocação da imagem, orquestração das quatro implementações, geração dos `.pgm` e do `times.txt` |
| `calculo.c` / `calculo.h` | Cálculo do conjunto de Mandelbrot: `calcular_pixel` (mapeamento pixel→plano complexo, iteração, normalização) e as quatro funções de geração de imagem (`ImagemSerial`, `ImagemOpenMP`, `ImagemPthreads1`, `ImagemPthreads2`) |
| `Makefile` | Compilação (`make`) e limpeza (`make clean`) |
