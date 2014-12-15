
#include "window_create.h"

//
// �E�B���h�E�����N���X�i�����j
//

// �E�B���h�E�����t���O
bool win::isCreate = false;

// �Q�[�����s���̃C���X�^���X
std::unique_ptr<AppEnv> win::app;

// �}�E�X�J�[�\���ʒu�i���A���j
Vec2f win::mouse;

// �E�B���h�E��������
// TIPS: �K�� main() �̈�ԍŏ��ɌĂяo���悤�ɂ���
void win::create() {
  if (!isCreate) {
    app = std::make_unique<AppEnv>(WIDTH, HEIGHT, false, true);
    isCreate = true;
  }
}

// �}�E�X���W�̎擾
void win::mouse_translate() {
  mouse = app->mousePosition();
}
