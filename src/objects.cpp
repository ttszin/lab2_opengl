//Colocar os objetos aqui para serem chamados
#include <GL/glut.h>
#include "objects.h" // Incluindo o arquivo de modelagem dos objetos
#include "geometric_transformations.h"
#include <initializer_list>
//======================================================================
// MODELAGEM DOS OBJETOS DO LABORATÓRIO
//======================================================================


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
    glColor3f(0.9f, 0.9f, 0.9f); // Cor branca/cinza claro
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
    glColor4f(0.7f, 0.9f, 1.0f, 0.5f); // Azul claro, 50% opaco

    // Desenha o cubo que representa o vidro
    geometricTransformation::Scale(largura, altura, 0.02f); // Bem fino
    desenhaCubo();

    glPopMatrix();
}


void Objects::desenhaMonitor() {
    glPushMatrix();
    // Base do monitor
    glColor3f(0.2f, 0.2f, 0.2f); // Cinza escuro
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.05f, 0.0f);
    geometricTransformation::Scale(0.3f, 0.1f, 0.3f);
    desenhaCubo();
    glPopMatrix();

    // Haste do monitor
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.2f, 0.0f);
    geometricTransformation::Scale(0.05f, 0.3f, 0.05f);
    desenhaCubo();
    glPopMatrix();

    // Tela do monitor
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.5f, 0.0f);
    geometricTransformation::Scale(0.7f, 0.5f, 0.05f);
    desenhaCubo();
    glPopMatrix();

    // "Vidro" da tela (um pouco à frente, preto sólido)
    glDisable(GL_LIGHTING); // Desliga a iluminação para cor sólida
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.5f, 0.026f); // Levemente à frente da tela
    geometricTransformation::Scale(0.65f, 0.45f, 0.01f);
    desenhaCubo();
    glPopMatrix();
    glEnable(GL_LIGHTING); // Liga a iluminação de volta

    glPopMatrix();
}

void Objects::desenhaGabinetePC() {
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    geometricTransformation::Scale(0.2f, 0.5f, 0.4f);
    desenhaCubo();
    glPopMatrix();
}

void Objects::desenhaCadeira() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.4f); // Azul escuro
    
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
    glColor3f(0.2f, 0.2f, 0.2f);
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
    float altura = 0.7f;
    float espessura_tampo = 0.05f;
    float espessura_pe = 0.1f;

    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.2f); // Cor de madeira

    // Tampo
    glPushMatrix();
    geometricTransformation::Translate(0.0f, altura - (espessura_tampo / 2.0f), 0.0f);
    geometricTransformation::Scale(largura, espessura_tampo, profundidade);
    desenhaCubo();
    glPopMatrix();

    // Pés
    float pos_x = largura / 2.0f - espessura_pe / 2.0f;
    float pos_z = profundidade / 2.0f - espessura_pe / 2.0f;
    float alt_pe = altura - espessura_tampo;

    // Pé 1 (frente, direita)
    glPushMatrix();
    geometricTransformation::Translate(pos_x, alt_pe / 2.0f, pos_z);
    geometricTransformation::Scale(espessura_pe, alt_pe, espessura_pe);
    desenhaCubo();
    glPopMatrix();

    // Pé 2 (frente, esquerda)
    glPushMatrix();
    geometricTransformation::Translate(-pos_x, alt_pe / 2.0f, pos_z);
    geometricTransformation::Scale(espessura_pe, alt_pe, espessura_pe);
    desenhaCubo();
    glPopMatrix();

    // Pé 3 (trás, direita)
    glPushMatrix();
    geometricTransformation::Translate(pos_x, alt_pe / 2.0f, -pos_z);
    geometricTransformation::Scale(espessura_pe, alt_pe, espessura_pe);
    desenhaCubo();
    glPopMatrix();

    // Pé 4 (trás, esquerda)
    glPushMatrix();
    geometricTransformation::Translate(-pos_x, alt_pe / 2.0f, -pos_z);
    geometricTransformation::Scale(espessura_pe, alt_pe, espessura_pe);
    desenhaCubo();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaQuadroNegro() {
    glPushMatrix();
    // Superfície do quadro
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.2f, 0.1f); // Verde bem escuro
    glPushMatrix();
    geometricTransformation::Scale(3.0f, 1.5f, 0.02f);
    desenhaCubo();
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // Moldura de madeira
    glColor3f(0.5f, 0.35f, 0.05f);
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
    geometricTransformation::Translate(0.4f, 0.25f, 0.0f);
    desenhaGabinetePC();
    glPopMatrix();

    // Cadeira em frente à mesa
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.0f, 0.6f);
    desenhaCadeira();
    glPopMatrix();

    glPopMatrix();
}

void Objects::desenhaSala(float largura, float altura, float profundidade) {
    float larg = largura / 2.0f; float alt = altura; float prof = profundidade / 2.0f;
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.7f); glNormal3f(0.0f, 1.0f, 0.0f); glBegin(GL_QUADS); glVertex3f(-larg, 0.0f, -prof); glVertex3f( larg, 0.0f, -prof); glVertex3f( larg, 0.0f,  prof); glVertex3f(-larg, 0.0f,  prof); glEnd();
    glColor3f(0.9f, 0.9f, 0.9f); glNormal3f(0.0f, -1.0f, 0.0f); glBegin(GL_QUADS); glVertex3f(-larg, alt,  prof); glVertex3f( larg, alt,  prof); glVertex3f( larg, alt, -prof); glVertex3f(-larg, alt, -prof); glEnd();
    glColor3f(0.7f, 0.7f, 0.9f); glNormal3f(1.0f, 0.0f, 0.0f); glBegin(GL_QUADS); glVertex3f(-larg, 0.0f,  prof); glVertex3f(-larg, alt,   prof); glVertex3f(-larg, alt,  -prof); glVertex3f(-larg, 0.0f, -prof); glEnd();
    glColor3f(0.7f, 0.7f, 0.9f); glNormal3f(-1.0f, 0.0f, 0.0f); glBegin(GL_QUADS); glVertex3f(larg, 0.0f, -prof); glVertex3f(larg, alt,  -prof); glVertex3f(larg, alt,   prof); glVertex3f(larg, 0.0f,  prof); glEnd();
    glColor3f(0.9f, 0.8f, 0.8f); glNormal3f(0.0f, 0.0f, 1.0f); glBegin(GL_QUADS); glVertex3f(-larg, 0.0f, -prof); glVertex3f(-larg, alt,  -prof); glVertex3f( larg, alt,  -prof); glVertex3f( larg, 0.0f, -prof); glEnd();
    glColor3f(0.9f, 0.9f, 0.8f); glNormal3f(0.0f, 0.0f, -1.0f); glBegin(GL_QUADS); glVertex3f(-larg, 0.0f, prof); glVertex3f(larg, 0.0f, prof); glVertex3f(larg, alt, prof); glVertex3f(-larg, alt, prof); glEnd();
    glPopMatrix();
}