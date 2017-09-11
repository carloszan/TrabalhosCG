#include <GL/glut.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

GLfloat win;

int telaFacil[3][4] = {{1, 1, 2, 2}, {3, 3, 4, 4}, {5, 5, 6, 6}};
bool desenhadoFacil[3][4] = {{false, false, false, false},
                             {false, false, false, false}, 
                             {false, false, false, false}};

int telaDificil[4][5] = {{1, 1, 2, 2, 3}, {3, 4, 4, 5, 5}, {6, 6, 7, 7, 8}, {8, 9, 9, 10, 10}};
// bool desenhadoDificil[4][5] = {{true, true, true, true, true},
//                                {true, true, true, true, true}, 
//                                {true, true, true, true, true},
//                                {true, true, true, true, true}};

bool desenhadoDificil[4][5] = {{false, false, false, false, false},
                               {false, false, false, false, false}, 
                               {false, false, false, false, false},
                               {false, false, false, false, false}};                        

// bool desenhadoFacil[3][4] = {{true, true, true, true},
//                              {true, true, true, true}, 
//                              {true, true, true, true}};
int x0, yo, x1, y1;
bool  primeiroClique;
int i0, j0, i1, j1;
bool memoriaFacil; 

void Randomizar()
{
    int linha, coluna;
    if(memoriaFacil){ linha = 3; coluna = 4; }
    else {linha = 4; coluna = 5; }
    
    srand(time(NULL));
    for(int i = 0; i < linha; i++)
    {
        for(int j = 0; j < coluna; j++)
        {
            int linhaParaTrocar = rand() % linha;
            int colunaParaTrocar = rand() % coluna;
            if(memoriaFacil)
                std::swap(telaFacil[i][j], telaFacil[linhaParaTrocar][colunaParaTrocar]);
            else
                std::swap(telaDificil[i][j], telaDificil[linhaParaTrocar][colunaParaTrocar]);
        }
    }
}

void DesenhaLosango(GLfloat x, GLfloat y)
{
    glBegin(GL_QUADS);
        glVertex2f(x, y - 25.0f);
        glVertex2f(x + 20.0f, y);
        glVertex2f(x + 40.0f, y - 25.0f);
        glVertex2f(x + 20.0f, y - 50.0f);
    glEnd();
}

void DesenhaQuadrado(GLfloat x, GLfloat y)
{
    if(memoriaFacil){
        glBegin(GL_QUADS);
            glVertex2f(x, y - 66.3f);
            glVertex2f(x, y);
            glVertex2f(x + 50.0f, y);
            glVertex2f(x + 50.0f, y - 66.3f);
        glEnd();
    }
    else{
        glBegin(GL_QUADS);
            glVertex2f(x, y - 50.0f);
            glVertex2f(x, y);
            glVertex2f(x + 40.0f, y);
            glVertex2f(x + 40.0f, y - 50.0f);
        glEnd();
    }
}

// Função que desenha um triângulo
void DesenhaTriangulo(GLfloat x, GLfloat y)
{
    if(memoriaFacil){
        glBegin(GL_TRIANGLES);
            glVertex2f(x, y - 66.7f);
            glVertex2f(x + 25.0f, y);
            glVertex2f(x + 50.0f, y - 66.7f);              
        glEnd();
    }
    else{
        glBegin(GL_TRIANGLES);
            glVertex2f(x, y - 50.0f);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 40.0f, y - 50.0f);              
        glEnd();
    }
}

// a - I
// b - J
void DesenhaTelaFacil()
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

void DesenhaTelaDificil()
{
    GLfloat x = -win, y = win; 
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(telaDificil[i][j] == 1 && desenhadoDificil[i][j] == true){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaDificil[i][j] == 2 && desenhadoDificil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaDificil[i][j] == 3 && desenhadoDificil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 1.0f);
                DesenhaQuadrado(x, y);
            }
            if(telaDificil[i][j] == 4 && desenhadoDificil[i][j] == true){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaTriangulo(x, y);
            }
            if(telaDificil[i][j] == 5 && desenhadoDificil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaTriangulo(x, y);
            }
            if(telaDificil[i][j] == 6 && desenhadoDificil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 0.0f);
                DesenhaTriangulo(x, y);
            }
            if(telaDificil[i][j] == 7 && desenhadoDificil[i][j] == true){
                // azul
                glColor3f(0.0f, 0.0f, 1.0f);
                DesenhaLosango(x, y);
            }
            if(telaDificil[i][j] == 8 && desenhadoDificil[i][j] == true){
                // vermelho
                glColor3f(1.0f, 0.0f, 0.0f);
                DesenhaLosango(x, y);
            }
            if(telaDificil[i][j] == 9 && desenhadoDificil[i][j] == true){
                // verde
                glColor3f(0.0f, 1.0f, 0.0f);
                DesenhaLosango(x, y);
            }
            if(telaDificil[i][j] == 10 && desenhadoDificil[i][j] == true){
                // cinza
                glColor3f(0.5f, 0.5f, 0.5f);
                DesenhaLosango(x, y);
            }
            x += 40.0f;
        }
        x = -win;
        y -= 50.0f;
    }
}   


