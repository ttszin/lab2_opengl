# Ambiente Virtual do laboratório 2 FURG/C3 em OpenGL

Este é um projeto acadêmico para a disciplina de Computação Gráfica, desenvolvido com o objetivo de criar um ambiente virtual 3D que representa o laboratório 2 da **Universidade Federal do Rio Grande (FURG)** e/ou do **Centro de Ciências Computacionais (C3)**.

## 👥 Integrantes

  * Matheus Teixeira de Souza
  * Vinicius Furtado

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

      * Siga o tutorial detalhado para instalar o conjunto de compiladores C/C++ no Windows:
      * **Tutorial:** [Instalando o MinGW](https://ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html)

2.  **Instalar o OpenGL (GLUT) no Windows:**

      * A instalação do GLUT no MinGW envolve copiar os arquivos da biblioteca para os diretórios corretos. Um guia comum e funcional é o do Nate Robins, cujos arquivos podem ser encontrados online.
      * **Tutorial Sugerido:** [Como instalar o GLUT no Code::Blocks (MinGW)](https://www.google.com/search?q=http://www.youtube.com/watch%3Fv%3D1) - Este vídeo mostra o processo, que se resume a:
        1.  Baixar os arquivos do GLUT.
        2.  Copiar `glut.h` para a pasta `MinGW\include\GL`.
        3.  Copiar `glut32.lib` para a pasta `MinGW\lib`.
        4.  Copiar `glut32.dll` para a pasta `C:\Windows\System32` (para 32 bits) ou `C:\Windows\SysWOW64` (para 64 bits).

    > **Atenção:** O segundo link fornecido na descrição do trabalho (`https://www.youtube.com/watch?v=Y4F0tI7WlDs`) está quebrado. O método descrito acima é a alternativa recomendada.

### Compilação

Com o ambiente configurado, abra o terminal (Prompt de Comando ou PowerShell) na pasta raiz do projeto e execute o seguinte comando para compilar o código:

```bash
g++ main.cpp -o lab_app -lopengl32 -lglu32 -lglut32 -lm
```

Isso irá gerar um arquivo executável chamado `lab_app.exe`.

### Execução

Para executar a aplicação, basta rodar o arquivo gerado no passo anterior:

```bash
./lab_app.exe
```

## ✨ Funcionalidades e Requisitos Implementados

Este projeto atende aos seguintes requisitos da disciplina:

  * `[x]` **(25%) Modelagem das Geometrias:**

      * Foram modelados elementos que representam o ambiente da FURG/C3, como: *[Descreva aqui o que foi modelado, ex: o prédio do C3, o logo da universidade, um laboratório específico, etc.]*

  * `[ ]` **(20%) Transformações Geométricas:**

      * Implementação de funções de **translação**, **rotação** e **escala** utilizando matrizes customizadas, aplicadas aos objetos da cena através da função `glMultMatrixf()`.

  * `[ ]` **(15%) Projeções:**

      * Implementação de funções para gerar projeções **perspectiva** e **ortogonal** através de matrizes customizadas, aplicadas com `glMultMatrixf()`.

  * `[ ]` **(15%) Modelo de Iluminação e Tonalização:**

      * Aplicação do modelo de iluminação de **Phong** e do método de tonalização de **Gouraud** utilizando as rotinas nativas da OpenGL (`glLight`, `glMaterial`, `glShadeModel(GL_SMOOTH)`).

  * `[ ]` **(15%) Algoritmo de Rasterização:**

      * Implementação e aplicação do algoritmo de **[DDA ou Bresenham]** para renderizar *[Descreva onde o algoritmo foi usado, ex: uma grade no chão, o contorno de um objeto, etc.]*.

  * `[ ]` **(10%) Algoritmo de Visibilidade:**

      * Utilização de um algoritmo de visibilidade para o correto tratamento de superfícies ocultas, como o **Z-Buffer** (Depth Test), habilitado via `glEnable(GL_DEPTH_TEST)`.

## 🕹️ Controles da Aplicação

  * **W, A, S, D:** Mover a câmera para frente, esquerda, trás e direita.
  * **O, F:** Abrir/Fechar as janelas.
  * **Mouse:** Rotacionar a visão da câmera.
  * **R:** Rotacionar o objeto selecionado.
  * **P:** Alternar entre projeção perspectiva e ortogonal.
  * **L:** Ligar/Desligar a iluminação.