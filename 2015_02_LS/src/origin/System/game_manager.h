
#pragma once
#include "window_create.h"
#include "../../lib/font.hpp"
#include "../Object/collision.h"

//
// ƒQ[ƒ€ŠÇ—ƒNƒ‰ƒX
//

class GameManager {
  //a

  void title();
  void game();

  void mode_select();
  void pause();
  void stage_select();
  void stage_play();
  void result();

public:
  GameManager();
  bool EXIT;
  void play();
};
