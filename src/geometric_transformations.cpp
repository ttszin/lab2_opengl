//================================================================================================================
// Aqui estão implementadas as funções de transformação geométrica (TRANSLAÇÃO, ROTAÇÃO, ESCALA.)
//================================================================================================================

#include <GL/glut.h>
#include "geometric_transformations.h"


void geometricTransformation::Translate(float tx, float ty, float tz) {
    GLfloat matriz[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        tx, ty, tz, 1.0f
    };
    glMultMatrixf(matriz);
}

void geometricTransformation::Scale(float sx, float sy, float sz) {
    GLfloat matriz[16] = {
        sx,   0.0f, 0.0f, 0.0f,
        0.0f, sy,   0.0f, 0.0f,
        0.0f, 0.0f, sz,   0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(matriz);
}

// Implementa rotação em torno de um dos eixos principais (X, Y ou Z)
void geometricTransformation::Rotate(float angulo, float x, float y, float z) {
    float rad = angulo * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    GLfloat matriz[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    if (x == 1.0f && y == 0.0f && z == 0.0f) { // Rotação em X
        matriz[5] = c;
        matriz[6] = s;
        matriz[9] = -s;
        matriz[10] = c;
    } else if (x == 0.0f && y == 1.0f && z == 0.0f) { // Rotação em Y
        matriz[0] = c;
        matriz[2] = -s;
        matriz[8] = s;
        matriz[10] = c;
    } else if (x == 0.0f && y == 0.0f && z == 1.0f) { // Rotação em Z
        matriz[0] = c;
        matriz[1] = s;
        matriz[4] = -s;
        matriz[5] = c;
    }

    glMultMatrixf(matriz);
}

void geometricTransformation::Perspective(float fovy, float aspect, float zNear, float zFar) {
    // Converte o campo de visão (fovy) de graus para radianos
    float f = 1.0f / tan((fovy * M_PI / 180.0f) / 2.0f);

    // Constrói a matriz de projeção perspectiva (column-major)
    GLfloat matriz[16] = {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f,    0.0f, 0.0f,
        0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), -1.0f,
        0.0f, 0.0f, (2.0f * zFar * zNear) / (zNear - zFar), 0.0f
    };

    glMultMatrixf(matriz);
}

void geometricTransformation::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar) {
    GLfloat matriz[16] = {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (zFar - zNear), 0.0f, // <-- CORRIGIDO
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), 1.0f // <-- CORRIGIDO
    };

    glMultMatrixf(matriz);
}
