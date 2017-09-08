#include <GL/glut.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>

GLfloat win;

int telaFacil[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 6}};
bool desenhadoFacil[3][4] = {{false, false, false, false},
                             {false, false, false, false}, 
                             {false, false, false, false}};

// bool desenhadoFacil[3][4] = {{true, true, true, true},
//                              {true, true, true, true}, 
//                              {true, true, true, true}};
int x0, y0, x1, y1;
bool  primeiroClique;

void Randomizar(int linha, int coluna)
{
    srand(time(NULL));
    for(int i = 0; i < linha; i++)
    {
        for(int j = 0; j < coluna; j++)
        {
            int linhaParaTrocar = rand() % linha;
            int colunaParaTrocar = rand() % coluna;
            std::swap(telaFacil[i][j], telaFacil[linhaParaTrocar][colunaParaTrocar]);
        }
    }
}

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
void DesenhaTriangulo(GLfloat x, GLfloat y)
{
     glBegin(GL_TRIANGLES);
        glVertex2f(x, y - 50.0f);
        glVertex2f(x + 66.7f/2, y);
        glVertex2f(x + 66.7f, y - 50.0f);              
     glEnd();
}

void DesenhaTela()
{
    GLfloat x = -win, y = win; 
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
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
                DesenhaTriangulo(x, y);
            }
            if(telaFacil[i][j] == 5 && desenhadoFacil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaTriangulo(x, y);
            }
            if(telaFacil[i][j] == 6 && desenhadoFacil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 0.0f);
                DesenhaTriangulo(x, y);
            }    
            x += 50.0f;
        }
        x = -win;
        y -= 66.7f;
    }
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaTela();

    glutSwapBuffers();
}

void Inicializa (void) 
{
    win = 100.0f;
    //define a cor de background da janela
    glClearColor (1.0, 1.0, 1.0, 0.0);
    Randomizar(3,4);
    primeiroClique = true;

    desenhadoFacil[0][0] = true;
    desenhadoFacil[1][0] = true;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-win, win, -win, win);
}

int TransformaX(int x)
{
    if(x < 100)
        return -(100 - x);
    return x - 100;
}

int TransformaY(int y)
{
    if (y < 100)
        return 100 - y;
    return -(y - 100);
}

int MapearParaMatrizI(int i)
{
    if(i >= 50) return 3;
    else if (i >= 0) return 2;
    else if(i >= -50) return 1;
    else return 0;
}

int MapearParaMatrizJ(int j)
{
    if(j >= 33.3) return 0;
    else if(j >= -33.7) return 1;
    else return 2;
}
void MousePressionado(int x, int y)
{

    printf("P: (%d, %d) -> (%d, %d)", x, y, TransformaX(x), TransformaY(y));
    printf("M: (%d, %d)\n", MapearParaMatrizJ(TransformaY(y)), MapearParaMatrizI(TransformaX(x)));
    if(primeiroClique){
        x0 = TransformaX(x);
        y0 = TransformaY(y);
        desenhadoFacil[MapearParaMatrizI(x0)][MapearParaMatrizJ(y0)] = true;
        primeiroClique = false;        
    }
    // else{
    //     x1 = TransformaX(x);
    //     y1 = TransformaY(y);

    //     //DesenhaObjeto(x1, y1, MapearX(x1), MapearY(y1));
    //     x0 = MapearX(x0);
    //     y0 = MapearY(y1);
    //     x1 = MapearX(x1);
    //     y1 = MapearY(y1);

    //     sprintf(texto, "antigo: (%d, %d), novo: (%d, %d)", x0, y0, x1, y1);
    //     if(!(desenhadoFacil[x0][y0] && desenhadoFacil[x1][y1])){
    //         if(telaFacil[x0][y0] == telaFacil[x1][y1])
    //             desenhadoFacil[x0][y0] = desenhadoFacil[x1][y1] = true;
    //         else
    //             desenhadoFacil[x1][y1] = desenhadoFacil[x0][y0] = false;
    //     }
    //     primeiroClique = true;
    // }
      
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (200, 200); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Trabalho CG");
    Inicializa();
    glutDisplayFunc(Desenha); 
    glutMotionFunc(MousePressionado);
    glutMainLoop();
    return 0;   
}