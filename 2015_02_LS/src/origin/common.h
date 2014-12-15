
#pragma once
#include "../lib/defines.hpp"
#include "../lib/appEnv.hpp"

//
// システム共通
//

/* マクロ、定数 */
//////////////////////////////////////////////////////////////////////

// ウィンドウサイズ
enum Window {
  WIDTH  = 1024,
  HEIGHT = 766,
};

// システム
enum GameSystem {
  Fps = 60,
  Member = 20,   // プレイヤーが作成できる、PTメンバーの上限
};

// 色
struct Col{
  Color red;
  Color blue;
  Color white_alpha;
  Col() : red(Color(1, 0, 0)), blue(Color(0, 0, 1)), white_alpha(Color(1, 1, 1, 0.6f)){}
};
/* 定義 */
//////////////////////////////////////////////////////////////////////

typedef unsigned short  u_short;

//////////////////////////////////////////////////////////////////////
