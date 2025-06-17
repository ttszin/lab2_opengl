// File: objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>

class Objects {
    private:
            float largura;
            float profundidade;
            float anguloAbertura;
            float altura;
    public:
        // Apenas as declarações dos métodos de desenho
        void desenhaCubo();
        void desenhaJanela(float anguloAbertura);
        void desenhaMonitor();
        void desenhaGabinetePC();
        void desenhaCadeira();
        void desenhaMesaLaboratorio(float largura, float profundidade);
        void desenhaQuadroNegro();
        void desenhaPostoDeTrabalho();
        void desenhaEstruturaDaSala(float largura, float altura, float profundidade);
        void desenhaParedesComJanelas(float largura, float altura, float profundidade);
        void desenhaSala(float largura, float altura, float profundidade);
};

#endif // OBJECTS_H