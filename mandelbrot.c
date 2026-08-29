#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "calculo.h"
#include <time.h>
#include <omp.h>

void salvar_imagem(int *imagem, long largura, long altura, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "erro ao abrir arquivo da imagem\n");
        exit(EXIT_FAILURE);
    }
    for (long y = 0; y < altura; y++) {
        for (long x = 0; x < largura; x++) {
            fprintf(arquivo, "%d ", imagem[y * largura + x]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void salvar_tempos(double tempo_serial, double tempo_openmp) {
    FILE *arquivo = fopen("times.txt", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo de tempos\n");
        exit(EXIT_FAILURE);
    }
    fprintf(arquivo, "serial: %.9f segundos\n", tempo_serial);
    fprintf(arquivo, "openmp: %.9f segundos\n", tempo_openmp);

    fclose(arquivo);
}


double calcular_tempo(struct timespec inicio, struct timespec fim) {
    double segundos = (double)(fim.tv_sec - inicio.tv_sec);
    double nanossegundos = (double)(fim.tv_nsec - inicio.tv_nsec);
    return segundos + nanossegundos / 1000000000.0;
}

int main(int argc, char *argv[]){
    long largura; 
    long altura;
    long max_iteracoes;
    long num_threads; 
    char *endptr;

    if(argc != 5){
        fprintf(stderr, "Qtd de argumentos invalida\n");
        exit(EXIT_FAILURE);
    }else{
        errno = 0;
        largura = strtol(argv[1], &endptr, 10);
        if(*endptr != '\0' || argv[1] == endptr || largura <= 0 || errno == ERANGE){
            fprintf(stderr, "largura invalida\n");
            exit(EXIT_FAILURE);
        }
        errno = 0;
        altura = strtol(argv[2], &endptr, 10);
        if(*endptr != '\0' || argv[2] == endptr || altura <= 0 || errno == ERANGE){
            fprintf(stderr, "altura invalida\n");
            exit(EXIT_FAILURE);
        }
        errno = 0;
        max_iteracoes = strtol(argv[3], &endptr, 10);
        if(*endptr != '\0' || argv[3] == endptr || max_iteracoes <= 0 || errno == ERANGE){
            fprintf(stderr, "numero de iteracoes invalido\n");
            exit(EXIT_FAILURE);
        }
        errno = 0;
        num_threads = strtol(argv[4], &endptr, 10);  
        if(*endptr != '\0' || argv[4] == endptr || num_threads <= 0 || errno == ERANGE){
            fprintf(stderr, "numero de threads invalido\n");
            exit(EXIT_FAILURE);
        }    
    }
    int *imagem = malloc(largura * altura * sizeof(int));

    if (imagem == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a imagem\n");
        exit(EXIT_FAILURE);
    }

    struct timespec inicio_serial;
    struct timespec fim_serial;

    clock_gettime(CLOCK_MONOTONIC, &inicio_serial);
    ImagemSerial(imagem, largura, altura, max_iteracoes);
    clock_gettime(CLOCK_MONOTONIC, &fim_serial);

    double tempo_serial = calcular_tempo(inicio_serial, fim_serial);
    salvar_imagem(imagem, largura, altura, "mandelbrot_grp_serial.pgm");

    double inicio_openmp = omp_get_wtime();
    ImagemOpenMP(imagem, largura, altura, max_iteracoes, num_threads);
    double fim_openmp = omp_get_wtime();
    double tempo_openmp = fim_openmp - inicio_openmp;
    salvar_imagem(imagem,largura, altura, "mandelbrot_grp_openmp.pgm");
    salvar_tempos(tempo_serial, tempo_openmp);

    free(imagem);

    return 0;
}