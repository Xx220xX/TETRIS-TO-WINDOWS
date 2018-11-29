
char **alocarMatriz(int linhas, int colunas) {
    char **mat;
    int i;
    mat = (char **) calloc(linhas, sizeof(char *));//m pornteiros
    for (i = 0; i < linhas; i++)
        mat[i] = (char *) calloc(colunas, sizeof(char));//n elementos para os ponteiros
    return mat;
}

void liberar(char **m, int linhas) {
    int i;
    for (i = 0; i < linhas; i++)
        free(m[i]);
    free(m);
}

void printaMatriz(char **mat, int m, int n, int x0, int y0) {
    int i, j, b, x = x0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            textbackground(BLACK);
            b = mat[i][j];
            gotoxy(x, y0);
            if (b) {
                textbackground(LIGHTMAGENTA);
            }
            printf("%03d", b);
            x += 4;
        }
        x = x0;
        y0++;
    }

}

char fullLine(char *vet, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (!vet[i]) {
            return 0;
        }
    }
    return 1;
}

int completei(char **mat, int m, int n) {
    int i, k = 0;
    char linhas[5] = {0};
    for (i = 0; i < m && k < 5; ++i) {
        if (fullLine(mat[i], n)) {
            linhas[k++] = i;
        }
    }
    linhas[k] = -1;

    descerLinhas(mat, n, linhas);
    return k;
}

void girar(char **mat, char **buff, int ordem, char transposta) {
    int i, j;
    if (transposta == 2) {
        buff[0][0] = mat[0][0];//1=1
        buff[0][1] = mat[0][1];//2=2
        buff[0][2] = mat[2][2];//3=9
        buff[1][0] = mat[1][2];//4=6
        buff[1][1] = mat[1][1];//5=5
        buff[1][2] = mat[1][0];//6=4
        buff[2][0] = mat[2][0];//7=7
        buff[2][1] = mat[2][1];//8=8
        buff[2][2] = mat[0][2];//9=3

        return;
    }
    if (transposta == 3) {
        buff[0][0] = mat[2][0];//1=7
        buff[0][1] = mat[0][1];//2=2
        buff[0][2] = mat[0][2];//3=3
        buff[1][0] = mat[1][2];//4=6
        buff[1][1] = mat[1][1];//5=5
        buff[1][2] = mat[1][0];//6=4
        buff[2][0] = mat[0][0];//7=1
        buff[2][1] = mat[2][1];//8=8
        buff[2][2] = mat[2][2];//9=9
        return;
    }
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            if (transposta)
                buff[i][j] = mat[j][i];
            else
                buff[j][i] = mat[i][ordem - j - 1];
        }
    }
}

void descerLinhas(char **mat, int n, char *linhas) {
    int i, j;
    char *aux;

    for (j = 0; j < 5 && linhas[j] >= 0; j++) {
        for (i = 0; i < n; i++) {
            mat[linhas[j]][i] = 0;
        }
        for (i = linhas[j]; i > 0; i--) {
            aux = mat[i];
            mat[i] = mat[i - 1];
            mat[i - 1] = aux;
        }
    }
}