void salvarJogo(Record *at, int tmX, int tmY) {
    int i;
    for (i = 0; i < 10; i++) {
        if (at[i].existe == 3) {
            at[i].existe = 1;
            if (!gmConfig.nivel) {
                at[i].trap = 1;
            } else {
                at[i].trap = 0;
            }
            at[i].linhas = gmConfig.linhas;
            for (;;) {
                gotoxy(tmX / 3 + 1, tmY / 3 + 1);
                printf("DIGITE SEU NOME:");
                at[i].nome[0] = 0;
                fflush(stdin);
                fgets(at[i].nome, 24, stdin);
                fflush(stdin);
                if (at[i].nome[0] == 0 || at[i].nome[0] == ' ') {
                    gotoxy(tmX / 3 + 1, tmY / 3 + 2);
                    printf("gostaria de saber seu nome ");
                    espera(1200);
                    gotoxy(tmX / 3 + 1, tmY / 3 + 2);
                    printf("                           ");
                    
                } else {
                    break;
                }
            }
            break;
        }
    }
    salvarHistorico(at);
}

void nextBlock(Peca *p, int x0, int y0) {
    textcolor(WHITE);
    int i, j, y = y0 + 3, x = x0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            
            gotoxy(x++, y);
            if (i < p->ordem && j < p->ordem) {
                textbackground(p->m[i][j]);
            } else {
                textbackground(FUNDO);
            }
            printf(" ");
        }
        x = x0;
        y++;
    }
    textbackground(FUNDO);
}

void fazerTelaGame(Record *atual, int x0Nxt, int y0Nxt, int tmX, int tmY) {
    textcolor(WHITE);
    textbackground(FUNDO);
    gotoxy(x0Nxt, y0Nxt + 1);
    printf("NEXT");
    fazerQuadrado(x0Nxt - 1, y0Nxt + 2, 5, 5);
    fazerQuadrado(x0Nxt - 1, y0Nxt, 5, 2);
    lerHistorico(atual);
    fazerQuadrado(1, 1, tmX, tmY);
    fazerQuadrado(1, 1, tmX / 3 - 1, gmConfig.sizeBlock * 24 + 1);
    textbackground(1);
    fazerQuadrado(tmX / 3, 1, gmConfig.sizeBlock * 10 + 1, gmConfig.sizeBlock * 24 + 1);
    textbackground(0);
    organizar(atual);
    mostrar(atual, tmX, tmY);
    
}

void telinha(char *p, int length, int tmX, int tmY) {
    textbackground(FUNDO);
    system("cls");
    fazerQuadrado(1, 1, tmX, tmY);
    fazerQuadrado(tmX / 3, tmY / 3 - 4, tmX / 4, 2);
    textcolor(WHITE);
    gotoxy(tmX / 2 - length, tmY / 3 - 3);
    printf("%s", p);
    fazerQuadrado(tmX / 3, tmY / 3, tmX / 4, tmY / 4);
}

void confgVideoCorAleatoria(char *corAleat, int tmX, int tmY) {
    char escolha, opcoes[2][30] = {{"SIM"},
                                   {"VOLTAR"}};
    textcolor(WHITE);
    telinha(*corAleat ? "DESATIVAR CORES ALEATORIAS" : "ATIVAR CORES ALEATORIAS", 21, tmX, tmY);
    escolha = fazerMenu(opcoes, 2, tmX / 3 + 1, tmY / 3 + 1, YELLOW, LIGHTRED, WHITE);
    switch (escolha) {
        case 0:*corAleat = !*corAleat;
            return;
        case 2:return;
    }
}

void configSons(char *ativarSom, int tmX, int tmY) {
    char escolha, opcoes[2][30] = {{"SIM"},
                                   {"VOLTAR"}};
    telinha(*ativarSom ? "DESATIVAR SONS" : "ATIVAR SONS", 16, tmX, tmY);
    escolha = fazerMenu(opcoes, 2, tmX / 3 + 1, tmY / 3 + 1, YELLOW, LIGHTRED, WHITE);
    switch (escolha) {
        case 0:*ativarSom = !*ativarSom;
            return;
        default:return;
    }
}

