#pragma once


#include "AbstractScene.h"

class  EndScene :public AbstractScene
{
private:

	float size;


	int background_image;		//”wŒi‰æ‘œ
	int Health;					//Health‰æ‘œ
	int barrier;				//Barrier‰æ‘œ
	int Zone;					//Zone‰æ‘œ
	int Button;					//Bƒ{ƒ^ƒ“‘I‘ð

public:
	EndScene();
	~EndScene();
	virtual AbstractScene* Update() override;
	void Draw()const;


};

