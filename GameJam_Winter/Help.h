#pragma once

#include "AbstractScene.h"

class HelpScene :public AbstractScene
{
private:

	float size;


	int background_image;		//”wŒi‰æ‘œ
	int Health;					//Health‰æ‘œ
	int barrier;				//Barrier‰æ‘œ
	int Zone;					//Zone‰æ‘œ

public:
	HelpScene();
	~HelpScene();
	virtual AbstractScene* Update() override;
	void Draw()const;

	
	//virtual void Initialize() override;
	//virtual eAbstractSceneType Update() override;
	//virtual void Draw() const override;
	//virtual void Finalize() override;

	//virtual eAbstractSceneType GetNowScene() const override;

}; 