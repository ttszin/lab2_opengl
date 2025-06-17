import sys
from OpenGL.GL import *
from OpenGL.GLUT import *

# Função de desenho (renderização)
def desenha():
    """Função chamada para desenhar a cena."""
    # 1. Limpa a tela (buffer de cor e de profundidade)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    # Inicia o desenho de um ou mais triângulos
    glBegin(GL_TRIANGLES)
    
    # Vértice 1 (Vermelho)
    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-0.5, -0.5, 0.0)
    
    # Vértice 2 (Verde)
    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.5, -0.5, 0.0)
    
    # Vértice 3 (Azul)
    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.5, 0.0)
    
    glEnd()  # Finaliza o desenho

    # 2. Troca os buffers para exibir o que foi desenhado
    glutSwapBuffers()

# Função principal
def main():
    """Função principal que inicializa tudo."""
    # Inicializa a GLUT
    glutInit(sys.argv)
    
    # Configura o modo de exibição
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    
    # Configura a janela
    glutInitWindowSize(800, 600)
    glutInitWindowPosition(100, 100)
    glutCreateWindow(b"Triangulo Colorido em Python") # Título da janela
    
    # Registra a função de desenho
    glutDisplayFunc(desenha)
    
    # Define a cor de fundo (preto)
    glClearColor(0.0, 0.0, 0.0, 1.0)
    
    # Inicia o loop principal da GLUT
    print("Janela criada. Pressione ESC para fechar.")
    glutMainLoop()

# Executa a função principal
if __name__ == "__main__":
    main()