#include"Object.h"
#include <tchar.h>
#include <urlmon.h>

void editaCursor(char ativo, int tamanho) {
    HANDLE meuCmd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorDaTela;
    cursorDaTela.dwSize = tamanho;
    cursorDaTela.bVisible = ativo;
    SetConsoleCursorInfo(meuCmd, &cursorDaTela);
}
void requisitos(){
	FILE *f ;
	char esc =0 ;
	HRESULT down;
  	LPCTSTR Url,File;
	int i,flag=0;
	char links[11][300] = {"http://download1347.mediafire.com/68jwf8axd8pg/o1h6oedd28ad4s4/mario.wav",
					"http://download1474.mediafire.com/5532u4ym86vg/w3jif6lyo39e2vq/pacman.wav",
					"http://download939.mediafire.com/khajcay4ul9g/mac8di459eh3kxs/bet.wav",
					"http://download1655.mediafire.com/y4t7a6k78e4g/p4374ggi45c5nnc/pacman1.bin",
					"http://download1082.mediafire.com/a1mo54sw3edg/lnbjupofdfxlepg/pacman2.bin",
					"http://download2267.mediafire.com/1x78y4ek6cog/9i4o76i8h3q0hux/pacman3.bin",
					"http://download2261.mediafire.com/8p7j1f0chkrg/s047b5ris48b7ss/pacman4.bin",
					"http://download2260.mediafire.com/2umcva7cvpmg/k48s8k28dyq263l/pacman5.bin",
					"http://download2261.mediafire.com/dagdp083qwng/ix7cfmj7llp5psf/peca1.bin",
					"http://download2262.mediafire.com/rqt5g9tpa9vg/uq52i693p60iiu5/peca2.bin",
					"http://download1482.mediafire.com/9bop4z8kkxzg/h678lretxaevmkt/peca3.bin"};
	char files[11][30] = {"mario.wav",
					"pacman.wav",
					"bet.wav",
					"pacman1.bin",
					"pacman2.bin",
					"pacman3.bin",
					"pacman4.bin",
					"pacman5.bin",
					"peca1.bin",
					"peca2.bin",
					"peca3.bin"					
					};
	for(i=0;i<11;i++){
		f =  fopen(files[i],"r");
		if(!f){
			flag=1;
			break;
		}
		fclose(f);
	}
		if(!flag)return;
	
		printf("baixar os arquivos necessarios para rodar esse programa?\n [S] para sim\n [N] para nao\n   :");
		scanf("%c",&esc);
		switch(esc){
			case 's':
			case 'S':
				printf("por favor espere...\n");
				for(i = 0 ;i<11;i++){
					printf("donwload %d of 11 ... ",i+1);
					Url = _T(links[i]);
					File = _T(files[i]);
					f =  fopen(files[i],"r");
					if(!f)
					down = URLDownloadToFileA(NULL, Url, File, 0, NULL);
					else fclose(f);
					if(!down){
						textcolor(GREEN);
 						printf("SUCCESS\n");
					}else{
						textcolor(RED);
		 				printf("FAILED!!");
					}
					textcolor(WHITE);
				}
			break;
			default:
				exit(0);
					
				
		}
	
	
	
	

}
int main() {
    gmConfig.sizeBlock = 3;
    style = 2;
    printa = _4D;
    SetConsoleTitleA("          TETRIS");
    editaCursor(0, 1);
    Record atualR[10] = {0};
    int scrxT = 175, scryT = 99, nextX0 = scrxT * 2 / 3.0 + 3, nextY0 = 2;
    requisitos();
    gmConfig.rec = atualR;
    for (;;) {
        switch (telaInicial(&gmConfig, &scrxT, &scryT, &nextX0, &nextY0)) {
            case 0:
                jogo(atualR, &scrxT, &scryT, &nextX0, &nextY0);
                gmConfig.nivel = 0;
                break;
            case 1:
                nivel(scrxT, scryT);
                break;
            case 2:
                menuConfig(&gmConfig, &scrxT, &scryT);
                break;
            case 3:
                system("cls");
                printf("AINDA NAO FOI FINALIZADO");
                getch();
                break;
            case 4:
                return 0;
        }
    }
}

