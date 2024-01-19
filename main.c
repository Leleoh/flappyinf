#include "raylib.h"
#define BACKGROUND_WIDTH 2400
#define BACKGROUND_HEIGHT 800

int main() {
    // Inicializar a janela
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "FlappyInf");

    // Carregar a imagem de fundo
    Image backgroundImage = LoadImage("C:/Users/leone/Desktop/flappyinf/imgs/floordia.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);

    //Posi��o do cen�rio
    float backgroundX = 0;

    // Configurar a c�mera 2D
    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Definir a cor de fundo da janela
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // L�gica do jogo aqui

        //Atualiza posi��o do cen�rio
        backgroundX -= 2.0f;

        // Se o cen�rio sair da tela, resete a posi��o para criar um efeito de loop
        if (backgroundX <= -BACKGROUND_WIDTH) {
            backgroundX = 0;
        }

        // Desenha o cen�rio na posi��o atualizada e tamb�m na posi��o x + largura para a repeti��o suave
        DrawTextureEx(backgroundTexture, (Vector2){backgroundX, 0}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(backgroundTexture, (Vector2){backgroundX + BACKGROUND_WIDTH, 0}, 0.0f, 1.0f, WHITE);

        // Desenhar
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenhar o plano de fundo
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        // Desenhar elementos do jogo aqui

        EndDrawing();
    }

    // Limpar recursos
    UnloadTexture(backgroundTexture);
    CloseWindow();

    return 0;
}
