
#include "title.h"

//
// タイトル画面（実装）
//

// コンストラクタ
Title::Title() :
font(std::make_unique<Font>("res/font/alphabet.ttf"))/*,
BG(Texture("res/png/Title_BG.png"))*/ {
  font->size(40);
}

// 描画
void Title::draw() {
  drawFillBox(0, 0, 100, 100, Color(1, 1, 1));
}

// 更新
void Title::update(){
}

// リセット
void Title::reset(){
}
