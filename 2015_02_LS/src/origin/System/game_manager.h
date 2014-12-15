
#pragma once
#include "window_create.h"
#include "../../lib/font.hpp"
#include "../Scene/result.h"
#include "../Scene/title.h"
#include "../Game/stage_select.h"
#include "../Game/stage.h"

//
// ƒQ[ƒ€ŠÇ—ƒNƒ‰ƒX
//

class GameManager {
  Title title_;
  StageSelect stage_select_;
  Result result_;
  Stage stage_;

  void title();
  void game();

  void mode_select();
  void pause();
  void stage_select();
  void stage_play();
  void result();

  int mode;
  int stage;
  bool exit;

public:
  GameManager();

  void play();
};