void nivel(int tmx, int tmy) {
    char titulo[9] = "NIVEL    ";

    char escolha, opcoes[4][30] = {{"AUMENTAR NIVEL"},
                                   {"DIMINUIR NIVEL"},
                                   {"DIGITAR NIVEL           "},
                                   {"VOLTAR"}};
    titulo[6] = gmConfig.nivel / 10 + 48;
    titulo[7] = gmConfig.nivel % 10 + 48;
    titulo[8] = 0;
    for (;;) {
        textcolor(WHITE);
        telinha(titulo, 14, tmx, tmy);
        escolha = fazerMenu(opcoes, 4, tmx / 3 + 1, tmy / 3 + 1, YELLOW, LIGHTRED, WHITE);
        switch (escolha) {
            case 0:
                gmConfig.nivel = gmConfig.nivel < 30 ? gmConfig.nivel + 1 : gmConfig.nivel;
                titulo[6] = gmConfig.nivel / 10 + 48;
                titulo[7] = gmConfig.nivel % 10 + 48;
                titulo[8] = 0;
                break;
            case 1:
                gmConfig.nivel = gmConfig.nivel > 0 ? gmConfig.nivel - 1 : gmConfig.nivel;
                titulo[6] = gmConfig.nivel / 10 + 48;
                titulo[7] = gmConfig.nivel % 10 + 48;
                titulo[8] = 0;
                break;
            case 2:
                gotoxy(tmx / 3 + 21, tmy / 3 + 6);
                editaCursor(1, 50);
                scanf("%d", &gmConfig.nivel);
                gmConfig.nivel = gmConfig.nivel < 0 ? -gmConfig.nivel : gmConfig.nivel;
                if (gmConfig.nivel > 30) {
                    gmConfig.nivel = gmConfig.nivel % 31;
                }
                editaCursor(0, 50);
                titulo[6] = gmConfig.nivel / 10 + 48;
                titulo[7] = gmConfig.nivel % 10 + 48;
                titulo[8] = 0;
                break;
            case 3:
                textcolor(WHITE);
                return;
        }
    }
}

void _1(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd) {
    int i, j, x = x0, y = y0;
    int l,l2;
    if (*modifiquei == 0) {
        return;
    }
    textcolor(WHITE);

    *modifiquei = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] && mat[i][j]!=-5) {
                if (mat[i][j] == -1) {
                    textbackground(FUNDO);
                } else {
                    textbackground(mat[i][j]);
                }

                for(l=0;l<gmConfig.sizeBlock-1;l++){
                    for(l2=0;l2<gmConfig.sizeBlock-1;l2++){
                        gotoxy(x+l2, y+l);
                        printf(" ");
                    }}

            } else if (mostraTd) {
                textbackground(FUNDO);
                for(l=0;l<gmConfig.sizeBlock-1;l++){
                    for(l2=0;l2<gmConfig.sizeBlock-1;l2++){
                        gotoxy(x+l2, y+l);
                        printf(" ");
                    }
                }


            }
            x += gmConfig.sizeBlock;

        }
        y += gmConfig.sizeBlock;
        x = x0;
    }
}

void _2(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd) {
    int i, j, x = x0, y = y0;
    if (*modifiquei == 0) {
        return;
    }
    textcolor(WHITE);
    *modifiquei = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j]) {
                textbackground(FUNDO);
                if (mat[i][j] == -1) {
                    textcolor(FUNDO);
                } else if (mat[i][j] > 0) {
                    textcolor(mat[i][j]);
                } else {
                    textcolor(WHITE);
                }
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);


            } else if (mostraTd) {
                textcolor(FUNDO);
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);

            }
            x += gmConfig.sizeBlock;

        }
        y += gmConfig.sizeBlock;
        x = x0;
    }
    textcolor(WHITE);
}

