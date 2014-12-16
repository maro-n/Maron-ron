
#pragma once
#include "../lib/defines.hpp"
#include "../lib/appEnv.hpp"

//
// �V�X�e������
//

/* �}�N���A�萔 */
//////////////////////////////////////////////////////////////////////

// �E�B���h�E�T�C�Y
enum Window {
  WIDTH  = 600,
  HEIGHT = 800,
};

// �V�X�e��
enum GameSystem {
  Fps = 60,
  Member = 20,   // �v���C���[���쐬�ł���APT�����o�[�̏��

  GameStart = 1,    // �Q�[���J�n���̐w�n�̐�
  GameClear = 12,   // �w�n�̐��F���ׂĂ̐w�n���l������
};

// �Q�[����Փx
enum class Difficulty {
  EASY,
  NORMAL,
  HARD,
};

// �F
struct Col{
  Color red;
  Color blue;
  Color white_alpha;
  Col() : red(Color(1, 0, 0)), blue(Color(0, 0, 1)), white_alpha(Color(1, 1, 1, 0.6f)) {}
};


/* ��` */
//////////////////////////////////////////////////////////////////////

typedef unsigned short  u_short;


//////////////////////////////////////////////////////////////////////
