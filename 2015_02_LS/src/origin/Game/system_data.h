
#pragma once
#include "../System/window_create.h"
#include <string>
#include <fstream>

//
// �V�X�e���f�[�^
// TIPS: �V�X�e���̃Z�[�u�f�[�^�Ɋ܂ނ��̈ꗗ
// stage : �l�������}�X�̐��i�����l�F1�j
//
class SystemData {
  SystemData() = default;

  static std::string fstr_;

public:
  static Difficulty dif_;

  static short stage_count_;
  static short clear_count_;

  static void BugProof();

  static void DataLoad(const int);
  static void DataSave(const int);
};

typedef SystemData  Sys;
