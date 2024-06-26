#include <anim.h>

Anim* NewAnim(Texture2D* frames, size_t len, float duration)
{
  Anim* a = malloc(sizeof(Anim));
  a->curr = 0;
  a->frames_len = len;
  a->frames = frames;
  a->timer = NewTimer(true, duration);
  return a;
}

void AnimTick(Anim* a, float delta)
{
  if (TimerTick(a->timer, delta))
  {
    a->curr = (a->curr + 1) % a->frames_len;
  }
}

Texture2D AnimCurrent(const Anim* a)
{
  return a->frames[a->curr];
}

void UnloadAnim(Anim* a)
{
  UnloadTimer(a->timer);
  free(a->frames);
  free(a);
}
