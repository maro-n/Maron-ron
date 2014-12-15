
#include "stage.h"

//
// �{�ҁi�����j
//

// �R���X�g���N�^
Stage::Stage() :
font(Font("res/font/MeiryoConsolas.ttf")) {
  player.own = Texture("res/png/player.png");
  player.hp_max = 10;
  player.wait_time = 0;
  player.attack = 2;
  player.defend = 2;
  player.speed = 11;

  enemy.own = Texture("res/png/enemy.png");
  enemy.hp_max = 9;
  enemy.wait_time = 0;
  enemy.attack = 3;
  enemy.defend = 1;
  enemy.speed = 8;

  bg = Texture("res/png/bg.png");
  turn = true;

  std::string temp_str;

  for (int i = 0; i < 3; ++i) {
    switch (i) {
    case 0: temp_str = "��������"; break;
    case 1: temp_str = "�ڂ�����"; break;
    case 2: temp_str = "�����ӂ�"; break;
    default:;
    }

    button[i] = Button_(
      Vec2f(-WIDTH / 2 + 30, HEIGHT / 2 - 80 * (i + 1)),
      Color(1, 1, 1),
      temp_str);
  }

  font.size(40);
}

// �`��
void Stage::draw() {
  draw_bg();
  draw_player();
  draw_enemy();

  if (turn) { draw_button(); }
  draw_hp();
  //draw_turn_list();
}

// �w�i�\��
void Stage::draw_bg() {
  drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT,
    0, 0, 1024, 512,
    bg, Color(1, 1, 1));
}

// �v���C���[�\��
void Stage::draw_player() {
  drawTextureBox(-WIDTH / 2, -HEIGHT / 2 + 64, 128, 128,
    0, 0, 128, 128,
    player.own, Color(1, 1, 1));
}

// �G�L�����\��
void Stage::draw_enemy() {
  drawTextureBox(WIDTH / 2 - 128, -HEIGHT / 2 + 64, 128, 128,
    0, 0, 128, 128,
    enemy.own, Color(1, 1, 1));
}

// �{�^���\��
void Stage::draw_button() {
  for (int i = 0; i < 3; ++i) {
    drawFillBox(button[i].pos.x(), button[i].pos.y(),
      250, 50, button[i].color);

    font.draw(button[i].str, button[i].pos, Color(0, 0, 0));
  }
}

// ���Ԃ̕\��
void Stage::draw_turn_list() {
  temp = (player.wait_time > enemy.wait_time)
    ? player.own : enemy.own;

  drawTextureBox(WIDTH / 2 - 64, HEIGHT / 2 - 64, 128, 128,
    0, 0, 128, 128,
    temp, Color(1, 1, 1),
    0, Vec2f(0.5, 0.5), Vec2f(0, 0));
}

// �g�o�̕\��
void Stage::draw_hp() {
  // �v���C���[
  num.init_value(player.hp);
  num.disp_value(-WIDTH / 2 + 100, -HEIGHT / 2 + 220);

  // �G�L����
  num.init_value(enemy.hp);
  num.disp_value(WIDTH / 2 - 50, -HEIGHT / 2 + 220);
}

// �X�V
void Stage::update() {
  /*
  if (!turn) {
  player.count = (10000 - player.wait_time) / player.speed;
  enemy.count = (10000 - enemy.wait_time) / enemy.speed;

  count = (player.count > enemy.count) ? player.count : enemy.count;
  player.wait_time = count * player.speed;
  enemy.wait_time = count * enemy.speed;

  return;
  }
  */

  // �v���C���[
  if (turn) {
    for (int i = 0; i < 3; ++i) {
      button[i].color = Color(1, 1, 1);
      if (box_to_cursor(button[i].pos, Vec2f(250, 50))) {
        button[i].color = Color(1, 0, 0);

        if (win::app->isPushButton(Mouse::LEFT)) {
          turn = false;

          switch (i) {
          case 0:    // ��������
            enemy.hp += enemy.defend - player.attack;
            break;

          case 1:    // �ڂ�����i�A���t�@�F�������Ȃ��j
            break;

          default:   // �����ӂ�
            player.hp += 2;
          }
        }
      }
    }
  }

  // �G�L����
  if (!turn) {
    player.hp += player.defend - enemy.attack;
    turn = true;
  }
}

// ���Z�b�g
void Stage::reset() {
  player.hp = player.hp_max;
  enemy.hp = enemy.hp_max;
}

// �Q�[���I������
bool Stage::game_set(int& mode, int& stage) {
  if (!player.hp) { mode = 0; return true; }
  if (!enemy.hp) { mode = 1; stage++; return true; }

  return false;
}
