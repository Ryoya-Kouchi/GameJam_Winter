#pragma once
#include"AbstractScene.h"

class GameMain :public AbstractScene
{
private:

public:
	GameMain();
	~GameMain();
	void Draw()const;
	virtual AbstractScene* Update()override;

};