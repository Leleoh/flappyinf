/*
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-FLAPPY INF-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
-=-=-=-=-=-=-=-=-=-=-=LEONEL HERNANDEZ E MATHEUS BELLO-=-=-=-=-=-=-=-=-
*/


#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1200


int random(int min, int max)
{
    return min + (rand()%(max-min+1)); //retorna um valor entre min e max
}

void derrota(int *FloorX, int *FloorY, int *FloorW, int *FloorH, int *RoofX, int *RoofY, int *RoofW,int *RoofH, int *tube1X, int *tube1Y, int *tube1W, int *tube1H, int *tube2X, int *tube2Y, int *tube2W, int *tube2H, float *posX, float *posY, int *recorde,int*score, int *estadojogo )
{

    // const int SCREENWIDTH = 1200;
    const int screenheight = 800;
    Music ostmenu = LoadMusicStream("./Recursos/ostmenu.mp3");
    Texture2D background = LoadTexture("./Recursos/floordia.png");
    Texture2D Telafim = LoadTexture("./Recursos/telafim.png");
    // PlaySound(bateu);
    //Reset de todas as variáveis
    *FloorX = 0;
    *FloorY = screenheight-100;
    *FloorW = SCREENWIDTH;
    *FloorH = 20;
    *RoofX = 0;
    *RoofY = 0;
    *RoofW = SCREENWIDTH;
    *RoofH = 3;
    *tube1X = SCREENWIDTH;
    *tube1Y = 0;
    *tube1W = 102;
    *tube1H = 450;
    *tube2X = SCREENWIDTH-20;
    *tube2Y = 450;
    *tube2W = 102;
    *tube2H = 450;
    *posX = 100.0f;
    *posY = 100.0f;

    int scoresalvo = *score;

    if(*recorde < *score)
        *recorde = *score;

    while(!(IsKeyPressed(KEY_SPACE)))
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(ostmenu);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(Telafim, 0, 0, WHITE);
        DrawText(TextFormat("%d", scoresalvo), (SCREENWIDTH/2)-50, (SCREENWIDTH/2)-230,40, GREEN);
        DrawText(TextFormat("%d", *recorde), (SCREENWIDTH/2)-50, (SCREENWIDTH/2)-160,40, BLUE);
        EndDrawing();

        *estadojogo = 0;
        *score = 0;

    }
}

void MoveCanos(int *score, int *tube1X, int *tube1Y, Sound pontos)
{

    const int screenheight = 800;


    if(*score < 450)
    {

        *tube1X = *tube1X -11;
    }
    else if(*score <= 1000 && *score >= 450)
    {

        *tube1X = *tube1X -17;

    }

    else if(*score > 1000)
    {

        *tube1X = *tube1X -22;

    }

    //Reseta a posição do tubo para o início da tela e também adiciona 50 pontos quando ele chega ao fim
    if(*tube1X < -102)
    {
        *tube1X = SCREENWIDTH;
        *tube1Y = random(-350, 0);
        *score = *score + 50;
        PlaySound(pontos);
    }

}

void MovePassaro(float *speedpassaro, float *groundX1, float *groundX2, float *groundSpeed, float *posY, float *rotation, int *frameAtual, int *timer, int *frameSpeed, Sound somasas)
{

    const float gravidade = 0.8f;
    const float gravidadedobro = 1.2f;
    const float jumpForce = -13.5f;
    const float maxrotation = 5.0f;
    const float rotationDelay = 0.05f;
    float rotationStartTime = 0.0f;

    // const int SCREENWIDTH = 1200;
    const int screenheight = 800;

    //Controle do pulo
    if (IsKeyPressed(KEY_SPACE))
    {
        *speedpassaro = jumpForce;
        PlaySound(somasas);
    }

    //Gravidade
    if (*speedpassaro < 0)
    {
        //Subida
        *speedpassaro += gravidade * gravidade;
    }
    else
    {
        //Descida
        *speedpassaro += gravidade * gravidadedobro;
    }

    //Limitação da velocidade de descida
    if (*speedpassaro > 10.0f)
    {
        *speedpassaro = 12.0f;
    }

    //Movimento do pássaro
    *posY += *speedpassaro;

    //Movimento do chão
    *groundX1 -= *groundSpeed;
    *groundX2 -= *groundSpeed;

    if (*groundX1 <= -SCREENWIDTH)
    {
        *groundX1 = SCREENWIDTH;
    }
    if (*groundX2 <= -SCREENWIDTH)
    {
        *groundX2 = SCREENWIDTH;
    }

    //Rotação de descida e subida do pássaro influenciada pela velocidade (A inclinadinha)
    if (*speedpassaro < 0)
    {
        *rotation = -maxrotation - 10;
        rotationStartTime = GetTime();
    }
    else if (*speedpassaro > 0 && (GetTime() - rotationStartTime) > rotationDelay)
    {
        *rotation = maxrotation + 20;
    }

}

