#include <raylib.h>
#include <time.h>
#include <stdlib.h>


int random(int min, int max)
{
    return min + (rand()%(max-min+1)); //retorna um valor entre min e max
}





int main()
{

    clock_t tempo, t;


    //Inicializar dispositivo de áudio
    InitAudioDevice();

    //Inicialização da janela
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "FlappyInf");


    // Definição da posição e dimensões do chão
    Rectangle ground = { 0, screenHeight - 50, screenWidth, 50 };

    //Carregar o plano de fundo do jogo
    Texture2D background = LoadTexture("./Recursos/floordia.png");

    //Carregar os planos de fundo do menu
    Texture2D menu1 = LoadTexture("./Recursos/menu1.png");
    Texture2D menu2 = LoadTexture("./Recursos/menu2.png");
    Texture2D menu3 = LoadTexture("./Recursos/menu3.png");

    //Carregar o plano de fundo do ranking
    Texture2D ranking = LoadTexture("./Recursos/ranking.png");

    //Variáveis de controle de animação do menu
    int menuFrame = 0;
    int menuTimer = 0;
    int menuFrameSpeed = 10;

    //Taxa de atualização do jogo
    SetTargetFPS(60);

    //Carregando os frames do pássaro
    Texture2D asa1 = LoadTexture("./Recursos/asa1.png");
    Texture2D asa2 = LoadTexture("./Recursos/asa2.png");
    Texture2D asa3 = LoadTexture("./Recursos/asa3.png");

    //Variáveis de controle para animação das asas
    int frameAtual = 0;
    int timer = 0;
    int frameSpeed = 10;

    //Variáveis de posição e velocidade do pássaro (X, Y)
    float posX = 250.0f;
    float posY = screenHeight/2;
    float speedpassaro = 0.0f;
    const float gravidade = 0.6f;
    const float gravidadedobro = 1.2f;
    const float jumpForce = -10.0f;
    const float maxrotation = 5.0f;
    const float rotationDelay = 0.03f;
    float rotationStartTime = 0.0f;

    //variáveis relacionadas ao chão
    int FloorX = 0;
    int FloorY = screenHeight - 50;
    int FloorW = screenWidth;
    int FloorH = 20;
    //variáveis relacionadas ao teto
    int RoofX = 0;
    int RoofY = 0;
    int RoofW = screenWidth;
    int RoofH = 3;
    //variáveis do cano de cima
    int tube1X = screenWidth;
    int tube1Y = 0;
    int tube1W = 102;
    int tube1H = 450;

    int tube2X = screenWidth-20;
    int tube2Y = 450;
    int tube2W = 102;
    int tube2H = 450;

    //colisões
    Rectangle Floor = {FloorX, FloorY, FloorW, FloorH};
    bool collision;
    Rectangle Roof = {RoofX, RoofY, RoofW, RoofH};
    Rectangle tubetop = {tube1X, tube1Y, tube1W, tube1H};
    Rectangle tubebottom = {tube2X, tube2Y, tube2W, tube2H};


    //Variáveis de posição e controle do chão
    float groundX1 = 0.0f;
    float groundX2 = screenWidth;
    float groundSpeed = 2.5f;

    //Carregar música do menu
    Music ostmenu = LoadMusicStream("./Recursos/ostmenu.mp3");
    PlayMusicStream(ostmenu);
    const float volumemenu = 0.2f;
    SetMusicVolume(ostmenu, volumemenu);

    //Carregar música do ranking
    Music ostranking = LoadMusicStream("./Recursos/ostranking.mp3");
    PlayMusicStream(ostranking);
    const float volumeranking = 1.0f;
    SetMusicVolume(ostranking, volumeranking);


    //Formatos dos botões para fazer as ações (JOGAR, RANKING, DIFICULDADE, SAIR)
    Rectangle botaojogar = { screenWidth / 2 - 290, screenHeight / 2 - 50, 200, 100 };
    Rectangle botaodificuldade = { screenWidth / 2 - 290, screenHeight / 2 + 125, 200, 30 };
    Rectangle botaoranking = { screenWidth / 2 + 15, screenHeight / 2 - 50, 200, 100 };
    Rectangle botaorankingvoltar = { screenWidth / 2 + 360, screenHeight / 2 + 200, 200, 80 };
    Rectangle botaosair = { screenWidth / 2 + 15, screenHeight / 2 + 125, 200, 30 };

    //Variável para estados do jogo
    bool fimdejogo = false; //Controle para verificar se o pássaro bateu em algo e perdeu
    bool jogoiniciado = false; //Controle para verificar se o jogo já começou (Aperto da barra de espaço)
    int estadojogo = 0; //0 para MENU, 1 para JOGO, 2 para RANKING

    // Variáveis de posição e tamanho do jogador

    t = clock();

    //Loop Principal
    while(!WindowShouldClose()) //Detecta o fechamento da janela
    {
<<<<<<< HEAD
=======


        tempo = (int)(clock()-t)/1000;



>>>>>>> 0e8c9377568ed6740159cf0c8c46832aa245fb0f
        //Música menu
        UpdateMusicStream(ostmenu);

        //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão jogar
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaojogar))
        {
            estadojogo = 1; // Mudar para o estado de jogo
            int movimento = 1;
            StopMusicStream(ostmenu); //Para a música ao mudar para a gameplay
        };

        //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão ranking
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaoranking))
        {
            estadojogo = 2; // Mudar para o estado de jogo 2
            StopMusicStream(ostmenu); //Para a música ao mudar para o ranking
        };
        //Fechar o jogo ao botão sair ser pressionado
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaosair))
            {
                CloseWindow(); // Fechar o jogo
                return 0;
            }

        //Lógica do Menu
        if (estadojogo == 0)
        {
            //Atualizar a animação do menu
            menuTimer++;
            if(menuTimer >= menuFrameSpeed)
            {
                menuFrame++;
                if (menuFrame > 2)
                {
                    menuFrame = 0;
                }
                menuTimer = 0;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            //Desenhar a textura do menu de acordo com o frame atual
            switch (menuFrame)
            {
            case 0:
                DrawTexture(menu1, 0, 0, WHITE);
                break;
            case 1:
                DrawTexture(menu2, 0, 0, WHITE);
                break;
            case 2:
                DrawTexture(menu3, 0, 0, WHITE);
                break;
            }
            EndDrawing();
        }

        //Mudar para a tela de ranking
        else if(estadojogo == 2){
            //Tocar a música do ranking
            PlayMusicStream(ostranking);
            UpdateMusicStream(ostranking);

            //Desenhar a textura do ranking
            BeginDrawing();
            DrawTexture(ranking, 0, 0, WHITE);

            //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão ranking
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaorankingvoltar))
            {
                estadojogo = 0; // Mudar para o estado de jogo 0 (MENU)
                StopMusicStream(ostranking);//Pausa a música do ranking
                PlayMusicStream(ostmenu); //Volta a tocar a música do menu
            };

            EndDrawing();
        }

        //Muda para a gameplay
        else if(estadojogo == 1)
        {
            //Controle do pulo
            if (IsKeyPressed(KEY_SPACE))
            {
                jogoiniciado = true;
                speedpassaro = jumpForce;
            }

            if (jogoiniciado){

                //Gravidade
                if (speedpassaro < 0)
                {
                    //Subida
                    speedpassaro += gravidade * gravidade;
                }
                else
                {
                    //Descida
                    speedpassaro += gravidade * gravidadedobro;
                }

                //Limitação da velocidade de descida
                if (speedpassaro > 10.0f)
                {
                    speedpassaro = 12.0f;
                }

                //Movimento do pássaro
                posY += speedpassaro;

                //Asas batendo
                timer ++;
                if (timer >= frameSpeed)
                {
                    frameAtual++;
                    if (frameAtual > 2)
                    {
                        frameAtual = 0;
                    }
                    timer = 0;
                }
            }
            //Movimento do chão
            groundX1 -= groundSpeed;
            groundX2 -= groundSpeed;

            if (groundX1 <= -screenWidth)
            {
                groundX1 = screenWidth;
            }
            if (groundX2 <= -screenWidth)
            {
                groundX2 = screenWidth;
            }

            //Rotação de descida e subida do pássaro influenciada pela velocidade (A inclinadinha)
            float rotation = 0.0f;
            if (speedpassaro < 0)
            {
                rotation = -maxrotation - 10;
                rotationStartTime = GetTime();
            }
            else if (speedpassaro > 0 && (GetTime() - rotationStartTime) > rotationDelay)
            {
                rotation = maxrotation + 20;
            }


            //Desenhar
            BeginDrawing();
            ClearBackground(RAYWHITE);

            //Desenhar o plano de fundo
            DrawTexture(background, 0, 0, WHITE);

            //Desenhar o chão
            DrawTexture(background, groundX1, screenHeight - background.height, WHITE);
            DrawTexture(background, groundX2, screenHeight - background.height, WHITE);

            // Asas batendo
            if(!jogoiniciado){
                timer++;
                if (timer >= frameSpeed)
                {
                    frameAtual++;
                    if (frameAtual > 2)
                    {
                        frameAtual = 0;
                    }
                    timer = 0;
                }
                switch(frameAtual)
                {
                case 0:
                    DrawTexturePro(asa1, (Rectangle)
                    {
                        0, 0, asa1.width, asa1.height
                    }, (Rectangle)
                    {
                        posX, posY, asa1.width, asa1.height
                    }, (Vector2)
                    {
                        asa1.width / 2, asa1.height / 2
                    }, rotation, WHITE);
                    break;
                case 1:
                    DrawTexturePro(asa2, (Rectangle)
                    {
                        0, 0, asa2.width, asa2.height
                    }, (Rectangle)
                    {
                        posX, posY, asa2.width, asa2.height
                    }, (Vector2)
                    {
                        asa2.width / 2, asa2.height / 2
                    }, rotation, WHITE);
                    break;
                case 2:
                    DrawTexturePro(asa3, (Rectangle)
                    {
                        0, 0, asa3.width, asa3.height
                    }, (Rectangle)
                    {
                        posX, posY, asa3.width, asa3.height
                    }, (Vector2)
                    {
                        asa3.width / 2, asa3.height / 2
                    }, rotation, WHITE);
                    break;
                }
            }
            else{
                // Asas batendo
                switch (frameAtual)
                {
                case 0:
                    DrawTexturePro(asa1, (Rectangle){0, 0, asa1.width, asa1.height}, (Rectangle){posX, posY, asa1.width, asa1.height}, (Vector2){asa1.width / 2, asa1.height / 2}, rotation, WHITE);
                    break;
                case 1:
                    DrawTexturePro(asa2, (Rectangle){0, 0, asa2.width, asa2.height}, (Rectangle){posX, posY, asa2.width, asa2.height}, (Vector2){asa2.width / 2, asa2.height / 2}, rotation, WHITE);
                    break;
                case 2:
                    DrawTexturePro(asa3, (Rectangle){0, 0, asa3.width, asa3.height}, (Rectangle){posX, posY, asa3.width, asa3.height}, (Vector2){asa3.width / 2, asa3.height / 2}, rotation, WHITE);
                    break;
                }
            }

            //Futuros elementos


            //Coisas relacionadas às colisões

            Rectangle player = {posX-38, posY-75, 75, 65};
            bool onFloor = CheckCollisionRecs(player, Floor);
            bool onRoof = CheckCollisionRecs(player, Roof);
<<<<<<< HEAD
            //Condicional de colisão com o teto
=======

            tube1X = tube1X -15;
            tube2X = tube2X -15;

            if(tube1X < -102){

                tube1X = screenWidth;
                tube1Y = random(-350, 0);
            }



            Rectangle tubetop = {tube1X, tube1Y, tube1W, tube1H};
            Rectangle tubebottom = {tube1X, tube1Y+450+200, tube2W, tube2H+100};
            bool onTube = CheckCollisionRecs(player, tubetop);
            bool onTube2 = CheckCollisionRecs(player, tubebottom);

                        //condicional de colisão com o teto
>>>>>>> 0e8c9377568ed6740159cf0c8c46832aa245fb0f
            if(onRoof){

                speedpassaro = 1;

            }
<<<<<<< HEAD
            //Condicional de colisão com o chão
            if(onFloor)
=======
            //condicional de colisão com o chão
            if(onFloor ||onTube || onTube2)
>>>>>>> 0e8c9377568ed6740159cf0c8c46832aa245fb0f
            {
                posY = 0;
            }




            DrawRectangleRec(tubetop, GOLD);
            DrawRectangleRec(tubebottom, GOLD);
            DrawRectangleRec(player, PURPLE);




            EndDrawing();
        }


    }

    //Limpar e fechar
    UnloadTexture(background);
    CloseWindow();

    return 0;

}
