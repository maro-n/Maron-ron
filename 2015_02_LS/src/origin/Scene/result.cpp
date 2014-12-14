
#include "result.h"

//
// リザルト画面（実装）
//

// コンストラクタ
Result::Result()/* :  BG(Texture("res/png/Result_BG.png"))*/{
  cmd[0] = Vec2f(-WIDTH / 2, 60);
  cmd[1] = Vec2f(-WIDTH / 2, -60);
  size = Vec2f(200, 50);
}

// 描画
void Result::draw(){
  game_clear();
}

void Result::game_clear(){
  for (int i = 0; i < 2; ++i){
    drawFillBox(cmd[i].x(), cmd[i].y(), size.x(), size.y(), color[i]);
  }
}

// 更新
void Result::update(bool& click, bool& EXIT){

  win::mouse_translate();

  // 適当に矩形をだしてあたり判定の動作チェック
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

// リセット
void Result::reset(){
}
