//Colocar os objetos aqui para serem chamados
#include <GL/glut.h>
#include "objects.h" // Incluindo o arquivo de modelagem dos objetos
#include "geometric_transformations.h"
#include <initializer_list>
#include "rasterization.h"
#include <vector> // Precisaremos de vetores para armazenar os pontos

// --- PALETA DE MATERIAIS PARA O MODELO DE PHONG ---

// Material: Chão Cinza Claro
const GLfloat MAT_FLOOR_AMBIENT[]  = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat MAT_FLOOR_DIFFUSE[]  = {0.8f, 0.8f, 0.7f, 1.0f};
const GLfloat MAT_FLOOR_SPECULAR[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Sem brilho
const GLfloat MAT_FLOOR_SHININESS  = 10.0f;

// Material: Teto Branco
const GLfloat MAT_CEILING_AMBIENT[]  = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat MAT_CEILING_DIFFUSE[]  = {0.9f, 0.9f, 0.9f, 1.0f};
const GLfloat MAT_CEILING_SPECULAR[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Sem brilho
const GLfloat MAT_CEILING_SHININESS  = 10.0f;

// Material: Paredes Laterais (Azuladas)
const GLfloat MAT_SIDEWALL_AMBIENT[]  = {0.1f, 0.1f, 0.2f, 1.0f};
const GLfloat MAT_SIDEWALL_DIFFUSE[]  = {0.7f, 0.7f, 0.9f, 1.0f};
const GLfloat MAT_SIDEWALL_SPECULAR[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Pouco brilho
const GLfloat MAT_SIDEWALL_SHININESS  = 10.0f;

// Material: Parede do Fundo (Rosada)
const GLfloat MAT_BACKWALL_AMBIENT[]  = {0.2f, 0.1f, 0.1f, 1.0f};
const GLfloat MAT_BACKWALL_DIFFUSE[]  = {0.9f, 0.8f, 0.8f, 1.0f};
const GLfloat MAT_BACKWALL_SPECULAR[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Pouco brilho
const GLfloat MAT_BACKWALL_SHININESS  = 10.0f;

// Material: Parede da Frente (Bege)
const GLfloat MAT_FRONTWALL_AMBIENT[]  = {0.2f, 0.2f, 0.1f, 1.0f};
const GLfloat MAT_FRONTWALL_DIFFUSE[]  = {0.9f, 0.9f, 0.8f, 1.0f};
const GLfloat MAT_FRONTWALL_SPECULAR[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Pouco brilho
const GLfloat MAT_FRONTWALL_SHININESS  = 10.0f;

// Material: Plástico Preto/Cinza Escuro (para monitores, gabinetes)
const GLfloat MAT_DARK_PLASTIC_AMBIENT[]  = {0.02f, 0.02f, 0.02f, 1.0f};
const GLfloat MAT_DARK_PLASTIC_DIFFUSE[]  = {0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat MAT_DARK_PLASTIC_SPECULAR[] = {0.4f, 0.4f, 0.4f, 1.0f};
const GLfloat MAT_DARK_PLASTIC_SHININESS  = 32.0f;

// Material: Cadeira Azul
const GLfloat MAT_CHAIR_BLUE_AMBIENT[]  = {0.0f, 0.0f, 0.1f, 1.0f};
const GLfloat MAT_CHAIR_BLUE_DIFFUSE[]  = {0.1f, 0.1f, 0.5f, 1.0f};
const GLfloat MAT_CHAIR_BLUE_SPECULAR[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat MAT_CHAIR_BLUE_SHININESS  = 40.0f;

// Material: Mesa Vermelha
const GLfloat MAT_TABLE_RED_AMBIENT[]  = {0.2f, 0.0f, 0.0f, 1.0f};
const GLfloat MAT_TABLE_RED_DIFFUSE[]  = {0.8f, 0.1f, 0.1f, 1.0f};
const GLfloat MAT_TABLE_RED_SPECULAR[] = {0.3f, 0.1f, 0.1f, 1.0f}; // Brilho mais sutil e avermelhado
const GLfloat MAT_TABLE_RED_SHININESS  = 10.0f; // Menos concentrado, mais fosco

// Material: Painel de Madeira
const GLfloat MAT_WOOD_AMBIENT[]  = {0.2f, 0.15f, 0.1f, 1.0f};
const GLfloat MAT_WOOD_DIFFUSE[]  = {0.6f, 0.4f, 0.2f, 1.0f};
const GLfloat MAT_WOOD_SPECULAR[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Quase sem brilho
const GLfloat MAT_WOOD_SHININESS  = 5.0f;

// Material: Metal Preto Polido
const GLfloat MAT_BLACK_METAL_AMBIENT[]  = {0.02f, 0.02f, 0.02f, 1.0f};
const GLfloat MAT_BLACK_METAL_DIFFUSE[]  = {0.05f, 0.05f, 0.05f, 1.0f};
const GLfloat MAT_BLACK_METAL_SPECULAR[] = {0.9f, 0.9f, 0.9f, 1.0f};
const GLfloat MAT_BLACK_METAL_SHININESS  = 100.0f;

// Material: Vidro Preto Polido (para telas de monitor)
const GLfloat MAT_GLASS_AMBIENT[]  = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat MAT_GLASS_DIFFUSE[]  = {0.01f, 0.01f, 0.01f, 1.0f}; // Quase preto
const GLfloat MAT_GLASS_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Reflexo branco e forte
const GLfloat MAT_GLASS_SHININESS  = 128.0f; // Expoente MUITO alto para um brilho nítido

//======================================================================
// MODELAGEM DOS OBJETOS DO LABORATÓRIO
//======================================================================

void Objects::desenhaTampoDaMesa(float largura, float profundidade, float espessura) {
    float raio_canto = 0.2f;
    int num_segmentos_canto = 10;
    float l = largura / 2.0f;
    float p = profundidade / 2.0f;
    float e = espessura / 2.0f;

    // --- Face de Cima (Lógica Corrigida) ---
    glNormal3f(0.0f, 1.0f, 0.0f);
    // 1. Parte retangular principal (forma de "T" que cobre a maior parte da área)
    glBegin(GL_QUADS);
        glVertex3f(-l, e, -p);
        glVertex3f(l, e, -p);
        glVertex3f(l, e, p - raio_canto);
        glVertex3f(-l, e, p - raio_canto);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-(l - raio_canto), e, p - raio_canto);
        glVertex3f((l - raio_canto), e, p - raio_canto);
        glVertex3f((l - raio_canto), e, p);
        glVertex3f(-(l - raio_canto), e, p);
    glEnd();

    // 2. Canto superior direito (preenchendo o vão com um leque de triângulos)
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(l - raio_canto, e, p - raio_canto); // Ponto central do leque
        glVertex3f(l, e, p - raio_canto); // Ponto inicial da curva
        for (int i = 1; i <= num_segmentos_canto; ++i) {
            float angulo = (float)i / (float)num_segmentos_canto * 90.0f;
            float rad = angulo * M_PI / 180.0f;
            glVertex3f((l - raio_canto) + cos(rad) * raio_canto, e, (p - raio_canto) + sin(rad) * raio_canto);
        }
    glEnd();

    // 3. Canto superior esquerdo
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(l - raio_canto), e, p - raio_canto); // Ponto central do leque
        glVertex3f(-(l - raio_canto), e, p); // Ponto inicial da curva
        for (int i = 1; i <= num_segmentos_canto; ++i) {
            float angulo = 90.0f + (float)i / (float)num_segmentos_canto * 90.0f;
            float rad = angulo * M_PI / 180.0f;
            glVertex3f(-(l - raio_canto) + cos(rad) * raio_canto, e, (p - raio_canto) + sin(rad) * raio_canto);
        }
        glVertex3f(-l, e, p - raio_canto); // Ponto final da curva
    glEnd();


    // --- Face de Baixo (Lógica Corrigida) ---
    glNormal3f(0.0f, -1.0f, 0.0f);
    // 1. Parte retangular principal
    glBegin(GL_QUADS);
        glVertex3f(-l, -e, p - raio_canto);
        glVertex3f(l, -e, p - raio_canto);
        glVertex3f(l, -e, -p);
        glVertex3f(-l, -e, -p);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(-(l - raio_canto), -e, p);
        glVertex3f((l - raio_canto), -e, p);
        glVertex3f((l - raio_canto), -e, p - raio_canto);
        glVertex3f(-(l - raio_canto), -e, p - raio_canto);
    glEnd();
    // 2. Canto inferior direito
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(l - raio_canto, -e, p - raio_canto);
        for (int i = num_segmentos_canto; i >= 0; --i) { // Ordem invertida
            float angulo = (float)i / (float)num_segmentos_canto * 90.0f;
            float rad = angulo * M_PI / 180.0f;
            glVertex3f((l - raio_canto) + cos(rad) * raio_canto, -e, (p - raio_canto) + sin(rad) * raio_canto);
        }
    glEnd();
    // 3. Canto inferior esquerdo
     glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-(l - raio_canto), -e, p - raio_canto);
        for (int i = num_segmentos_canto; i >= 0; --i) { // Ordem invertida
            float angulo = 90.0f + (float)i / (float)num_segmentos_canto * 90.0f;
            float rad = angulo * M_PI / 180.0f;
            glVertex3f(-(l - raio_canto) + cos(rad) * raio_canto, -e, (p - raio_canto) + sin(rad) * raio_canto);
        }
    glEnd();


    // --- Faces Laterais, Traseira e Frontal Curva ---
    // O código para estas faces estava correto e pode permanecer o mesmo.
    // Face de Trás
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(l, -e, -p); glVertex3f(l, e, -p); glVertex3f(-l, e, -p); glVertex3f(-l, -e, -p);
    glEnd();

    // Face da Frente Curva
    glBegin(GL_QUAD_STRIP); // Canto direito
    for (int i = 0; i <= num_segmentos_canto; ++i) {
        float angulo = (float)i / (float)num_segmentos_canto * 90.0f; float rad = angulo * M_PI / 180.0f;
        float x_pos = (l - raio_canto) + cos(rad) * raio_canto; float z_pos = (p - raio_canto) + sin(rad) * raio_canto;
        glNormal3f(cos(rad), 0.0f, sin(rad));
        glVertex3f(x_pos, e, z_pos); glVertex3f(x_pos, -e, z_pos);
    }
    glEnd();
    glBegin(GL_QUAD_STRIP); // Parte reta
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(l - raio_canto, e, p); glVertex3f(l - raio_canto, -e, p);
        glVertex3f(-(l - raio_canto), e, p); glVertex3f(-(l - raio_canto), -e, p);
    glEnd();
    glBegin(GL_QUAD_STRIP); // Canto esquerdo
    for (int i = 0; i <= num_segmentos_canto; ++i) {
        float angulo = 90.0f + (float)i / (float)num_segmentos_canto * 90.0f; float rad = angulo * M_PI / 180.0f;
        float x_pos = -(l - raio_canto) + cos(rad) * raio_canto; float z_pos = (p - raio_canto) + sin(rad) * raio_canto;
        glNormal3f(cos(rad), 0.0f, sin(rad));
        glVertex3f(x_pos, e, z_pos); glVertex3f(x_pos, -e, z_pos);
    }
    glEnd();
}

void Objects::desenhaLixeira() {
    // Define os 8 vértices: 4 para a base (menor) e 4 para o topo (maior)
    float base = 0.2f;  // metade da largura da base
    float topo = 0.3f;  // metade da largura do topo
    float altura = 0.5f;

    GLfloat vertices[8][3] = {
        // Base (y=0)
        {-base, 0, -base}, {base, 0, -base}, {base, 0, base}, {-base, 0, base},
        // Topo (y=altura)
        {-topo, altura, -topo}, {topo, altura, -topo}, {topo, altura, topo}, {-topo, altura, topo}
    };
    
    // Define as faces
    int faces[6][4] = {
        {0, 1, 2, 3}, // Base
        {4, 5, 6, 7}, // Topo (abertura, não desenhamos)
        {0, 1, 5, 4}, // Lado 1
        {1, 2, 6, 5}, // Lado 2
        {2, 3, 7, 6}, // Lado 3
        {3, 0, 4, 7}  // Lado 4
    };

    // Desenha a base
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        for(int i = 0; i < 4; ++i) glVertex3fv(vertices[faces[0][i]]);
    glEnd();

    // Desenha as faces laterais
    // (O cálculo da normal aqui é simplificado, mas funcional para este caso)
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        for(int i = 0; i < 4; ++i) glVertex3fv(vertices[faces[2][i]]);
        glNormal3f(1, 0, 0);
        for(int i = 0; i < 4; ++i) glVertex3fv(vertices[faces[3][i]]);
        glNormal3f(0, 0, 1);
        for(int i = 0; i < 4; ++i) glVertex3fv(vertices[faces[4][i]]);
        glNormal3f(-1, 0, 0);
        for(int i = 0; i < 4; ++i) glVertex3fv(vertices[faces[5][i]]);
    glEnd();
}

void Objects::desenhaLixeiraWireframeBresenham() {
    // 1. Vértices da lixeira
    float base = 0.2f;
    float topo = 0.3f;
    float altura = 0.5f;

    struct Point3D { float x, y, z; };
    Point3D vertices[8] = {
        {-base, 0, -base}, {base, 0, -base}, {base, 0, base}, {-base, 0, base},
        {-topo, altura, -topo}, {topo, altura, -topo}, {topo, altura, topo}, {-topo, altura, topo}
    };

    int arestas[12][2] = {
        {0,1}, {1,2}, {2,3}, {3,0}, // base
        {4,5}, {5,6}, {6,7}, {7,4}, // topo
        {0,4}, {1,5}, {2,6}, {3,7}  // laterais
    };

    // 2. Rasterização 3D com GL_POINTS
    //glColor3f(1.0f, 0.6f, 0.0f); // Laranja
    glPointSize(2.0f);
    glBegin(GL_POINTS);

    auto bresenham3D = [](Point3D p1, Point3D p2) {
        int steps = 100; // Número de pontos (qualidade da linha)

        float dx = (p2.x - p1.x) / steps;
        float dy = (p2.y - p1.y) / steps;
        float dz = (p2.z - p1.z) / steps;

        for (int i = 0; i <= steps; ++i) {
            float x = p1.x + dx * i;
            float y = p1.y + dy * i;
            float z = p1.z + dz * i;
            //Pode fazer com o espaçamento de pontos diferente
            // if (i % 5 == 0) {
            //     glVertex3f(x, y, z);
            // }
            glVertex3f(x, y, z);
        }
    };

    for (int i = 0; i < 12; ++i) {
        bresenham3D(vertices[arestas[i][0]], vertices[arestas[i][1]]);
    }

    glEnd();
}


void Objects::desenhaCubo() {
    // Face da frente
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f( 0.5f, -0.5f, 0.5f);
        glVertex3f( 0.5f,  0.5f, 0.5f);
        glVertex3f(-0.5f,  0.5f, 0.5f);
    glEnd();
    // Face de trás
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f,  0.5f, -0.5f);
        glVertex3f( 0.5f,  0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f, -0.5f);
    glEnd();
    // Face do topo
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f,  0.5f, -0.5f);
        glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();
    // Face da base
    glBegin(GL_QUADS);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f,  0.5f);
        glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();
    // Face da direita
    glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f( 0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f,  0.5f, -0.5f);
        glVertex3f( 0.5f,  0.5f,  0.5f);
        glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();
    // Face da esquerda
    glBegin(GL_QUADS);
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5f, -0.5f,  0.5f);
        glVertex3f(-0.5f,  0.5f,  0.5f);
        glVertex3f(-0.5f,  0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

//======================================================================
// MODELAGEM DOS OBJETOS DO LABORATÓRIO
//======================================================================

void Objects::desenhaJanela(float anguloAbertura) {
    float largura = 1.0f;
    float altura = 1.5f;
    float espessura_moldura = 0.05f;

    // --- Caixilho (a parte fixa na parede) ---
    //glColor3f(0.9f, 0.9f, 0.9f); // Cor branca/cinza claro
    glPushMatrix();
    // Moldura superior e inferior
    for (float y_pos : {-altura / 2.0f, altura / 2.0f}) {
        glPushMatrix();
        geometricTransformation::Translate(0.0f, y_pos, 0.0f);
        geometricTransformation::Scale(largura + espessura_moldura, espessura_moldura, espessura_moldura);
        desenhaCubo();
        glPopMatrix();
    }
    // Moldura esquerda e direita
    for (float x_pos : {-largura / 2.0f, largura / 2.0f}) {
        glPushMatrix();
        geometricTransformation::Translate(x_pos, 0.0f, 0.0f);
        geometricTransformation::Scale(espessura_moldura, altura - espessura_moldura, espessura_moldura);
        desenhaCubo();
        glPopMatrix();
    }
    glPopMatrix();


    // --- Vidraça (a parte móvel e transparente) ---
    glPushMatrix();

    // A MÁGICA DA ROTAÇÃO:
    // 1. Mova o sistema de coordenadas para o ponto de pivô (a "dobradiça" no topo do caixilho).
    geometricTransformation::Translate(0.0f, altura / 2.0f, 0.0f);
    // 2. Rotacione em torno do eixo X.
    geometricTransformation::Rotate(anguloAbertura, 1.0f, 0.0f, 0.0f);
    // 3. Mova a vidraça para baixo para que ela se alinhe com o pivô.
    geometricTransformation::Translate(0.0f, -altura / 2.0f, 0.0f);

    // Define a cor do vidro com transparência (o quarto valor 'alpha')
    //glColor4f(0.7f, 0.9f, 1.0f, 0.5f); // Azul claro, 50% opaco

    // Desenha o cubo que representa o vidro
    geometricTransformation::Scale(largura, altura, 0.02f); // Bem fino
    desenhaCubo();

    glPopMatrix();
}


void Objects::desenhaMonitor() {
    glPushMatrix();

    // --- Parte 1: Corpo de Plástico Escuro ---
    // Define o material para as partes plásticas do monitor
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_DARK_PLASTIC_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_DARK_PLASTIC_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_DARK_PLASTIC_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_DARK_PLASTIC_SHININESS);

    // Desenha a Base, a Haste e a Moldura da tela
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.05f, 0.0f);
    geometricTransformation::Scale(0.3f, 0.1f, 0.3f);
    desenhaCubo();
    glPopMatrix();

    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.2f, 0.0f);
    geometricTransformation::Scale(0.05f, 0.3f, 0.05f);
    desenhaCubo();
    glPopMatrix();

    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.5f, 0.0f);
    geometricTransformation::Scale(0.7f, 0.5f, 0.05f);
    desenhaCubo();
    glPopMatrix();

    // --- Parte 2: A Tela de Vidro Polido ---
    // Agora, trocamos para o material de vidro para desenhar a tela
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_GLASS_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_GLASS_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_GLASS_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_GLASS_SHININESS);

    glPushMatrix();
    // A tela fica levemente à frente da moldura
    geometricTransformation::Translate(0.0f, 0.5f, 0.026f);
    geometricTransformation::Scale(0.65f, 0.45f, 0.01f);
    desenhaCubo();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaGabinetePC() {
    glPushMatrix();
    //glColor3f(0.2f, 0.2f, 0.2f);
    geometricTransformation::Scale(0.2f, 0.5f, 0.4f);
    desenhaCubo();
    glPopMatrix();
}

