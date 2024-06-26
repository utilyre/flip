#include <stdio.h>
#include <raylib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1600;
  const int screenHeight = 900;

  float radius = 40.0f;
  Vector2 pos = {.x = 0.5f * screenWidth, .y = 0.5f * screenHeight};
  Vector2 vel = {.x = 150.0f, .y = 150.0f};

  Color colors[] = {RED, GREEN, BLUE};
  size_t color_idx = 0;

  InitWindow(screenWidth, screenHeight, "Flip");

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    float dt =GetFrameTime();

    pos.x += dt * vel.x;
    pos.y += dt * vel.y;

    if (pos.x <= radius || pos.x >= screenWidth - radius) {
      vel.x = -vel.x;
      color_idx = (color_idx + 1) % 3;
    }
    if (pos.y <= radius || pos.y >= screenHeight - radius) {
      vel.y = -vel.y;
      color_idx = (color_idx + 1) % 3;
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);
    DrawCircle(pos.x, pos.y, radius, colors[color_idx]);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
