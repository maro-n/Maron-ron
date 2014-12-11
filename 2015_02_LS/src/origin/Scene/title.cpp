
#include "title.h"

//
// �^�C�g����ʁi�����j
//

// �R���X�g���N�^
Title::Title() :
font(std::make_unique<Font>("res/font/alphabet.ttf")) {
  font->size(40);
}

// �`��
void Title::draw() {
  draw_logo();
}

// ���S
void Title::draw_logo() {
  font->draw("�^�C�g��", Vec2f(0, 0), Color(1, 1, 1));
}
