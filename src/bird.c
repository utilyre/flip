#include <raylib.h>

#include <assets.h>
#include <anim.h>
#include <bird.h>

Bird NewBird(Assets assets)
{
  Texture2D* frames = malloc(3 * sizeof(Texture2D));
  frames[0] = assets.bird_downflap;
  frames[1] = assets.bird_midflap;
  frames[2] = assets.bird_upflap;

  return (Bird){
    .accel_y = 1500.0f,
    .jmp_vel_y = -600.0f,
    .vel_y = 0.0f,
    .pos = (Vector2){
      0.5f * (GetScreenWidth() - assets.bird_downflap.width),
      0.5f * (GetScreenHeight() - assets.bird_downflap.height),
    },
    .anim = NewAnim(0.2f, frames, 3),
};
}

void DelBird(Bird b)
{
  DelAnim(b.anim);
}

void BirdUpdate(Bird* b)
{
  if (IsKeyPressed(KEY_SPACE)) b->vel_y = b->jmp_vel_y;

  float dt = GetFrameTime();
  AnimTick(&b->anim, dt);
  b->pos.y += 0.5f * b->accel_y * dt * dt + b->vel_y * dt;
  b->vel_y += b->accel_y * dt;
}

void BirdDraw(Bird b)
{
  DrawTextureV(AnimCurrent(b.anim), b.pos, WHITE);
}
