void finalizarMusica(Musica *m) {
    free(m->m.tempo);
    free(m->m.notas);
}

void iniciarMusica(Musica *m) {
    m->i = 0;
}

char readMlh(Mlh *m, char *nome) {
    FILE *f;
    char p[4], *pc;
    int tam = 0, i, *pI;
    f = fopen(nome, "r");
    if (!f || !gmConfig.sonsAtivos) {
        return 0;
    }
    pI = (int *) p;
    p[0] = fgetc(f);
    p[1] = fgetc(f);
    p[2] = fgetc(f);
    p[3] = fgetc(f);
    m->tamanho = *pI;

    tam = *pI * sizeof(int);

    m->notas = calloc(tam, 1);
    m->tempo = calloc(tam, 1);
    pc = (char *) m->notas;
    for (i = 0; i < tam; i++) {
        pc[i] = fgetc(f);
    }
    pc = (char *) m->tempo;
    for (i = 0; i < tam; i++) {
        pc[i] = fgetc(f);
    }
    if (fgetc(f) != '#') {
    }

    fclose(f);
    return 1;
}

void tocar(Musica *m) {
    Beep(m->m.notas[m->i], 1000 / m->m.tempo[m->i]);
    m->i++;
    if (m->i >= m->m.tamanho) {
        m->i = 0;
    }
}

void cairPeca(int beep) {
    Beep(beep, 75);
}

void somConfirm() {
    Beep(784, 150);
    Beep(831, 150);
}

void linhaCompleta(int linhas) {
    int i, x;
    x = 3000 / (linhas + 1);
    for (i = 0; i <= 3000; i += x) {
        Beep(i + linhas * linhas * linhas, 50);
        Sleep(50);
    }

}

void derrota() {
    int nota[] = {494, 523, 587, 880, 740, 880, 523, 494, 440
    };
    int tempo[] = {500, 300, 500, 800, 800, 800, 1000, 250, 250,};
    char pausa[] = {80, 80, 80, 80, 80, 80, 80, 40, 40};
    int n = 9;
    int i;
    for (i = 0; i < n; i++) {
        Beep(nota[i], tempo[i]);
        Sleep(pausa[i]);
    }
}

void derrota2() {
    int nota[] = {
            740, 659, 523,
            659, 784, 880, 659, 784, 740,
            784, 880, 659, 988, 880, 740, 659, 494,
    };
    int tempo[] = {250, 250, 600,
                   500, 500, 500, 500, 500, 500,
                   500, 400, 250, 600, 600, 400, 150, 600
    };
    char pausa[] = {20, 20, 100, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 10, 0, 0, 0};
    int n = 17;
    int i;
    for (i = 0; i < n; i++) {
        Beep(nota[i], tempo[i]);
        Sleep(pausa[i]);
    }
}
