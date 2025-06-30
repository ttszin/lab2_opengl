#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "objects.h"            //Chamando o arquivo que contém a modelagem dos objetos de cena
#include "geometric_transformations.h"

// --- Constantes e Variáveis Globais ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Variáveis da Câmera em Primeira Pessoa (FPS) ---
float camera_x = 0.0f, camera_y = 1.7f, camera_z = 8.0f;
float camera_yaw = -90.0f;
float camera_pitch = 0.0f;

// --- Variáveis da Janela ---
int window_width = 1280;
int window_height = 720;
float anguloJanelas = 0.0f;

// --- NOVO SISTEMA DE CÂMERA ---
enum CameraMode {
    FIRST_PERSON,
    TOP_VIEW,
    BOTTOM_VIEW,
    FRONT_VIEW,
    BACK_VIEW,
    LEFT_VIEW,
    RIGHT_VIEW
};
CameraMode current_camera_mode = FIRST_PERSON; // Começa no modo FPS

//======================================================================
// CÓDIGO DA APLICAÇÃO (SALA, CÂMERA, ETC.)
//======================================================================
void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);


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

    // Força o cursor a voltar para o centro da janela
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

    glutPassiveMotionFunc(mouseMove); // Registra a função de movimento do mouse
    glutSetCursor(GLUT_CURSOR_NONE);  // Oculta o cursor do sistema
    
    std::cout << "\nLaboratorio modelado!\n";
    std::cout << "Controles:\n";
    std::cout << "  - W/S/A/D: Mover (apenas no modo 1-FPS)\n";
    std::cout << "  - Mouse: Olhar (apenas no modo 1-FPS)\n";
    std::cout << "  - O/F: Abrir/Fechar janelas\n";
    std::cout << "  - Teclas 1-7: Trocar de Camera\n";
    std::cout << "     1: Primeira Pessoa\n";
    std::cout << "     2: Vista Superior\n";
    std::cout << "     3: Vista Frontal\n";
    std::cout << "     4: Vista Traseira\n";
    std::cout << "     5: Vista da Esquerda\n";
    std::cout << "     6: Vista da Direita\n";
    std::cout << "     7: Vista Inferior\n";
    std::cout << "  - ESC: Sair\n";

    glutMainLoop();
    return 0;
}

