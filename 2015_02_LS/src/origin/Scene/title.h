
#pragma once
#include "../System/window_create.h"
#include "../../lib/font.hpp"

//
// ƒ^ƒCƒgƒ‹‰æ–Ê
//

class Title {
  std::unique_ptr<Font> font;

  Texture BG;

public:
  Title();

  void draw();
  void update();

  void reset();
};
