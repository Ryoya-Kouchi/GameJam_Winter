#include "Title.h"
#include "PadInput.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}


//初期化処理
void TitleScene::Initialize()
{
	//画像読み込み
	background_image = LoadGraph("Resource/images/Title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
}

		if (std::abs(stick_y1) > stick_sensitivity || std::abs(stick_y2) > stick_sensitivity) {
			// スティックが上に移動した場合
			if (stick_y1 > 0 || stick_y2 > 0 ) {
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
		switch (menu_cursor)
		{
		case 0:
			return eAbstractSceneType::E_MAIN;
		case 1:
			return eAbstractSceneType::E_RANKING_DISP;
		case 2:
			return eAbstractSceneType::E_HELP;
		default:
			return eAbstractSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描面
	DrawGraph(120, 200, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eAbstractSceneType TitleScene::GetNowScene() const
{
	return eAbstractSceneType::E_TITLE;
}