void clrRec(Record *rec, int tmX, int tmY) {
    char escolha, opcoes[2][30] = {{"SIM"},
                                   {"VOLTAR"}};
    int i;
    telinha("LIMPAR RECORDS ? ", 20, tmX, tmY);
    
    escolha = fazerMenu(opcoes, 2, tmX / 3 + 1, tmY / 3 + 1, YELLOW, LIGHTRED, WHITE);
    switch (escolha) {
        case 0:
            for (i = 0; i < 10; i++) {
                rec[i].existe = 0;
            }
            salvarHistorico(rec);
            gotoxy(tmX / 2 - 20, tmY / 3 - 3);
            printf("LIMPAR RECORDS ? PRONTINHO!! ");
            espera(1000);
            return;
        default:return;
    }
}

void menuConfig(Config *cfg, int *tmX, int *tmY) {
    char escolha, opcoes[4][30] = {{"VIDEO"},
                                   {"SONS"},
                                   {"LIMPAR RANKING "},
                                   {"VOLTAR"}};
    
    for (;;) {
        textcolor(WHITE);
        telinha("CONFIGURACOES", 14, *tmX, *tmY);
        escolha = fazerMenu(opcoes, 4, *tmX / 3 + 1, *tmY / 3 + 1, YELLOW, LIGHTRED, WHITE);
        switch (escolha) {
            case 0:
                if (confgVideo(&cfg->corAleatoria, tmX, tmY)) {
                    return;
                }
                break;
            case 1:configSons(&cfg->sonsAtivos, *tmX, *tmY);
                break;
            case 2:clrRec(cfg->rec, *tmX, *tmY);
                break;
            case 3:textcolor(WHITE);
                return;
        }
    }
    
    
}

char confgVideoStyle(int tmx, int tmy) {
    char escolha, opcoes[6][30] = {{"COLORIDO"},
                                   {"FANTASMA "},
                                   {"CLASSICO"},
                                   {"3D"},
                                   {"VOLTAR"},
                                   {"VOLTAR Tudo"}};
    for (;;) {
        textcolor(WHITE);
        telinha("STYLE ", 14, tmx, tmy);
        if (style == 1) {
            textbackground(YELLOW);
            gotoxy(tmx / 3 + 22, tmy / 3 + 2);
            printf("  ");
            gotoxy(tmx / 3 + 22, tmy / 3 + 3);
            printf("  ");
            gotoxy(tmx / 3 + 22, tmy / 3 + 4);
            printf("  ");
        } else if (style == 2) {
            textcolor(WHITE);
            textbackground(FUNDO);
            fazerQuadrado(tmx / 3 + 22, tmy / 3 + 1, 3, 3);
        } else {
            textbackground(FUNDO);
            textcolor(WHITE);
            fazerQuadrado(tmx / 3 + 22, tmy / 3 + 1, 3, 3);
            textbackground(YELLOW);
            gotoxy(tmx / 3 + 23, tmy / 3 + 2);
            printf("  ");
            gotoxy(tmx / 3 + 23, tmy / 3 + 3);
            printf("  ");
        }
        textbackground(FUNDO);
        escolha = fazerMenu(opcoes, 6, tmx / 3 + 1, tmy / 3 + 1, YELLOW, LIGHTRED, WHITE);
        switch (escolha) {
            case 0:printa = _1;
                style = 1;
                break;
            case 1:printa = _2;
                style = 2;
                break;
            case 2:style = 3;
                printa = _3;
                break;
            case 3:style = 4;
                printa = _4D;
                break;
            case 4:textcolor(WHITE);
                return 0;
            case 5:textcolor(WHITE);
                return 1;
        }
    }
}

char confgVideo(char *corAleatoria, int *tmX, int *tmY) {
    
    char escolha, opcoes[4][30] = {{"CORES"},
                                   {"ESTILO"},
                                   {"TAMANHO DA TELA"},
                                   {"VOLTAR"}};
    
    for (;;) {
        textcolor(WHITE);
        telinha("VIDEO ", 14, *tmX, *tmY);
        escolha = fazerMenu(opcoes, 4, *tmX / 3 + 1, *tmY / 3 + 1, YELLOW, LIGHTRED, WHITE);
        switch (escolha) {
            case 0:confgVideoCorAleatoria(corAleatoria, *tmX, *tmY);
                break;
            case 1:
                if (confgVideoStyle(*tmX, *tmY)) {
                    return 1;
                }
                break;
            case 2:ajustarTela(tmX, tmY);
                break;
            case 3:textcolor(WHITE);
                return 0;
        }
    }
}

