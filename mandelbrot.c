#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int largura; 
    int altura;
    int max_iteracoes;
    int num_threads; 

    /*double real_min = -2.0;
    double real_max = 1.0;
    double imag_min = -1.5;
    double imag_max = 1.5;*/

    if(argc != 5){
        //mensagem de erro aqui
        //exit();
    }else{
        largura = atoi(argv[1]);
        altura = atoi(argv[2]);
        max_iteracoes = atoi(argv[3]);
        num_threads = atoi(argv[4]);        
    }

    return 0;
}