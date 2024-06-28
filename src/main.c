#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include <assets.h>
#include <bird.h>
#include <pipes.h>

int main()
{
  srand(time(0));
  InitWindow(3 * 288, 3 * 512, "Flip");

  Assets assets = LoadAssets();
  Bird player = NewBird(assets);
  Pipes pipes = NewPipes(assets);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BirdUpdate(&player);
    PipesUpdate(&pipes);

    BeginDrawing();

    DrawTexture(assets.background, 0, 0, WHITE);

    PipesDraw(pipes);

    DrawTexture(assets.base, 0, GetScreenHeight() - assets.base.height, WHITE);

    BirdDraw(player);

    EndDrawing();
  }

  DelPipes(pipes);
  DelBird(player);
  UnloadAssets(assets);
  CloseWindow();
}
