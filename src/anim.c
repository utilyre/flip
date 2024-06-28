#include <anim.h>

Anim NewAnim(float duration, Texture2D* frames, size_t len)
{
  return (Anim){
    .timer = NewTimer(true, duration),
    .frames = frames,
    .frames_len = len,
    .curr = 0,
  };
}

void DelAnim(Anim a)
{
  free(a.frames);
}

Texture2D AnimCurrent(Anim a)
{
  return a.frames[a.curr];
}

void AnimTick(Anim* a, float delta)
{
  if (TimerTick(&a->timer, delta))
  {
    a->curr = (a->curr + 1) % a->frames_len;
  }
}
