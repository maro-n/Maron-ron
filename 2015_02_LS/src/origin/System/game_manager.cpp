
#pragma once
#include "game_manager.h"

//
// �Q�[���Ǘ��N���X�i�����j
//

// �R���X�g���N�^
GameManager::GameManager() {
  mode = 0;
  stage = 1;
  exit = false;
}

// �Q�[�����s
void GameManager::play() {
  while (win::app->isOpen() && !exit) {
    title();
    game();
  }
}

/* �^�C�g����ʊ֌W */
//////////////////////////////////////////////////////////////////////

// �^�C�g���̏����{��
void GameManager::title() {
  Font font("res/font/MeiryoConsolas.ttf");
  font.size(40);

  title_.reset();

  while (win::app->isOpen()) {
    if (win::app->isPushButton(Mouse::LEFT)) { break; }

    title_.update();

    win::app->setupDraw();

    title_.draw();
    font.draw("�^�C�g���i���j", Vec2f(0, 0), Color(1, 1, 1)); //debug

    win::app->update();
  }
  win::app->flushInput();
}


/* �{�Ҋ֌W */
//////////////////////////////////////////////////////////////////////

// �{�҂̏����{��
void GameManager::game() {
  while (win::app->isOpen() && !exit) {
    stage_select();
    stage_play();
    result();
  }
}

// �|�[�Y���
void GameManager::pause() {
}

// �X�e�[�W�Z���N�g���
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
    font.draw("�X�e�[�W�I���i���j", Vec2f(0, 50), Color(1, 1, 1)); //debug

    win::app->update();

    if (click) { break; }
  }
  win::app->flushInput();
}

// �X�e�[�W���
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


/* ���U���g��ʊ֌W */
//////////////////////////////////////////////////////////////////////

// ���U���g�̏����{��
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
