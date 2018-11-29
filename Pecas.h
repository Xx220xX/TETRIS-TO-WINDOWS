#define   C1   LIGHTBLUE
#define   C2  LIGHTGREEN
#define   C3   YELLOW
#define   C4    MAGENTA
#define   C5   LIGHTCYAN
#define   C6   LIGHTRED
#define   C7   LIGHTGRAY

char PIPE[16] = {0, 0, 0, 0,
                 0, 0, 0, 0,
                 C1, C1, C1, C1,
                 0, 0, 0, 0
};
char SQUARE[4] = {C2, C2,
                  C2, C2
};

char ZLEFT[9] = {0, C3, C3,
                 C3, C3, 0,
                 0, 0, 0
};

char ZRIGHT[9] = {C4, C4, 0,
                  0, C4, C4,
                  0, 0, 0

};

char LRIGHT[9] = {0, C5, 0,
                  0, C5, 0,
                  0, C5, C5
};

char LLEFT[9] = {0, C6, 0,
                 0, C6, 0,
                 C6, C6, 0
};

char T[9] = {0, 0, 0,
             C7, C7, C7,
             0, C7, 0
};

void sorteiaPeca(Peca *p) {
    int aleatorio = rand() % 7 + 1;
    if (gmConfig.corAleatoria)
        p->cor = lcg_rand(&aleat)% 5 + 9 ;
    switch (aleatorio) {
        case 1:
            colocaModelo(p, PIPE, 4, 1);
            break;
        case 2:
            colocaModelo(p, SQUARE, 2, 0);
            break;
        case 3:
            colocaModelo(p, ZLEFT, 3, 2);
            break;
        case 4:
            colocaModelo(p, ZRIGHT, 3, 3);
            break;
        case 5:
            colocaModelo(p, LRIGHT, 3, 0);
            break;
        case 6:
            colocaModelo(p, LLEFT, 3, 0);
            break;
        case 7:
            colocaModelo(p, T, 3, 0);
            break;
        default:
            break;
    }
    p->i = -p->ordem;
    p->iA = p->i;
    p->j = 5;
    p->jA = 5;
}

void colocaModelo(Peca *peca, char *novaPeca, int ordem, char transposta) {
    int i, j, k = 0;
    peca->ordem = ordem;
    peca->i = 0 - ordem;
    peca->j = LARGURA / 2;
    peca->iA = 0 - ordem;
    peca->jA = LARGURA / 2;
    peca->girei = 0;
    peca->justT = transposta;
    for (i = 0; i < ordem; ++i) {
        for (j = 0; j < ordem; ++j) {
            if (novaPeca[k]) {
                if (gmConfig.corAleatoria) {
                    peca->m[i][j] = peca->cor;
                } else {
                    peca->m[i][j] = novaPeca[k];
                }
            } else {
                peca->m[i][j] = 0;
            }
            k++;
        }
    }
}
