#include "calculo.h"
#include <omp.h>
#include <pthread.h>
int calcular_pixel(long x, long y, long largura, long altura, long max_iteracoes) {
    double cr = REAL_MIN + (double)x * (REAL_MAX - REAL_MIN) / (double)(largura);
    double ci = IMAG_MIN + (double)y * (IMAG_MAX - IMAG_MIN) / (double)(altura);

    double zr = 0.0;
    double zi = 0.0;
    long iter = 0;
    while ((zr * zr + zi * zi) <= 4.0 && iter < max_iteracoes) {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        iter++;
    }
    return (int)((iter * 255) / max_iteracoes);
}

void ImagemSerial(int *imagem, long largura, long altura, long max_iteracoes) {
    for (long y = 0; y < altura; y++) {
        for (long x = 0; x < largura; x++) {
            imagem[y * largura + x] = calcular_pixel(x, y, largura, altura, max_iteracoes);
        }
    }
}

void ImagemOpenMP(int *imagem, long largura, long altura, long max_iteracoes, long num_threads) {
    #pragma omp parallel for num_threads(num_threads)
    for (long y = 0; y < altura; y++) {
        for (long x = 0; x < largura; x++) {
            imagem[y * largura + x] =
                calcular_pixel(x, y, largura, altura, max_iteracoes);
        }
    }
}

typedef struct {
    int *imagem;
    long largura;
    long altura;
    long max_iteracoes;
    long inicio;
    long fim;
} DadosThread;

void *calcular_parte(void *arg) {
    DadosThread *dados = (DadosThread *)arg;
    for (long y = dados->inicio; y < dados->fim; y++) {
        for (long x = 0; x < dados->largura; x++) {
            dados->imagem[y * dados->largura + x] =
                calcular_pixel(x, y, dados->largura, dados->altura, dados->max_iteracoes);
        }
    }
    return NULL;
}

void ImagemPthreads1(int *imagem, long largura, long altura, long max_iteracoes, long num_threads) {
    pthread_t threads[num_threads];
    DadosThread dados[num_threads];
    long linhas_por_thread = altura / num_threads;
    long resto = altura % num_threads;
    long inicio = 0;

    for (long i = 0; i < num_threads; i++) {
        long quantidade_linhas = linhas_por_thread;
        if (i < resto) {
            quantidade_linhas++;
        }
        dados[i].imagem = imagem;
        dados[i].largura = largura;
        dados[i].altura = altura;
        dados[i].max_iteracoes = max_iteracoes;
        dados[i].inicio = inicio;
        dados[i].fim = inicio + quantidade_linhas;
        pthread_create(&threads[i], NULL, calcular_parte, &dados[i]);
        inicio = dados[i].fim;
    }
    for (long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

typedef struct {
    int *imagem;
    long largura;
    long altura;
    long max_iteracoes;
    long id_thread;
    long num_threads;
} DadosThreadCiclica;


void *parte_ciclica(void *arg) {
    DadosThreadCiclica *dados = (DadosThreadCiclica *)arg;
    for (long y = dados->id_thread; y < dados->altura; y += dados->num_threads) {
        for (long x = 0; x < dados->largura; x++) {
            dados->imagem[y * dados->largura + x] =
                calcular_pixel(x,  y, dados->largura, dados->altura, dados->max_iteracoes);
        }
    }
    return NULL;
}


void ImagemPthreads2(int *imagem, long largura, long altura, long max_iteracoes, long num_threads) {
    pthread_t threads[num_threads];
    DadosThreadCiclica dados[num_threads];
    for (long i = 0; i < num_threads; i++) {
        dados[i].imagem = imagem;
        dados[i].largura = largura;
        dados[i].altura = altura;
        dados[i].max_iteracoes = max_iteracoes;
        dados[i].id_thread = i;
        dados[i].num_threads = num_threads;
        pthread_create(&threads[i],NULL, calcular_parte, &dados[i]);
    }
    for (long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}