void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    
    if(memoriaFacil)
        DesenhaTelaFacil();
    else
        DesenhaTelaDificil();

    glutSwapBuffers();
}

void MenuPares(int op){
    if(op == 0){
        memoriaFacil = true;        
        Randomizar();
        Desenha();
    }
    else{
        memoriaFacil = false;
        Randomizar();
        Desenha();
    }
}
void MenuSequencia(int op){}
void MenuPrincipal(int op)
{
    if(op == 0)
        glutDestroyWindow(win);
        exit(0);
}

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

void Inicializa (void) 
{
    win = 100.0f;
    //define a cor de background da janela
    glClearColor (1.0, 1.0, 1.0, 0.0);
    primeiroClique = true;
    memoriaFacil = true;

    Desenha();
    CriaMenu();

    // printar a matriz
    // for(int i = 0; i < 3; i++) {
    //     for(int j = 0; j < 4; j++)
    //         printf("(%d)", telaFacil[i][j]);
    //     printf("\n");    
    // }

    
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

// recebe X
int MapearParaMatrizJ(int i)
{
    if(memoriaFacil){
        if(i >= 50) return 3;
        else if (i >= 0) return 2;
        else if(i >= -50) return 1;
        else return 0;
    }
    else{
        if(i >= 60) return 4;
        else if (i >= 20) return 3;
        else if(i >= -20) return 2;
        else if(i >= -60) return 1;
        else return 0;
    }
}

// recebe Y
int MapearParaMatrizI(int j)
{
    if(memoriaFacil){
        if(j >= 33.3) return 0;
        else if(j >= -33.7) return 1;
        else return 2;
    }
    else{
        if(j >= 50) return 0;
        else if(j >= 0) return 1;
        else if(j >= -50) return 2;
        else return 3;
    }
}

void MousePressionado(int button, int state, int x, int y)
{   
    if(state == GLUT_DOWN){
    // printf("P: (%d, %d) -> (%d, %d)", x, y, TransformaX(x), TransformaY(y));
    // printf("M: (%d, %d)\n", MapearParaMatrizI(TransformaY(y)), MapearParaMatrizJ(TransformaX(x)));
    if(primeiroClique){
        x0 = TransformaX(x);
        yo = TransformaY(y);
        i0 = MapearParaMatrizI(yo);
        j0 = MapearParaMatrizJ(x0);
        
        if(memoriaFacil){
            if(desenhadoFacil[i0][j0])
                return;
            desenhadoFacil[i0][j0] = true;
        }
        else{
            if(desenhadoDificil[i0][j0])
                return;
            desenhadoDificil[i0][j0] = true;
        }
        Desenha();

        primeiroClique = false;
        printf("esperando segunda jogada");  
    }
    else{
        x1 = TransformaX(x);
        y1 = TransformaY(y);

        j1 = MapearParaMatrizJ(x1);
        i1 = MapearParaMatrizI(y1);

        if(memoriaFacil){
            if(desenhadoFacil[i1][j1]){
                desenhadoFacil[i0][j0] = true;
                Desenha();
                return;            
            }
            desenhadoFacil[i1][j1] = true;
        }
        else{
            if(desenhadoDificil[i1][j1]){
                desenhadoDificil[i0][j0] = true;
                Desenha();
                return;            
            }
            desenhadoDificil[i1][j1] = true;
        }
        Desenha();
        glFlush();
        sleep(1);
        

        // se os dois já não estiverem desenhados
        if(memoriaFacil){
            if(telaFacil[i0][j0] != telaFacil[i1][j1])
                desenhadoFacil[i0][j0] = desenhadoFacil[i1][j1] = false;
        }
        else{
            if(telaDificil[i0][j0] != telaDificil[i1][j1])
                desenhadoDificil[i0][j0] = desenhadoDificil[i1][j1] = false;
        }
        primeiroClique = true;
    }
    printf("\n");
    glutPostRedisplay();
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (200, 200); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Trabalho CG");
    Inicializa();
    glutDisplayFunc(Desenha); 
    glutMouseFunc(MousePressionado);
    glutMainLoop();
    return 0;   
}