#pragma once

#include "AbstractScene.h"

enum class TITLE_MENU
{
	GAME_START,
	GAME_HELP,
	GAME_END,
	TITLE_SIZE
};

class TitleScene :public AbstractScene
{
private:

private:
	/*const char* menu_items[static_cast<int>(TITLE_MENU::TITLE_SIZE)] = {
   "すたーと",
   "ヘルプ",
   "えんど"
	};*/
	int background_image;			//背景画像
	int now_menu;                   //現在選択してるメニュー
	int MenuFont;                   //メニュー用のフォント
	int input_margin;               //操作時間間隔

public:
	TitleScene();
	~TitleScene();
	//描画以外の更新を実行
	AbstractScene* Update() override;
	//描画に関することを実装
	void Draw() const override;
};
