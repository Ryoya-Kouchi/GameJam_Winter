#pragma once


#include "AbstractScene.h"

class  EndScene :public AbstractScene
{
private:

	float size;


	int background_image;		//�w�i�摜
	int Health;					//Health�摜
	int barrier;				//Barrier�摜
	int Zone;					//Zone�摜
	int Button;					//B�{�^���I��

public:
	EndScene();
	~EndScene();
	virtual AbstractScene* Update() override;
	void Draw()const;


};

