#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "calculo.h"

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
    return 0;
}