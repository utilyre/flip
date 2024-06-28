#include <raylib.h>

#include <assets.h>
#include <bird.h>

static const int WINDOW_WIDTH = 3 * 288;
static const int WINDOW_HEIGHT = 3 * 512;
static const char* WINDOW_TITLE = "Flip";

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  Assets assets = LoadAssets();
  Bird* bird = NewBird(assets);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();
    BirdUpdate(bird);

    BeginDrawing();

    DrawTexture(assets.background, 0, 0, WHITE);
    DrawTexture(assets.base, 0, WINDOW_HEIGHT - assets.base.height, WHITE);

    BirdDraw(bird);

    EndDrawing();
  }

  DelBird(bird);
  UnloadAssets(assets);
  CloseWindow();
}
