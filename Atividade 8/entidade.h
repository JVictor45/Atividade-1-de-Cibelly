#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "raylib.h"

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

typedef union {
    int dano;
    int valor;
} ExtraEntidade;

typedef struct {
    TipoEntidade tipo;
    Vector2 pos;
    float raio;
    int vida;
    Color cor;
    ExtraEntidade extra;
} Entidade;

Entidade *entidadeCriar(TipoEntidade tipo, Vector2 pos);
bool entidadeColidiu(Entidade *a, Entidade *b);
void entidadeDesenhar(Entidade *e);
void entidadeAplicarDano(Entidade *e, int dano);
bool entidadeEstaViva(Entidade *e);

#endif
