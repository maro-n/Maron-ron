
#pragma once
#include "game_manager.h"

//
// ゲーム管理クラス（実装）
//

// コンストラクタ
GameManager::GameManager() {
  mode = 0;
  stage = 1;
  exit = false;
}

// ゲーム実行
void GameManager::play() {
  while (win::app->isOpen() && !exit) {
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
  while (win::app->isOpen() && !exit) {
    stage_select();
    stage_play();
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
  stage_.reset();

  while (win::app->isOpen()) {
    if (stage_.game_set(mode, stage)) { break; }

    win::mouse_translate();
    stage_.update();

    win::app->setupDraw();

    stage_.draw();

    win::app->update();
  }
  win::app->flushInput();
}


/* リザルト画面関係 */
//////////////////////////////////////////////////////////////////////

// リザルトの処理本体
void GameManager::result() {
  bool click;

  result_.reset();

  if (mode == 1){
    stage_select_.win();
  }
  if (stage == 12){
    mode = 2;
  }

  while (win::app->isOpen()) {

    click = false;
    result_.update(click, exit);

    win::app->setupDraw();

    result_.draw(mode);

    win::app->update();

    if (click) { break; }
  }
  win::app->flushInput();
}


//////////////////////////////////////////////////////////////////////