void ajustarTela(int *tmX, int *tmY) {
    char c, opcoes[4][30] = {"TAMANHO EM X", "TAMANHO EM Y", "TAMANHO DOS BLOCOS", "VOLTAR"};
    int i = 0;
    textcolor(LIGHTBLUE);
    telinha("CONFIGURACOES", 14, *tmX, *tmY);
    _OP(opcoes, 4, *tmX / 3 + 1, *tmY / 3 + 2, YELLOW, LIGHTRED, i);
    gotoxy(*tmX / 3 + 25, *tmY / 3 + 2);
    printf("%d", *tmX);
    gotoxy(*tmX / 3 + 25, *tmY / 3 + 4);
    printf("%d", *tmY);
    gotoxy(*tmX / 3 + 35, *tmY / 3 + 6);
    printf("%d", gmConfig.sizeBlock);
    for (;;) {
        if (kbhit()) {
            c = getch();
            if (c == ENTER && i == 3) {
                piscar(opcoes, 4, *tmX / 3 + 1, *tmY / 3 + 2, YELLOW, LIGHTMAGENTA, i);
                return;
            }
            if (c == -32) {
                c = getch();
                switch (c) {
                    case SETA_BAIXO:i = i == 3 ? 0 : i + 1;
                        break;
                    case SETA_CIMA:i = i == 0 ? 3 : i - 1;
                        break;
                    case SETA_DIREITA:
                        if (i == 0 && *tmX + 1 < 225) {
                            *tmX = *tmX + 1;
                            
                        } else if (i == 1 && *tmY + 1 < 100) {
                            *tmY = *tmY + 1;
                        } else if (i == 2) {
                            gmConfig.sizeBlock = gmConfig.sizeBlock < 8 ? gmConfig.sizeBlock + 1 : gmConfig.sizeBlock;
                        }
                        
                        break;
                    case SETA_ESQUERDA:
                        if (i == 0 && *tmX - 1 > 100) {
                            *tmX = *tmX - 1;
                            
                        } else if (i == 1 && *tmY - 1 > 50) {
                            *tmY = *tmY - 1;
                        } else if (i == 2) {
                            gmConfig.sizeBlock = gmConfig.sizeBlock > 2 ? gmConfig.sizeBlock - 1 : gmConfig.sizeBlock;
                        }
                        
                        break;
                }
                textcolor(LIGHTBLUE);
                telinha("CONFIGURACOES", 14, *tmX, *tmY);
                _OP(opcoes, 4, *tmX / 3 + 1, *tmY / 3 + 2, YELLOW, LIGHTRED, i);
                textcolor(YELLOW);
                gotoxy(*tmX / 3 + 25, *tmY / 3 + 2);
                printf("%d", *tmX);
                gotoxy(*tmX / 3 + 25, *tmY / 3 + 4);
                printf("%d", *tmY);
                gotoxy(*tmX / 3 + 35, *tmY / 3 + 6);
                printf("%d", gmConfig.sizeBlock);
            }
            
        }
    }
    
}


char pauseTela(Config *gamingConfig, int *tmX, int *tmY) {
    char escolha = 1, opcoes[3][30] = {{"CONFIGURACOES"},
                                       {"VOLTAR AO JOGO "},
                                       {"SAIR DO JOGO "},};
    
    stopSound();
    textbackground(FUNDO);
    system("cls");
    fazerQuadrado(1, 1, *tmX, *tmY);
    fazerQuadrado(*tmX / 3, *tmY / 3 - 4, *tmX / 4, 2);
    textcolor(WHITE);
    gotoxy(*tmX / 3, *tmY / 3 - 4);
    printf("JOGO PAUSADO");
    for (;;) {
        escolha = fazerMenuMario(
                opcoes, 3, *tmX / 3 + 1, *tmY / 3 + 1, LIGHTGREEN, LIGHTCYAN, LIGHTMAGENTA, *tmX, *tmY);
        switch (escolha) {
            case 0 :menuConfig(gamingConfig, tmX, tmY);
                textbackground(FUNDO);
                system("cls");
                fazerQuadrado(1, 1, *tmX, *tmY);
                fazerQuadrado(*tmX / 3, *tmY / 3 - 4, *tmX / 4, 2);
                textcolor(WHITE);
                gotoxy(*tmX / 3, *tmY / 3 - 4);
                printf("JOGO PAUSADO");
                break;
            case 1:return 0;
            default:return 2;
            
        }
    }
    
}

