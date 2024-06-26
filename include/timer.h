#ifndef TIMER_H
#define TIMER_H

typedef struct Timer {
  bool repeat;
  float duration;

  float elapsed;
} Timer;

Timer* NewTimer(bool repeat, float duration);
bool TimerTick(Timer* t, float delta);
void UnloadTimer(Timer* t);

#endif
