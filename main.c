#include <raylib.h>

int main()
{
    //Inicializa��o da janela
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "FlappyInf");

    //Carregar o plano de fundo do menu
    Texture2D background = LoadTexture("C:/Users/leone/Desktop/flappyinf/Recursos/floordia.png");

    //Taxa de atualiza��o do jogo
    SetTargetFPS(60);

    //Carregando os frames do p�ssaro
    Texture2D asa1 = LoadTexture("C:/Users/leone/Desktop/flappyinf/Recursos/asa1.png");
    Texture2D asa2 = LoadTexture("C:/Users/leone/Desktop/flappyinf/Recursos/asa2.png");
    Texture2D asa3 = LoadTexture("C:/Users/leone/Desktop/flappyinf/Recursos/asa3.png");

    //Vari�veis de controle para anima��o das asas
    int frameAtual = 0;
    int timer = 0;
    int frameSpeed = 10;

    //Vari�veis de posi��o e velocidade do p�ssaro (X, Y)
    float posX = 100.0f;
    float posY = 100.0f;
    float speedpassaro = 0.0f;
    const float gravidade = 0.6f;
    const float jumpForce = -10.0f;
    const float maxrotation = 25.0f;

    //Vari�veis de posi��o e controle do ch�o
    float groundX1 = 0.0f;
    float groundX2 = screenWidth;
    float groundSpeed = 1.0f;

    //Loop Principal
    while(!WindowShouldClose()) //Detecta o fechamento da janela
        {
        //Atualizar

        //Controle do pulo
        if (IsKeyPressed(KEY_SPACE)){
            speedpassaro = jumpForce;
        }

        //Gravidade
        speedpassaro += gravidade;

        //Limita��o da velocidade de descida
        if (speedpassaro > 10.0f){
            speedpassaro = 10.0f;
        }

        //Movimento do p�ssaro
        posY += speedpassaro;

        //Asas batendo
        timer ++;
        if (timer >= frameSpeed){
            frameAtual++;
            if (frameAtual > 2){
                frameAtual = 0;
            }
            timer = 0;
        }

        //Movimento do ch�o
        groundX1 -= groundSpeed;
        groundX2 -= groundSpeed;

        if (groundX1 <= -screenWidth){
            groundX1 = screenWidth;
        }
        if (groundX2 <= -screenWidth){
            groundX2 = screenWidth;
        }



        /*Rota��o de descida e subida do p�ssaro influenciada pela velocidade (A inclinadinha) (AINDA N�O FUNCIONA)
        float rotation = 0.0f;
        if (speedpassaro < 0){
            rotation = maxrotation * DEG2RAD;
        }
        else if (speedpassaro > 0){
            rotation = -maxrotation * DEG2RAD;
        */

        //Desenhar
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Desenhar o plano de fundo
        DrawTexture(background, 0, 0, WHITE);

        //Desenhar o ch�o
        DrawTexture(background, groundX1, screenHeight - background.height, WHITE);
        DrawTexture(background, groundX2, screenHeight - background.height, WHITE);

        //Asas batendo
        switch(frameAtual){
        case 0:
            DrawTexture(asa1, posX, posY, WHITE);
            break;
        case 1:
            DrawTexture(asa2, posX, posY, WHITE);
            break;
        case 2:
            DrawTexture(asa3, posX, posY, WHITE);
            break;
        };


        //Futuros elementos


        EndDrawing();


    }

    //Limpar e fechar
    UnloadTexture(background);
    CloseWindow();

    return 0;

}
