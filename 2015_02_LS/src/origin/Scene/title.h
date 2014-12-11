
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"

//
// ƒ^ƒCƒgƒ‹‰æ–Ê
//

class Title {
  std::unique_ptr<Font> font;

  void draw_bg();
  void draw_logo();

public:
  Title();

  void draw();
};