void _3(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd) {
    int i, j, x = x0, y = y0;
    if (*modifiquei == 0) {
        return;
    }
    textcolor(WHITE);
    textbackground(FUNDO);
    *modifiquei = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] && mat[i][j] != -5) {
                if (mat[i][j] == -1) {
                    textcolor(FUNDO);
                } else {
                    textcolor(mat[i][j]);
                }
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);
                if (mat[i][j] == -1) {
                    textbackground(FUNDO);
                } else {
                    textbackground(mat[i][j]);
                }
                fazerQuadrado(x + 1, y + 1, 1, 1);
                textbackground(FUNDO);
                textcolor(WHITE);

            } else if (mostraTd) {
                textcolor(FUNDO);
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);
                textbackground(mat[i][j]);
                fazerQuadrado(x + 1, y + 1, 1, 1);
                textbackground(FUNDO);

            }
            x += gmConfig.sizeBlock;

        }
        y += gmConfig.sizeBlock;
        x = x0;
    }
    textcolor(WHITE);
}
void _4D(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd) {
    int i, j, x = x0, y = y0,l,l2;
    if (*modifiquei == 0) {
        return;
    }
    textcolor(WHITE);
    textbackground(FUNDO);
    *modifiquei = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] && mat[i][j] != -5) {
                if (mat[i][j] == -1) {
                    textcolor(FUNDO);
                } else {
                    textcolor(mat[i][j]);
                }
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);
                if (mat[i][j] == -1) {
                    textbackground(FUNDO);
                } else {
                    textbackground(mat[i][j]);
                }
                fazerQuadrado(x, y ,gmConfig.sizeBlock-2 , gmConfig.sizeBlock-2);
                for(l=0;l<gmConfig.sizeBlock-2;l++){
                    for(l2=0;l2<gmConfig.sizeBlock-2;l2++){
                        gotoxy(x+l2, y+l);
                        printf(" ");
                    }}
                textbackground(FUNDO);
                textcolor(WHITE);

            } else if (mostraTd) {
                textcolor(FUNDO);
                fazerQuadrado(x, y, gmConfig.sizeBlock-1, gmConfig.sizeBlock-1);
                textbackground(mat[i][j]);
                fazerQuadrado(x , y, gmConfig.sizeBlock-2 , gmConfig.sizeBlock-2);
                for(l=0;l<gmConfig.sizeBlock-2;l++){
                    for(l2=0;l2<gmConfig.sizeBlock-2;l2++){
                        gotoxy(x+l2, y+l);
                        printf(" ");
                    }}
                textbackground(FUNDO);

            }
            x += gmConfig.sizeBlock;

        }
        y += gmConfig.sizeBlock;
        x = x0;
    }
    textcolor(WHITE);
}

void preparaMostra(Peca *minhaPeca, char **_controle, char **_coloca, char **_mostra, int m, int n) {
    int i, j, k,
            ip = minhaPeca->i < 0 ? -minhaPeca->i : 0,
            jp = minhaPeca->j < 0 ? -minhaPeca->j : 0, colar = 0,
            iPA = minhaPeca->iA < 0 ? -minhaPeca->iA : 0,
            jPA = minhaPeca->jA < 0 ? -minhaPeca->jA : 0, colarA = 0;
    for (i = 0; i < m; i++) {

        if (i >= minhaPeca->i && i < minhaPeca->i + minhaPeca->ordem) {
            colar = 1;
            jp = minhaPeca->j < 0 ? -minhaPeca->j : 0;
        } else {
            colar = 0;
        }
        if (i >= minhaPeca->iA && i < minhaPeca->iA + minhaPeca->ordem) {
            colarA = 1;
            jPA = minhaPeca->jA < 0 ? -minhaPeca->jA : 0;
        } else {
            colarA = 0;
        }
        for (j = 0; j < n; j++) {
            _coloca[i][j] = _controle[i][j];
            if (_mostra[i][j] == -5) {
                _coloca[i][j] = LIMPAR;
            }
            _mostra[i][j] = 0;
            if (colarA && j >= minhaPeca->jA) {
                if (j < minhaPeca->jA + minhaPeca->ordem) {
                    if (minhaPeca->m[iPA][jPA]) {//
                        _coloca[i][j] = LIMPAR;
                    }
                    jPA++;
                }
            }
            if (colar && j >= minhaPeca->j) {
                if (j < minhaPeca->j + minhaPeca->ordem) {
                    if (minhaPeca->girei && minhaPeca->mg[ip][jp]) {
                        _coloca[i][j] = LIMPAR;
                    }
                    if (minhaPeca->m[ip][jp]) {
                        _coloca[i][j] = minhaPeca->m[ip][jp];
                    }
                    jp++;

                }
            }
            _mostra[i][j] = _coloca[i][j] == _controle[i][j] ? 0 : _coloca[i][j];
            if (_mostra[i][j] > 0) {
                _controle[i][j] = _mostra[i][j];
            } else {
                _controle[i][j] = _coloca[i][j] <= LIMPAR ? 0 : _coloca[i][j];
            }
        }
        jp = minhaPeca->j < 0 ? -minhaPeca->j : 0;
        jPA = minhaPeca->jA < 0 ? -minhaPeca->jA : 0;
        if (colar)
            ip++;
        if (colarA)
            iPA++;
    }

    minhaPeca->girei = 0;
    minhaPeca->iA = minhaPeca->i;
    minhaPeca->jA = minhaPeca->j;
    k = hardDrop(_controle, minhaPeca);
    if (k > 0) {
        for (i = minhaPeca->i + k, ip = 0; ip < minhaPeca->ordem; i++, ip++) {
            for (j = minhaPeca->j, jp = 0; jp < minhaPeca->ordem; jp++, j++) {
                if (i < ALTURA && j < LARGURA && j >= 0 && i >= 0 && minhaPeca->m[ip][jp] > 0) {
                    if (_controle[i][j]) {
                        return;
                    }
                }
            }
        }
        if (k > 0) {
            for (i = minhaPeca->i + k, ip = 0; ip < minhaPeca->ordem; i++, ip++) {
                for (j = minhaPeca->j, jp = 0; jp < minhaPeca->ordem; jp++, j++) {
                    if (i < ALTURA && j < LARGURA && j >= 0 && i >= 0 && minhaPeca->m[ip][jp] > 0) {
                        _mostra[i][j] = -5;

                    }
                }
            }
        }
    }
}

