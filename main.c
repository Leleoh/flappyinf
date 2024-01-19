#include <raylib.h>

int main()
{
    //Inicialização da janela
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "FlappyInf");

    //Carregar o plano de fundo do menu
    Texture2D background = LoadTexture("C:/Users/leone/Desktop/flappyinf/imgs/floordia.png");

    //Taxa de atualização do jogo
    SetTargetFPS(60);

    //Loop Principal
    while(!WindowShouldClose()) //Detecta o fechamento da janela
        {
        //Atualizar

        //Desenhar
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Desenhar o plano de fundo
        DrawTexture(background, 0, 0, WHITE);

        //Futuros elementos


        EndDrawing();



    }

    //Limpar e fechar
    UnloadTexture(background);
    CloseWindow();

    return 0;

}
