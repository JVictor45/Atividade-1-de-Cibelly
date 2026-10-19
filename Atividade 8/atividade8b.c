#include "raylib.h"
#include "entidade.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));
    InitWindow(800, 600, "Atividade 8B - Reutilizando o modulo");
    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){200, 300});
    Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){400, 300});
    Entidade *item = entidadeCriar(ENTIDADE_ITEM, (Vector2){600, 300});

    if (jogador == NULL || inimigo == NULL || item == NULL) {
        free(jogador);
        free(inimigo);
        free(item);
        CloseWindow();
        return 1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Exercicio 2 - Mesmo modulo, outro programa", 90, 70, 24, DARKGRAY);
        entidadeDesenhar(jogador);
        entidadeDesenhar(inimigo);
        entidadeDesenhar(item);
        DrawText("Jogador", 165, 345, 20, BLUE);
        DrawText("Inimigo", 365, 345, 20, MAROON);
        DrawText("Item", 580, 345, 20, GOLD);
        DrawText("ESC para sair", 20, 560, 18, GRAY);
        EndDrawing();
    }

    free(jogador);
    free(inimigo);
    free(item);
    CloseWindow();
    return 0;
}
