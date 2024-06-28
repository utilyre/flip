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

  return (Assets){
    .background = background,
    .base = base,
    .bird_downflap = bird_downflap,
    .bird_midflap = bird_midflap,
    .bird_upflap = bird_upflap,
  };
}

void UnloadAssets(Assets assets)
{
  // in the reverse order of loading
  UnloadTexture(assets.bird_upflap);
  UnloadTexture(assets.bird_midflap);
  UnloadTexture(assets.bird_downflap);
  UnloadTexture(assets.base);
  UnloadTexture(assets.background);
}
