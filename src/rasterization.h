//Declara todas as variáveis e funções utilizadas no rasterization.cpp
#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <functional> // Para std::function

// Estrutura simples para guardar um ponto 3D. É bom tê-la aqui.
struct Point3D {
    float x, y, z;
};

// Declaração das funções que outros arquivos poderão usar
void drawScreenPixel(int x, int y);
void bresenham(int x1, int y1, int x2, int y2, std::function<void(int, int)> drawPixelFunc);

#endif // RASTERIZATION_H