void display() {
    Objects obj;
    geometricTransformation gt;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- LÓGICA DE MÚLTIPLAS CÂMERAS ---
    switch (current_camera_mode) {
        case FIRST_PERSON: {
            float rad_yaw = camera_yaw * M_PI / 180.0f;
            float rad_pitch = camera_pitch * M_PI / 180.0f;
            float olhar_x = cos(rad_pitch) * cos(rad_yaw);
            float olhar_y = sin(rad_pitch);
            float olhar_z = cos(rad_pitch) * sin(rad_yaw);
            gluLookAt(camera_x, camera_y, camera_z,
                      camera_x + olhar_x, camera_y + olhar_y, camera_z + olhar_z,
                      0.0f, 1.0f, 0.0f);
            break;
        }
        case TOP_VIEW:
            // Câmera posicionada bem acima, olhando para baixo. O "up" é o fundo da sala.
            gluLookAt(0.0f, 20.0f, 0.0f,   // Posição (Eye)
                      0.0f, 0.0f, 0.0f,    // Ponto para onde olha (Center)
                      0.0f, 0.0f, -1.0f);  // Vetor "para cima" (Up)
            break;
        case BOTTOM_VIEW:
            // Câmera posicionada bem abaixo, olhando para cima.
            gluLookAt(0.0f, -20.0f, 0.0f,  // Eye
                      0.0f, 0.0f, 0.0f,    // Center
                      0.0f, 0.0f, -1.0f);  // Up
            break;
        case FRONT_VIEW:
            // Câmera na frente da sala (porta), olhando para o fundo (quadro).
            gluLookAt(0.0f, 2.0f, 15.0f,   // Eye
                      0.0f, 2.0f, 0.0f,    // Center
                      0.0f, 1.0f, 0.0f);   // Up
            break;
        case BACK_VIEW:
            // Câmera atrás do quadro, olhando para a porta.
            gluLookAt(0.0f, 2.0f, -15.0f,  // Eye
                      0.0f, 2.0f, 0.0f,    // Center
                      0.0f, 1.0f, 0.0f);   // Up
            break;
        case LEFT_VIEW:
            // Câmera na parede das janelas, olhando para a parede oposta.
            gluLookAt(-15.0f, 2.0f, 0.0f,  // Eye
                      0.0f, 2.0f, 0.0f,    // Center
                      0.0f, 1.0f, 0.0f);   // Up
            break;
        case RIGHT_VIEW:
            // Câmera na parede da direita, olhando para as janelas.
            gluLookAt(15.0f, 2.0f, 0.0f,   // Eye
                      0.0f, 2.0f, 0.0f,    // Center
                      0.0f, 1.0f, 0.0f);   // Up
            break;
    }

    // --- MONTAGEM DA CENA ---
    // 1. Desenha a sala
    const float room_width = 10.0f; // Largura
    const float room_height = 4.0f; //altura
    const float room_depth = 18.0f; //Profundidade
    obj.desenhaSala(room_width, room_height, room_depth);



    // 2. Desenha o quadro negro
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 2.0f, -8.95f);
    obj.desenhaQuadroNegro();
    glPopMatrix();

    // 3. Lixeira no canto
    glPushMatrix();
    geometricTransformation::Translate(-(room_width/2.0f)+1.0f, 0.0f, 8.5f);
    obj.desenhaLixeiraWireframeBresenham();
    glPopMatrix();

    // --- LÂMPADAS NO TETO E FONTES DE LUZ ---
    int light_num = 0; // Contador para saber qual luz estamos posicionando (de 0 a 7)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            glPushMatrix();
                float lamp_x = -3.0f + (j * 6.0f);
                float lamp_z = -6.0f + (i * 4.0f);
                // Move o sistema de coordenadas para a posição da lâmpada
                geometricTransformation::Translate(lamp_x, room_height - 0.1f, lamp_z);

                // Define a posição da luz. Como a matriz de transformação já foi aplicada,
                // a posição {0,0,0,1} significa que a luz estará exatamente no mesmo
                // lugar que a lâmpada que vamos desenhar em seguida.
                GLfloat light_pos[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Posição local da luz
                glLightfv(GL_LIGHT0 + light_num, GL_POSITION, light_pos);

                // Desenha o objeto da lâmpada (que agora terá uma luz real dentro)
                obj.desenhaLampada();
            glPopMatrix();

            light_num++; // Incrementa para a próxima luz no próximo loop
        }
    }

    // 5. --- APARELHOS DE AR CONDICIONADO ---
    // Dois acima do quadro
    glPushMatrix();
    geometricTransformation::Translate(-2.5f, 3.5f, -8.87f);
    obj.desenhaArCondicionado();
    glPopMatrix();
    
    glPushMatrix();
    geometricTransformation::Translate(2.5f, 3.5f, -8.87f);
    obj.desenhaArCondicionado();
    glPopMatrix();

    // Um na parede de trás
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 3.5f, 8.87f);
    obj.desenhaArCondicionado();
    glPopMatrix();

    // 6. --- MESA DO PROFESSOR ---
    // Posicionada na frente, à direita do quadro
    glPushMatrix();
    geometricTransformation::Translate(2.5f, 0.0f, -6.0f);
    geometricTransformation::Rotate(-180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona a mesa para ficar de frente
    obj.desenhaMesaLaboratorio(2.0f, 1.0f); // Mesa um pouco menor
    glPushMatrix();
    geometricTransformation::Translate(0.0f, 0.0f, 0.0f); // Apenas um posto de trabalho
    obj.desenhaPostoDeTrabalho();
    glPopMatrix();
    glPopMatrix();

    // 7. --- MESAS DOS ALUNOS ---
    const float x_columns[] = {-1.1f, 2.96f}; // Posições X ajustadas
    const int num_rows = 6;
    const float z_start = -4.5f;
    const float z_spacing = 2.2f;

    glPushMatrix();

    // Porta na frente, à direita
    glPushMatrix();
    geometricTransformation::Translate(4.5f, 1.0f, 8.945f); // Posição na frente, à direita
    geometricTransformation::Rotate(-180.0f, 0.0f, 1.0f, 0.0f); // Rotaciona para ficar de frente
    obj.desenhaPorta();
    glPopMatrix();

    for (int i = 0; i < num_rows; ++i) {
        for (float pos_x : x_columns) {
            float pos_z = z_start + (i * z_spacing);
            glPushMatrix();
            geometricTransformation::Translate(pos_x, 0.0f, pos_z);
            obj.desenhaMesaLaboratorio(4.0f, 1.0f);
            glPushMatrix();
            geometricTransformation::Translate(-1.0f, 0.0f, 0.0f);
            obj.desenhaPostoDeTrabalho();
            glPopMatrix();
            glPushMatrix();
            geometricTransformation::Translate(1.0f, 0.0f, 0.0f);
            obj.desenhaPostoDeTrabalho();
            glPopMatrix();
            glPopMatrix();
        }
    }

    // 8. --- JANELAS ---
    float parede_x = -(room_width / 2.0f); // Posição da parede agora é -5.0f
    float altura_janela = 2.0f;
    
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        float pos_z = -6.0f + (i * 2.5f);
        gt.Translate(parede_x, altura_janela, pos_z);
        gt.Rotate(90.0f, 0.0f, 1.0f, 0.0f); 
        obj.desenhaJanela(anguloJanelas);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Definições das outras funções (init, reshape, keyboard)

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Cenário preto/azulado escuro
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH); // Ativa Gouraud Shading
    glEnable(GL_LIGHTING); // Habilita o sistema de iluminação

    // Propriedades que serão compartilhadas por todas as luzes das lâmpadas
    GLfloat luz_ambiente[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // Pouca luz ambiente
    GLfloat luz_difusa[]   = { 0.8f, 0.8f, 0.8f, 1.0f };    // Luz difusa branca, com força moderada
    GLfloat luz_especular[]= { 0.9f, 0.9f, 0.9f, 1.0f };    // Brilho especular também moderado

    
    // Loop para configurar e habilitar GL_LIGHT0 até GL_LIGHT7
    for (int i = 0; i < 8; i++) {
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, luz_ambiente);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, luz_difusa);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, luz_especular);

        // Atenuação: faz a luz ficar mais fraca com a distância
        glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 0.1f);
        glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 0.05f);

        glEnable(GL_LIGHT0 + i); // Habilita a luz atual
    }

    // Habilita transparência para as janelas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Garante a correção automática de normais após a escala
    glEnable(GL_NORMALIZE);

}

