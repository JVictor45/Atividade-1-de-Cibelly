#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define RAIO_JOGADOR   20.0f
#define TOTAL_MOEDAS   15

// enum: cada valor representa uma categoria de moeda
typedef enum {
    MOEDA_BRONZE,
    MOEDA_PRATA,
    MOEDA_OURO,
    MOEDA_DIAMANTE
} TipoMoeda;

typedef struct {
    Vector2   pos;
    float     raio;
    TipoMoeda tipo;
    int       valor;
    bool      coletada;
    float     tempoColeta;
} Moeda;

/* devolve a cor associada a cada tipo do enum */
Color corDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:   return (Color){160, 90, 40, 255};
        case MOEDA_PRATA:    return (Color){190, 190, 190, 255};
        case MOEDA_OURO:     return GOLD;
        case MOEDA_DIAMANTE: return (Color){0, 220, 255, 255};
        default:             return WHITE;
    }
}

/* devolve o valor em pontos associado a cada tipo do enum */
int valorDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:   return 5;
        case MOEDA_PRATA:    return 10;
        case MOEDA_OURO:     return 25;
        case MOEDA_DIAMANTE: return 50;
        default:             return 0;
    }
}

/* cria o vetor dinâmico de moedas, sorteando tipo e posição de cada uma */
Moeda *criarMoedas(int quantidade) {
    Moeda *moedas = (Moeda *)malloc(quantidade * sizeof(Moeda));
    if (moedas == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Moeda *m = (moedas + i); // ponteiro para o i-ésimo elemento

        m->pos = (Vector2){
            GetRandomValue(30, LARGURA_JANELA - 30),
            GetRandomValue(30, ALTURA_JANELA - 30)
        };

        m->raio = 10.0f;

        if (GetRandomValue(0, 9) == 0) {
            m->tipo = MOEDA_DIAMANTE;
        }
        else {
            m->tipo = (TipoMoeda)GetRandomValue(MOEDA_BRONZE, MOEDA_OURO);
        }

        m->valor = valorDaMoeda(m->tipo);
        m->coletada = false;
        m->tempoColeta = 0;
    }

    return moedas;
}

/* recebe um PONTEIRO para a moeda: marca como coletada diretamente no vetor original */
bool tentarColetar(Moeda *m, Vector2 posJogador, float raioJogador) {
    if (m->coletada) return false;

    float dx = m->pos.x - posJogador.x;
    float dy = m->pos.y - posJogador.y;
    float distancia = (dx * dx + dy * dy);
    float somaRaios = (m->raio + raioJogador) * (m->raio + raioJogador);

    if (distancia <= somaRaios) {
        m->coletada = true;
        m->tempoColeta = GetTime();
        return true;
    }

    return false;
}

void desenharMoeda(Moeda *m) {
    if (m->coletada) return;
    DrawCircleV(m->pos, m->raio, corDaMoeda(m->tipo));
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 2 - Enum + Struct + Alocacao Dinamica");
    SetTargetFPS(60);

    Vector2 jogador = { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f };
    int pontuacao = 0;

    Moeda *moedas = criarMoedas(TOTAL_MOEDAS); // vetor dinâmico de struct

    while (!WindowShouldClose()) {

        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador.y += vel;

        // percorre o vetor com aritmética de ponteiros: (moedas + i)
        for (int i = 0; i < TOTAL_MOEDAS; i++) {
            Moeda *m = (moedas + i);

            if (m->coletada && GetTime() - m->tempoColeta >= 3.0) {
                m->pos = (Vector2){
                    GetRandomValue(30, LARGURA_JANELA - 30),
                    GetRandomValue(30, ALTURA_JANELA - 30)
                };

                m->coletada = false;
            }

            if (tentarColetar(m, jogador, RAIO_JOGADOR)) {
                pontuacao += m->valor;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < TOTAL_MOEDAS; i++) {
                desenharMoeda(moedas + i);
            }

            DrawCircleV(jogador, RAIO_JOGADOR, BLUE);

            DrawText(TextFormat("Pontuacao: %d", pontuacao), 10, 10, 22, DARKGRAY);
            DrawText("Setas movem o jogador | ESC sai", 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    free(moedas); // libera o vetor dinâmico

    CloseWindow();
    return 0;
}
