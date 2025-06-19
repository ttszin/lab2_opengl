
#ifndef GEOMETRIC_TRANSFORMATION_H // Corrigi o nome do include guard
#define GEOMETRIC_TRANSFORMATION_H

#include <GL/glut.h>
#include <cmath> // Necessário para cos() e sin()

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class geometricTransformation {
    //Declarando as variáveis para nao dar erro
    private:
        float tx;
        float ty;
        float tz;
        float sx;
        float sy;
        float sz;
        float x;
        float y;
        float z;
        float angulo;
        float  fovy;
        float aspect;
        float zNear;
        float zFar;
    public: // <-- TORNA OS MÉTODOS PÚBLICOS E ACESSÍVEIS
        // Métodos estáticos não precisam de um objeto para serem chamados
        static void Translate(float tx, float ty, float tz);
        static void Scale(float sx, float sy, float sz);
        static void Rotate(float angulo, float x, float y, float z);

        // --- NOVOS MÉTODOS DE PROJEÇÃO ---
        static void Perspective(float fovy, float aspect, float zNear, float zFar);
        static void Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
};

#endif // GEOMETRIC_TRANSFORMATION_H