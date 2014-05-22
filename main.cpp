//
// LEFT or RIGHT!?
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
	WIDTH = 512,
	HEIGHT = 384
};

// 得点表示
void dispPlayPoint(int play_point){
	float x = -Window::WIDTH / 2 + 50;
	float y = -Window::HEIGHT / 2 + 25;

	// 10の位を大きな円で表示
	int ten_points = play_point / 10;
	while (ten_points > 0) {
		drawFillCircle(x, y, 15, 15,
			20,
			Color(1, 0, 0));

		x += 15 * 2 + 5;
		ten_points -= 1;
	}

	// 1の位を小さな円で表示
	int one_points = play_point % 10;
	while (one_points > 0) {
		drawFillCircle(x, y, 10, 10,
			20,
			Color(1, 1, 0));

		x += 10 * 2 + 5;
		one_points -= 1;
	}

}
// 矩形の上にマウスカーソルが乗っているかどうか
bool isMouseOnBox(float x, float y, float width, float height,
	Vec2f mouse_pos)
{
	if (mouse_pos.x() > x) {
		if (mouse_pos.x() < (x + width)) {
			if (mouse_pos.y() > y) {
				if (mouse_pos.y() < (y + height)) {
					return true;
				}
			}
		}
	}
	return false;
}

// マウスのカーソルが乗ってたらカードの色を変える
Color setCardColor(bool on_card){
	if (on_card){
		return Color(1, 0.5, 0.5);
	}
	return Color(1, 1, 1);
}

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT);

	while (1){

		int random_count = 0;

		// タイトル画面
		{
			// タイトル画像
			Texture title_image("res/title.png");

			// 「Click to Start」演出用変数を用意
			float title_angle = 0.0;
			int blink = 0;

			// メインループ

			while (1) {

				random_count += 1;

				// ウィンドウが閉じられたらアプリを終了
				if (!app_env.isOpen()) return 0;

				// 描画準備
				app_env.setupDraw();

				// マウスのボタンがクリックされたらゲーム本編へ
				if (app_env.isPushButton(Mouse::LEFT))  break;
				if (app_env.isPushButton(Mouse::RIGHT)) break;

				// タイトルロゴ
				drawTextureBox(0 - 279 / 2, 40 - 285 / 2, 279, 285,
					0, 0, 279, 285,
					title_image,
					Color(1, 0.25, 0.25));

				// 「Click to Start」演出用変数を用意
				title_angle += 0.05;
				// sinの値の絶対値を色に利用
				float title_color = std::abs(std::sin(title_angle));

				// 「Click to Start」

				blink += 1;
				int value = (blink / 30) % 2;

				if (value){
					drawTextureBox(0 - 512 / 2, -Window::HEIGHT / 2, 512, 66,
						0, 297, 512, 66,
						title_image,
						Color(1, 1, 1));
				}


				// ここにゲームの処理を書く
				// 

				// 画面を更新
				app_env.update();
			}
			// 入力のフラッシュ
			app_env.flushInput();
		}

		// 本編追加

		// ゲームで使うさまざまな変数
		// プレイ時間(15秒)
		int play_time = 60 * 15;
		// 得点
		int play_point = 0;

		// 取り出したカードの場所
		int card_index = 0;

		app_env.random().setSeed(random_count);

		// ゲーム本編
		{
			// カード一枚ごとの情報を構造体で定義
			struct Card {
				// 画像からの切り抜き情報
				float texture_x, texture_y;
				float texture_width, texture_height;

				// カードの数字(1～13)
				int number;

				// カードのマーク
				// 0:スペード 1:ハート 2:クラブ 3:ダイア
				int mark;
			};

			// ジョーカー抜きの52枚のカード情報を配列で用意
			Card cards_info[] = {
				// スペード
				{ 0 * 72, 0 * 96, 72, 96, 1, 0 },
				{ 1 * 72, 0 * 96, 72, 96, 2, 0 },
				{ 2 * 72, 0 * 96, 72, 96, 3, 0 },
				{ 3 * 72, 0 * 96, 72, 96, 4, 0 },
				{ 4 * 72, 0 * 96, 72, 96, 5, 0 },
				{ 5 * 72, 0 * 96, 72, 96, 6, 0 },
				{ 6 * 72, 0 * 96, 72, 96, 7, 0 },
				{ 7 * 72, 0 * 96, 72, 96, 8, 0 },
				{ 8 * 72, 0 * 96, 72, 96, 9, 0 },
				{ 9 * 72, 0 * 96, 72, 96, 10, 0 },
				{ 10 * 72, 0 * 96, 72, 96, 11, 0 },
				{ 11 * 72, 0 * 96, 72, 96, 12, 0 },
				{ 12 * 72, 0 * 96, 72, 96, 13, 0 },

				// ハート
				{ 0 * 72, 1 * 96, 72, 96, 1, 1 },
				{ 1 * 72, 1 * 96, 72, 96, 2, 1 },
				{ 2 * 72, 1 * 96, 72, 96, 3, 1 },
				{ 3 * 72, 1 * 96, 72, 96, 4, 1 },
				{ 4 * 72, 1 * 96, 72, 96, 5, 1 },
				{ 5 * 72, 1 * 96, 72, 96, 6, 1 },
				{ 6 * 72, 1 * 96, 72, 96, 7, 1 },
				{ 7 * 72, 1 * 96, 72, 96, 8, 1 },
				{ 8 * 72, 1 * 96, 72, 96, 9, 1 },
				{ 9 * 72, 1 * 96, 72, 96, 10, 1 },
				{ 10 * 72, 1 * 96, 72, 96, 11, 1 },
				{ 11 * 72, 1 * 96, 72, 96, 12, 1 },
				{ 12 * 72, 1 * 96, 72, 96, 13, 1 },

				// クラブ
				{ 0 * 72, 2 * 96, 72, 96, 1, 2 },
				{ 1 * 72, 2 * 96, 72, 96, 2, 2 },
				{ 2 * 72, 2 * 96, 72, 96, 3, 2 },
				{ 3 * 72, 2 * 96, 72, 96, 4, 2 },
				{ 4 * 72, 2 * 96, 72, 96, 5, 2 },
				{ 5 * 72, 2 * 96, 72, 96, 6, 2 },
				{ 6 * 72, 2 * 96, 72, 96, 7, 2 },
				{ 7 * 72, 2 * 96, 72, 96, 8, 2 },
				{ 8 * 72, 2 * 96, 72, 96, 9, 2 },
				{ 9 * 72, 2 * 96, 72, 96, 10, 2 },
				{ 10 * 72, 2 * 96, 72, 96, 11, 2 },
				{ 11 * 72, 2 * 96, 72, 96, 12, 2 },
				{ 12 * 72, 2 * 96, 72, 96, 13, 2 },

				// ダイア
				{ 0 * 72, 3 * 96, 72, 96, 1, 3 },
				{ 1 * 72, 3 * 96, 72, 96, 2, 3 },
				{ 2 * 72, 3 * 96, 72, 96, 3, 3 },
				{ 3 * 72, 3 * 96, 72, 96, 4, 3 },
				{ 4 * 72, 3 * 96, 72, 96, 5, 3 },
				{ 5 * 72, 3 * 96, 72, 96, 6, 3 },
				{ 6 * 72, 3 * 96, 72, 96, 7, 3 },
				{ 7 * 72, 3 * 96, 72, 96, 8, 3 },
				{ 8 * 72, 3 * 96, 72, 96, 9, 3 },
				{ 9 * 72, 3 * 96, 72, 96, 10, 3 },
				{ 10 * 72, 3 * 96, 72, 96, 11, 3 },
				{ 11 * 72, 3 * 96, 72, 96, 12, 3 },
				{ 12 * 72, 3 * 96, 72, 96, 13, 3 },
			};

			// カードの画像を読み込む
			Texture cards_image("res/cards.png");

			// トランプをシャッフル
			int i = 0;
			while (i < 52)	{
				std::swap(cards_info[i],
					cards_info[app_env.random().fromZeroToLast(52)]);
				i += 1;
			}
			// 本編１を追加

			// メインループ
			while (1) {
				// ウインドウが閉じられたら終了
				if (!app_env.isOpen()) return 0;

				// 描画準備
				app_env.setupDraw();

				// カードを二枚、配列から取り出す
				Card left_card = cards_info[card_index];
				Card right_card = cards_info[card_index + 1];

				// マウスの位置を変数にコピー
				Vec2f mouse_pos = app_env.mousePosition();
				// 左クリックしたかどうかを変数にコピー
				bool left_click = app_env.isPushButton(Mouse::LEFT);

				// 左側のカードの処理
				{
					// カードの表示位置
					float x = -100 - 72 / 2;
					float y = 0 - 96 / 2;

					// マウスカーソルがカードの上にあるか調べる
					bool on_card = isMouseOnBox(x, y, left_card.texture_width, left_card.texture_height,
						mouse_pos);


					// マウスカーソルがカードの上にあって、左クリックされたら...
					if (on_card) {
						if (left_click) {
							// 左クリックされてたら右のカードと数字を比べる
							if (left_card.number >= right_card.number) {
								play_point += 1;
							}

							// カードを引く位置を二枚先に変更
							if (card_index < (52 - 2)) {
								card_index += 2;
							}
							else {
								// カードが無くなったら本編終了
								break;
							}
						}
					}

					// マウスカーソルがカードの上にあるなら色を赤くする
					Color card_color = setCardColor(on_card);

					// カードを表示
					drawTextureBox(x, y, left_card.texture_width, left_card.texture_height,
						left_card.texture_x, left_card.texture_y, left_card.texture_width, left_card.texture_height,
						cards_image,
						card_color);
				}

				// 右側のカードの処理
				{
					// カードの表示位置
					float x = 100 - 72 / 2;
					float y = 0 - 96 / 2;

					// マウスカーソルがカードの上にあるか調べる
					bool on_card = isMouseOnBox(x, y, left_card.texture_width, left_card.texture_height,
						mouse_pos);

					// マウスカーソルがカードの上にあって、左クリックされたら...
					if (on_card) {
						if (left_click) {
							// 左クリックされてたら左のカードと数字を比べる
							if (right_card.number >= left_card.number) {
								play_point += 1;
							}

							// カードを引く位置を２枚先に変更
							if (card_index < (52 - 2)) {
								card_index += 2;
							}
							else {
								// カードが無くなったら本編終了
								break;
							}
						}
					}

					// マウスカーソルがカードの上にあるなら色を赤くする
					Color card_color = setCardColor(on_card);

					// カードを表示
					drawTextureBox(x, y, right_card.texture_width, right_card.texture_height,
						right_card.texture_x, right_card.texture_y, right_card.texture_width, right_card.texture_height,
						cards_image,
						card_color);
				}

				// 本編追加２

				// 残り時間表示
				{
					// 表示位置
					float x = -100;
					float y = -Window::HEIGHT / 2 + 50;

					// 表示サイズ(残り時間を矩形の横幅で表現)
					float width = (play_time * 200) / (60 * 15);
					float height = 30;

					// 残り時間を矩形で表示
					drawFillBox(x, y, width, height, Color(0, 1, 1));
					// 枠線
					drawBox(x, y, 200, height, 2, Color(1, 1, 1));
				}

				// 得点表示
				dispPlayPoint(play_point);



				// プレイ時間を減らす
				play_time -= 1;
				// 時間が無くなったらループを抜ける
				if (play_time == 0) break;

				// 画面を更新
				app_env.update();
			}
			// 入力のフラッシュ
			app_env.flushInput();
		}

		// 結果画面
		{
			// 結果画面の画像
			Texture results_image("res/results.png");

			// 結果画面演出用変数
			float angle = 0.0;

			// メインループ
			while (1) {
				// ウインドウが閉じられたら終了
				if (!app_env.isOpen()) return 0;

				if (app_env.isPushButton(Mouse::LEFT)){
					if (app_env.isPushButton(Mouse::RIGHT))
						break;
				}
				// 描画準備
				app_env.setupDraw();

				// 演出用の変数を変更
				angle += 0.2;
				// sinの値が 0.0～1.0 に収まるように計算
				float color_red = (std::sin(angle) + 1.0) / 2.0;

				// 「終了」表示
				drawTextureBox(-512 / 2, -128 / 2, 512, 128,
					0, 0, 512, 128,
					results_image,
					Color(color_red, 1, 1));

				// 得点表示
				dispPlayPoint(play_point);


				// 画面を更新
				app_env.update();
			}

			// 入力のフラッシュ
			app_env.flushInput();
		}

	}
	// アプリ終了
}