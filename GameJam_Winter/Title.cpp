#include "Title.h"
#include "PadInput.h"
#include"DxLib.h"
#include<iostream>
#include"Help.h"
#include"GameMainScene.h"

#define SCREEN_WIDTH 1280

TitleScene::TitleScene()
{
	//MenuFont = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 32, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	//画像読み込み
    background_image = LoadGraph("Resource/images/Title.png");
	//	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.pngがありません\n");
	}
	now_menu = static_cast<int>(TITLE_MENU::GAME_START);
	input_margin = 0;
}

TitleScene::~TitleScene()
{

}

AbstractScene* TitleScene::Update()
{	// 操作間隔時間
	const int max_input_margin = 15;
	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// スティックのY座標を取得
		int stick_y1 = PAD_INPUT::GetLStick1().ThumbY;
		int stick_y2 = PAD_INPUT::GetLStick2().ThumbY;

		if (std::abs(stick_y1) > stick_sensitivity || std::abs(stick_y2) > stick_sensitivity) {
			// スティックが上に移動した場合
			if (stick_y1 > 0 || stick_y2 > 0) {
				// メニュー選択肢を一つ前に移動
				now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			//スティックが下に移動した場合
			else if (stick_y1 < 0 || stick_y2 < 0) {
				// メニュー選択肢を一つ次に移動
				now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			input_margin = 0;
		}
	}
	// 十字キー上に移動した場合
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_DPAD_UP) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_DPAD_UP) == true)) {
		// メニュー選択肢を一つ前に移動
		now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
	}
	//十字キー下に移動した場合
	else if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_DPAD_DOWN) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_DPAD_DOWN) == true)) {
		// メニュー選択肢を一つ次に移動
		now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
	}


	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		TITLE_MENU current_select = static_cast<TITLE_MENU>(now_menu);
		switch (current_select)
		{
		case TITLE_MENU::GAME_START:
			return new GameMainScene();
			break;
		case TITLE_MENU::GAME_HELP:
			return new HelpScene();
			break;
		case TITLE_MENU::GAME_END:
			return nullptr;
			break;
		default:
			printfDx("未実装な機能です。\n");
			break;
		}
	}

	return this;

}

//描画処理
void TitleScene::Draw() const
{

	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);
	
	for (int i = 0; i < static_cast<int>(TITLE_MENU::TITLE_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 200;

		// 文字列のY座標間隔
		const int margin_y = 100;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (now_menu == i) {
			color = ~color;
			border_color = ~border_color;
		}
		DrawStringToHandle(SCREEN_WIDTH / 2 - 100, i * margin_y + base_y, menu_items[i], color, MenuFont, border_color);
	}
	DrawStringToHandle(150, 100, "GameJam_Winter", 0xffffff, MenuFont);

}

////終了時処理
//void TitleScene::Finalize()
//{
//	
//}

////現在のシーン情報を取得
//eAbstractSceneType TitleScene::GetNowScene() const
//{
//	return eAbstractSceneType::E_TITLE;
//}