void tetrisBegin(Peca *p, Peca *p2) {
    semente(&aleat, time(NULL));
    srand(time(NULL));
    p->m = alocarMatriz(4, 4);
    p->mg = alocarMatriz(4, 4);
    p2->m = alocarMatriz(4, 4);
    p2->mg = alocarMatriz(4, 4);
    controle = alocarMatriz(ALTURA, LARGURA);
    coloca = alocarMatriz(ALTURA, LARGURA);
    mostra = alocarMatriz(ALTURA, LARGURA);
}

void tetrisFinish(Peca *p, Peca *p2) {
    liberar(controle, ALTURA);
    liberar(coloca, ALTURA);
    liberar(mostra, ALTURA);
    liberar(p->m, 4);
    liberar(p->mg, 4);
    liberar(p2->m, 4);
    liberar(p2->mg, 4);
}

int hardDrop(char **posi, Peca *at) {
    int i, j, l, ip, jp = 0, max = ALTURA, atual = 0, pode = 0;
    if (at->i < 0 && at->i + at->ordem - 1 < 0) {
        return 0;
    }
    j = at->j < 0 ? 0 : at->j;
    jp = at->j < 0 ? -at->j : 0;
    for (; j < LARGURA && j < at->j + at->ordem; j++, jp++) {
        ip = at->ordem - 1;
        for (i = at->i + at->ordem - 1; i >= at->i && i >= 0; i--, ip--) {
            if (at->m[ip][jp]) {
                for (l = i; l < ALTURA; l++) {
                    if (l + 1 == ALTURA) {
                        atual = l - i;
                        if (atual < max) {
                            max = atual;
                        }
                        continue;
                    }
                    if (posi[l + 1][j]) {
                        atual = l - i;
                        if (atual < max) {
                            max = atual;
                        }
                        if (max == 0) {
                            return 0;
                        }
                    } else if (!pode) {
                        pode = 1;
                    }
                }
                break;
            }
        }
    }
    if (!pode) {
        return 0;
    }
    return max;
}

int possoIrB(char **posi, Peca *at) {
    int i, j, ip, jp = 0;
    j = at->j < 0 ? 0 : at->j;
    jp = at->j < 0 ? -at->j : 0;
    if (at->i < 0 && at->i + at->ordem - 1 < 0) {
        for (; j < LARGURA && jp < at->ordem; j++) {

            if (posi[0][j]) {
                return -1;
            }
            jp++;
        }
        return 1;
    }

    j = at->j < 0 ? 0 : at->j;
    jp = at->j < 0 ? -at->j : 0;
    for (; j < LARGURA && j < at->j + at->ordem; j++) {
        ip = at->ordem - 1;
        for (i = at->i + at->ordem - 1; i >= at->i && i >= 0; i--) {
            if (at->m[ip][jp]) {
                if (i + 1 >= ALTURA || posi[i + 1][j]) {
                    return 0;
                }
                break;
            }
            ip--;
        }
        jp++;
    }
    return 1;
}

