#include <stdio.h>
#include <string.h>
#include <raylib.h>

#include <bird.h>

static Texture2D LoadAndScaleTexture(const char* fileName, float factor)
{
  Image img = LoadImage(fileName);
  ImageResize(&img, factor * img.width, factor * img.height);
  return LoadTextureFromImage(img);
}

static Texture2D* LoadFrames(const char* name)
{
  char downflap[strlen(name) + 20 + 1];
  char midflap[strlen(name) + 19 + 1];
  char upflap[strlen(name) + 18 + 1];
  sprintf(downflap, "assets/%s-downflap.png", name);
  sprintf(midflap, "assets/%s-midflap.png", name);
  sprintf(upflap, "assets/%s-upflap.png", name);

  Texture2D* frames = malloc(3 * sizeof(Texture2D));
  frames[0] = LoadAndScaleTexture(downflap, 2.5f);
  frames[1] = LoadAndScaleTexture(midflap, 2.5f);
  frames[2] = LoadAndScaleTexture(upflap, 2.5f);

  return frames;
}

Bird* NewBird(const char* name)
{
  Texture2D* frames = LoadFrames(name);

  Bird* b = malloc(sizeof(Bird));
  b->accel_y = 1500.0f;
  b->vel_y = 0.0f;
  b->pos = (Vector2){
    (GetScreenWidth() - frames[0].width) / 2.0f,
    (GetScreenHeight() - frames[0].height) / 2.0f,
  };
  b->anim = NewAnim(frames, 3, 0.2f);

  return b;
}

void DelBird(Bird* b)
{
  DelAnim(b->anim);
  free(b);
}

void BirdUpdate(Bird* b)
{
  if (IsKeyPressed(KEY_SPACE)) b->vel_y = -800.0f;

  float dt = GetFrameTime();
  AnimTick(b->anim, dt);
  b->pos.y += 0.5f * b->accel_y * dt * dt + b->vel_y * dt;
  b->vel_y += b->accel_y * dt;
}

void BirdDraw(Bird* b)
{
  DrawTextureV(AnimCurrent(b->anim), b->pos, WHITE);
}
