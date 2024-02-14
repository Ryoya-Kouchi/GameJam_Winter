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
	menu_image_Start = LoadGraph("Resource/images/start_m.bmp");
	menu_image_Help  = LoadGraph("Resource/images/help_m.bmp");
	menu_image_End   = LoadGraph("Resource/images/end_m.bmp");
	//	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.pngがありません\n");
	}
	now_menu = static_cast<int>(TITLE_MENU::GAME_START);
	input_margin = 0;
	//タイトル遷移時タイトル用BGMをループで流す
	PlaySoundFile("Resource/BGM/maou_bgm_neorock76.mp3", DX_PLAYTYPE_LOOP);
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
	DrawGraph(0, 0, background_image, TRUE);

	// 点滅処理用の変数
	static int BrinkCounter;

	// 点滅用の変数に 1 を足す
	BrinkCounter++;

	// 点滅用の変数が 60 になっていたら 0 にする
	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", BrinkCounter);

	for (int i = 0; i < static_cast<int>(TITLE_MENU::TITLE_SIZE); i++)
	{
		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (now_menu == i) {
			// 点滅用の変数の値が 30 未満のときだけSTART,HELP,ENDを描画する
			if (BrinkCounter < 30)
			{
				if (now_menu == 0) {
					SetFontSize(90);
					DrawString(100, 250, "    START  ", GetColor(255, 255, 255));
				}
				if (now_menu == 1) {
					SetFontSize(90);
					DrawString(100, 400, "    HELP   ", GetColor(255, 255, 255));
				}
				if (now_menu == 2) {
					SetFontSize(90);
					DrawString(100, 550, "    END    ", GetColor(255, 255, 255));
				}
			}
				if (now_menu != 0) {
					SetFontSize(90);
					DrawString(100, 250, "    START  ", GetColor(255, 255, 255));
				}
				if (now_menu != 1) {
					SetFontSize(90);
					DrawString(100, 400, "    HELP   ", GetColor(255, 255, 255));
				}
				if (now_menu  != 2) {
					SetFontSize(90);
					DrawString(100, 550, "    END    ", GetColor(255, 255, 255));
				}
		}
	}
}