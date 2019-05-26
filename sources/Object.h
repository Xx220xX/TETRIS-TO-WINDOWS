#define ALTURA 24
#define LARGURA 10
#define LIMPAR -1
#define FUNDO  BLACK
typedef struct {
    char pix[16][16];
} IMG;
typedef struct {
    int tamanho;
    int *notas, *tempo;
    char *nome;
} Mlh;
typedef struct {
    char **m, **mg, girei, justT;
    int i, j, iA, jA, ordem;//i antigo LRIGHT j antigo
    int cor;
} Peca;
typedef struct {
    int i;
    Mlh m;
} Musica;
typedef struct {
    int pontos, linhas;
    char nome[25];
    char existe;
    char trap;
    
} Record;

typedef struct {
    char corAleatoria, sonsAtivos, nivel;
    Record *rec;
    int linhas, sizeBlock;
} Config;
typedef unsigned long long int Bytes8;
typedef struct LCG {
    Bytes8 a, c, m, rand_max, atual;
} LCG;

void semente(LCG *r, Bytes8 seed) {
// constantes do POSIX [de]rand48, glibc [de]rand48[_r]
// ULL transforma a constante ï¿½intï¿½ em ï¿½unsigned long long intï¿½
    r->a = 0x5DEECE66DULL;
    r->c = 11ULL;
    r->m = (1ULL << 48);
    r->rand_max = r->m - 1;
    r->atual = seed;
}

Bytes8 lcg_rand(LCG *r) {
    r->atual = (r->a * r->atual + r->c) % r->m;
    return r->atual;
}

double lcg_rand_01(LCG *r) {
    return ((double) lcg_rand(r)) / (r->rand_max);
}

Config gmConfig = {1, 1, 0, 0, 6};
char **controle, **coloca, **mostra, style;
LCG aleat;

void (*printa )(char **, int, int, int, int, char *, char);

void _1(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd);

void _2(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd);

void _3(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd);

void _4D(char **mat, int m, int n, int x0, int y0, char *modifiquei, char mostraTd);

void preparaMostra(Peca *minhaPeca, char **_controle, char **_coloca, char **_mostra, int m, int n);

void tetrisBegin(Peca *p, Peca *p2);

void tetrisFinish(Peca *p, Peca *p2);

char possoIrDir(char **posi, Peca *at);

char virar(Peca *peca, char **mapa);

int possoIrB(char **posi, Peca *at);

char possoIrEsq(char **posi, Peca *at);

void jogo(Record *atualR, int *scrxT, int *scryT, int *nextX0, int *nextY0);

int completei(char **mat, int m, int n);

void nivel(int tmx, int tmy);

void ajuste(unsigned int *tmp, int nivel);

int hardDrop(char **posi, Peca *at);

void descerLinhas(char **mat, int n, char *linhas);


void espera(int ms);

void fazerQuadrado(int x0, int y0, int largura, int altura);

void colocaModelo(Peca *peca, char *novaPeca, int ordem, char transposta);

void sorteiaPeca(Peca *p);

char confgVideo(char *corAleatoria, int *tmx, int *tmy);

void ajustarTela(int *tmX, int *tmY);

void playSound(char *arq);

void stopSound();

#include <windows.h>
#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include <time.h>

#include"Historico.h"
#include"letras.h"
#include"Matriz.h"
#include"Songs.h"
#include"Pecas.h"
#include"Tela.h"
