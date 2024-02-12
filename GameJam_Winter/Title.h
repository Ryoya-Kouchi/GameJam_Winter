#pragma once
#include"AbstractScene.h"

enum class TITLE_MENU
{
	GAME_START,
	GAME_END,
	TITLE_SIZE
};
class Title :public AbstractScene
{
private:
	const char* menu_items[static_cast<int>(TITLE_MENU::TITLE_SIZE)] = {
   "すたーと",
   "えんど"
	};
	int now_menu; //現在選択してるメニュー
	int MenuFont; //メニュー用のフォント
	int input_margin;  //操作時間間隔

public:
	//コンストラクタ
	Title();

	//デストラクタ
	virtual ~Title();

	//描画以外の更新を実装する
	virtual AbstractScene* Update()override;

	//描画に関することを実装する
	virtual void Draw() const override;
};
