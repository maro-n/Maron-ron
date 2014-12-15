
#pragma once
#include "window_create.h"
#include "../../lib/font.hpp"
#include "../Object/collision.h"
#include "../Scene/result.h"
#include "../Scene/title.h"
#include "../Game/stage_select.h"

//
// ƒQ[ƒ€ŠÇ—ƒNƒ‰ƒX
//

class GameManager {
  //a

  int win_judge;

  Title title_;
  StageSelect stage_select_;
  Result result_;

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
