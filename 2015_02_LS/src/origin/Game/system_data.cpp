
#include "system_data.h"

std::string Sys::fstr_;

Difficulty Sys::dif_;
short Sys::stage_count_;
short Sys::clear_count_;

// �o�O���
// TIPS: �K���Q�[���{�҃��[�v���̍ŏ��Ɏ��s
void Sys::BugProof() {
  // 1 <= stage <= 12 �̔���
  stage_count_ = short(std::min(float(GameStart),
    std::max(float(stage_count_), float(GameClear))));
}

void Sys::DataLoad(const int slot) {
  switch (slot) {
    case  0: fstr_ = "res/data/system/save_1.txt"; break;
    case  1: fstr_ = "res/data/system/save_2.txt"; break;
    case  2: fstr_ = "res/data/system/save_3.txt"; break;
    default: fstr_ = "res/data/system/default.txt";
  }

  std::ifstream load(fstr_);
  if (load) {
  }
}

void Sys::DataSave(const int slot) {
  switch (slot) {
    case  0: fstr_ = "res/data/system/save_1.txt"; break;
    case  1: fstr_ = "res/data/system/save_2.txt"; break;
    case  2: fstr_ = "res/data/system/save_3.txt"; break;
    default: return;   // �Z�[�u�����������I�ɒ��f
  }

  std::ofstream save(fstr_);
  if (save) {
  }
}
