#include <stdlib.h>
#include <raylib.h>

#include <timer.h>

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;
static const char* WINDOW_TITLE = "Flip";

Texture2D LoadAndScaleTexture(const char* fileName, float factor)
{
  Image img = LoadImage(fileName);
  ImageResize(&img, factor * img.width, factor * img.height);
  return LoadTextureFromImage(img);
}

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  size_t bird_anim_frame = 0;
  Timer* bird_anim_timer = NewTimer(true, 0.2f);
  Texture bird_anim_frames[] = {
    LoadAndScaleTexture("assets/bluebird-downflap.png", 4),
    LoadAndScaleTexture("assets/bluebird-midflap.png", 4),
    LoadAndScaleTexture("assets/bluebird-upflap.png", 4),
  };

  const float BIRD_ACCEL = 1500.0f;
  Vector2 bird_vel = {0};
  Vector2 bird_pos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    if (IsKeyPressed(KEY_F)) ToggleFullscreen();
    if (IsKeyPressed(KEY_SPACE)) bird_vel.y = -800.0f;

    if (TimerTick(bird_anim_timer, dt))
    {
      bird_anim_frame = (bird_anim_frame + 1) % (sizeof(bird_anim_frames)/sizeof(bird_anim_frames[0]));
    }

    bird_pos.y += 0.5f * BIRD_ACCEL * dt * dt + bird_vel.y * dt;
    bird_vel.y += BIRD_ACCEL * dt;

    BeginDrawing();
    ClearBackground((Color){78, 192, 202, 255});

    DrawTextureV(bird_anim_frames[bird_anim_frame], bird_pos, WHITE);

    EndDrawing();
  }

  for (size_t i = 0; i < sizeof(bird_anim_frames)/sizeof(bird_anim_frames[0]); i++)
  {
    UnloadTexture(bird_anim_frames[i]);
  }
  free(bird_anim_timer);

  CloseWindow();
}
