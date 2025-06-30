#include <GL/glut.h>
#include "objects.h" // Incluindo o arquivo de modelagem dos objetos
#include "geometric_transformations.h"
#include <initializer_list>
#include "rasterization.h"
#include <vector> // Precisaremos de vetores para armazenar os pontos

// --- PALETA DE MATERIAIS PARA O MODELO DE PHONG ---

// --- Material para Estofado Preto (Tecido) ---

const GLfloat MAT_BLACK_UPHOLSTERY_AMBIENT[]  = {0.02f, 0.02f, 0.02f, 1.0f}; // Uma cor ambiente muito baixa para parecer preto
const GLfloat MAT_BLACK_UPHOLSTERY_DIFFUSE[]  = {0.1f, 0.1f, 0.1f, 1.0f};   // A cor difusa também é muito escura
const GLfloat MAT_BLACK_UPHOLSTERY_SPECULAR[] = {0.05f, 0.05f, 0.05f, 1.0f}; // Um brilho especular quase nulo, apenas para dar um mínimo de forma
const GLfloat MAT_BLACK_UPHOLSTERY_SHININESS  = 5.0f;                      // Um valor de brilho muito baixo

// Material para Vidro ---

const GLfloat MAT_GLASS_WINDOW_AMBIENT[]  = {0.7f, 0.8f, 0.8f, 0.1f}; // Reflete um pouco da luz ambiente com um tom levemente azulado/esverdeado
const GLfloat MAT_GLASS_WINDOW_DIFFUSE[]  = {0.4f, 0.4f, 0.5f, 0.1f}; // A cor difusa é baixa, pois vidro não espalha muita luz
const GLfloat MAT_GLASS_WINDOW_SPECULAR[] = {0.9f, 0.9f, 0.9f, 0.1f}; // Reflexo especular branco e intenso
const GLfloat MAT_GLASS_WINDOW_SHININESS  = 120.0f;                   // Um valor de "shininess" (brilho) bem alto para um reflexo pequeno e focado

