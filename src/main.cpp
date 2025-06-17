#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "objects.h"            //Chamando o arquivo que contém a modelagem dos objetos de cena

// --- Constantes e Variáveis Globais ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float camera_x = 0.0f, camera_y = 1.7f, camera_z = 8.0f; // Posição inicial da câmera
float camera_yaw = -90.0f;
float anguloJanelas = 0.0f;

//======================================================================
// CÓDIGO DA APLICAÇÃO (SALA, CÂMERA, ETC.)
//======================================================================
void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Laboratorio de Computacao - C++");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    std::cout << "\nLaboratorio modelado!\n";
    std::cout << "Controles: W/S/A/D para mover, ESC para sair.\n";
    std::cout << "Controles: W/S/A/D para mover.\n";
    std::cout << "           O/F para abrir/fechar as janelas.\n";
    std::cout << "           ESC para sair.\n";

    glutMainLoop();
    return 0;
}

void display() {
    Objects obj;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float olhar_x = camera_x + cos(camera_yaw * M_PI / 180.0f);
    float olhar_z = camera_z + sin(camera_yaw * M_PI / 180.0f);
    
    gluLookAt(camera_x, camera_y, camera_z,
              olhar_x, camera_y, olhar_z,
              0.0f, 1.0f, 0.0f);

    // --- MONTAGEM DA CENA ---
    obj.desenhaSala(12.0f, 4.0f, 16.0f);

    // Coloca o quadro negro na parede de trás
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -7.9f); // -8 é a parede, -7.9 para ficar um pouco na frente
    obj.desenhaQuadroNegro();
    glPopMatrix();

    // Fileira de mesas da esquerda
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    obj.desenhaMesaLaboratorio(3.0f, 1.0f);
    glPopMatrix();

    // Fileira de mesas da direita
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);
    obj.desenhaMesaLaboratorio(3.0f, 1.0f);
    glPopMatrix();

    // Coloca 2 postos de trabalho em cada fileira
    float posicoes_mesas[] = {-3.0f, 3.0f};
    for(float pos_x : posicoes_mesas) {
        // Posto 1
        glPushMatrix();
        glTranslatef(pos_x, 0.0f, 0.0f); // Posição x da fileira, z do posto
        obj.desenhaPostoDeTrabalho();
        glPopMatrix();

        // Posto 2
        glPushMatrix();
        glTranslatef(pos_x, 0.0f, -3.0f);
        obj.desenhaPostoDeTrabalho();
        glPopMatrix();
    }

    // --- DESENHA AS JANELAS NA PAREDE ESQUERDA ---
    // A parede esquerda está em X = -6.0f (metade da largura da sala que é 12.0f)
    float parede_x = -5.98f; // Um pouco para dentro para não "brigar" com a parede
    float altura_janela = 2.0f; // Altura do centro da janela em relação ao chão
    
    // Desenha 5 janelas em uma fileira (aumentei o espaçamento para caber)
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        // Calcula a posição Z para cada janela, espaçando-as
        float pos_z = -6.0f + (i * 2.5f);
        glTranslatef(parede_x, altura_janela, pos_z);
        
        // Gira a janela para alinhar com a parede (opcional, se necessário)
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 

        obj.desenhaJanela(anguloJanelas);
        glPopMatrix();
    }
    
    // (Opcional) Desenha mais 5 janelas na parede direita para simetria
    float parede_direita_x = 5.98f;
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        float pos_z = -6.0f + (i * 2.5f);
        glTranslatef(parede_direita_x, altura_janela, pos_z);
        obj.desenhaJanela(-anguloJanelas); // Abre para o outro lado
        glPopMatrix();
    }


    glutSwapBuffers();
}

// Definições das outras funções (init, reshape, keyboard) - sem alterações

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat luz_ambiente[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat luz_difusa[]   = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat luz_posicao[]  = { 0.0f, 3.5f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicao);
    glShadeModel(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);

    // --- HABILITA TRANSPARÊNCIA ---
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y) {
    float velocidade = 0.2f;
    float rad_yaw = camera_yaw * M_PI / 180.0f;
    switch (key) {
        case 'w': case 'W': camera_x += cos(rad_yaw) * velocidade; camera_z += sin(rad_yaw) * velocidade; break;
        case 's': case 'S': camera_x -= cos(rad_yaw) * velocidade; camera_z -= sin(rad_yaw) * velocidade; break;
        case 'a': case 'A': camera_yaw -= 3.0f; break;
        case 'd': case 'D': camera_yaw += 3.0f; break;
        case 27: exit(0); break;
    }
    switch (key) {
        // ... (cases para w, s, a, d, 27) ...
        
        // --- NOVOS CONTROLES PARA AS JANELAS ---
        case 'o': // 'o' para "Open" (Abrir)
        case 'O':
            anguloJanelas += 5.0f;
            if (anguloJanelas > 70.0f) anguloJanelas = 70.0f; // Limite de abertura
            break;
        case 'f': // 'f' para "Fechar"
        case 'F':
            anguloJanelas -= 5.0f;
            if (anguloJanelas < 0.0f) anguloJanelas = 0.0f; // Limite de fechamento
            break;
    }
    glutPostRedisplay();
}