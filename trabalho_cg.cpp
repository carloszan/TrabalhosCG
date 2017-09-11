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
                               
int sequencia[25] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0};


bool desenhadoSequencia[25] = {true, false, false, false, false, 
                                false, false, false, false, false, 
                                false, false, false, false, false, 
                                false, false, false, false, false, 
                                false, false, false, false, false };

// bool desenhadoSequencia[25] = {true, true, true, true, true, 
//     true, true, true, true, true, 
//     true, true, true, true, true, 
//     true, true, true, true, true, 
//     true, true, true, true, true };

// bool desenhadoFacil[3][4] = {{true, true, true, true},
//                              {true, true, true, true}, 
//                              {true, true, true, true}};
int x0, yo, x1, y1;
bool  primeiroClique;
int i0, j0, i1, j1;
bool memoriaFacil;
bool clicandoSequencia = false;
bool jogoSequencia = false;
int contadorSequencia = 1;
int contadorClique = 0;

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

void RandomizarSequencia()
{
    srand(time(NULL));
    for(int i = 0; i < 25; i++)
    {
        int numeroParaTrocar = rand() % 25;
        std::swap(sequencia[i], sequencia[numeroParaTrocar]);
    }
}

void DesenhaSequencia(GLfloat x, GLfloat y)
{
    glBegin(GL_QUADS);
        glVertex2f(x, y - 100.0f);
        glVertex2f(x, y);
        glVertex2f(x + 100.0f, y);
        glVertex2f(x + 100.0f, y - 100.0f);
    glEnd();
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

void DesenhaTelaSequencia(int i)
{
    GLfloat x = -win, y = win;

    if(i == 0){
        glColor3f(1.0f, 0.0f, 0.0f);
        DesenhaSequencia(x, y);
    }
    else if(i == 1){
        glColor3f(0.0f, 1.0f, 0.0f);
        DesenhaSequencia(x + 100, y);
    }
    else if(i == 2){
        glColor3f(0.0f, 0.0f, 1.0f);
        DesenhaSequencia(x, y - 100);
    }
    else if(i == 3){
        glColor3f(0.5f, 0.5f, 0.5f);
        DesenhaSequencia(x + 100, y - 100);
    }
    
}

void DesenharSequencia()
{
    for(int i = 0; i < contadorSequencia; i++){
        if(desenhadoSequencia[i]){
            DesenhaTelaSequencia(sequencia[i]);
            
        }
    }
    desenhadoSequencia[contadorSequencia] = true;
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
    
    if(jogoSequencia)
        DesenharSequencia();
    else if(memoriaFacil)
        DesenhaTelaFacil();
    else
        DesenhaTelaDificil();

    glutSwapBuffers();
}

void MenuPares(int op){
    jogoSequencia = false;
    if(op == 0){
        memoriaFacil = true;       
        Randomizar();
        for (int i = 0; i < 3; i++)
            for(int j = 0; j < 4; j++)
                desenhadoFacil[i][j] = false;
        Desenha();
    }
    else{
        memoriaFacil = false;
        Randomizar();
        for (int i = 0; i < 4; i++)
            for(int j = 0; j < 5; j++)
                desenhadoDificil[i][j] = false;
        Desenha();
    }
}
void MenuSequencia(int op){
    jogoSequencia = true;
    RandomizarSequencia();
    for (int i = 0; i < 25; i++)
        desenhadoSequencia[i] = false;
    Desenha();
}
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

int SequenciaMapear(int i, int j){
    if(i >= 0 && j >= 0) return 1;
    else if(i >= -100 && j >= 0) return 0;
    else if(i >= 0 && j >= -100) return 3;
    else if(i >= -100 && j >= -100) return 2;
}

void MousePressionado(int button, int state, int x, int y)
{   
    
    if(state == GLUT_DOWN){
    if(jogoSequencia){
        for(int i = 0; i < 25; i++)
            printf("%d ", sequencia[i]);
        printf("\n");
        if(clicandoSequencia == false)
            Desenha();
        short clique = SequenciaMapear(TransformaX(x),TransformaY(y)); // 0..3
        if(clique == sequencia[contadorClique]){
            if(contadorClique == contadorSequencia){
                printf("acertou %d", contadorSequencia);
                Desenha();
                contadorClique++;
            }
            else{
                DesenhaTelaSequencia(clique);
            }
        }
        else{
            contadorClique = 0;
            //RandomizarSequencia();
            DesenharSequencia();
            clicandoSequencia = true;
            contadorSequencia = 1;
            contadorClique = 1;
            for(int i = 1; i < 25; i++)
                desenhadoSequencia[i] = false;
        }
    }
    else{
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

        Desenha();
    
    }
    printf("\n");
    glutPostRedisplay();
    }}
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (200, 200); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Trabalho CG");
    Inicializa();
    //glutDisplayFunc(Desenha); 
    glutMouseFunc(MousePressionado);
    glutMainLoop();
    return 0;   
}