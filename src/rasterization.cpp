#include <functional> // Necessário para std::function
#include <GL/glut.h>
#include "rasterization.h"
#include <cmath>

extern int window_width;
extern int window_height;

// Função auxiliar que desenha um único pixel na tela nas coordenadas da janela
void drawScreenPixel(int x, int y) {
    // Salva as matrizes atuais para não bagunçar o resto da cena
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Configura uma projeção ortográfica 2D do tamanho da janela
    gluOrtho2D(0, window_width, 0, window_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desenha um único ponto nas coordenadas x, y
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();

    // Restaura as matrizes originais
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Implementação do Algoritmo de Linha de Bresenham
// Recebe as coordenadas de dois pontos e uma função para desenhar cada pixel
// Em rasterization.cpp

// Substitua sua função bresenham por esta versão modificada
void bresenham(int x1, int y1, int x2, int y2, std::function<void(int, int)> drawPixelFunc) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    // --- LÓGICA PARA PONTILHADO ---
    int counter = 0;      // Um contador de passos
    int spacing = 2;      // Desenhará 1 a cada 4 pixels. Mude este valor para mais ou menos pontos.
    // -----------------------------

    while (true) {
        // Só desenha o pixel se o contador for um múltiplo do espaçamento
        if (counter % spacing == 0) {
            drawPixelFunc(x1, y1);
        }
        
        counter++; // Incrementa o contador a cada passo

        if (x1 == x2 && y1 == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}