//---------------------------------------------------------------------------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL MAIN
//---------------------------------------------------------------------------------------------------------------------------------------------

int main()
{

    //---------------------------------------------------------------------------------------------------------------------------------------------
    // DEFINIÇÕES INICIAS DE VARIÁVEIS
    //---------------------------------------------------------------------------------------------------------------------------------------------

    int recorde = 0;

    //Inicializar dispositivo de áudio
    InitAudioDevice();

    //Inicialização da janela
    // const int SCREENWIDTH = 1200;
    const int screenheight = 800;
    InitWindow(SCREENWIDTH, screenheight, "FlappyInf");


    // Definição da posição e dimensões do chão
    Rectangle ground = { 0, screenheight - 50, SCREENWIDTH, 50 };

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
    float posX = 100.0f;
    float posY = 100.0f;
    float speedpassaro = 0.0f;
    const float gravidade = 0.8f;
    const float gravidadedobro = 1.2f;
    const float jumpForce = -13.5f;
    const float maxrotation = 5.0f;
    const float rotationDelay = 0.05f;
    float rotationStartTime = 0.0f;
    float rotation = 0.0f;
    //Variáveis relacionadas ao chão
    int FloorX = 0;
    int FloorY = screenheight-100;
    int FloorW = SCREENWIDTH;
    int FloorH = 20;

    //Variáveis relacionadas ao teto
    int RoofX = 0;
    int RoofY = 0;
    int RoofW = SCREENWIDTH;
    int RoofH = 3;

    //Variáveis do cano de cima
    int tube1X = SCREENWIDTH;
    int tube1Y = 0;
    int tube1W = 102;
    int tube1H = 450;

    //Variáveis relacionadas ao cano de baixo
    int tube2X = SCREENWIDTH-20;
    int tube2Y = 450;
    int tube2W = 102;
    int tube2H = 450;

    //Colisões
    Rectangle Floor = {FloorX, FloorY, FloorW, FloorH};
    bool collision;
    Rectangle Roof = {RoofX, RoofY, RoofW, RoofH};
    Rectangle tubetop = {tube1X, tube1Y, tube1W, tube1H};
    Rectangle tubebottom = {tube2X, tube2Y, tube2W, tube2H};

    //Variáveis de posição e controle do chão (Efeito do chão andar)
    float groundX1 = 0.0f;
    float groundX2 = SCREENWIDTH;
    float groundSpeed = 1.0f;

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

    //Carregar efeitos sonoros
    Sound pontos = LoadSound("./Recursos/point.wav");
    Sound transicao = LoadSound("./Recursos/swoosh.wav");
    Sound bateu = LoadSound("./Recursos/hit.wav");
    Sound somasas = LoadSound("./Recursos/wing.wav");

    //Formatos dos botões para fazer as ações (JOGAR, RANKING, DIFICULDADE, SAIR)
    Rectangle botaojogar = { SCREENWIDTH / 2 - 290, screenheight / 2 - 50, 200, 100 };
    Rectangle botaodificuldade = { SCREENWIDTH / 2 - 290, screenheight / 2 + 125, 200, 30 };
    Rectangle botaoranking = { SCREENWIDTH / 2 + 15, screenheight / 2 - 50, 200, 100 };
    Rectangle botaorankingvoltar = { SCREENWIDTH / 2 + 360, screenheight / 2 + 200, 200, 80 };
    Rectangle botaosair = { SCREENWIDTH / 2 + 15, screenheight / 2 + 125, 200, 30 };

    //Variável para estados do jogo
    int estadojogo = 0; //0 para MENU, 1 para JOGO, 2 para RANKING
    int score = 0;

    //Carregar texturas
    Texture2D Tubocima = LoadTexture("./Recursos/canocima.png");
    Texture2D Tubobaixo = LoadTexture("./Recursos/canobaixo.png");
    Texture2D Telafim = LoadTexture("./Recursos/telafim.png");

//---------------------------------------------------------------------------------------------------------------------------------------------
// LOOP PRINCIPAL
//---------------------------------------------------------------------------------------------------------------------------------------------

    while(!WindowShouldClose()) //Detecta o fechamento da janela
    {

        //Música menu
        UpdateMusicStream(ostmenu);

        //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão jogar
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaojogar))
        {
            estadojogo = 1; // Mudar para o estado de jogo
            int movimento = 1;
            StopMusicStream(ostmenu); //Para a música ao mudar para a gameplay
            PlaySound(transicao);
        };

        //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão ranking
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaoranking))
        {
            estadojogo = 2; // Mudar para o estado de jogo 2 (RANKING)
            StopMusicStream(ostmenu); //Para a música do menu ao mudar para o ranking
        };

        //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão sair
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaosair))
        {
            StopMusicStream(ostmenu); //Para a música do menu
            return 0;
        };

        //---------------------------------------------------------------------------------------------------------------------------------------------
        // MENU INICIAL
        //---------------------------------------------------------------------------------------------------------------------------------------------

        //Lógica do Menu
        if (estadojogo == 0)
        {
            UpdateMusicStream(ostmenu);
            PlayMusicStream(ostmenu);
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

        //---------------------------------------------------------------------------------------------------------------------------------------------
        // RANKING
        //---------------------------------------------------------------------------------------------------------------------------------------------

        //Mudar para a tela de ranking
        else if(estadojogo == 2)
        {
            //Tocar a música do ranking
            PlayMusicStream(ostranking);
            UpdateMusicStream(ostranking);

            //Desenhar a textura do ranking
            BeginDrawing();
            DrawTexture(ranking, 0, 0, WHITE);

            //Verificação para se o botão esquerdo do mouse foi pressionado dentro da área executável do botão voltar, dentro do ranking
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaorankingvoltar))
            {
                StopMusicStream(ostranking); //Para a música do ranking
                estadojogo = 0; // Mudar para o estado de jogo 0 (MENU)
                PlayMusicStream(ostmenu); //Volta a tocar a música do menu
            };
            EndDrawing();
        }

        //---------------------------------------------------------------------------------------------------------------------------------------------
        // GAMEPLAY
        //---------------------------------------------------------------------------------------------------------------------------------------------

        //Muda para a gameplay
        else if(estadojogo == 1)
        {

            MovePassaro(&speedpassaro, &groundX1, &groundX2, &groundSpeed, &posY, &rotation, &frameAtual, &timer, &frameSpeed, somasas);

            //Desenhar
            BeginDrawing();
            ClearBackground(RAYWHITE);

            //Desenhar o plano de fundo
            DrawTexture(background, 0, 0, WHITE);

            //Desenhar o chão
            DrawTexture(background, groundX1, screenheight - background.height, WHITE);
            DrawTexture(background, groundX2, screenheight - background.height, WHITE);

            //Parte responsável pela animação das asas durante a gameplay
                    (timer)++;
            if (timer >= frameSpeed)
            {
                frameAtual++;
                if (frameAtual > 2)
                {
                    frameAtual = 0;
                }
                timer = 0;
            }

            // Asas batendo
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

            //Futuros elementos


            //Coisas relacionadas às colisões
            Rectangle player = {posX-38, posY-65, 75, 50};
            bool onFloor = CheckCollisionRecs(player, Floor);
            bool onRoof = CheckCollisionRecs(player, Roof);

            MoveCanos(&score, &tube1X, &tube1Y, pontos);

            Rectangle tubetop = {tube1X, tube1Y, tube1W-20, tube1H};
            Rectangle tubebottom = {tube1X, tube1Y+450+200, tube2W, tube2H+100};
            bool onTube = CheckCollisionRecs(player, tubetop);
            bool onTube2 = CheckCollisionRecs(player, tubebottom);

            //Condicional de colisão com o teto
            if(onRoof)
            {
                speedpassaro = 1;
            }

            //Condicional de colisão com o chão
            if(onFloor ||onTube || onTube2)
            {
                PlaySound(bateu);
                derrota(&FloorX, &FloorY, &FloorW, &FloorH,  &RoofX, &RoofY, &RoofW, &RoofH, &tube1X, &tube1Y, &tube1W, &tube1H, &tube2X, &tube2Y, &tube2W, &tube2H, &posX, &posY, &recorde, &score, &estadojogo );
            }

            DrawTexture(Tubocima, tube1X, tube1Y-30, WHITE);
            DrawTexture(Tubobaixo, tube1X, tube1Y+450+200-20, WHITE);
            //DrawRectangleRec(tubetop, GOLD);
            //DrawRectangleRec(tubebottom, GOLD);
            //DrawRectangleRec(player, PURPLE);
            DrawText(TextFormat("Score: %d", score), 80, 0, 50, YELLOW);

            EndDrawing();
        }
    }

    //Limpar e fechar
    UnloadTexture(background);
    CloseWindow();

    return 0;

}
