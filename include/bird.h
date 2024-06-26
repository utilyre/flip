#ifndef BIRD_H
#define BIRD_H

#include <raylib.h>
#include <anim.h>

typedef struct Bird {
  float accel_y;
  float vel_y;
  Vector2 pos;
  Anim* anim;
} Bird;

Bird* NewBird(const char* name);
void UnloadBird(Bird* b);
void BirdUpdate(Bird* b);
void BirdDraw(Bird* b);

#endif