void jogo(Record *atualR, int *scrxT, int *scryT, int *nextX0, int *nextY0) {
    unsigned int t0, tf, tmp = 600;
    int max, pnts = 0, pnts0 = 0, nivel = gmConfig.nivel;
    char modifiquei = 1, c = 0, sair = 1, travou = 0, escol, mexi = 0, quebreiRecord = -1;
    char **mat_aux;
	ajuste(&tmp, nivel);
    gmConfig.corAleatoria = 0;
    gmConfig.linhas = 0;
    system("cls");
    Peca atual, proxima, aux;
    tetrisBegin(&atual, &proxima);
    sorteiaPeca(&atual);
    sorteiaPeca(&proxima);
    nextBlock(&proxima, *nextX0, *nextY0);
    fazerTelaGame(atualR, *nextX0, *nextY0, *scrxT, *scryT);
    gotoxy((*scrxT / 4) * 3 + 2, 4);
    printf("Nivel     : %d", nivel);
    gotoxy((*scrxT / 4) * 3 + 2, 5);
    printf("pontuacao : %d", pnts);
    t0 = clock();
    playSound("bet.wav");
    for (; sair > 0;) {
        tf = clock();
        if (kbhit()) {
            c = getch();
            if (c == -32) {
                c = getch();
                switch (c) {
                    case SETA_BAIXO:
                        c = 's';
                        break;
                    case SETA_CIMA:
                        c = 'g';
                        break;
                    case SETA_DIREITA:
                        c = 'd';
                        break;
                    case SETA_ESQUERDA:
                        c = 'a';
                        break;
                    default :
                        break;
                }
            }
            switch (c) {
                case ' ':
                    escol = pauseTela(&gmConfig, scrxT, scryT);
                    playSound("bet.wav");
                    if (escol) {
                        sair = -5;
                        break;
                    }
                    *nextX0 = *scrxT * 2 / 3.0 + 3;
                    *nextY0 = 2;
                    system("cls");
                    fazerTelaGame(atualR, *nextX0, *nextY0, *scrxT, *scryT);
                    nextBlock(&proxima, *nextX0, *nextY0);
                    modifiquei = 1;
                    printa(controle, ALTURA, LARGURA, *scrxT / 3 + 1, 2, &modifiquei, 0);
                    break;
                case 'g':
                    girar(atual.m, atual.mg, atual.ordem, atual.justT);
                    if (virar(&atual, controle)) {
                        mat_aux = atual.mg;
                        atual.mg = atual.m;
                        atual.m = mat_aux;
                        atual.girei = 1;
                        modifiquei = 1;
                        mexi = 2;
                    }
                    break;
                case 'w':
                    atual.iA = atual.i;
                    atual.i--;
                    modifiquei = 1;
                    mexi = 1;
                    break;
                case 's':
                    travou = possoIrB(controle, &atual);
                    if (travou > 0) {
                        atual.iA = atual.i;
                        atual.i++;
                        modifiquei = 1;
                        mexi = 1;
                        travou = 0;
                    } else if (travou == 0) {
                        travou = 1;
                        mexi = 1;
                    }
                    break;
                case 'z':
                case 'h':
                    max = hardDrop(controle, &atual);
                    if (max > 0) {
                        atual.iA = atual.i;
                        atual.i += max;
                        modifiquei = 1;
                        mexi = 1;
                        travou = 1;
                    }
                    break;
                case 'a':
                    if (possoIrEsq(controle, &atual)) {
                        atual.jA = atual.j;
                        atual.j--;
                        modifiquei = 1;
                        mexi = 1;
                    }
                    break;
                case 'd':
                    if (possoIrDir(controle, &atual)) {
                        atual.jA = atual.j;
                        atual.j++;
                        modifiquei = 1;
                        mexi = 1;
                    }
                    break;
                case 'q':
                    sair = 0;
                    break;
                default:
                    break;
            }

        }
        if (tf - t0 > tmp && !mexi) {
            travou = possoIrB(controle, &atual);
            if (travou > 0) {
                atual.iA = atual.i;
                atual.i++;
                modifiquei = 1;
                travou = 0;
            } else if (travou == 0) {
                travou = 1;
            }
            t0 = clock();
        }
        preparaMostra(&atual, controle, coloca, mostra, ALTURA, LARGURA);
        printa(mostra, ALTURA, LARGURA, *scrxT / 3 + 1, 2, &modifiquei, 0);
        if (mexi && mexi != 2 && nivel > 26) {
            t0 = clock();
        }
        mexi = 0;
        if (travou < 0) {
            sair = 0;
            continue;
        } else if (travou) {
            travou = completei(controle, ALTURA, LARGURA);
            aux = atual;
            atual = proxima;
            proxima = aux;
            textbackground(FUNDO);
            sorteiaPeca(&proxima);
            nextBlock(&proxima, *nextX0, *nextY0);
            if (travou) {
                gmConfig.linhas += travou;
               nivel =gmConfig.nivel+ gmConfig.linhas/10;
               if(nivel>30){
               	nivel = 30;
			   }
                linhaCompleta(travou);
                pnts += (nivel + 1) *
                        (93.333333333333 * travou * travou * travou - 490 * travou * travou + 876.6666667 * travou -
                         440);
                ajuste(&tmp, nivel);
                gotoxy((*scrxT / 4) * 3 + 2, 4);
                printf("Nivel     : %d", nivel);
                gotoxy((*scrxT / 4) * 3 + 2, 5);
                printf("pontuacao : %d", pnts);
                quebreiRecord = ranking(pnts, atualR, *scrxT, *scryT, quebreiRecord);
                modifiquei = 1;
                printa(controle, ALTURA, LARGURA, *scrxT / 3 + 1, 2, &modifiquei, 1);
            }
            travou = 0;
        }
    }
    //evolucao diferencial
    stopSound();
    tetrisFinish(&atual, &proxima);
    textbackground(FUNDO);
    salvarJogo(atualR, *scrxT, *scryT);
    textcolor(FUNDO);
}

