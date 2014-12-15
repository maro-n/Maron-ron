
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"

//
// タイトル画面
//

class Title {
  std::unique_ptr<Font> font;

  Texture bg;

  void draw_bg();
  void draw_logo();

public:
  Title();

  void draw();
  void update();

  void reset();
};
