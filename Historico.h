void salvarHistorico(Record *rec) {
    FILE *f;
    int i;
    f = fopen("hst.bin", "wb");

    for (i = 0; i < 10; i++) {
        if (rec[i].existe) {
            rec[i].existe = 1;
        }
    }
    i = fwrite(rec, sizeof(Record), 10, f);
    fclose(f);
}

void lerHistorico(Record *buf) {
    int i;
    FILE *f;
    f = fopen("hst.bin", "rb");
    if (!f) {
        return;
    }
    i = fread(buf, sizeof(Record), 10, f);
    fclose(f);
}

void remove_13(char *str) {
    int i = 0;
    for (; str[i] && i < 24; i++) {
        if (str[i] == '\n' || str[i] == 13) {
            str[i] = 0;
            return;
        }
    }
}

int mostrar(Record *at, int tmx, int tmy) {
    int i, y = 3, posi = -1;
    gotoxy(2, y);
    printf("NOME ");
    gotoxy(tmx / 6 - 2, y);
    printf("RANKING ");
    gotoxy(tmx / 4 - 2, y);
    printf("PONTUACAO");
    y += 3;
    for (i = 0; i < 10 && at[i].existe; i++) {
        switch (i) {
            case 0:
                textcolor(LIGHTCYAN);
                break;
            case 1:
                textcolor(YELLOW);
                break;
            case 2:
                textcolor(LIGHTRED);
                break;
            default:
                textcolor(WHITE);
                break;
        }
        if (at[i].existe == 3) {
            at[i].linhas = gmConfig.linhas;
            textcolor(LIGHTGREEN);
        }
        remove_13(at[i].nome);
        gotoxy(2, y);
        printf("                       ");
        gotoxy(2, y);
        printf("%s      ", at[i].nome);

        gotoxy(tmx / 6, y);
        printf("%d  %s", i + 1, at[i].trap ? " <-" : "   ");
        gotoxy(tmx / 4, y);
        printf("          ");
        gotoxy(tmx / 4 - 10, y);
        printf("%d Linhas", at[i].linhas);
        gotoxy(tmx / 4, y);
        printf("%d", at[i].pontos);
        if (at[i].existe == 3) {
            posi = i;
        }
        y += 2;
    }
    return posi;
}

int compara(Record a, Record b) {
    return (!!a.existe) * a.pontos - ((!!b.existe) * b.pontos);
}

void organizar(Record *buf) {
    Record aux = {0};
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i != j && compara(buf[i], buf[j]) > 0) {
                aux = buf[i];
                buf[i] = buf[j];
                buf[j] = aux;
            }
        }
    }
}

char ranking(int pnts, Record *at, int tmX, int tmY, char quebreiRecord) {

    if (quebreiRecord >= 0) {
        at[quebreiRecord].pontos = pnts;
        organizar(at);
        return mostrar(at, tmX, tmY);
    }

    if (at[9].existe == 0 || pnts > at[9].pontos) {
        at[9].nome[0] = 'V';
        at[9].nome[1] = 'O';
        at[9].nome[2] = 'C';
        at[9].nome[3] = 'E';
        at[9].nome[4] = '\0';
        at[9].existe = 3;
        at[9].pontos = pnts;
        organizar(at);
        return mostrar(at, tmX, tmY);;
    }

    return -1;
}