// Material para Plástico Branco (Ar Condicionado)
const GLfloat MAT_WHITE_PLASTIC_AMBIENT[]  = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat MAT_WHITE_PLASTIC_DIFFUSE[]  = {0.9f, 0.9f, 0.9f, 1.0f};
const GLfloat MAT_WHITE_PLASTIC_SPECULAR[] = {0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat MAT_WHITE_PLASTIC_SHININESS  = 20.0f;

// Material para Luz da Lâmpada (Emissivo)
// GL_EMISSION faz o objeto brilhar com luz própria, independente das fontes de luz.
const GLfloat MAT_LAMP_LIGHT_EMISSION[] = {0.9f, 0.9f, 0.85f, 1.0f}; // Cor do brilho
const GLfloat MAT_LAMP_LIGHT_AMBIENT[]  = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat MAT_LAMP_LIGHT_DIFFUSE[]  = {0.9f, 0.9f, 0.9f, 1.0f};

// Material para Inox / Metal Cromado ---

const GLfloat MAT_STAINLESS_STEEL_AMBIENT[]  = {0.25f, 0.25f, 0.25f, 1.0f}; // Cor ambiente acinzentada
const GLfloat MAT_STAINLESS_STEEL_DIFFUSE[]  = {0.4f, 0.4f, 0.4f, 1.0f};    // Cor difusa metálica/cinza
const GLfloat MAT_STAINLESS_STEEL_SPECULAR[] = {0.8f, 0.8f, 0.8f, 1.0f};    // Reflexo especular forte e branco/cinza claro
const GLfloat MAT_STAINLESS_STEEL_SHININESS  = 95.0f;                     // Um valor de brilho alto para um reflexo nítido de metal

// Material: Paredes
const GLfloat MAT_WALL_AMBIENT[]  = {0.894f, 0.878f, 0.843f, 1.0f}; // A cor ambiente pode ser a mesma da difusa ou um pouco mais escura
const GLfloat MAT_WALL_DIFFUSE[]  = {0.894f, 0.878f, 0.843f, 1.0f}; // A cor principal da parede sob a luz
const GLfloat MAT_WALL_SPECULAR[] = {0.0f, 0.0f, 0.0f, 1.0f};       // Sem componente especular para um acabamento fosco
const GLfloat MAT_WALL_SHININESS  = 5.0f;                          // Valor de brilho baixo, não terá muito efeito já que o especular é preto

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
const GLfloat MAT_GLASS_DIFFUSE[]  = {0.01f, 0.0f, 0.0f, 1.0f}; // Quase preto
const GLfloat MAT_GLASS_SPECULAR[] = {0.9f, 0.9f, 0.9f, 1.0f};   // Reflexo branco e forte
const GLfloat MAT_GLASS_SHININESS  = 300.0f; // Expoente MUITO alto para um brilho nítido

// Material: Metal Prateado Polido (para a moldura do quadro)
const GLfloat MAT_SILVER_METAL_AMBIENT[]  = {0.2f, 0.2f, 0.2f, 1.0f};
const GLfloat MAT_SILVER_METAL_DIFFUSE[]  = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat MAT_SILVER_METAL_SPECULAR[] = {0.9f, 0.9f, 0.9f, 1.0f};
const GLfloat MAT_SILVER_METAL_SHININESS  = 90.0f;

// Material: Superfície Branca (para a área de escrita do quadro)
const GLfloat MAT_WHITEBOARD_AMBIENT[]  = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat MAT_WHITEBOARD_DIFFUSE[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat MAT_WHITEBOARD_SPECULAR[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Um brilho suave
const GLfloat MAT_WHITEBOARD_SHININESS  = 32.0f;

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

void Objects::desenhaLampada() {
    // Baseado nas luminárias retangulares embutidas no teto
    glPushMatrix();

    // 1. Moldura de metal da lâmpada
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_STAINLESS_STEEL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_STAINLESS_STEEL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_STAINLESS_STEEL_SPECULAR);
    glMaterialf(GL_FRONT,  GL_SHININESS, MAT_STAINLESS_STEEL_SHININESS);
    // Zera a emissão que pode ter sido definida por outro objeto
    GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

    glPushMatrix();
    geometricTransformation::Scale(1.2f, 0.05f, 0.3f);
    desenhaCubo();
    glPopMatrix();

    // 2. Parte que emite luz (com material emissivo)
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_LAMP_LIGHT_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_LAMP_LIGHT_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_EMISSION,  MAT_LAMP_LIGHT_EMISSION); // APLICA O BRILHO

    glPushMatrix();
    // Um pouco menor e mais para cima para encaixar na moldura
    geometricTransformation::Translate(0.0f, 0.01f, 0.0f); 
    geometricTransformation::Scale(1.1f, 0.04f, 0.2f);
    desenhaCubo();
    glPopMatrix();

    // Reseta a emissão para não afetar outros objetos na cena
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

    glPopMatrix();
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

void Objects::desenhaArCondicionado() {
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WHITE_PLASTIC_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WHITE_PLASTIC_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WHITE_PLASTIC_SPECULAR);
    glMaterialf(GL_FRONT,  GL_SHININESS, MAT_WHITE_PLASTIC_SHININESS);
    // Garante que não tenha emissão
    GLfloat no_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

    // Corpo principal do ar condicionado
    glPushMatrix();
    geometricTransformation::Scale(0.8f, 0.25f, 0.2f);
    desenhaCubo();
    glPopMatrix();
    
    glPopMatrix();
}

//======================================================================
// MODELAGEM DOS OBJETOS DO LABORATÓRIO
//======================================================================

void Objects::desenhaJanela(float anguloAbertura) {
    float largura = 1.0f;
    float altura = 1.5f;
    float espessura_moldura = 0.05f;

    // --- Caixilho (a parte fixa na parede) ---
    glPushMatrix();
    // Moldura superior e inferior

    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_STAINLESS_STEEL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_STAINLESS_STEEL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_STAINLESS_STEEL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_STAINLESS_STEEL_SHININESS);

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

    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_GLASS_WINDOW_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_GLASS_WINDOW_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_GLASS_WINDOW_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_GLASS_WINDOW_SHININESS);

    // A MÁGICA DA ROTAÇÃO:
    // 1. Mova o sistema de coordenadas para o ponto de pivô (a "dobradiça" no topo do caixilho).
    geometricTransformation::Translate(0.0f, altura / 2.0f, 0.0f);
    // 2. Rotacione em torno do eixo X.
    geometricTransformation::Rotate(anguloAbertura, 1.0f, 0.0f, 0.0f);
    // 3. Mova a vidraça para baixo para que ela se alinhe com o pivô.
    geometricTransformation::Translate(0.0f, -altura / 2.0f, 0.0f);

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

    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_DARK_PLASTIC_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_DARK_PLASTIC_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_DARK_PLASTIC_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_DARK_PLASTIC_SHININESS);

    geometricTransformation::Scale(0.2f, 0.5f, 0.4f);
    desenhaCubo();
    glPopMatrix();
}

