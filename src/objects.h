//Declara todas as variáveis e funções utilizadas no objects.cpp
#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glut.h>

class Objects {
    private:
            float largura;
            float profundidade;
            float anguloAbertura;
            float altura;
            float espessura;
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
        void desenhaTampoDaMesa(float largura, float profundidade, float espessura);
        void desenhaMesaLaboratorioWireframeTampo(float largura, float profundidade);
        void desenhaLixeira();
        void desenhaLixeiraWireframeBresenham();
        void desenhaParedeComJanelas(float largura, float altura, float profundidade);
        void desenhaLampada();
        void desenhaArCondicionado();
        void desenhaPorta();
};

#endif // OBJECTS_H