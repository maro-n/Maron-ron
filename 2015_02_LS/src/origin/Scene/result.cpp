
#include "result.h"

//
// ���U���g��ʁi�����j
//

// �R���X�g���N�^
Result::Result()/* :  BG(Texture("res/png/Result_BG.png"))*/{
  cmd[0] = Vec2f(-WIDTH / 2, 60);
  cmd[1] = Vec2f(-WIDTH / 2, -60);
  size = Vec2f(200, 50);
}

// �`��
void Result::draw(){
  game_clear();
}

void Result::game_clear(){
  for (int i = 0; i < 2; ++i){
    drawFillBox(cmd[i].x(), cmd[i].y(), size.x(), size.y(), color[i]);
  }
}

// �X�V
void Result::update(bool& click, bool& EXIT){

  win::mouse_translate();

  // �K���ɋ�`�������Ă����蔻��̓���`�F�b�N
  for (int i = 0; i < 2; ++i){
    color[i] = Color(1, 1, 1);
    if (Collision::box_to_cursor(cmd[i], size)){
      color[i] = Color(1, 0, 0);
      if (win::app->isPushButton(Mouse::LEFT)){
        click = true;
        if (i == 1){
          EXIT = true;
        }
      }
    }
  }

}

// ���Z�b�g
void Result::reset(){
}
