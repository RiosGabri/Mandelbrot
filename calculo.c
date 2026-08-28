#include "calculo.h"
int calcular_pixel(long x, long y, long largura, long altura, long max_iteracoes) {
    double cr = REAL_MIN + (double)x * (REAL_MAX - REAL_MIN) / (double)(largura - 1);
    double ci = IMAG_MIN + (double)y * (IMAG_MAX - IMAG_MIN) / (double)(altura - 1);

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

void ImagemSerial(int *imagem, long largura, long altura, long max_iter) {
    for (long y = 0; y < altura; y++) {
        for (long x = 0; x < largura; x++) {
            imagem[y * largura + x] = calcular_pixel(x, y, largura, altura, max_iter);
        }
    }
}

