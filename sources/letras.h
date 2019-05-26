
#define SETA_DIREITA 77
#define SETA_ESQUERDA 75
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define ENTER 13

#define CARACTERE_CIMA_ESQUERDA "\xDA"
#define CARACTERE_CIMA_DIREITA "\xBF"
#define CARACTERE_BAIXO_ESQUERDA "\xC0"
#define CARACTERE_BAIXO_DIREITA "\xD9"
#define CARACTERE_BARRA_VERTICAL "\xB3"
#define CARACTERE_BARRA_HORIZONTAL "\xC4"

void espera(int ms) {
    long long int inicio = clock();
    long long int fim = clock();
    do {
        fim = clock();
    } while (fim - inicio < ms);
}

void fazerQuadrado(int x0, int y0, int largura, int altura) {
    int i = 0, j = 0;
    gotoxy(x0, y0);
    for (i = 0; i < largura; i++) {
        printf(CARACTERE_BARRA_HORIZONTAL);
    }
    gotoxy(x0, y0 + altura);
    for (i = 0; i < largura; i++) {
        printf(CARACTERE_BARRA_HORIZONTAL);
    }
    for (i = 0; i < altura; i++) {
        gotoxy(x0, y0 + i);
        printf(CARACTERE_BARRA_VERTICAL);
        gotoxy(x0 + largura, y0 + j++);
        printf(CARACTERE_BARRA_VERTICAL);
    }
    gotoxy(x0, y0);
    printf(CARACTERE_CIMA_ESQUERDA);
    gotoxy(x0 + largura, y0);
    printf(CARACTERE_CIMA_DIREITA);
    gotoxy(x0, y0 + altura);
    printf(CARACTERE_BAIXO_ESQUERDA);
    gotoxy(x0 + largura, y0 + altura);
    printf(CARACTERE_BAIXO_DIREITA);
}

void _OP(char opc[][30], int linhas, int x0, int y0, int comum, int corSel, int esp) {
    int i;
    for (i = 0; i < linhas; i++) {
        gotoxy(x0, y0);
        y0 += 2;
        if (i == esp) {
            textcolor(corSel);
            printf(" -> %s", opc[i]);
        } else {
            textcolor(comum);
            printf("%s    ", opc[i]);
        }
    }
}

void piscar(char opc[][30], int linhas, int x0, int y0, int comum, int brilhar, int esp) {
    int i, j;
    for (i = 0; i < linhas; i++) {

        if (i == esp) {
            for (j = 0; j < 4; j++) {
                gotoxy(x0, y0);
                textcolor(brilhar);
                printf("->%s<-", opc[i]);
                espera(70);
                gotoxy(x0, y0);
                textcolor(comum);
                printf("->%s<-", opc[i]);
            }
            return;

        }
        y0 += 2;
    }
}

char fazerMenu(char opcoes[][30], int linhas, int x0, int y0, int corComum, int corAtual, int corSelct) {
    int i = 0;
    char c;
    _OP(opcoes, linhas, x0, y0 + 1, corComum, corAtual, i);
    for (;;) {
        if (kbhit()) {
            c = getch();
            if (c == ENTER) {
                piscar(opcoes, linhas, x0, y0 + 1, corComum, corSelct, i);
                return i;
            }
            if (c == -32) {
                c = getch();
                switch (c) {
                    case SETA_BAIXO:
                        i = i == linhas - 1 ? 0 : i + 1;
                        break;
                    case SETA_CIMA:
                        i = i == 0 ? linhas - 1 : i - 1;
                        break;
                }
            }
            _OP(opcoes, linhas, x0, y0 + 1, corComum, corAtual, i);
        }
    }
}

void printaMario(int x0, int y0, char mario[][16][16], int olhar) {
    int i, j, x = x0, y = y0;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            gotoxy(x++, y);
            textbackground(mario[olhar][i][j]);
            printf(" ");
        }
        x = x0;
        y++;
    }
}

char fazerMenuMario(char opcoes[][30], int linhas, int x0, int y0, int corComum, int corAtual, int corSelct, int scrx,
                    int scry) {
    unsigned int t0, tf;
    int i, j, j2;


    char c, lado = 0, marioPresente = 0, F = FUNDO,
            M = BROWN,
            R = LIGHTRED,
            Y = YELLOW,
            W = WHITE,
            P = BLACK,
            B = LIGHTBLUE,
            mario[2][16][16] = {{
                                        {F, F, F, F, F, R, R, R, R, R, F, F, F, F, F, F},
                                        {F, F, F, F, R, R, R, R, R, R, R, R, R, F, F, F},
                                        {F, F, F, M, M, M, M, Y, Y, M, Y, F, F, F, F, F},
                                        {F, F, F, M, Y, M, Y, Y, Y, M, Y, Y, Y, F, F, F},
                                        {F, F, F, M, Y, M, M, Y, Y, Y, M, Y, Y, Y, F, F},
                                        {F, F, F, F, M, Y, Y, Y, Y, M, M, M, M, F, F, F},
                                        {F, F, F, F, F, Y, Y, Y, Y, Y, Y, F, F, F, F, F},
                                        {F, F, F, F, R, R, B, R, R, B, R, R, F, F, F, F},
                                        {F, F, F, R, R, R, B, R, R, B, R, R, R, F, F, F},
                                        {F, F, R, R, R, B, B, B, B, B, B, R, R, R, F, F},
                                        {F, F, Y, Y, R, B, Y, B, B, Y, B, R, Y, Y, F, F},
                                        {F, F, Y, Y, Y, B, B, B, B, B, B, Y, Y, Y, F, F},
                                        {F, F, Y, Y, B, B, B, B, B, B, B, B, Y, Y, F, F},
                                        {F, F, F, F, B, B, B, F, F, B, B, B, F, F, F, F},
                                        {F, F, F, M, M, M, F, F, F, F, M, M, M, F, F, F},
                                        {F, F, M, M, M, M, F, F, F, F, M, M, M, M, F, F}
                                },
                                {       0}};
    for (i = 0; i < 16; i++) {
        j2 = 15;
        for (j = 0; j < 16; j++) {
            mario[1][i][j] = mario[0][i][j2--];
        }
    }
    i = 0;
    _OP(opcoes, linhas, x0, y0 + 1, corComum, corAtual, i);
    t0 = clock();
    for (;;) {
        if (kbhit()) {
            c = getch();
            if (c == ENTER) {
                piscar(opcoes, linhas, x0, y0 + 1, corComum, corSelct, i);
               stopSound();
                return i;
            }
            if (c == ' ') {
                return 1;
            }
            if (c == -32) {
                c = getch();
                switch (c) {
                    case SETA_BAIXO:
                        i = i == linhas - 1 ? 0 : i + 1;
                        break;
                    case SETA_CIMA:
                        i = i == 0 ? linhas - 1 : i - 1;
                        break;
                }
            }
            _OP(opcoes, linhas, x0, y0 + 1, corComum, corAtual, i);
        }
        tf = clock();
        if (tf - t0 > 10000) {
            marioPresente = 1;
            playSound("mario.wav");
        }
        if (marioPresente) {
            if (tf - t0 >= 5000) {
                printaMario(2, scry - 17, mario, lado);
                printaMario(scrx - 17, scry - 17, mario, !lado);
                lado = !lado;
                t0 = clock();
            }
          
        }

    }
}