void Objects::desenhaCadeira() {
    glPushMatrix();
    
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
    // Definindo as dimensões
    float alturaMesa = 0.75f;
    float alturaPrateleira = 0.4f;
    float espessuraTampo = 0.05f;
    float espessuraPainel = 0.05f;

    glPushMatrix();

    // --- Tampo Principal (vermelho) com cantos arredondados ---

    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_TABLE_RED_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_TABLE_RED_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_TABLE_RED_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_TABLE_RED_SHININESS);

    glPushMatrix();
    geometricTransformation::Translate(0.0f, alturaMesa, 0.0f);
    geometricTransformation::Rotate(-180.0f, 1.0f, 0.0f, 0.0f); // Rotaciona para ficar horizontal
    desenhaTampoDaMesa(largura, profundidade, espessuraTampo); // Chama a função correta do tampo
    glPopMatrix();

    // --- Prateleira Inferior (vermelha) ---
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_TABLE_RED_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_TABLE_RED_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_TABLE_RED_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_TABLE_RED_SHININESS);

    glPushMatrix();
    geometricTransformation::Translate(0.0f, alturaPrateleira, 0.4f);
    // É um pouco mais estreita para se encaixar entre os painéis de suporte
    geometricTransformation::Scale(largura - (2 * espessuraPainel), espessuraTampo, profundidade * 0.9f);
    desenhaCubo();
    glPopMatrix();

    // --- Painéis Laterais (madeira) ---
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WOOD_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WOOD_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WOOD_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_WOOD_SHININESS);

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

    // --- Superfície de Escrita Branca ---
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WHITEBOARD_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WHITEBOARD_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WHITEBOARD_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_WHITEBOARD_SHININESS);

    glPushMatrix();
    geometricTransformation::Scale(3.0f, 1.5f, 0.02f);
    desenhaCubo();
    glPopMatrix();

    // --- Moldura de Metal Prateado ---
    // Aplicamos o material de metal para as 4 partes da moldura
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_SILVER_METAL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_SILVER_METAL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_SILVER_METAL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_SILVER_METAL_SHININESS);
    
    // Move a moldura inteira um pouco para frente (no eixo Z) para evitar Z-Fighting
    geometricTransformation::Translate(0.0f, 0.0f, 0.01f);

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

    // Gabinete
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.5f, 0.42f);
    geometricTransformation::Rotate(-90.0f, 0.0f, 0.0f, 1.0f); // Gira o gabinete para ficar de lado
    desenhaGabinetePC();
    glPopMatrix();

    // Cadeira em frente à mesa
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.0f, 0.8f);
    geometricTransformation::Rotate(-180.0f, 0.0f, 1.0f, 0.0f); // Gira a cadeira para frente
    desenhaCadeira();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaParedeComJanelas(float largura, float altura, float profundidade) {
    const float larg = largura / 2.0f;
    const float prof = profundidade / 2.0f;
    const float alt = altura;

    // Constantes da janela
    const float win_largura = 1.0f;
    const float win_altura = 1.5f;
    const float win_y_centro = 2.0f;
    const int num_janelas = 5;
    const float espacamento_z = 2.5f;
    const float z_inicial = -6.0f;

    const float win_y_bottom = win_y_centro - (win_altura / 2.0f);
    const float win_y_top = win_y_centro + (win_altura / 2.0f);
    
    // Criamos uma sobreposição minúscula para evitar frestas de renderização
    const float overlap = 0.001f;

    // 1. Parte de baixo da parede (sem alteração)
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-larg, 0.0f, -prof);
        glVertex3f(-larg, win_y_bottom, -prof);
        glVertex3f(-larg, win_y_bottom, prof);
        glVertex3f(-larg, 0.0f, prof);
    glEnd();

    // 2. Parte de cima da parede (sem alteração)
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-larg, win_y_top, -prof);
        glVertex3f(-larg, alt, -prof);
        glVertex3f(-larg, alt, prof);
        glVertex3f(-larg, win_y_top, prof);
    glEnd();

    // 3. Borda do início da parede até a primeira janela (com overlap)
    float z_borda_primeira_janela = z_inicial - (win_largura / 2.0f);
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-larg, win_y_bottom - overlap, -prof);
        glVertex3f(-larg, win_y_top + overlap,    -prof);
        glVertex3f(-larg, win_y_top + overlap,    z_borda_primeira_janela);
        glVertex3f(-larg, win_y_bottom - overlap, z_borda_primeira_janela);
    glEnd();

    // 4. Pilares entre cada janela (com overlap)
    for (int i = 0; i < num_janelas - 1; ++i) {
        float z_borda_direita_atual = (z_inicial + i * espacamento_z) + (win_largura / 2.0f);
        float z_borda_esquerda_proxima = (z_inicial + (i + 1) * espacamento_z) - (win_largura / 2.0f);
        
        glBegin(GL_QUADS);
        
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-larg, win_y_bottom - overlap, z_borda_direita_atual);
            glVertex3f(-larg, win_y_top + overlap,    z_borda_direita_atual);
            glVertex3f(-larg, win_y_top + overlap,    z_borda_esquerda_proxima);
            glVertex3f(-larg, win_y_bottom - overlap, z_borda_esquerda_proxima);
        glEnd();
    }

    // 5. Borda da última janela até o fim da parede (com overlap)
    float z_borda_ultima_janela = (z_inicial + (num_janelas - 1) * espacamento_z) + (win_largura / 2.0f);
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-larg, win_y_bottom - overlap, z_borda_ultima_janela);
        glVertex3f(-larg, win_y_top + overlap,    z_borda_ultima_janela);
        glVertex3f(-larg, win_y_top + overlap,    prof);
        glVertex3f(-larg, win_y_bottom - overlap, prof);
    glEnd();
}

