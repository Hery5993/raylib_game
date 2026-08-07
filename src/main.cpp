#include <raylib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <random>

int player_score = 0;
int cpu_score = 0;

class Ball{
    public:
        float x, y;
        int dx, dy;
        int radius;

        void draw(){
            // Draw the ball
            DrawCircle(x, y, radius, WHITE);
        }

        void update(){
            // update the position of the ball
            x += dx;
            y += dy;

            if(y + radius > GetScreenHeight() || y - radius <= 0)
                dy *= -1;

            if(x + radius >= GetScreenWidth()){
                dx *= -1;
                cpu_score++;
            }

            if(x -radius <= 0){
                dx *= -1;
                player_score++;
            }

        }
};


class Paddle{
    public:
        float x, y;
        float width, height;
        int speed;

        void draw(){
            DrawRectangle(x, y, width, height, WHITE);
        }

        void update(){
            if(IsKeyDown(KEY_UP))
                y = std::max<float>(0, y - speed);
            else if (IsKeyDown(KEY_DOWN))
                y = std::min<float>(GetScreenHeight() - height, y + speed);
        }
};

class CpuPaddle: public Paddle{
    public:
        void update(const Ball & ball){
            // Ne bouger que si la balle vient vers le CPU
            if(ball.dx >= 0)
                return;

            if(y + height/2 > ball.y)
                y = std::max<float>(0, y - speed);
            
            if(y + height/2 < ball.y )
                y = std::min<float>(GetScreenHeight() - height, y + speed);
        }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
    const int screen_width = 1200;
    const int screen_height = 800;

    const int paddle_width = 25;
    const int paddle_height = 120;

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.dx = 7;
    ball.dy = 7;

    player.width = 25;
    player.height = 120;
    player.speed = 7;
    player.x = screen_width - player.width - 10;
    player.y = screen_height/2 - player.height / 2;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;


    InitWindow(screen_width, screen_height, "My First Window Using Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Update the ball
        ball.update();
        player.update();
        cpu.update(ball);

        // Check Collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            ball.dx *= -1;
        
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            ball.dx *= -1;
    
        // Clear background
        ClearBackground(BLACK);

        // Draw separation line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        // Draw the ball
        ball.draw();

        // Draw the paddles
        cpu.draw();
        player.draw();

        // Show the scoring
        DrawText(TextFormat("%i", cpu_score), screen_width / 4, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), screen_width * 3 / 4, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}