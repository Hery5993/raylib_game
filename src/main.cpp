#include <raylib.h>
#include <map>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    const int Width = 1200;
    const int Height = 800;

    InitWindow(Width, Height, "My First Window Using Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}