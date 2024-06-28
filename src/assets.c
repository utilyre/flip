#include <raylib.h>

#include <assets.h>

static Texture2D LoadAndScaleTextureTo(const char* fileName, int width)
{
  Image img = LoadImage(fileName);
  ImageResize(&img, width, width * img.height / img.width);
  Texture2D tex = LoadTextureFromImage(img);
  UnloadImage(img);
  return tex;
}

static Texture2D LoadAndScaleTexture(const char* fileName, float factor)
{
  Image img = LoadImage(fileName);
  ImageResize(&img, factor * img.width, factor * img.height);
  Texture2D tex = LoadTextureFromImage(img);
  UnloadImage(img);
  return tex;
}

Assets LoadAssets()
{
  Texture2D background = LoadAndScaleTextureTo("assets/background-day.png", GetScreenWidth());
  Texture2D base = LoadAndScaleTextureTo("assets/base.png", GetScreenWidth());

  Texture2D bird_downflap = LoadAndScaleTexture("assets/bluebird-downflap.png", 2.5f);
  Texture2D bird_midflap = LoadAndScaleTexture("assets/bluebird-midflap.png", 2.5f);
  Texture2D bird_upflap = LoadAndScaleTexture("assets/bluebird-upflap.png", 2.5f);

  Image pipe_rev = LoadImage("assets/pipe-green.png");
  ImageFlipVertical(&pipe_rev);
  ImageResize(&pipe_rev, 3.0f * pipe_rev.width, 3.0f * pipe_rev.height);
  Texture2D pipe_above = LoadTextureFromImage(pipe_rev);
  Texture2D pipe_below = LoadAndScaleTexture("assets/pipe-green.png", 3.0f);

  return (Assets){
    .background = background,
    .base = base,
    .bird_downflap = bird_downflap,
    .bird_midflap = bird_midflap,
    .bird_upflap = bird_upflap,
    .pipe_above = pipe_above,
    .pipe_below = pipe_below,
  };
}

void UnloadAssets(Assets assets)
{
  // in the reverse order of loading
  UnloadTexture(assets.pipe_below);
  UnloadTexture(assets.pipe_above);
  UnloadTexture(assets.bird_upflap);
  UnloadTexture(assets.bird_midflap);
  UnloadTexture(assets.bird_downflap);
  UnloadTexture(assets.base);
  UnloadTexture(assets.background);
}
