// Menu.c - Isabel H. Manssour
// Um programa OpenGL simples que exemplifica
// como exibir textos e utilizar menus e funções 
// callback para verificar a movimentação do 
// mouse na janela GLUT.
// Este código está baseado nos exemplos 
// disponíveis no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

#include <GL/glut.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

// Constantes
#define QUADRADO 1
#define TRIANGULO 2
#define LOSANGO   3

// Variáveis
char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, primitiva;
int telaFacil[4][3] = {{1, 1, 2}, {2, 3, 3}, {4, 4, 5}, {5, 6, 6}};
bool desenhadoFacil[4][3] = {{false, false, false},
                  {false, false, false},{false, false, false},{false, false, false}};
// bool desenhadoFacil[4][3] = {{true, true, true},
// {true, true, true},{true, true, true},{true, true, true}};
int x0, y0, x1, y1;
bool  primeiroClique;

void DesenhaQuadrado(GLfloat x, GLfloat y)
{
    glBegin(GL_QUADS);
        glVertex2f(x, y - 50.0f);
        glVertex2f(x, y);
        glVertex2f(x + 66.7f, y);
        glVertex2f(x + 66.7f, y - 50.0f);
    glEnd();
}

// Função que desenha um triângulo
void DesenhaTriangulo(void)
{
     glBegin(GL_TRIANGLES);
               glVertex2f(-25.0f, -25.0f);
               glVertex2f(0.0f, 25.0f);
               glVertex2f(25.0f, -25.0f);              
     glEnd();
}

// Função que desenha um losango
void DesenhaLosango(void)
{
     glBegin(GL_POLYGON);
               glVertex2f(-25.0f, 0.0f);
               glVertex2f(0.0f, 25.0f);
               glVertex2f(25.0f, 0.0f);
               glVertex2f(0.0f, -25.0f);               
     glEnd();
}

// Desenha um texto na janela GLUT
void DesenhaTexto(char *string) 
{  
  	glPushMatrix();
        // Posição no universo onde o texto será colocado          
        glRasterPos2f(-win,win-(win*0.08)); 
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	glPopMatrix();
}

void Randomizar(int linha, int coluna)
{
    for(int i = 0; i < linha; i++)
    {
        for(int j = 0; j < coluna; j++)
        {
            int linhaParaTrocar = rand() % linha;
            int colunaParaTrocar = rand() % coluna;
            std::swap(telaFacil[i][j], telaFacil[linhaParaTrocar][colunaParaTrocar]);
        }
    }
    //return array;
}

void DesenhaTela()
{
    GLfloat x = -win, y = win; 
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(telaFacil[i][j] == 1 && desenhadoFacil[i][j] == true){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 2 && desenhadoFacil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 3 && desenhadoFacil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 4 && desenhadoFacil[i][j] == true){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 5 && desenhadoFacil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 6 && desenhadoFacil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }    
            x += 66.7f;
        }
        x = -100.0f;
        y -= 50.0f;
    }
}

void DesenhaObjeto(int x, int y, int i, int j)
{
    if(desenhadoFacil[i][j])
        return;
    if(telaFacil[i][j] == 1){
        // azul
        glColor3f(0.0f, 0.0f, 1.0f);
        DesenhaQuadrado(x, y);
    }
    else if(telaFacil[i][j] == 2){
        // vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
        DesenhaQuadrado(x, y);
    }
    else if(telaFacil[i][j] == 3){
        // verde
        glColor3f(0.0f, 1.0f, 1.0f);
        DesenhaQuadrado(x, y);
    }
    else if(telaFacil[i][j] == 4){
        // azul
        glColor3f(0.0f, 0.0f, 1.0f);
        DesenhaQuadrado(x, y);
    }
    else if(telaFacil[i][j] == 5){
        // vermelho
        glColor3f(1.0f, 0.0f, 0.0f);
        DesenhaQuadrado(x, y);
    }
    else if(telaFacil[i][j] == 6){
        // verde
        glColor3f(0.0f, 1.0f, 0.0f);
        DesenhaQuadrado(x, y);
    } 
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Define a cor corrente
    //glColor3f(r,g,b);

    DesenhaTela();

    // Exibe a posição do mouse na janela
    glColor3f(1.0f,1.0f,1.0f);
    DesenhaTexto(texto);

    glutSwapBuffers();
}

