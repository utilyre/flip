#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;
static const char* WINDOW_TITLE = "Flip";

typedef struct Timer {
  bool repeat;
  float duration;

  // bool finished;
  float elapsed;
} Timer;

Timer* new_timer(bool repeat, float duration)
{
  Timer* t = malloc(sizeof(Timer));
  t->repeat = repeat;
  t->duration = duration;
  // t->finished = false;
  t->elapsed = 0.0f;

  return t;
}

bool timer_tick(Timer* t, float delta)
{
  t->elapsed += delta;
  if (t->elapsed > t->duration) {
    t->elapsed = t->repeat ? 0.0f : t->duration;
    return true;
  }

  return false;
}

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  size_t bird_anim_frame = 0;
  Timer* bird_anim_timer = new_timer(true, 0.2f);
  Texture bird_anim_frames[] = {
    LoadTexture("assets/bluebird-downflap.png"),
    LoadTexture("assets/bluebird-midflap.png"),
    LoadTexture("assets/bluebird-upflap.png"),
  };

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();

    if (timer_tick(bird_anim_timer, GetFrameTime()))
    {
      bird_anim_frame = (bird_anim_frame + 1) % (sizeof(bird_anim_frames)/sizeof(bird_anim_frames[0]));
    }

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(bird_anim_frames[bird_anim_frame], WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WHITE);

    EndDrawing();
  }

  for (size_t i = 0; i < sizeof(bird_anim_frames)/sizeof(bird_anim_frames[0]); i++)
  {
    UnloadTexture(bird_anim_frames[i]);
  }

  free(bird_anim_timer);
  CloseWindow();
}
