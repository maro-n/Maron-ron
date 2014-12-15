
#pragma once
#include "../System/window_create.h"
#include "../../lib/random.hpp"
#include "../Object/collision.h"
#include <ctime>

//
// ステージ選択画面
//

struct Button {
  Vec2f pos;
  Color color;
  int mode;

  Button() {}
  Button(Vec2f pos0, Color col, int m) {
    pos = pos0;
    color = col;
    mode = m;
  }
};

class StageSelect {
  Texture BG;

  Button button[12];
  Random random;
  Col color_variation;

  int r;
  int on_box;
  int click_pos;

public:
  StageSelect();

  void draw();
  void update(bool&);

  void reset();

  void win();
};
