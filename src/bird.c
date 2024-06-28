#include <raylib.h>

#include <assets.h>
#include <bird.h>

static const float BIRD_JUMP_SPEED = 600.0f;
static const float BIRD_ANIM_DURATION = 0.6f;

Bird* NewBird(Assets assets)
{
  Bird* b = malloc(sizeof(Bird));
  b->accel_y = 1500.0f;
  b->vel_y = 0.0f;
  b->pos = (Vector2){
    0.5f * (GetScreenWidth() - assets.bird_downflap.width),
    0.5f * (GetScreenHeight() - assets.bird_downflap.height),
  };

  Texture2D* frames = malloc(3 * sizeof(Texture2D));
  frames[0] = assets.bird_downflap;
  frames[1] = assets.bird_midflap;
  frames[2] = assets.bird_upflap;
  b->anim = NewAnim(frames, 3, BIRD_ANIM_DURATION / 3);

  return b;
}

void DelBird(Bird* b)
{
  DelAnim(b->anim);
  free(b);
}

void BirdUpdate(Bird* b)
{
  if (IsKeyPressed(KEY_SPACE)) b->vel_y = -BIRD_JUMP_SPEED;

  float dt = GetFrameTime();
  AnimTick(b->anim, dt);
  b->pos.y += 0.5f * b->accel_y * dt * dt + b->vel_y * dt;
  b->vel_y += b->accel_y * dt;
}

void BirdDraw(Bird* b)
{
  DrawTextureV(AnimCurrent(b->anim), b->pos, WHITE);
}
