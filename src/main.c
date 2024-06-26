#include <math.h>
#include <raylib.h>

float clamp(float f, float min, float max) {
  const float t = f < min ? min : f;
  return t > max ? max : t;
}

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
  float vel = 300.0f;

  InitWindow(screenWidth, screenHeight, "Flip");

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    float dt =GetFrameTime();

    Vector2 dr = {0};
    if (IsKeyDown(KEY_W)) dr.y -= 1.0f;
    if (IsKeyDown(KEY_A)) dr.x -= 1.0f;
    if (IsKeyDown(KEY_S)) dr.y += 1.0f;
    if (IsKeyDown(KEY_D)) dr.x += 1.0f;

    float len = sqrt(dr.x*dr.x + dr.y*dr.y);
    if (len > 0) {
      dr.x /= len;
      dr.y /= len;
    }

    pos.x = clamp(pos.x + vel * dr.x * dt, radius, screenWidth - radius);
    pos.y = clamp(pos.y + vel * dr.y * dt, radius, screenHeight - radius);

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);
    DrawCircle(pos.x, pos.y, radius, RED);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
