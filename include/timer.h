#ifndef TIMER_H
#define TIMER_H

typedef struct Timer {
  bool repeat;
  float duration;

  float elapsed;
} Timer;

Timer* NewTimer(bool repeat, float duration);
void DelTimer(Timer* t);
bool TimerTick(Timer* t, float delta);

#endif
