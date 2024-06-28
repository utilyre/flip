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

  const float PIPE_SPACING = 400.0f;
  const float PIPE_VEL_X = -250.0f;
  const float HOLE_SIZE = 250.0f;
  const float HOLE_PADDING = 100.0f;

  Vector2 pipes[] = {
    {
      WINDOW_WIDTH,
      rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING,
    },
    {
      WINDOW_WIDTH + PIPE_SPACING + assets.pipe_above.width,
      rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING,
    },
    {
      WINDOW_WIDTH + 2.0f * (PIPE_SPACING + assets.pipe_above.width),
      rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING,
    },
  };

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BirdUpdate(&player);

    for (size_t i = 0; i < 3; i++)
    {
      Vector2* pipe = &pipes[i];
      pipe->x += PIPE_VEL_X * GetFrameTime();
      if (pipe->x <= -assets.pipe_above.width) {
        pipe->x += 3 * (assets.pipe_above.width + PIPE_SPACING);
        pipe->y = rand() % (int)(WINDOW_HEIGHT - HOLE_SIZE - assets.base.height - 2.0f * HOLE_PADDING) + HOLE_PADDING;
      }
    }

    BeginDrawing();

    DrawTexture(assets.background, 0, 0, WHITE);

    for (size_t i = 0; i < 3; i++)
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
