#pragma once

#include "AbstractScene.h"

class HelpScene :public AbstractScene
{
private:
	int background_image;		//�w�i�摜

public:
	HelpScene();
	virtual~HelpScene();

	virtual void Initialize() override;
	virtual eAbstractSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eAbstractSceneType GetNowScene() const override;

}; 