# Ambiente Virtual do laboratório 2 FURG/C3 em OpenGL

Este é um projeto acadêmico para a disciplina de Computação Gráfica, desenvolvido com o objetivo de criar um ambiente virtual 3D que representa uma sala de laboratório do **Centro de Ciências Computacionais (C3)** da **Universidade Federal do Rio Grande (FURG)**.

## 👥 Integrantes

* Matheus Teixeira de Souza
* Vinicius Furtado
* António Lopes
## ⚙️ Tecnologias Utilizadas

* **Linguagem:** C++
* **Biblioteca Gráfica:** OpenGL
* **Utilitário:** GLUT (OpenGL Utility Toolkit)
* **Compilador:** MinGW (GCC para Windows)

## 🚀 Começando

Siga as instruções abaixo para compilar e executar o projeto em seu computador.

### Pré-requisitos

Para rodar este programa, é essencial ter o compilador **MinGW** e as bibliotecas do **GLUT** instalados e configurados no seu ambiente Windows.

### Guia de Instalação

1.  **Instalar o MinGW (GCC for Windows):**
    * É necessário um compilador C++. O MinGW é uma excelente opção para Windows.
    * **Tutorial de Instalação:** [Instalando o MinGW via MSYS2](https://www.msys2.org/) (Método recomendado e moderno).

2.  **Configurar a Biblioteca GLUT:**
    * Baixe os binários pré-compilados da GLUT para Windows.
    * **Link para Download:** [glut-3.7.6-bin.zip](https://www.transmission.mspro.com/download/glut-3.7.6-bin.zip)
    * Após descompactar, copie os arquivos para os diretórios do seu MinGW:
        1.  Copie `glut.h` para a pasta `MinGW\include\GL\` (crie a pasta `GL` se ela não existir).
        2.  Copie `glut32.lib` para a pasta `MinGW\lib\`.
        3.  Copie `glut32.dll` para a **pasta raiz do seu projeto** (a mesma onde o `lab_app.exe` será gerado). Esta é a abordagem mais simples e segura.

### Compilação

Com o ambiente configurado, abra o terminal (Prompt de Comando ou PowerShell) na pasta raiz do projeto e execute o seguinte comando para compilar todos os arquivos de código-fonte:

```bash
Linux:
g++ main.cpp geometric_transformations.cpp objects.cpp rasterization.cpp -o lab_app -lGL -lGLU -lglut
Windows:
g++ main.cpp geometric_transformations.cpp objects.cpp rasterization.cpp -o lab_app -lopengl32 -lglu32 -lglut32 -lm
```

Isso irá gerar um arquivo executável chamado `lab_app.exe`.

### Execução

Para executar a aplicação, basta rodar o arquivo gerado no passo anterior:

```bash
./lab_app.exe
```

## ✨ Funcionalidades e Requisitos Implementados

Este projeto atende a todos os requisitos solicitados na disciplina:

* `[x]` **(25%) Modelagem das Geometrias:**
    * Foram modelados elementos que representam um laboratório de informática, contendo bancadas de dois níveis com cantos frontais arredondados, cadeiras de escritório, monitores widescreen, gabinetes de PC (torre), janelas basculantes que se abrem e um quadro branco na parede.

* `[x]` **(20%) Transformações Geométricas:**
    * Implementação de funções de **translação**, **rotação** e **escala** utilizando matrizes customizadas, aplicadas aos objetos da cena através da função `glMultMatrixf()`.

* `[x]` **(15%) Projeções:**
    * Implementação de funções para gerar as matrizes de projeção **perspectiva** e **ortogonal**. A troca entre os modos é feita em tempo real e, no modo ortogonal, foram implementadas visões fixas (topo, frontal, etc.) e uma câmera de órbita.

* `[x]` **(15%) Modelo de Iluminação e Tonalização:**
    * Aplicação do modelo de iluminação de **Phong** através da configuração de uma fonte de luz com componentes ambiente, difuso e especular (`glLightfv`), e da configuração das propriedades do material dos objetos (`glColorMaterial`, `glMaterialfv`). A tonalização de **Gouraud** foi ativada com `glShadeModel(GL_SMOOTH)`.

* `[x]` **(15%) Algoritmo de Rasterização:**
    * Implementação e aplicação do algoritmo de **Bresenham** para renderizar o contorno (wireframe) de uma das cadeiras da cena. O processo envolve projetar os vértices 3D do objeto para o espaço de tela 2D e, em seguida, usar o algoritmo para desenhar cada pixel das arestas com `GL_POINTS`.

* `[x]` **(10%) Algoritmo de Visibilidade:**
    * Utilização do algoritmo **Z-Buffer** (Depth Buffer), habilitado via `glEnable(GL_DEPTH_TEST)` na função de inicialização, para garantir que os objetos mais próximos ocultem corretamente os mais distantes na cena 3D.

## 🕹️ Controles da Aplicação

* **W, A, S, D:** Mover a câmera (modo Perspectiva/FPS) ou controlar o zoom (modo Ortogonal/Órbita).
* **Mouse:** Rotacionar a visão da câmera.
* **P:** Alternar entre projeção Perspectiva e Ortogonal.
* **V:** (Apenas no modo Ortogonal) Ciclar entre as visões: Órbita Livre, Topo, Base, Frente, Trás, Esquerda, Direita.
* **O, F:** Abrir e fechar as janelas.
* **ESC:** Fechar a aplicação.