char possoIrEsq(char **posi, Peca *at) {
    int i = at->i, j, ip = 0, jp;
    for (; ip < at->ordem; i++, ip++) {
        jp = 0;
        j = at->j;
        for (; jp < at->ordem; j++, jp++) {
            if (at->m[ip][jp]) {
                if (i < 0) {
                    if (j - 1 < 0) {
                        return 0;
                    }
                    break;
                } else if (j - 1 < 0 || posi[i][j - 1]) {
                    return 0;
                }
                break;
            }
        }
    }

    return 1;
}

char possoIrDir(char **posi, Peca *at) {
    int i = at->i, j, ip = 0, jp;

    for (; ip < at->ordem; i++, ip++) {
        j = at->j + at->ordem - 1;
        jp = at->ordem - 1;
        for (; jp >= 0; jp--, j--) {
            if (at->m[ip][jp]) {
                if (i < 0) {
                    if (j + 1 >= LARGURA) {
                        return 0;
                    }
                } else if (j < 0 || j + 1 >= LARGURA || posi[i][j + 1]) {
                    return 0;
                }
                break;
            }
        }
    }
    return 1;
}

void ajuste(unsigned int *t, int nivel) {
    *t =	(nivel<=15)*(4.3333*nivel*nivel - 123.33*nivel + 1000)+(nivel>15)*( 0.3333*nivel*nivel - 21.667*nivel + 375);
}

char virar(Peca *peca, char **mapa) {
    int i = peca->i, j;
    int ip = 0, jp = 0;
    for (ip = 0; ip < peca->ordem; i++, ip++) {
        j = peca->j;
        for (jp = 0; jp < peca->ordem; j++, jp++) {
            if (i > ALTURA - 4 || j < 0 || j >= LARGURA) {
                if (peca->mg[ip][jp]) {
                    return 0;
                }
            }
            if (i >= 0 && i < ALTURA && j >= 0 && j < LARGURA) {
                if (!peca->m[ip][jp] && peca->mg[ip][jp]) {
                    if (mapa[i][j]) {
                        return 0;

                    }
                }
            }

        }

    }
    return 1;
}
