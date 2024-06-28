#ifndef ASSETS_H
#define ASSETS_H

#include <raylib.h>

typedef struct Assets {
  Texture2D background;
  Texture2D base;
  Texture2D bird_downflap;
  Texture2D bird_midflap;
  Texture2D bird_upflap;
} Assets;

Assets LoadAssets();
void UnloadAssets(Assets assets);

#endif
