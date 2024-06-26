#include <raylib.h>

#include <anim.h>

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;
static const char* WINDOW_TITLE = "Flip";

// typedef struct Bird {
// } Bird;

Texture2D LoadAndScaleTexture(const char* fileName, float factor)
{
  Image img = LoadImage(fileName);
  ImageResize(&img, factor * img.width, factor * img.height);
  return LoadTextureFromImage(img);
}

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  Texture2D bird_anim_frames[] = {
    LoadAndScaleTexture("assets/bluebird-downflap.png", 4),
    LoadAndScaleTexture("assets/bluebird-midflap.png", 4),
    LoadAndScaleTexture("assets/bluebird-upflap.png", 4),
  };
  Anim* bird_anim = NewAnim(bird_anim_frames, sizeof(bird_anim_frames)/sizeof(bird_anim_frames[0]), 0.2f);

  const float BIRD_ACCEL = 1500.0f;
  Vector2 bird_vel = {0};
  Vector2 bird_pos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    if (IsKeyPressed(KEY_F)) ToggleFullscreen();
    if (IsKeyPressed(KEY_SPACE)) bird_vel.y = -800.0f;

    AnimTick(bird_anim, dt);

    bird_pos.y += 0.5f * BIRD_ACCEL * dt * dt + bird_vel.y * dt;
    bird_vel.y += BIRD_ACCEL * dt;

    BeginDrawing();
    ClearBackground((Color){78, 192, 202, 255});

    DrawTextureV(AnimCurrent(bird_anim), bird_pos, WHITE);

    EndDrawing();
  }

  UnloadAnim(bird_anim);
  CloseWindow();
}
