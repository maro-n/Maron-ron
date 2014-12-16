
#include "politics.h"
//
// �����ʁi�����j
//

// �R���X�g���N�^
Politics::Politics() : /*BG(Texture("res/png/Politics_BG.png");*/
font(Font("res/font/MeiryoConsolas.ttf")){
  // ��:0 �G:1 ��Q:2
  button[0] = Button(Vec2f(-WIDTH / 2, HEIGHT / 2 - 100), color_variation.red, 1);
  button[1] = Button(Vec2f(-WIDTH / 2, 0), color_variation.red, 1);
  button[2] = Button(Vec2f(-WIDTH / 2, -HEIGHT / 2), color_variation.red, 1);
  button[3] = Button(Vec2f(-WIDTH / 4, HEIGHT / 2 - 100), color_variation.red, 1);
  button[4] = Button(Vec2f(-WIDTH / 4, 0), color_variation.red, 1);
  button[5] = Button(Vec2f(-WIDTH / 4, -HEIGHT / 2), color_variation.red, 1);
  button[6] = Button(Vec2f(WIDTH / 4 - 100, HEIGHT / 2 - 100), color_variation.red, 1);
  button[7] = Button(Vec2f(WIDTH / 4 - 100, 0), color_variation.red, 1);
  button[8] = Button(Vec2f(WIDTH / 4 - 100, -HEIGHT / 2), color_variation.red, 1);
  button[9] = Button(Vec2f(WIDTH / 2 - 100, HEIGHT / 2 - 100), color_variation.red, 1);
  button[10] = Button(Vec2f(WIDTH / 2 - 100, 0), color_variation.red, 1);
  button[11] = Button(Vec2f(WIDTH / 2 - 100, -HEIGHT / 2), color_variation.red, 1);

  on_box = -1;
  click_pos = 0;

  random.setSeed(u_int(time(nullptr)));
  r = random.fromZeroToLast(12);

  button[r].mode = 0;
  button[r].color = color_variation.blue;

  font.size(40);
}

// �`��
void Politics::draw(int& p_mode){
  switch (p_mode){
  case 0: politics_draw(); break;
  case 1: stage_draw(); break;
  }
}

void Politics::politics_draw(){
  font.draw("����i���j", Vec2f(0, 50), Color(1, 1, 1)); //debug
}

void Politics::stage_draw() {
  for (int i = 0; i < 12; ++i) {
    drawFillBox(button[i].pos.x(), button[i].pos.y(),
      100, 100, button[i].color);

    if (on_box == i) {
      if (button[i].mode != 0) {
        drawFillBox(button[i].pos.x(), button[i].pos.y(), 100, 100, color_variation.white_alpha);
      }
    }
  }
  font.draw("�X�e�[�W�I���i���j", Vec2f(0, 50), Color(1, 1, 1)); //debug
}

// �X�V
void Politics::update(int& p_mode, bool& click){
  switch (p_mode){
  case 0: politics_update(); break;
  case 1: stage_update(click); break;
  }
}

void Politics::politics_update(){
}

void Politics::stage_update(bool& click) {
  // �K���ɋ�`�������Ă����蔻��̓���`�F�b�N
  for (int i = 0; i < 12; ++i) {
    on_box = -1;
    if (Collision::box_to_cursor(button[i].pos, Vec2f(100, 100))) {
      on_box = i;
      if (win::app->isPushButton(Mouse::LEFT)) {
        if (button[i].mode != 0) {
          click = true;
          click_pos = i;
        }
      }
      break;
    }
  }
}

// ���􃊃Z�b�g
void Politics::politics_reset() {
}

// �X�e�[�W���Z�b�g
void Politics::stage_reset(){
  button[0] = Button(Vec2f(-WIDTH / 2, HEIGHT / 2 - 100), color_variation.red, 1);
  button[1] = Button(Vec2f(-WIDTH / 2, 0), color_variation.red, 1);
  button[2] = Button(Vec2f(-WIDTH / 2, -HEIGHT / 2), color_variation.red, 1);
  button[3] = Button(Vec2f(-WIDTH / 4, HEIGHT / 2 - 100), color_variation.red, 1);
  button[4] = Button(Vec2f(-WIDTH / 4, 0), color_variation.red, 1);
  button[5] = Button(Vec2f(-WIDTH / 4, -HEIGHT / 2), color_variation.red, 1);
  button[6] = Button(Vec2f(WIDTH / 4 - 100, HEIGHT / 2 - 100), color_variation.red, 1);
  button[7] = Button(Vec2f(WIDTH / 4 - 100, 0), color_variation.red, 1);
  button[8] = Button(Vec2f(WIDTH / 4 - 100, -HEIGHT / 2), color_variation.red, 1);
  button[9] = Button(Vec2f(WIDTH / 2 - 100, HEIGHT / 2 - 100), color_variation.red, 1);
  button[10] = Button(Vec2f(WIDTH / 2 - 100, 0), color_variation.red, 1);
  button[11] = Button(Vec2f(WIDTH / 2 - 100, -HEIGHT / 2), color_variation.red, 1);

  on_box = -1;
  click_pos = 0;

  r = random.fromZeroToLast(12);

  button[r].mode = 0;
  button[r].color = color_variation.blue;
}

// �s�k
void Politics::win(){
  button[click_pos].mode = 0;
  button[click_pos].color = color_variation.blue;
}
