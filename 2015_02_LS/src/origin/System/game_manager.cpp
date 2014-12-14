
#pragma once
#include "game_manager.h"

//
// �Q�[���Ǘ��N���X�i�����j
//

// �R���X�g���N�^
GameManager::GameManager() {
  EXIT = false;
}

// �Q�[�����s
void GameManager::play() {
  while (win::app->isOpen() && !EXIT) {
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
  while (win::app->isOpen() && !EXIT) {
    stage_select();
    //stage_play();
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

    font.draw("�{�ҁi���j", Vec2f(0, 0), Color(1, 1, 1)); //debug
    win::app->update();

    if (click) { break; }
  }
  win::app->flushInput();
}


/* ���U���g��ʊ֌W */
//////////////////////////////////////////////////////////////////////

// ���U���g�̏����{��
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
