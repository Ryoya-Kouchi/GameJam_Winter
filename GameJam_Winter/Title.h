#pragma once

#include "AbstractScene.h"

class TitleScene :public AbstractScene
{
private:

private:
	int background_image;			//背景画像
	int menu_image;					//メニュー画像
	int cursor_image;				//カーソル画像
	int  menu_cursor;				//メニューカーソル番号

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eAbstractSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eAbstractSceneType GetNowScene() const override;

};