void Objects::desenhaPorta() {
    // Porta branca simples com batente e maçaneta
    glPushMatrix();

    // 1. Batente da Porta (usa o material da parede)
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WALL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WALL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WALL_SPECULAR);
    glMaterialf(GL_FRONT,  GL_SHININESS, MAT_WALL_SHININESS);
    
    // Batente superior
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 1.05f, 0.0f);
    geometricTransformation::Scale(0.9f, 0.1f, 0.1f);
    desenhaCubo();
    glPopMatrix();
    // Batente esquerdo
    glPushMatrix();
    geometricTransformation::Translate(-0.4f, 0.0f, 0.0f);
    geometricTransformation::Scale(0.1f, 2.0f, 0.1f);
    desenhaCubo();
    glPopMatrix();
    // Batente direito
    glPushMatrix();
    geometricTransformation::Translate(0.4f, 0.0f, 0.0f);
    geometricTransformation::Scale(0.1f, 2.0f, 0.1f);
    desenhaCubo();
    glPopMatrix();

    // 2. Painel da Porta (plástico branco)
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WHITE_PLASTIC_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WHITE_PLASTIC_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WHITE_PLASTIC_SPECULAR);
    glMaterialf(GL_FRONT,  GL_SHININESS, MAT_WHITE_PLASTIC_SHININESS);

    glPushMatrix();
    geometricTransformation::Scale(0.75f, 2.0f, 0.05f);
    desenhaCubo();
    glPopMatrix();

    // 3. Maçaneta (metal)
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_STAINLESS_STEEL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_STAINLESS_STEEL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_STAINLESS_STEEL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_STAINLESS_STEEL_SHININESS);

    glPushMatrix();
    geometricTransformation::Translate(0.28f, 0.0f, 0.05f);
    geometricTransformation::Scale(0.05f, 0.05f, 0.1f);
    desenhaCubo();
    glPopMatrix();
    
    glPopMatrix();
}

void Objects::desenhaSala(float largura, float altura, float profundidade) {
    float larg = largura / 2.0f; 
    float alt = altura; 
    float prof = profundidade / 2.0f;

    // >>>>>>>> APLICA O MATERIAL PARA TODAS AS PAREDES <<<<<<<<<<
    glMaterialfv(GL_FRONT, GL_AMBIENT,   MAT_WALL_AMBIENT);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   MAT_WALL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  MAT_WALL_SPECULAR);
    glMaterialf(GL_FRONT, GL_SHININESS, MAT_WALL_SHININESS);

    glPushMatrix();

    // Chão (com sombreamento suave)
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-larg, 0.0f, -prof); glVertex3f( larg, 0.0f, -prof); glVertex3f( larg, 0.0f,  prof); glVertex3f(-larg, 0.0f,  prof); 
    glEnd();


    // Teto
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-larg, alt,  prof); glVertex3f( larg, alt,  prof); glVertex3f( larg, alt, -prof); glVertex3f(-larg, alt, -prof); 
    glEnd();

    // Parede da esquerda com os vãos
    desenhaParedeComJanelas(largura, altura, profundidade);

    // Parede da Direita
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(larg, 0.0f, -prof); glVertex3f(larg, alt,  -prof); glVertex3f(larg, alt,   prof); glVertex3f(larg, 0.0f,  prof); 
    glEnd();

    // Parede do Fundo
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-larg, 0.0f, -prof); glVertex3f(-larg, alt,  -prof); glVertex3f( larg, alt,  -prof); glVertex3f( larg, 0.0f, -prof); 
    glEnd();

    // Parede da Frente
    glBegin(GL_QUADS); 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-larg, 0.0f, prof); glVertex3f(larg, 0.0f, prof); glVertex3f(larg, alt, prof); glVertex3f(-larg, alt, prof); 
    glEnd();

    glPopMatrix();
}