#include "rasterization.h"
#include <GL/glut.h>
#include <cmath>
#include <functional>

// Diz ao compilador que estas variáveis globais existem em outro arquivo (main.cpp)
extern int window_width;
extern int window_height;

void drawScreenPixel(int x, int y) {
    // 1. Muda para o modo de PROJEÇÃO para salvar o estado 3D
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Salva a matriz de Projeção Perspectiva/Ortogonal

        // 2. Configura uma projeção 2D temporária para desenhar no pixel exato
        glLoadIdentity();
        gluOrtho2D(0, window_width, 0, window_height);

        // 3. Muda para o modo de MODELVIEW para salvar o estado da câmera
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); // Salva a matriz da Câmera 3D
            
            // Reseta a modelview para que (0,0) seja o canto da tela
            glLoadIdentity();

            // Desenha o ponto
            glBegin(GL_POINTS);
                glVertex2i(x, y);
            glEnd();

        glPopMatrix(); // 4. Restaura a matriz da CÂMERA 3D. O modo ativo ainda é GL_MODELVIEW.

    // 5. MUDA o modo de volta para PROJEÇÃO PRIMEIRO!
    glMatrixMode(GL_PROJECTION);
    // 6. AGORA, com a pilha de projeção ativa, restaura a matriz de PROJEÇÃO 3D.
    glPopMatrix(); 

    // 7. Finalmente, deixa o modo MODELVIEW como o padrão para o resto da cena.
    glMatrixMode(GL_MODELVIEW);
}

//Aplica bresenham para cada pixel entre os pontos (x1, y1) e (x2, y2).
void bresenham(int x1, int y1, int x2, int y2, std::function<void(int, int)> drawPixelFunc) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int counter = 0;
    int spacing = 4;
    while (true) {
        if (counter % spacing == 0) {
            drawPixelFunc(x1, y1);
        }
        counter++;
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}