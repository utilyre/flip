#include <stdlib.h>
#include <time.h>
#include <math.h>
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

  const float PIPE_SPACING = 400.0f;
  const float PIPE_VEL_X = -250.0f;
  const float HOLE_SIZE = 250.0f;
  const float HOLE_PADDING = 100.0f;

  size_t pipes_len = ceilf((WINDOW_WIDTH - assets.pipe_above.width) / (PIPE_SPACING + assets.pipe_above.width)) + 1;
  Vector2 pipes[pipes_len];
  for (size_t i = 0; i < pipes_len; i++)
  {
    pipes[i].x = WINDOW_WIDTH + i * (PIPE_SPACING + assets.pipe_above.width);
    pipes[i].y = HOLE_PADDING + rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - 2.0f * HOLE_PADDING - assets.base.height);
  }

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BirdUpdate(&player);

    for (size_t i = 0; i < pipes_len; i++)
    {
      Vector2* pipe = &pipes[i];
      pipe->x += PIPE_VEL_X * GetFrameTime();
      if (pipe->x <= -assets.pipe_above.width) {
        pipe->x += pipes_len * (assets.pipe_above.width + PIPE_SPACING);
        pipe->y = rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING;
      }
    }

    BeginDrawing();

    DrawTexture(assets.background, 0, 0, WHITE);

    for (size_t i = 0; i < pipes_len; i++)
    {
      Vector2 pipe = pipes[i];
      DrawTexture(assets.pipe_above, pipe.x, pipe.y - assets.pipe_above.height, WHITE);
      DrawTexture(assets.pipe_below, pipe.x, pipe.y + HOLE_SIZE, WHITE);
    }

    DrawTexture(assets.base, 0, WINDOW_HEIGHT - assets.base.height, WHITE);

    BirdDraw(player);

    EndDrawing();
  }

  DelBird(player);
  UnloadAssets(assets);
  CloseWindow();
}
