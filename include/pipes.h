#ifndef PIPES_H
#define PIPES_H

#include <stdlib.h>
#include <raylib.h>

#include <assets.h>

typedef struct Pipes {
  float padding;
  float spacing; // TODO: increase as the time goes
  float base_height;
  float hole_size;
  float min_speed;
  float max_speed;
  float vel_x;
  Vector2* pipes;
  size_t pipes_len;
  Texture2D pipe_above;
  Texture2D pipe_below;
} Pipes;

Pipes NewPipes(Assets assets);
void PipesUpdate(Pipes* p);
void PipesDraw(Pipes p);
void DelPipes(Pipes p);

#endif
