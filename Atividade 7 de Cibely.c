#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA  800
#define ALTURA_JANELA   600
#define TOTAL_PLACARES  15
#define PONTUACAO_MAX   100

typedef struct {
    char nome[16];
    int  pontuacao;
} Placar;

Placar *criarPlacares(int quantidade) {
    Placar *placares = (Placar *)malloc(quantidade * sizeof(Placar));
    if (placares == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Placar *p = (placares + i);
        TextCopy(p->nome, TextFormat("J%02d", i + 1));
        p->pontuacao = GetRandomValue(10, PONTUACAO_MAX);
    }
    return placares;
}

/* ---- ordenação: bubble sort contando comparações e trocas ---- */
void ordenarBubbleSort(Placar *vetor, int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (vetor[j].pontuacao > vetor[j + 1].pontuacao) {
                Placar temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

/* ---- exercício 1: insertion sort ---- */
void ordenarInsertionSort(Placar *vetor, int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 1; i < n; i++) {
        Placar chave = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;

            if (vetor[j].pontuacao > chave.pontuacao) {
                vetor[j + 1] = vetor[j];
                (*trocas)++;
                j--;
            } else {
                break;
            }
        }

        vetor[j + 1] = chave;
    }
}

/* ---- busca sequencial: O(n), funciona em qualquer ordem ---- */
int buscaSequencial(Placar *vetor, int n, int alvo, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (vetor[i].pontuacao == alvo) return i;
    }
    return -1;
}

/* ---- busca binária: O(log n), exige vetor ordenado ---- */
int buscaBinaria(Placar *vetor, int n, int alvo, long *comparacoes) {
    *comparacoes = 0;
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        (*comparacoes)++;
        int meio = (inicio + fim) / 2;

        if (vetor[meio].pontuacao == alvo) return meio;
        if (vetor[meio].pontuacao < alvo) inicio = meio + 1;
        else                              fim = meio - 1;
    }
    return -1;
}

void desenharBarras(Placar *vetor, int n, int indiceDestacado) {
    int larguraBarra = LARGURA_JANELA / n;

    for (int i = 0; i < n; i++) {
        int altura = vetor[i].pontuacao * 4;
        int x = i * larguraBarra;
        int y = ALTURA_JANELA - 60 - altura;

        Color cor = (i == indiceDestacado) ? LIME : SKYBLUE;
        DrawRectangle(x + 2, y, larguraBarra - 4, altura, cor);
        DrawText(TextFormat("%d", vetor[i].pontuacao), x + 4, y - 18, 12, DARKGRAY);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 7 - Complexidade: Busca e Ordenacao");
    SetTargetFPS(60);

    Placar *placares = criarPlacares(TOTAL_PLACARES);
    bool ordenado = false;

    long comparacoes = 0, trocas = 0;
    double tempoBubble = 0.0;

    int alvo = placares[GetRandomValue(0, TOTAL_PLACARES - 1)].pontuacao;
    int indiceEncontrado = -1;
    char resultado[96] = "Pressione Q para buscar (sequencial) ou W (binaria)";

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_O)) {
            double inicio = GetTime();

            ordenarBubbleSort(placares, TOTAL_PLACARES, &comparacoes, &trocas);

            double fim = GetTime();
            tempoBubble = (fim - inicio) * 1000.0;

            ordenado = true;
            indiceEncontrado = -1;
            TextCopy(resultado, TextFormat("Bubble: %ld comparacoes, %ld trocas, %.6f ms",
                                           comparacoes, trocas, tempoBubble));
        }

        if (IsKeyPressed(KEY_I)) {
            ordenarInsertionSort(placares, TOTAL_PLACARES, &comparacoes, &trocas);
            ordenado = true;
            indiceEncontrado = -1;
            TextCopy(resultado, TextFormat("Insertion: %ld comparacoes, %ld trocas",
                                           comparacoes, trocas));
        }

        if (IsKeyPressed(KEY_N)) {
            alvo = placares[GetRandomValue(0, TOTAL_PLACARES - 1)].pontuacao;
            indiceEncontrado = -1;
            TextCopy(resultado, TextFormat("Novo alvo sorteado: %d", alvo));
        }

        if (IsKeyPressed(KEY_Q)) {
            indiceEncontrado = buscaSequencial(placares, TOTAL_PLACARES, alvo, &comparacoes);
            TextCopy(resultado, TextFormat("Busca sequencial por %d: %ld comparacoes (O(n))", alvo, comparacoes));
        }

        if (IsKeyPressed(KEY_W)) {
            if (!ordenado) {
                TextCopy(resultado, "Ordene primeiro com O -- busca binaria exige vetor ordenado!");
            } else {
                indiceEncontrado = buscaBinaria(placares, TOTAL_PLACARES, alvo, &comparacoes);
                TextCopy(resultado, TextFormat("Busca binaria por %d: %ld comparacoes (O(log n))", alvo, comparacoes));
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            desenharBarras(placares, TOTAL_PLACARES, indiceEncontrado);

            DrawText(TextFormat("Alvo da busca: %d   Vetor ordenado: %s", alvo, ordenado ? "SIM" : "NAO"),
                      10, 10, 20, DARKGRAY);
            DrawText(resultado, 10, 34, 18, MAROON);
            DrawText(TextFormat("Tempo Bubble: %.6f ms", tempoBubble), 10, 56, 16, DARKGRAY);

            DrawText("O ordena | I insertion | N novo alvo | Q sequencial | W binaria | ESC sai",
                      10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    free(placares);

    CloseWindow();
    return 0;
}