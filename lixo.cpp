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
