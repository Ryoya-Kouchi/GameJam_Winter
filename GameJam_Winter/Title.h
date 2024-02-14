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
	int background_image;			//背景画像
	int menu_image_Start;			//メニュー画像スタート
	int menu_image_Help;            //メニュー画像ヘルプ
	int menu_image_End;             //メニュー画像エンド
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
