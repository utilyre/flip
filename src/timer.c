#include <timer.h>

Timer NewTimer(bool repeat, float duration)
{
  return (Timer){
    .repeat = repeat,
    .duration = duration,
    .elapsed = 0.0f,
  };
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
