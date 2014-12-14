
#pragma once
#include "game_manager.h"

//
// ゲーム管理クラス（実装）
//

// コンストラクタ
GameManager::GameManager() {
  EXIT = false;
}

// ゲーム実行
void GameManager::play() {
  while (win::app->isOpen() && !EXIT) {
    title();
    game();
  }
}

/* タイトル画面関係 */
//////////////////////////////////////////////////////////////////////

// タイトルの処理本体
void GameManager::title() {
  Font font("res/font/MeiryoConsolas.ttf");
  font.size(40);

  title_.reset();

  while (win::app->isOpen()) {
    if (win::app->isPushButton(Mouse::LEFT)) { break; }

    title_.update();

    win::app->setupDraw();

    title_.draw();

    font.draw("タイトル（仮）", Vec2f(0, 0), Color(1, 1, 1)); //debug
    win::app->update();
  }
  win::app->flushInput();
}


/* 本編関係 */
//////////////////////////////////////////////////////////////////////

// 本編の処理本体
void GameManager::game() {
  while (win::app->isOpen() && !EXIT) {
    stage_select();
    //stage_play();
    result();
  }
}

// ポーズ画面
void GameManager::pause() {
}

// ステージセレクト画面
void GameManager::stage_select() {
  Font font("res/font/MeiryoConsolas.ttf");
  font.size(40);

  bool click = false;

  stage_select_.reset();

  while (win::app->isOpen()) {

    win::mouse_translate();

    stage_select_.update(click);

    win::app->setupDraw();

    stage_select_.draw();
    font.draw("ステージ選択（仮）", Vec2f(0, 50), Color(1, 1, 1)); //debug
    win::app->update();

    if (click) { break; }
  }
  win::app->flushInput();
}

// ステージ画面
void GameManager::stage_play() {
  Font font("res/font/MeiryoConsolas.ttf");
  font.size(40);

  bool click;

  Vec2f cmd[3] = {
    { -WIDTH / 2, 60 },
    { -WIDTH / 2, 0 },
    { -WIDTH / 2, -60 }
  };

  Vec2f size(200, 50);
  Color color;

  while (win::app->isOpen()) {
    click = false;

    win::mouse_translate();

    //if(!bool){update();}
    // !bool ? update() : pause_update();

    win::app->setupDraw();

    for (int i = 0; i < 3; ++i) {
      color = Color(1, 1, 1);
      if (Collision::box_to_cursor(cmd[i], size)) {
        if (win::app->isPushButton(Mouse::LEFT)) { click = true; }
        color = Color(0, 0, 1);
      }
      drawFillBox(cmd[i].x(), cmd[i].y(), size.x(), size.y(), color);
    }

    font.draw("本編（仮）", Vec2f(0, 0), Color(1, 1, 1)); //debug
    win::app->update();

    if (click) { break; }
  }
  win::app->flushInput();
}


/* リザルト画面関係 */
//////////////////////////////////////////////////////////////////////

// リザルトの処理本体
void GameManager::result() {

  bool click;

   result_.reset();

  while (win::app->isOpen()) {

    click = false;

   result_.update(click, EXIT);

    win::app->setupDraw();

   result_.draw();

    win::app->update();
    if (click){ break; }
  }
  win::app->flushInput();
}


//////////////////////////////////////////////////////////////////////