void printaIMG(IMG *img, int x0, int y0) {
    int i, j;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            
            if (img->pix[i][j] < 0) {
                textbackground(!FUNDO);
            } else if (!img->pix[i][j]) {
                textbackground(FUNDO);
            } else {
                textbackground(img->pix[i][j]);
            }
            gotoxy(x0 + 2 * j, y0 + 2 * i);
            printf(" ");
        }
    }
    textcolor(WHITE);
    textbackground(FUNDO);
}

char getIMG(char *IMGname, IMG *img) {
    FILE *f;
    f = fopen(IMGname, "rb");
    if (!f) {
        return 0;
    }
    fread(img->pix, sizeof(char), 16 * 16, f);
    fclose(f);
}

char telaInicial(Config *conf, int *tmx, int *tmy, int *nextX, int *nextY) {
    IMG pacman[5], peca1, peca2, peca3, vazio = {0};
    char mus;
    FILE *f;
    Musica pmk = {0};
    char c, animacao, pm = 0, pc = 0, opcoes[][30] = {"JOGAR", "SELECIONAR NIVEL", "CONFIGURACOES", "CREDITOS", "QUIT"};
    unsigned int t0, tf;
    int x0 = 100, y0 = 1, i = 0;
    //  mus = readMlh(&pmk.m, "pumpedUpKicks.mlh");
    // iniciarMusica(&pmk);
    playSound("pacman.wav");
    animacao = 1;
    getIMG("pacman1.bin", &pacman[0]);
    getIMG("pacman2.bin", &pacman[1]);
    getIMG("pacman3.bin", &pacman[2]);
    getIMG("pacman4.bin", &pacman[3]);
    getIMG("pacman5.bin", &pacman[4]);
    
    f = fopen("peca1.bin", "rb");
    fread(&peca1, sizeof(IMG), 1, f);
    
    if (!f) {
        animacao = 0;
    }
    fclose(f);
    f = fopen("peca2.bin", "rb");
    fread(&peca2, sizeof(IMG), 1, f);
    if (!f) {
        animacao = 0;
    }
    fclose(f);
    f = fopen("peca3.bin", "rb");
    fread(&peca3, sizeof(IMG), 1, f);
    if (!f) {
        animacao = 0;
    }
    fclose(f);
    
    t0 = clock();
    textcolor(WHITE);
    textbackground(FUNDO);
    system("cls");
    
    _OP(opcoes, 5, *tmx / 2, *tmy / 2, LIGHTCYAN, LIGHTGREEN, i);
    for (;;) {
        if (animacao) {
            tf = clock();
            if (tf - t0 > 100) {
                t0 = clock();
                if (x0 < 38) {
                    pc++;
                    printaIMG(&vazio, x0 + 2, y0);
                    x0 = 100;
                    if (pc >= 3)
                        pc = 0;
                }
                switch (pc) {
                    case 0:printaIMG(&peca1, x0, y0);
                        break;
                    case 1:printaIMG(&peca2, x0, y0);
                        break;
                    case 2:printaIMG(&peca3, x0, y0);
                        break;
                }
                x0 -= 2;
                
                printaIMG(&pacman[pm], 1, 1);
                pm++;
                if (pm > 4)pm = 0;
            }
        }
        /* if (mus) {
             tocar(&pmk);
         }*/
        if (kbhit()) {
            c = getch();
            if (c == ENTER) {
                piscar(opcoes, 5, *tmx / 2, *tmy / 2, LIGHTCYAN, LIGHTRED, i);
                espera(30);
                textcolor(WHITE);
                textbackground(FUNDO);
                system("cls");
                stopSound();
                //finalizarMusica(&pmk);
                return i;
            }
            if (c == -32) {
                c = getch();
                switch (c) {
                    case SETA_BAIXO:i = i == 5 - 1 ? 0 : i + 1;
                        break;
                    case SETA_CIMA:i = i == 0 ? 5 - 1 : i - 1;
                        break;
                }
            }
            _OP(opcoes, 5, *tmx / 2, *tmy / 2, LIGHTCYAN, LIGHTGREEN, i);
        }
    }
}
