#include <math.h>
#include <raylib.h>

#include <pipes.h>

Pipes NewPipes(Assets assets)
{
  float padding = 100.0f;
  float spacing = 400.0f;
  float base_height = assets.base.height;
  float hole_size = 250.0f;
  size_t pipes_len = ceilf((GetScreenWidth() - assets.pipe_above.width) / (spacing + assets.pipe_above.width)) + 1;

  Vector2* pipes = malloc(pipes_len * sizeof(Vector2));
  for (size_t i = 0; i < pipes_len; i++)
  {
    pipes[i].x = GetScreenWidth() + i * (spacing + assets.pipe_above.width);
    pipes[i].y = padding + rand() % (int)(GetScreenHeight() - hole_size - 2.0f * padding - base_height);
  }

  return (Pipes){
    .padding = padding,
    .spacing = spacing,
    .base_height = base_height,
    .hole_size = hole_size,
    .min_speed = 250.0f,
    .max_speed = 500.0f,
    .pipes = pipes,
    .pipes_len = pipes_len,
    .pipe_above = assets.pipe_above,
    .pipe_below = assets.pipe_below,
  };
}

static float explerp(float rate, float a, float b, float x)
{
  return (a - b) * pow(rate, -x) + b;
}

void PipesUpdate(Pipes* p)
{
  p->vel_x = explerp(1.01, -p->min_speed, -p->max_speed, GetTime());

  for (size_t i = 0; i < p->pipes_len; i++)
  {
    Vector2* pipe = &p->pipes[i];
    pipe->x += p->vel_x * GetFrameTime();
    if (pipe->x <= -p->pipe_above.width) {
      pipe->x += p->pipes_len * (p->pipe_above.width + p->spacing);
      pipe->y = p->padding + rand() % (int)(GetScreenHeight() - p->hole_size - p->base_height - 2.0f * p->padding);
    }
  }
}

void PipesDraw(Pipes p)
{
  for (size_t i = 0; i < p.pipes_len; i++)
  {
    Vector2 pipe = p.pipes[i];
    DrawTexture(p.pipe_above, pipe.x, pipe.y - p.pipe_above.height, WHITE);
    DrawTexture(p.pipe_below, pipe.x, pipe.y + p.hole_size, WHITE);
  }
}

void DelPipes(Pipes p)
{
  free(p.pipes);
}
