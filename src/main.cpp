#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "objects.h"            //Chamando o arquivo que contém a modelagem dos objetos de cena
#include "geometric_transformations.h"

// --- Constantes e Variáveis Globais ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float camera_x = 0.0f, camera_y = 1.7f, camera_z = 8.0f; // Posição inicial da câmera
float camera_yaw = -90.0f;
float anguloJanelas = 0.0f;
// ... (variáveis da câmera existentes) ...
float camera_pitch = 0.0f; // Rotação vertical (olhar para cima/baixo)
int window_width = 1280;
int window_height = 720;

//======================================================================
// CÓDIGO DA APLICAÇÃO (SALA, CÂMERA, ETC.)
//======================================================================
void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

// Substitua a função mouseMove inteira por esta
void mouseMove(int x, int y) {
    // Calcula o deslocamento do mouse a partir do centro da tela
    float delta_x = x - (window_width / 2);
    float delta_y = y - (window_height / 2);

    // Se não houve movimento, não faz nada
    if (delta_x == 0 && delta_y == 0) return;

    // Fator de sensibilidade
    float sensibilidade = 0.1f;
    delta_x *= sensibilidade;
    delta_y *= sensibilidade;

    // Atualiza os ângulos de yaw e pitch
    camera_yaw += delta_x;
    camera_pitch -= delta_y; // Invertido

    // Limita o pitch
    if (camera_pitch > 89.0f) {
        camera_pitch = 89.0f;
    }
    if (camera_pitch < -89.0f) {
        camera_pitch = -89.0f;
    }

    // A MÁGICA: Força o cursor a voltar para o centro da janela
    glutWarpPointer(window_width / 2, window_height / 2);

    // Força o redesenho
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Laboratorio de Computacao - C++");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // --- NOVAS LINHAS PARA O MOUSE ---
    glutPassiveMotionFunc(mouseMove); // Registra a função de movimento do mouse
    glutSetCursor(GLUT_CURSOR_NONE);  // Oculta o cursor do sistema
    
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
    geometricTransformation gt;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- NOVA MATEMÁTICA DA CÂMERA ---
    // Converte ângulos para radianos
    float rad_yaw = camera_yaw * M_PI / 180.0f;
    float rad_pitch = camera_pitch * M_PI / 180.0f;

    // Calcula o vetor de direção da câmera no espaço 3D
    float olhar_x = cos(rad_pitch) * cos(rad_yaw);
    float olhar_y = sin(rad_pitch);
    float olhar_z = cos(rad_pitch) * sin(rad_yaw);
    
    // O ponto para onde olhamos é a posição da câmera + o vetor de direção
    gluLookAt(camera_x, camera_y, camera_z,
              camera_x + olhar_x, camera_y + olhar_y, camera_z + olhar_z,
              0.0f, 1.0f, 0.0f);

    // --- MONTAGEM DA CENA ---
    obj.desenhaSala(12.0f, 4.0f, 16.0f);

    // Coloca o quadro negro na parede de trás
    glPushMatrix();
    gt.Translate(0.0f, 2.0f, -7.9f); // -8 é a parede, -7.9 para ficar um pouco na frente
    obj.desenhaQuadroNegro();
    glPopMatrix();

    // Fileira de mesas da esquerda
    glPushMatrix();
    gt.Translate(-3.0f, 0.0f, 0.0f);
    obj.desenhaMesaLaboratorio(3.0f, 1.0f);
    glPopMatrix();

    // Fileira de mesas da direita
    glPushMatrix();
    gt.Translate(3.0f, 0.0f, 0.0f);
    obj.desenhaMesaLaboratorio(3.0f, 1.0f);
    glPopMatrix();

    // Coloca 2 postos de trabalho em cada fileira
    float posicoes_mesas[] = {-3.0f, 3.0f};
    for(float pos_x : posicoes_mesas) {
        // Posto 1
        glPushMatrix();
        gt.Translate(pos_x, 0.0f, 0.0f); // Posição x da fileira, z do posto
        obj.desenhaPostoDeTrabalho();
        glPopMatrix();

        // Posto 2
        glPushMatrix();
        gt.Translate(pos_x, 0.0f, -3.0f);
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
        gt.Translate(parede_x, altura_janela, pos_z);
        
        // Gira a janela para alinhar com a parede (opcional, se necessário)
        gt.Rotate(90.0f, 0.0f, 1.0f, 0.0f); 

        obj.desenhaJanela(anguloJanelas);
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
    window_width = w;
    window_height = h;
 
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y) {
    float velocidade = 0.2f;
    // Converte o ângulo de yaw para radianos APENAS UMA VEZ no início da função
    float rad_yaw = camera_yaw * M_PI / 180.0f;

    switch (key) {
        case 'w':
        case 'W':
            // Move para frente na direção do yaw
            camera_x += cos(rad_yaw) * velocidade;
            camera_z += sin(rad_yaw) * velocidade;
            break;
        case 's':
        case 'S':
            // Move para trás na direção oposta ao yaw
            camera_x -= cos(rad_yaw) * velocidade;
            camera_z -= sin(rad_yaw) * velocidade;
            break;
            
        // --- LÓGICA DE STRAFE ATUALIZADA ---
        case 'a':
        case 'A':
            // Move para a esquerda usando o vetor "direita" (perpendicular ao yaw)
            // O vetor "direita" tem componentes (sin(rad_yaw), -cos(rad_yaw))
            camera_x += sin(rad_yaw) * velocidade;
            camera_z -= cos(rad_yaw) * velocidade;
            break;
        case 'd':
        case 'D':
            // Move para a direita usando o vetor "direita"
            camera_x -= sin(rad_yaw) * velocidade;
            camera_z += cos(rad_yaw) * velocidade;
            break;
            
        case 27: // Tecla ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}