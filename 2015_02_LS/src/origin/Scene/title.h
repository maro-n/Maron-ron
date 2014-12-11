
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"

//
// タイトル画面
//

class Title {
  std::unique_ptr<Font> font;

  Texture BG;
  void draw_bg();
  void draw_logo();

public:
  Title();

  void draw();
};
