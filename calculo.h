#ifndef CALCULO_H
#define CALCULO_H

#define REAL_MIN -2.0
#define REAL_MAX  1.0
#define IMAG_MIN -1.5
#define IMAG_MAX  1.5

int calcular_pixel(long x, long y, long largura, long altura, long max_iteracoes);
void ImagemSerial(int *imagem, long largura, long altura, long max_iteracoes);
void ImagemOpenMP(int *imagem, long largura, long altura, long max_iteracoes, long num_threads);
void ImagemPthreads1(int *imagem, long largura, long altura,long max_iteracoes, long num_threads);
void ImagemPthreads2(int *imagem, long largura, long altura, long max_iteracoes, long num_threads);

#endif 