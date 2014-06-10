//
// 審査会用
//

#include "appEnv.hpp"


// アプリのウインドウサイズ
enum Window {
	WIDTH = 2048,
	HEIGHT = 1024
};

// 
// メインプログラム
// 
int main() {
	// アプリウインドウの準備
	AppEnv app_env(Window::WIDTH, Window::HEIGHT);

	// ハイスコア
	int hi_score = 0;
	{
		std::ifstream fstr("score.txt");
		if (fstr){
			fstr >> hi_score;
		}
	}
	// 結果画面からタイトル画面に戻るループ
	while (1){
		// 背景を動かす変数
		float scroll_back = 0;
		// 飛距離
		int jump_distance = 0;

		// タイトル画面
		{
			// タイトル画像
			Texture title_image("res/title_back.png");
			Texture title_rogo("res/title.png");
			Texture GAMESTART("res/GAME START.png");

			// 「Run and Jump」演出用変数を用意
			float title_angle = 0.0;
			int blink = 0;
			// メインループ
			while (1) {
				// ウィンドウが閉じられたらアプリを終了
				if (!app_env.isOpen()) return 0;

				// 描画準備
				app_env.setupDraw();

				// 入力による操作(break本編へ,returnアプリ終了)
				if (app_env.isPushButton(Mouse::RIGHT)) break;
				if (app_env.isPushButton(Mouse::LEFT))  break;
				if (app_env.isPushKey(GLFW_KEY_ENTER))  break;
				if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

				// タイトル画像
				drawTextureBox(0 - 2048 / 2, 0 - 1024 / 2, 2048, 1024,
					0, 0, 2048, 1024,
					title_image,
					Color(1, 1, 1));

				// タイトルロゴの色にサイン,コサインを利用
				title_angle += 0.05;
				float title_sin = std::abs(std::sin(title_angle));
				float title_cos = std::abs(std::cos(title_angle));

				// タイトルロゴを表示
				drawTextureBox(0 - 1024 / 2, 512 / 2, 565, 80,
					0, 512, 565, 80,
					title_rogo,
					Color(0, title_sin, title_cos),
					0,
					Vec2f(2, 2),
					Vec2f(0, 0));

				// 「GAME START」を表示
				blink += 1;
				int value = (blink / 30) % 2;

				if (value){
					drawTextureBox(0 - 360, 0 - 480, 512, 256,
						0, 0, 512, 256,
						GAMESTART,
						Color(1, 0, 0),
						0,
						Vec2f(1.8, 1.8),
						Vec2f(0, 0));
				}
				// 画面を更新
				app_env.update();
			}
			// 入力のフラッシュ
			app_env.flushInput();
		}
		// 操作説明画面
		{
		// 操作説明画像
		Texture tutorial("res/tuto.png");
		Texture back("res/field.png");

		// メインループ
		while (1) {
			// ウィンドウが閉じられたらアプリを終了
			if (!app_env.isOpen()) return 0;

			// 描画準備
			app_env.setupDraw();

			// 入力による操作(break本編へ,returnアプリ終了)
			if (app_env.isPushButton(Mouse::RIGHT)) break;
			if (app_env.isPushButton(Mouse::LEFT))  break;
			if (app_env.isPushKey(GLFW_KEY_ENTER))  break;
			if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

			// 操作説明画面
			drawTextureBox(0 - 2048 / 2, 0 - 1024 / 2, 2048, 1024,
				0, 0, 2048, 1024,
				back,
				Color(1, 1, 1));

			drawTextureBox(0 - 2048 / 2, 0 - 1024 / 2, 2048, 1024,
				0, 0, 2048, 1024,
				tutorial,
				Color(1, 1, 1));

			// 画面を更新
			app_env.update();

			// 入力のフラッシュ
			app_env.flushInput();
		}

		// 本編
		{
			// 本編の画像
			Texture back("res/field.png");
			Texture run("res/run.png");
			Texture jump("res/jump.png");
			Texture back2("res/field2.png");
			Texture back3("res/field3.png");
			Texture dispnumber("res/number.png");

			int blink = 0;
			// キャラの表示位置
			float x = 0 - 1024 / 1.5;
			float y = 0 - 380;
			// キャラの加速度
			float a = 0;
			// 重力加速度
			float g = -0.2;
			// キャラの速度
			float v = 0;
			// キャラのジャンプ回数
			int jump_count = 3;
			// キャラのジャンプスイッチ
			int jump_switch = 0;

			// メインループ
			while (1){
				// ウインドウが閉じられたら終了
				if (!app_env.isOpen()) return 0;
				if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

				// 描画準備
				app_env.setupDraw();

				// ゲーム本編
				{
					// キャラクターのモーション情報
					struct Texture {
						// 画像からの切り抜き情報
						float texture_x, texture_y;
						float texture_width, texture_height;
					};

					// キャラクターの情報を配列で用意
					Texture move_info[] = {
						{ 0 * 100, 0, 100, 150 },
						{ 1 * 100, 0, 100, 150 },
						{ 2 * 100, 0, 100, 150 },
						{ 3 * 100, 0, 100, 150 },
						{ 4 * 100, 0, 100, 150 },
						{ 5 * 100, 0, 100, 150 },
						{ 6 * 100, 0, 100, 150 },
					};

					// 数字の情報を配列で用意
					Texture number_info[] = {
						{ 0 * 50, 0, 29, 55 },
						{ 1 * 50, 0, 48, 54 },
						{ 2 * 50, 0, 44, 55 },
						{ 3 * 50, 0, 45, 54 },
						{ 4 * 50, 0, 47, 54 },
						{ 5 * 50, 0, 43, 55 },
						{ 6 * 50, 0, 43, 54 },
						{ 7 * 50, 0, 45, 55 },
						{ 8 * 50, 0, 43, 55 },
						{ 9 * 50, 0, 38, 57 },
					};

					// キャラクターの情報を配列から取り出す
					Texture move_chara1 = move_info[0];
					Texture move_chara2 = move_info[1];
					Texture move_chara3 = move_info[2];
					Texture move_chara4 = move_info[3];
					Texture move_chara5 = move_info[4];
					Texture move_chara6 = move_info[5];
					Texture move_chara7 = move_info[6];

					Texture disp_num1 = number_info[0];
					Texture disp_num2 = number_info[1];
					Texture disp_num3 = number_info[2];
					Texture disp_num4 = number_info[3];
					Texture disp_num5 = number_info[4];
					Texture disp_num6 = number_info[5];
					Texture disp_num7 = number_info[6];
					Texture disp_num8 = number_info[7];
					Texture disp_num9 = number_info[8];
					Texture disp_num0 = number_info[9];

					// キャラクター処理
					{
						// 本編背景を連ねて表示に必要な変数
						int draw_back = 0;
						float num_x = -Window::WIDTH / 2 + 50;
						float num_y = -Window::HEIGHT / 2 + 25;

						// 本編画像を表示					
						draw_back += 2000;

						if (app_env.isPressKey(GLFW_KEY_RIGHT)){
							scroll_back += 20;
						}

						drawTextureBox(0 - 2048 / 2 - scroll_back, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back,
							Color(1, 1, 1));

						drawTextureBox(0 - 2048 / 2 - scroll_back + 2000, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back,
							Color(1, 1, 1));

						drawTextureBox(0 - 2048 / 2 - scroll_back + 4000, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back2,
							Color(1, 1, 1));

						drawTextureBox(0 - 2048 / 2 - scroll_back + 6000, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back3,
							Color(1, 1, 1));

						drawTextureBox(0 - 2048 / 2 - scroll_back + 8000, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back3,
							Color(1, 1, 1));

						drawTextureBox(0 - 2048 / 2 - scroll_back + 10000, 0 - 1024 / 2,
							2048, 1024,
							0, 0,
							2048, 1024,
							back3,
							Color(1, 1, 1));

						// キャラをジャンプさせる
						if (app_env.isPushKey(GLFW_KEY_SPACE) && jump_count > 0){
							a = 10 + g;
							jump_count--;
							jump_switch = 1;
						}
						else{
							a = g;
						}
						v = v + a;
						y = y + ((1 / 2) * a) + v;

						if (y < (0 - 380)) {
							v = 0;
							y = 0 - 380;
							// キャラが飛んでから地面に足をついたら結果画面へ
							if (jump_switch == 1 && y <= 0 - 380){
								break;
							}
						}

						// キャラが画面上端を超えたら止める
						if (y >= 512 - 200){
							y = 512 - 200;
							v = 0;
						}

						// キャラを表示
						if (app_env.isPressKey(GLFW_KEY_RIGHT)){
							blink += 1;
						}
						int value = (blink / 3) % 7;

						if (value == 0){
							drawTextureBox(x, y, move_chara1.texture_width, move_chara1.texture_height,
								move_chara1.texture_x, move_chara1.texture_y,
								move_chara1.texture_width, move_chara1.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 1){
							drawTextureBox(x, y, move_chara2.texture_width, move_chara2.texture_height,
								move_chara2.texture_x, move_chara2.texture_y,
								move_chara2.texture_width, move_chara2.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 2){
							drawTextureBox(x, y, move_chara3.texture_width, move_chara3.texture_height,
								move_chara3.texture_x, move_chara3.texture_y,
								move_chara3.texture_width, move_chara3.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 3){
							drawTextureBox(x, y, move_chara4.texture_width, move_chara4.texture_height,
								move_chara4.texture_x, move_chara4.texture_y,
								move_chara4.texture_width, move_chara4.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 4){
							drawTextureBox(x, y, move_chara5.texture_width, move_chara5.texture_height,
								move_chara5.texture_x, move_chara5.texture_y,
								move_chara5.texture_width, move_chara5.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 5){
							drawTextureBox(x, y, move_chara6.texture_width, move_chara6.texture_height,
								move_chara6.texture_x, move_chara6.texture_y,
								move_chara6.texture_width, move_chara6.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}
						if (value == 6){
							drawTextureBox(x, y, move_chara7.texture_width, move_chara7.texture_height,
								move_chara7.texture_x, move_chara7.texture_y,
								move_chara7.texture_width, move_chara7.texture_height,
								run,
								Color(0, 0, 0),
								0,
								Vec2f(1.5, 1.5),
								Vec2f(0, 0));
						}

						// 飛距離を表示する
						if (scroll_back >= 3250 - x && jump_count >= 0){
							jump_distance = (scroll_back - 4100) / 20;
						}
						// 線を越えても飛んでなかったらファウル
						if (scroll_back >= 3300 - x && jump_count == 3){
							jump_distance = 0;
							break;
						}

						// 100の位
						if (jump_distance >= 100){
							int hundred_distance = jump_distance / 100;
							if (hundred_distance == 1){
								drawTextureBox(num_x, num_y, disp_num1.texture_width, disp_num1.texture_height,
									disp_num1.texture_x, disp_num1.texture_y,
									disp_num1.texture_width, disp_num1.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 2){
								drawTextureBox(num_x, num_y, disp_num2.texture_width, disp_num2.texture_height,
									disp_num2.texture_x, disp_num2.texture_y,
									disp_num2.texture_width, disp_num2.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 3){
								drawTextureBox(num_x, num_y, disp_num3.texture_width, disp_num3.texture_height,
									disp_num3.texture_x, disp_num3.texture_y,
									disp_num3.texture_width, disp_num3.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 4){
								drawTextureBox(num_x, num_y, disp_num4.texture_width, disp_num4.texture_height,
									disp_num4.texture_x, disp_num4.texture_y,
									disp_num4.texture_width, disp_num4.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 5){
								drawTextureBox(num_x, num_y, disp_num5.texture_width, disp_num5.texture_height,
									disp_num5.texture_x, disp_num5.texture_y,
									disp_num5.texture_width, disp_num5.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 6){
								drawTextureBox(num_x, num_y, disp_num6.texture_width, disp_num6.texture_height,
									disp_num6.texture_x, disp_num6.texture_y,
									disp_num6.texture_width, disp_num6.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 7){
								drawTextureBox(num_x, num_y, disp_num7.texture_width, disp_num7.texture_height,
									disp_num7.texture_x, disp_num7.texture_y,
									disp_num7.texture_width, disp_num7.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 8){
								drawTextureBox(num_x, num_y, disp_num8.texture_width, disp_num8.texture_height,
									disp_num8.texture_x, disp_num8.texture_y,
									disp_num8.texture_width, disp_num8.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 9){
								drawTextureBox(num_x, num_y, disp_num9.texture_width, disp_num9.texture_height,
									disp_num9.texture_x, disp_num9.texture_y,
									disp_num9.texture_width, disp_num9.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (hundred_distance == 0){
								drawTextureBox(num_x, num_y, disp_num0.texture_width, disp_num0.texture_height,
									disp_num0.texture_x, disp_num0.texture_y,
									disp_num0.texture_width, disp_num0.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
						}
						// 10の位
						if (jump_distance >= 10){
							int ten_distance = jump_distance % 100 / 10;
							if (ten_distance == 1){
								drawTextureBox(num_x + 120, num_y, disp_num1.texture_width, disp_num1.texture_height,
									disp_num1.texture_x, disp_num1.texture_y,
									disp_num1.texture_width, disp_num1.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 2){
								drawTextureBox(num_x + 120, num_y, disp_num2.texture_width, disp_num2.texture_height,
									disp_num2.texture_x, disp_num2.texture_y,
									disp_num2.texture_width, disp_num2.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 3){
								drawTextureBox(num_x + 120, num_y, disp_num3.texture_width, disp_num3.texture_height,
									disp_num3.texture_x, disp_num3.texture_y,
									disp_num3.texture_width, disp_num3.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 4){
								drawTextureBox(num_x + 120, num_y, disp_num4.texture_width, disp_num4.texture_height,
									disp_num4.texture_x, disp_num4.texture_y,
									disp_num4.texture_width, disp_num4.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 5){
								drawTextureBox(num_x + 120, num_y, disp_num5.texture_width, disp_num5.texture_height,
									disp_num5.texture_x, disp_num5.texture_y,
									disp_num5.texture_width, disp_num5.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 6){
								drawTextureBox(num_x + 120, num_y, disp_num6.texture_width, disp_num6.texture_height,
									disp_num6.texture_x, disp_num6.texture_y,
									disp_num6.texture_width, disp_num6.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 7){
								drawTextureBox(num_x + 120, num_y, disp_num7.texture_width, disp_num7.texture_height,
									disp_num7.texture_x, disp_num7.texture_y,
									disp_num7.texture_width, disp_num7.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 8){
								drawTextureBox(num_x + 120, num_y, disp_num8.texture_width, disp_num8.texture_height,
									disp_num8.texture_x, disp_num8.texture_y,
									disp_num8.texture_width, disp_num8.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 9){
								drawTextureBox(num_x + 120, num_y, disp_num9.texture_width, disp_num9.texture_height,
									disp_num9.texture_x, disp_num9.texture_y,
									disp_num9.texture_width, disp_num9.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (ten_distance == 0){
								drawTextureBox(num_x + 120, num_y, disp_num0.texture_width, disp_num0.texture_height,
									disp_num0.texture_x, disp_num0.texture_y,
									disp_num0.texture_width, disp_num0.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
						}
						// 1の位
						if (jump_distance >= 1){
							int one_distance = jump_distance % 10;
							if (one_distance == 1){
								drawTextureBox(num_x + 240, num_y, disp_num1.texture_width, disp_num1.texture_height,
									disp_num1.texture_x, disp_num1.texture_y,
									disp_num1.texture_width, disp_num1.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 2){
								drawTextureBox(num_x + 240, num_y, disp_num2.texture_width, disp_num2.texture_height,
									disp_num2.texture_x, disp_num2.texture_y,
									disp_num2.texture_width, disp_num2.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 3){
								drawTextureBox(num_x + 240, num_y, disp_num3.texture_width, disp_num3.texture_height,
									disp_num3.texture_x, disp_num3.texture_y,
									disp_num3.texture_width, disp_num3.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 4){
								drawTextureBox(num_x + 240, num_y, disp_num4.texture_width, disp_num4.texture_height,
									disp_num4.texture_x, disp_num4.texture_y,
									disp_num4.texture_width, disp_num4.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 5){
								drawTextureBox(num_x + 240, num_y, disp_num5.texture_width, disp_num5.texture_height,
									disp_num5.texture_x, disp_num5.texture_y,
									disp_num5.texture_width, disp_num5.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 6){
								drawTextureBox(num_x + 240, num_y, disp_num6.texture_width, disp_num6.texture_height,
									disp_num6.texture_x, disp_num6.texture_y,
									disp_num6.texture_width, disp_num6.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 7){
								drawTextureBox(num_x + 240, num_y, disp_num7.texture_width, disp_num7.texture_height,
									disp_num7.texture_x, disp_num7.texture_y,
									disp_num7.texture_width, disp_num7.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 8){
								drawTextureBox(num_x + 240, num_y, disp_num8.texture_width, disp_num8.texture_height,
									disp_num8.texture_x, disp_num8.texture_y,
									disp_num8.texture_width, disp_num8.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 9){
								drawTextureBox(num_x + 240, num_y, disp_num9.texture_width, disp_num9.texture_height,
									disp_num9.texture_x, disp_num9.texture_y,
									disp_num9.texture_width, disp_num9.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
							if (one_distance == 0){
								drawTextureBox(num_x + 240, num_y, disp_num0.texture_width, disp_num0.texture_height,
									disp_num0.texture_x, disp_num0.texture_y,
									disp_num0.texture_width, disp_num0.texture_height,
									dispnumber,
									Color(1, 1, 1),
									0,
									Vec2f(3, 3),
									Vec2f(0, 0));
							}
						}
					}
					// ハイスコア更新チェック
					if (jump_distance > hi_score){
						std::ofstream fstr("score.txt");
						if (fstr){
							fstr << jump_distance << std::endl;
							hi_score = jump_distance;
						}
					}

					// 画面を更新
					app_env.update();
				}
				// 入力のフラッシュ
				app_env.flushInput();
			}

			// 結果画面
			{
				Texture result("res/result.png");
				Texture back("res/field.png");
				Texture dispnumber("res/number.png");
				Texture Return("res/Return to Title");

				// メインループ
				while (1) {
					// ウィンドウが閉じられたらアプリを終了
					if (!app_env.isOpen()) return 0;

					float num_x = 0 - 25 / 2;
					float num_y_now = 0 - 30 / 2;
					float num_y_hi = 0 - 30 / 2 - 270;

					// 描画準備
					app_env.setupDraw();

					// 入力による操作(break本編へ,returnアプリ終了)
					if (app_env.isPushButton(Mouse::RIGHT)) break;
					if (app_env.isPushButton(Mouse::LEFT))  break;
					if (app_env.isPushKey(GLFW_KEY_ENTER))  break;
					if (app_env.isPushKey(GLFW_KEY_ESCAPE)) return 0;

					// キャラクターのモーション情報
					struct Texture {
						// 画像からの切り抜き情報
						float texture_x, texture_y;
						float texture_width, texture_height;
					};

					// キャラクターの情報を配列で用意
					Texture move_info[] = {
						{ 0 * 100, 0, 100, 150 },
						{ 1 * 100, 0, 100, 150 },
						{ 2 * 100, 0, 100, 150 },
						{ 3 * 100, 0, 100, 150 },
						{ 4 * 100, 0, 100, 150 },
						{ 5 * 100, 0, 100, 150 },
						{ 6 * 100, 0, 100, 150 },
					};

					// 数字の情報を配列で用意
					Texture number_info[] = {
						{ 0 * 50, 0, 29, 55 },
						{ 1 * 50, 0, 48, 54 },
						{ 2 * 50, 0, 44, 55 },
						{ 3 * 50, 0, 45, 54 },
						{ 4 * 50, 0, 47, 54 },
						{ 5 * 50, 0, 43, 55 },
						{ 6 * 50, 0, 43, 54 },
						{ 7 * 50, 0, 45, 55 },
						{ 8 * 50, 0, 43, 55 },
						{ 9 * 50, 0, 38, 57 },
					};

					// キャラクターの情報を配列から取り出す
					Texture move_chara1 = move_info[0];
					Texture move_chara2 = move_info[1];
					Texture move_chara3 = move_info[2];
					Texture move_chara4 = move_info[3];
					Texture move_chara5 = move_info[4];
					Texture move_chara6 = move_info[5];
					Texture move_chara7 = move_info[6];

					Texture disp_num1 = number_info[0];
					Texture disp_num2 = number_info[1];
					Texture disp_num3 = number_info[2];
					Texture disp_num4 = number_info[3];
					Texture disp_num5 = number_info[4];
					Texture disp_num6 = number_info[5];
					Texture disp_num7 = number_info[6];
					Texture disp_num8 = number_info[7];
					Texture disp_num9 = number_info[8];
					Texture disp_num0 = number_info[9];

					// 結果画面表示
					drawTextureBox(0 - 2048 / 2, 0 - 1024 / 2, 2048, 1024,
						0, 0, 2048, 1024,
						back,
						Color(1, 1, 1));

					drawTextureBox(0 - 2048 / 2, 0 - 1024 / 2, 2048, 1024,
						0, 0, 2048, 1024,
						result,
						Color(1, 1, 1));

					// 「Return to Title」を表示
					drawTextureBox(0 - 360, 0 - 480, 512, 256,
							0, 0, 512, 256,
							Return,
							Color(1, 0, 0),
							0,
							Vec2f(1.8, 1.8),
							Vec2f(0, 0));

					// 100の位
					if (jump_distance >= 100){
						int hundred_distance = jump_distance / 100;
						if (hundred_distance == 1){
							drawTextureBox(num_x, num_y_now, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 2){
							drawTextureBox(num_x, num_y_now, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 3){
							drawTextureBox(num_x, num_y_now, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 4){
							drawTextureBox(num_x, num_y_now, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 5){
							drawTextureBox(num_x, num_y_now, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 6){
							drawTextureBox(num_x, num_y_now, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 7){
							drawTextureBox(num_x, num_y_now, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 8){
							drawTextureBox(num_x, num_y_now, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 9){
							drawTextureBox(num_x, num_y_now, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 0){
							drawTextureBox(num_x, num_y_now, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}
					// 10の位
					if (jump_distance >= 10){
						int ten_distance = jump_distance % 100 / 10;
						if (ten_distance == 1){
							drawTextureBox(num_x + 120, num_y_now, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 2){
							drawTextureBox(num_x + 120, num_y_now, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 3){
							drawTextureBox(num_x + 120, num_y_now, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 4){
							drawTextureBox(num_x + 120, num_y_now, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 5){
							drawTextureBox(num_x + 120, num_y_now, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 6){
							drawTextureBox(num_x + 120, num_y_now, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 7){
							drawTextureBox(num_x + 120, num_y_now, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 8){
							drawTextureBox(num_x + 120, num_y_now, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 9){
							drawTextureBox(num_x + 120, num_y_now, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 0){
							drawTextureBox(num_x + 120, num_y_now, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}
					// 1の位
					if (jump_distance >= 0){
						int one_distance = jump_distance % 10;
						if (one_distance == 1){
							drawTextureBox(num_x + 240, num_y_now, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 2){
							drawTextureBox(num_x + 240, num_y_now, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 3){
							drawTextureBox(num_x + 240, num_y_now, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 4){
							drawTextureBox(num_x + 240, num_y_now, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 5){
							drawTextureBox(num_x + 240, num_y_now, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 6){
							drawTextureBox(num_x + 240, num_y_now, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 7){
							drawTextureBox(num_x + 240, num_y_now, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 8){
							drawTextureBox(num_x + 240, num_y_now, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 9){
							drawTextureBox(num_x + 240, num_y_now, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 0){
							drawTextureBox(num_x + 240, num_y_now, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}
					// ハイスコア
					// 100の位
					if (hi_score >= 100){
						int hundred_distance = hi_score / 100;
						if (hundred_distance == 1){
							drawTextureBox(num_x, num_y_hi, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 2){
							drawTextureBox(num_x, num_y_hi, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 3){
							drawTextureBox(num_x, num_y_hi, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 4){
							drawTextureBox(num_x, num_y_hi, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 5){
							drawTextureBox(num_x, num_y_hi, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 6){
							drawTextureBox(num_x, num_y_hi, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 7){
							drawTextureBox(num_x, num_y_hi, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 8){
							drawTextureBox(num_x, num_y_hi, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 9){
							drawTextureBox(num_x, num_y_hi, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (hundred_distance == 0){
							drawTextureBox(num_x, num_y_hi, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}
					// 10の位
					if (hi_score >= 10){
						int ten_distance = hi_score % 100 / 10;
						if (ten_distance == 1){
							drawTextureBox(num_x + 120, num_y_hi, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 2){
							drawTextureBox(num_x + 120, num_y_hi, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 3){
							drawTextureBox(num_x + 120, num_y_hi, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 4){
							drawTextureBox(num_x + 120, num_y_hi, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 5){
							drawTextureBox(num_x + 120, num_y_hi, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 6){
							drawTextureBox(num_x + 120, num_y_hi, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 7){
							drawTextureBox(num_x + 120, num_y_hi, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 8){
							drawTextureBox(num_x + 120, num_y_hi, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 9){
							drawTextureBox(num_x + 120, num_y_hi, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (ten_distance == 0){
							drawTextureBox(num_x + 120, num_y_hi, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}
					// 1の位
					if (hi_score >= 0){
						int one_distance = hi_score % 10;
						if (one_distance == 1){
							drawTextureBox(num_x + 240, num_y_hi, disp_num1.texture_width, disp_num1.texture_height,
								disp_num1.texture_x, disp_num1.texture_y,
								disp_num1.texture_width, disp_num1.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 2){
							drawTextureBox(num_x + 240, num_y_hi, disp_num2.texture_width, disp_num2.texture_height,
								disp_num2.texture_x, disp_num2.texture_y,
								disp_num2.texture_width, disp_num2.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 3){
							drawTextureBox(num_x + 240, num_y_hi, disp_num3.texture_width, disp_num3.texture_height,
								disp_num3.texture_x, disp_num3.texture_y,
								disp_num3.texture_width, disp_num3.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 4){
							drawTextureBox(num_x + 240, num_y_hi, disp_num4.texture_width, disp_num4.texture_height,
								disp_num4.texture_x, disp_num4.texture_y,
								disp_num4.texture_width, disp_num4.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 5){
							drawTextureBox(num_x + 240, num_y_hi, disp_num5.texture_width, disp_num5.texture_height,
								disp_num5.texture_x, disp_num5.texture_y,
								disp_num5.texture_width, disp_num5.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 6){
							drawTextureBox(num_x + 240, num_y_hi, disp_num6.texture_width, disp_num6.texture_height,
								disp_num6.texture_x, disp_num6.texture_y,
								disp_num6.texture_width, disp_num6.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 7){
							drawTextureBox(num_x + 240, num_y_hi, disp_num7.texture_width, disp_num7.texture_height,
								disp_num7.texture_x, disp_num7.texture_y,
								disp_num7.texture_width, disp_num7.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 8){
							drawTextureBox(num_x + 240, num_y_hi, disp_num8.texture_width, disp_num8.texture_height,
								disp_num8.texture_x, disp_num8.texture_y,
								disp_num8.texture_width, disp_num8.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 9){
							drawTextureBox(num_x + 240, num_y_hi, disp_num9.texture_width, disp_num9.texture_height,
								disp_num9.texture_x, disp_num9.texture_y,
								disp_num9.texture_width, disp_num9.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
						if (one_distance == 0){
							drawTextureBox(num_x + 240, num_y_hi, disp_num0.texture_width, disp_num0.texture_height,
								disp_num0.texture_x, disp_num0.texture_y,
								disp_num0.texture_width, disp_num0.texture_height,
								dispnumber,
								Color(1, 1, 1),
								0,
								Vec2f(3, 3),
								Vec2f(0, 0));
						}
					}

					// 画面を更新
					app_env.update();
				}
				// 入力のフラッシュ
				app_env.flushInput();
			}
		}
	}
		// アプリ終了
	}
}