void reshape(int w, int h) {
    window_width = w;
    window_height = h;
 
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    
    // Agora sempre usa perspectiva, já que removemos o modo ortogonal
    geometricTransformation::Perspective(45.0, aspect, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    float velocidade = 0.2f;

    // Movimento só funciona no modo FPS
    if (current_camera_mode == FIRST_PERSON) {
        float rad_yaw = camera_yaw * M_PI / 180.0f;
        switch (key) {
            case 'w': case 'W':
                camera_x += cos(rad_yaw) * velocidade;
                camera_z += sin(rad_yaw) * velocidade;
                break;
            case 's': case 'S':
                camera_x -= cos(rad_yaw) * velocidade;
                camera_z -= sin(rad_yaw) * velocidade;
                break;
            case 'a': case 'A':
                camera_x += sin(rad_yaw) * velocidade;
                camera_z -= cos(rad_yaw) * velocidade;
                break;
            case 'd': case 'D':
                camera_x -= sin(rad_yaw) * velocidade;
                camera_z += cos(rad_yaw) * velocidade;
                break;
        }
    }

    // Controles que funcionam em todos os modos
    switch (key) {
        // Controles de câmera
        case '1': current_camera_mode = FIRST_PERSON; break;
        case '2': current_camera_mode = TOP_VIEW; break;
        case '3': current_camera_mode = FRONT_VIEW; break;
        case '4': current_camera_mode = BACK_VIEW; break;
        case '5': current_camera_mode = LEFT_VIEW; break;
        case '6': current_camera_mode = RIGHT_VIEW; break;
        case '7': current_camera_mode = BOTTOM_VIEW; break;

        // Controles das janelas
        case 'o': case 'O': anguloJanelas += 5.0f; if (anguloJanelas > 70.0f) anguloJanelas = 70.0f; break;
        case 'f': case 'F': anguloJanelas -= 5.0f; if (anguloJanelas < 0.0f) anguloJanelas = 0.0f; break;
        
        // Sair
        case 27: exit(0); break;
    }

    // Força o redesenho após qualquer mudança
    glutPostRedisplay();
}