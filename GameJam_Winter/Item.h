#pragma once

#include "Vector2D.h"

class Item
{
private:
	int barrier_image;
	int helth_image;
	int supana_image;
	Vector2D location;	//位置情報

public:
	Item();
	~Item();
	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();
	Vector2D GetLocation() const;		//位置情報の取得
	Vector2D GetBoxSize() const;		//当たり判定の大きさ

};