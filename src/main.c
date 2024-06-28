#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include <assets.h>
#include <bird.h>
#include <pipes.h>

static const int WINDOW_WIDTH = 3 * 288;
static const int WINDOW_HEIGHT = 3 * 512;
static const char* WINDOW_TITLE = "Flip";

int main()
{
  srand(time(0));
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

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

    DrawTexture(assets.base, 0, WINDOW_HEIGHT - assets.base.height, WHITE);

    BirdDraw(player);

    EndDrawing();
  }

  DelPipes(pipes);
  DelBird(player);
  UnloadAssets(assets);
  CloseWindow();
}
