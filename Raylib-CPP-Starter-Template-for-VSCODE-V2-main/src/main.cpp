#include "raylib.h"
#include<iterator>
using namespace std;
//Define a structure for the rctabgles
struct Obstacle {
    int posX;
    int posY;
    int width;
    int height;
    bool scored;
};
int main()
{
    int width= 800;
    int height= 450;

    int score = 0;

    int columnWidth =100;
    int randomHeight;//rondomVerticalPosition;
    randomHeight =GetRandomValue(100, 150);
    int upperHeight;
    int xPosObstacle = width - columnWidth;
    int yPosObstacle = height - randomHeight;
    

    Obstacle obstacles[100] = {
        {xPosObstacle,yPosObstacle,columnWidth,randomHeight,false},
        {xPosObstacle,0,columnWidth,randomHeight,false},
    };
    int numberOfObstacles = 2;
    float intervalAddNewObstacle = 2.0;
    float spawnTimer = 0;

    InitWindow(width, height,"Game");

    //player
    Vector2 playerPosition = {300,225};
    float speed = 2.0;
    float r= 20.0;

    bool gameOver = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if(!gameOver){
            playerPosition.y += speed;
            if(playerPosition.y >= (height-r)){
                gameOver= true;
            }


        }

        //check score
        for(int i = 0; i < numberOfObstacles; i += 2){
            if(!obstacles[i].scored && obstacles[i].posX + columnWidth < playerPosition.x){
                score++;
                obstacles[i].scored = true;
                obstacles[i+1].scored = true;
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Spawn the obstacles logic
        spawnTimer += GetFrameTime();

        if(spawnTimer >= intervalAddNewObstacle){
            if(numberOfObstacles == 10){
                for (int i = 0; i < numberOfObstacles - 1; i++) {
                    obstacles[i] = obstacles[i + 1];
                }

                numberOfObstacles--;
            }

            randomHeight = GetRandomValue(100, 220);
            upperHeight = GetRandomValue(100,140);

            obstacles[numberOfObstacles] = {
                width - columnWidth,
                0,
                columnWidth,
                upperHeight,
                false
            };
            numberOfObstacles++;

            obstacles[numberOfObstacles] = {
                width - columnWidth,
                height - randomHeight,
                columnWidth,
                randomHeight,
                false
            };

            numberOfObstacles++;

            spawnTimer = 0;
        }

        if(IsKeyPressed(KEY_SPACE)){
            playerPosition.y -= speed+30;
        }

        if(!gameOver){
            for(int i = 0; i < numberOfObstacles; i++){
                obstacles[i].posX -= 150 * GetFrameTime();
            }
            DrawCircleV(playerPosition, r, RED);
            for (int i = 0; i < numberOfObstacles; i++) {
                DrawRectangle(
                    obstacles[i].posX,
                    obstacles[i].posY,
                    obstacles[i].width,
                    obstacles[i].height,
                    BLUE
                );
            }
            //check for collison
            for (int i = 0; i < numberOfObstacles; i++) {
                Rectangle obstacleRect = {
                    (float)obstacles[i].posX,
                    (float)obstacles[i].posY,
                    (float)obstacles[i].width,
                    (float)obstacles[i].height
                };

                if (CheckCollisionCircleRec(playerPosition, r, obstacleRect)) {
                    gameOver = true;
                }
            } 
        }
        else{
            DrawText("Game Over!!",width/2-100,height/2,50,RED);
        }
        DrawText(TextFormat("Score: %i", score), 20, 20, 30, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}