#ifndef ANIM_H
#define ANIM_H

#include <stdlib.h>
#include <raylib.h>

#include <timer.h>

typedef struct Anim {
  Timer timer;
  Texture2D* frames;
  size_t frames_len;
  size_t curr;
} Anim;

Anim NewAnim(float duration, Texture2D* frames, size_t len);
void DelAnim(Anim a);
Texture2D AnimCurrent(Anim a);
void AnimTick(Anim* a, float delta);

#endif