void Objects::desenhaCadeira() {
    glPushMatrix();
    //glColor3f(0.3f, 0.3f, 0.4f); // Azul escuro
    
    // Assento
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.25f, 0.0f);
    geometricTransformation::Scale(0.4f, 0.05f, 0.4f);
    desenhaCubo();
    glPopMatrix();
    
    // Encosto
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.6f, -0.18f);
    geometricTransformation::Scale(0.4f, 0.5f, 0.05f);
    desenhaCubo();
    glPopMatrix();
    
    // Haste central
    //glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.125f, 0.0f);
    geometricTransformation::Scale(0.05f, 0.25f, 0.05f);
    desenhaCubo();
    glPopMatrix();
    
    // Pés (base em cruz)
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.025f, 0.0f);
    geometricTransformation::Scale(0.4f, 0.05f, 0.05f);
    desenhaCubo();
    glPopMatrix();
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.025f, 0.0f);
    geometricTransformation::Scale(0.05f, 0.05f, 0.4f);
    desenhaCubo();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaMesaLaboratorio(float largura, float profundidade) {
    // Definindo as dimensões com base na foto
    float alturaMesa = 0.75f;
    float alturaPrateleira = 0.4f;
    float espessuraTampo = 0.05f;
    float espessuraPainel = 0.05f;

    glPushMatrix();

    // --- Tampo Principal (vermelho) com cantos arredondados ---
    //glColor3f(0.8f, 0.1f, 0.1f);
    glPushMatrix();
    geometricTransformation::Translate(0.0f, alturaMesa, 0.0f);
    desenhaTampoDaMesa(largura, profundidade, espessuraTampo); // Chama a função correta do tampo
    glPopMatrix();

    // --- Prateleira Inferior (vermelha) ---
    // Esta pode ser um cubo simples, pois é menos visível.
    glPushMatrix();
    geometricTransformation::Translate(0.0f, alturaPrateleira, 0.0f);
    // É um pouco mais estreita para se encaixar entre os painéis de suporte
    geometricTransformation::Scale(largura - (2 * espessuraPainel), espessuraTampo, profundidade * 0.9f);
    desenhaCubo();
    glPopMatrix();

    // --- Painéis de Suporte (cor de madeira) ---
    //glColor3f(0.9f, 0.8f, 0.6f); // Cor clara de madeira

    // Painel da Esquerda
    glPushMatrix();
    float posX_painel = -largura / 2.0f + espessuraPainel / 2.0f;
    geometricTransformation::Translate(posX_painel, (alturaMesa - espessuraTampo) / 2.0f, 0.0f);
    geometricTransformation::Scale(espessuraPainel, alturaMesa - espessuraTampo, profundidade);
    desenhaCubo();
    glPopMatrix();

    // Painel da Direita
    glPushMatrix();
    posX_painel = largura / 2.0f - espessuraPainel / 2.0f;
    geometricTransformation::Translate(posX_painel, (alturaMesa - espessuraTampo) / 2.0f, 0.0f);
    geometricTransformation::Scale(espessuraPainel, alturaMesa - espessuraTampo, profundidade);
    desenhaCubo();
    glPopMatrix();

    // Painel Central (para mesas longas)
    if (largura > 2.0f) {
        glPushMatrix();
        geometricTransformation::Translate(0.0f, (alturaMesa - espessuraTampo) / 2.0f, 0.0f);
        geometricTransformation::Scale(espessuraPainel, alturaMesa - espessuraTampo, profundidade);
        desenhaCubo();
        glPopMatrix();
    }

    glPopMatrix();
}

