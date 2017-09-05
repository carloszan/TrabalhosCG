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
    // 1 - Quadrado Azul
    // 2 - Quadrado Vermelho
    // 3 - Quadrado Verde
    // 4 - Quadrado Branco
    // 5 - Triangulo Azul
    // 6 - Triangulo Vermelho
    // 7 - Triangulo Verde
    // 8 - Triangulo Branco
    // 9 - Losango Azul
    // 10 - Losango Vermelh
    // 11 - Losango Verde
    // 12 - Losango Branco

    Randomizar(4, 3);

    //Randomiza(array, 4, 3);

    GLfloat x = -win, y = win; 
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(telaFacil[i][j] == 1){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 2){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 3){
                // verde
                glColor3f(0.0f, 1.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 4){
                // branco
                glColor3f(1.0f, 1.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 5){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaFacil[i][j] == 6){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }    
            x += 66.7f;
        }
        x = -100.0f;
        y -= 50.0f;
    }
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Define a cor corrente
    glColor3f(r,g,b);

    DesenhaTela();

    // Exibe a posição do mouse na janela
    glColor3f(1.0f,1.0f,1.0f);
    DesenhaTexto(texto);

    glutSwapBuffers();
}

void ParesFacil()
{
    printf("OI");
}

void ParesDificil()
{

}

void SequenciaFacil()
{

}

void SequenciaDificil()
{

}

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
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    win=100.0f;
    primitiva = QUADRADO;
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    strcpy(texto, "(0,0)");
    
    CriaMenu();
    
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
void MoveMouseBotaoPressionado(int x, int y)
{
     sprintf(texto, "Botao pressionado (%d,%d)", x, y);
     //glutPostRedisplay();
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT 
void MoveMouse(int x, int y)
{
     sprintf(texto, "(%d,%d)", x, y);
     //glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           win -= 10;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    if(key == GLUT_KEY_DOWN) {
           win += 10;
           if (win > 500) win = 500;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    //glutPostRedisplay();
}
 
/*           
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
           glutAttachMenu(GLUT_RIGHT_BUTTON);
         
    glutPostRedisplay();
}
*/
                     
// Programa Principal 
int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
    glutInitWindowSize(350,300);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Trabalho CG");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMotionFunc(MoveMouseBotaoPressionado); 
    glutPassiveMotionFunc(MoveMouse);
//     glutMouseFunc(GerenciaMouse);    
    glutSpecialFunc(TeclasEspeciais);
    Inicializa();
    glutMainLoop();
}
