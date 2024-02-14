#pragma once

#include "Vector2D.h"

class Item
{
private:
	int barrier_image;
	int helth_image;
	int supana_image;
	Vector2D location;	//ˆÊ’uî•ñ

public:
	Item();
	~Item();
	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();
	Vector2D GetLocation() const;		//ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;		//“–‚½‚è”»’è‚Ì‘å‚«‚³

};