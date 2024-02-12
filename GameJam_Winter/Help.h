#pragma once
#include"AbstractScene.h"
class Help : public AbstractScene
{
private:

public:
	Help();
	~Help();
	virtual AbstractScene* Update()override;
	void Draw()const;
};