void Objects::desenhaQuadroNegro() {
    glPushMatrix();
    // Superfície do quadro
    glDisable(GL_LIGHTING);
    //glColor3f(0.1f, 0.2f, 0.1f); // Verde bem escuro
    glPushMatrix();
    geometricTransformation::Scale(3.0f, 1.5f, 0.02f);
    desenhaCubo();
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // Moldura de madeira
    //glColor3f(0.5f, 0.35f, 0.05f);
    // Moldura superior
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.8f, 0.0f);
    geometricTransformation::Scale(3.1f, 0.1f, 0.04f);
    desenhaCubo();
    glPopMatrix();
    // Moldura inferior
    glPushMatrix();
    geometricTransformation::Translate(0.0f, -0.8f, 0.0f);
    geometricTransformation::Scale(3.1f, 0.1f, 0.04f);
    desenhaCubo();
    glPopMatrix();
    // Moldura esquerda
    glPushMatrix();
    geometricTransformation::Translate(-1.55f, 0.0f, 0.0f);
    geometricTransformation::Scale(0.1f, 1.7f, 0.04f);
    desenhaCubo();
    glPopMatrix();
    // Moldura direita
    glPushMatrix();
    geometricTransformation::Translate(1.55f, 0.0f, 0.0f);
    geometricTransformation::Scale(0.1f, 1.7f, 0.04f);
    desenhaCubo();
    glPopMatrix();
    
    glPopMatrix();
}

