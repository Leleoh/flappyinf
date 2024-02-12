
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

// Dimensões da janela;
#define LARGURA 1200
#define ALTURA 800

// Pontuação dos jogadores;
typedef struct tipo_score
{
    char nome[40];
    int score;
} TIPO_SCORE;

Texture2D image_menu;
Texture2D image_jogo;

int func_menu()
{
    image_menu = LoadTexture("resources/flappy_backg.png");
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawTexture(image_menu, 0, 0, WHITE);
    DrawText("FlappyINF", 471, 78, 51, BLACK);
    DrawText("FlappyINF", 470, 80, 50, WHITE);

    // Botao Jogar
    Rectangle botaoJogar = {LARGURA / 2 - 100, ALTURA / 2 - 150 + 0 * 100, 200, 80};
    DrawRectangleRec(botaoJogar, WHITE);
    DrawText("JOGAR", (int)(botaoJogar.x + botaoJogar.width / 2 - MeasureText("JOGAR", 20) / 2),
             (int)(botaoJogar.y + botaoJogar.height / 2 - 10), 20, BLACK);

    // Botao Dificuldade
    Rectangle botaoDificuldade = {LARGURA / 2 - 100, ALTURA / 2 - 150 + 1 * 100, 200, 80};
    DrawRectangleRec(botaoDificuldade, WHITE);
    DrawText("DIFICULDADE", (int)(botaoDificuldade.x + botaoDificuldade.width / 2 - MeasureText("DIFICULDADE", 20) / 2),
             (int)(botaoDificuldade.y + botaoDificuldade.height / 2 - 10), 20, BLACK);

    // Botao Ranking
    Rectangle botaoRanking = {LARGURA / 2 - 100, ALTURA / 2 - 150 + 2 * 100, 200, 80};
    DrawRectangleRec(botaoRanking, WHITE);
    DrawText("RANKING", (int)(botaoRanking.x + botaoRanking.width / 2 - MeasureText("RANKING", 20) / 2),
             (int)(botaoRanking.y + botaoRanking.height / 2 - 10), 20, BLACK);

    // Botao Sair
    Rectangle botaoSair = {LARGURA / 2 - 100, ALTURA / 2 - 150 + 3 * 100, 200, 80};
    DrawRectangleRec(botaoSair, RED);
    DrawText("SAIR", (int)(botaoSair.x + botaoSair.width / 2 - MeasureText("SAIR", 20) / 2),
             (int)(botaoSair.y + botaoSair.height / 2 - 10), 20, BLACK);

    EndDrawing();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), botaoJogar))
        {
            return 0;
        }
        if (CheckCollisionPointRec(GetMousePosition(), botaoDificuldade))
        {
            return 1;
        }
        if (CheckCollisionPointRec(GetMousePosition(), botaoRanking))
        {
            return 2;
        }
        if (CheckCollisionPointRec(GetMousePosition(), botaoSair))
        {
            return 3;
        }
    }
}

void Roda_jogo(int *game)
{
    image_jogo = LoadTexture("resources/floordia.png");
    BeginDrawing();
    DrawTexture(image_jogo, 0, 0, WHITE);
}

int main(void)
{
    InitWindow(LARGURA, ALTURA, "FlappyINF");

    while (!WindowShouldClose())
    {
        int game = 0;
        int estado = func_menu();
        switch (estado)
        {
        case 0:
            game = 1;
            Roda_jogo(&game);
            break;

        case 3:

            CloseWindow();
            break;
        }
    }

    SetTargetFPS(60);
    return 0;
}
