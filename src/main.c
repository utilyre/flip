#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include <assets.h>
#include <bird.h>

static const int WINDOW_WIDTH = 3 * 288;
static const int WINDOW_HEIGHT = 3 * 512;
static const char* WINDOW_TITLE = "Flip";

int main()
{
  srand(time(0));
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  Assets assets = LoadAssets();
  Bird player = NewBird(assets);

  const float PIPE_VEL_X = -250.0f;
  const float HOLE_SIZE = 250.0f;
  const float HOLE_PADDING = 100.0f;
  Vector2 hole = {
    WINDOW_WIDTH,
    rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING,
  };

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BirdUpdate(&player);

    hole.x += PIPE_VEL_X * GetFrameTime();
    if (hole.x <= -assets.pipe_above.width) {
      hole.x = GetScreenWidth();
      hole.y = rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING;
    }

    BeginDrawing();

    DrawTexture(assets.background, 0, 0, WHITE);

    DrawTexture(assets.pipe_above, hole.x, hole.y - assets.pipe_above.height, WHITE);
    DrawTexture(assets.pipe_below, hole.x, hole.y + HOLE_SIZE, WHITE);

    DrawTexture(assets.base, 0, WINDOW_HEIGHT - assets.base.height, WHITE);

    BirdDraw(player);

    EndDrawing();
  }

  DelBird(player);
  UnloadAssets(assets);
  CloseWindow();
}
