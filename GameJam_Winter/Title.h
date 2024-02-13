#pragma once

#include "AbstractScene.h"

class TitleScene :public AbstractScene
{
private:

private:
	int background_image;			//�w�i�摜
	int menu_image;					//���j���[�摜
	int cursor_image;				//�J�[�\���摜
	int  menu_cursor;				//���j���[�J�[�\���ԍ�

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eAbstractSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eAbstractSceneType GetNowScene() const override;

};