void ParesFacil()
{
    Randomizar(4,3);
}

void ParesDificil()
{}

void SequenciaFacil()
{}

void SequenciaDificil()
{}

void Sair(int op)
{
    glutDestroyWindow(op);
    exit(0);
}

void MenuPares(int op)
{
    switch(op)
    {
        case 0:
            ParesFacil();
            break;
        case 1:
            ParesDificil();
            break;
    }
}

void MenuSequencia(int op)
{
    switch(op)
    {
        case 0:
            SequenciaFacil();
            break;
        case 1:
            SequenciaDificil();
            break;
    }
}

// Gerenciamento do menu principal          
void MenuPrincipal(int op)
{
    if(op == 0)
        Sair(win);
}

// Criacao do Menu
void CriaMenu()
{
    int menu, pares, sequencia, sair;

    pares = glutCreateMenu(MenuPares);
    glutAddMenuEntry("Fácil", 0);
    glutAddMenuEntry("Dificil", 1);

    sequencia = glutCreateMenu(MenuSequencia);
    glutAddMenuEntry("Fácil", 0);
    glutAddMenuEntry("Díficil", 1);

    menu = glutCreateMenu(MenuPrincipal);    
    glutAddSubMenu("Formar pares", pares);
    glutAddSubMenu("Sequencia (Genius)", sequencia);
    glutAddMenuEntry("Sair", 0);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{   
    // Define a cor de fundo da janela de visualização como branca
    win = 100.0f;
    x0 = y0 = x1 = y1 = -1;
    primeiroClique = true;
    Randomizar(4,3);
    DesenhaTela();
    CriaMenu();
    
}

int TransformaX(int x)
{
    return x / (double) 400 * (100 - (-100)) + (-100);
}

int TransformaY(int y)
{
    return (1 - y / (double) 400) * (100 - (-100)) + (-100);
}

int MapearX(int x)
{
    if(x >= 33) return 2;
    else if(x >= -33) return 1;
    else return 0;
}

int MapearY(int y)
{
    if(y >= 50) return 0;
    else if(y >= 0) return 1;
    else if(y >= -50) return 2;
    else return 3;
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT com um botão pressionado
void MousePressionado(int x, int y)
{
    sprintf(texto, "Botao pressionado (%d,%d)", x, y);

    //desenhadoFacil[0][0] = true;
    
    if(primeiroClique){
        x0 = TransformaX(x);
        y0 = TransformaY(y);
        //DesenhaObjeto();
        if (desenhadoFacil[MapearX(x0)][MapearY(y0)])
            desenhadoFacil[MapearX(x0)][MapearY(y0)] = false;
        primeiroClique = false;        
    }
    else{
        x1 = TransformaX(x);
        y1 = TransformaY(y);

        DesenhaObjeto(x1, y1, MapearX(x1), MapearY(y1));
        x0 = MapearX(x0);
        y0 = MapearY(y1);
        x1 = MapearX(x1);
        y1 = MapearY(y1);

        sprintf(texto, "antigo: (%d, %d), novo: (%d, %d)", x0, y0, x1, y1);
        if(telaFacil[x0][y0] == telaFacil[x1][y1]){
            desenhadoFacil[x0][y0] = desenhadoFacil[x1][y1] = true;
        }
        primeiroClique = true;
    }
      
    glutPostRedisplay();
}

// Programa Principal 
int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Trabalho CG");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMotionFunc(MousePressionado); 
    //glutPassiveMotionFunc(MoveMouse);
    //glutMouseFunc(GerenciaMouse);    
    //glutSpecialFunc(TeclasEspeciais);
    Inicializa();
    glutMainLoop();
}
