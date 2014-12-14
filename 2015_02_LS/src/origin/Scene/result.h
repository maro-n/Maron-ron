
#pragma once
#include "../System/window_create.h"
#include "../Object/collision.h"

//
// ƒŠƒUƒ‹ƒg‰æ–Ê
//

class Result {
  Vec2f cmd[2];
  Vec2f size;
  Color color[2];

  Texture BG;

  void stage_clear();
  void game_over();
  void game_clear();

public:
  Result();

  void draw();
  void update(bool&, bool&);

  void reset();
};