//======================================================================
// COMPOSIÇÃO - JUNTA AS PEÇAS EM UM POSTO DE TRABALHO
//======================================================================
void Objects::desenhaPostoDeTrabalho() {
    glPushMatrix();

    // Monitor na mesa
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.7f, -0.1f); // 0.7 é a altura da mesa
    desenhaMonitor();
    glPopMatrix();

    // Gabinete no chão, ao lado da mesa
    glPushMatrix();
    geometricTransformation::Translate(0.4f, 1.0f, 0.0f);
    desenhaGabinetePC();
    glPopMatrix();

    // Cadeira em frente à mesa
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.0f, 0.6f);
    geometricTransformation::Rotate(-180.0f, 0.0f, 1.0f, 0.0f); // Gira a cadeira para frente
    desenhaCadeira();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaSala(float largura, float altura, float profundidade) {
    float larg = largura / 2.0f; 
    float alt = altura; 
    float prof = profundidade / 2.0f;

    glPushMatrix();

    // Chão
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_FLOOR_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_FLOOR_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_FLOOR_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_FLOOR_SHININESS);
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-larg, 0.0f, -prof); glVertex3f( larg, 0.0f, -prof); glVertex3f( larg, 0.0f,  prof); glVertex3f(-larg, 0.0f,  prof); 
    glEnd();

    // Teto
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_CEILING_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_CEILING_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_CEILING_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_CEILING_SHININESS);
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-larg, alt,  prof); glVertex3f( larg, alt,  prof); glVertex3f( larg, alt, -prof); glVertex3f(-larg, alt, -prof); 
    glEnd();

    // Paredes Laterais
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_SIDEWALL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_SIDEWALL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_SIDEWALL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_SIDEWALL_SHININESS);
    glBegin(GL_QUADS); // Esquerda
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-larg, 0.0f,  prof); glVertex3f(-larg, alt,   prof); glVertex3f(-larg, alt,  -prof); glVertex3f(-larg, 0.0f, -prof); 
    glEnd();
    glBegin(GL_QUADS); // Direita
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(larg, 0.0f, -prof); glVertex3f(larg, alt,  -prof); glVertex3f(larg, alt,   prof); glVertex3f(larg, 0.0f,  prof); 
    glEnd();

    // Parede do Fundo
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_BACKWALL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_BACKWALL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_BACKWALL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_BACKWALL_SHININESS);
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-larg, 0.0f, -prof); glVertex3f(-larg, alt,  -prof); glVertex3f( larg, alt,  -prof); glVertex3f( larg, 0.0f, -prof); 
    glEnd();

    // Parede da Frente
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_FRONTWALL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_FRONTWALL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_FRONTWALL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_FRONTWALL_SHININESS);
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-larg, 0.0f, prof); glVertex3f(larg, 0.0f, prof); glVertex3f(larg, alt, prof); glVertex3f(-larg, alt, prof); 
    glEnd();

    glPopMatrix();
}