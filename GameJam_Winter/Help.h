#pragma once

#include "AbstractScene.h"

class HelpScene :public AbstractScene
{
private:

	float size;


	int background_image;		//�w�i�摜
	int Health;					//Health�摜
	int barrier;				//Barrier�摜
	int Zone;					//Zone�摜
	int Button;					//B�{�^���I��

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