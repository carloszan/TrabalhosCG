// Função que desenha um quadrado
void DesenhaQuadrado(void)
{
    int y = -75.0f;
    int x = -75.0f;
    for(int i = 0; i < 5;i++)
    {
        int aux_x = x, aux_y = y;
        for(int j = 0; j < 4; j++)
        {
            glBegin(GL_QUADS);
                glVertex2f(aux_x, y - 50.0f);
                glVertex2f(aux_x, y);
                glVertex2f(aux_x + 50.0f, y);               
                glVertex2f(aux_x + 50.0f, y - 50.0f);
            glEnd();
            aux_x += 50.0f;
        }
        y = y + 50.0f;
    }
}

     // Desenha uma primitiva     
    // switch (primitiva) {
    //     case QUADRADO:  DesenhaQuadrado();
    //                     break;
    //     case TRIANGULO: DesenhaTriangulo();                          
    //                     break;
    //     case LOSANGO:   DesenhaLosango();                       
    //                     break;
    // }



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

    void DesenhaTriangulo(void)
    {
         glBegin(GL_TRIANGLES);
                   glVertex2f(-25.0f, -25.0f);
                   glVertex2f(0.0f, 25.0f);
                   glVertex2f(25.0f, -25.0f);              
         glEnd();
    }

    void Inicializa (void)
    {   
        // Define a cor de fundo da janela de visualização como branca
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        win=100.0f;
        primitiva = QUADRADO;
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
        strcpy(texto, "(0,0)");
        
        CriaMenu();
        
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

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
           glutAttachMenu(GLUT_RIGHT_BUTTON);
         
    //glutPostRedisplay();
}