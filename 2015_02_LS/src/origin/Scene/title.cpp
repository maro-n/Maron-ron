
#include "title.h"

//
// タイトル画面（実装）
//

// コンストラクタ
Title::Title() :
font(std::make_unique<Font>("res/font/alphabet.ttf")) {
  font->size(40);
}

// 描画
void Title::draw() {
  draw_logo();
}

// ロゴ
void Title::draw_logo() {
  font->draw("タイトル", Vec2f(0, 0), Color(1, 1, 1));
}
