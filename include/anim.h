#ifndef ANIM_H
#define ANIM_H

#include <stdlib.h>
#include <raylib.h>

#include <timer.h>

typedef struct Anim {
  size_t curr;
  size_t frames_len;
  Texture2D* frames;
  Timer* timer;
} Anim;

Anim* NewAnim(Texture2D* frames, size_t len, float duration);
void AnimTick(Anim* a, float delta);
Texture2D AnimCurrent(const Anim* a);
void UnloadAnim(Anim* a);

#endif
