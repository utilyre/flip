#include <raylib.h>

#include <bird.h>

static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 900;
static const char* WINDOW_TITLE = "Flip";

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  Bird* bird = NewBird("bluebird");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();
    BirdUpdate(bird);

    BeginDrawing();
    ClearBackground((Color){78, 192, 202, 255});

    BirdDraw(bird);

    EndDrawing();
  }

  UnloadBird(bird);
  CloseWindow();
}
