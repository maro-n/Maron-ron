
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
  //drawFillBox(0, 0, 100, 100, Color(1, 1, 1));
}

// �X�V
void Title::update() {
}

// ���Z�b�g
void Title::reset() {
}
