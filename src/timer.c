#include <stdlib.h>

#include <timer.h>

Timer* NewTimer(bool repeat, float duration)
{
  Timer* t = malloc(sizeof(Timer));
  t->repeat = repeat;
  t->duration = duration;
  t->elapsed = 0.0f;

  return t;
}

bool TimerTick(Timer* t, float delta)
{
  t->elapsed += delta;
  if (t->elapsed > t->duration) {
    t->elapsed = t->repeat ? 0.0f : t->duration;
    return true;
  }

  return false;
}
