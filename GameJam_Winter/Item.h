#pragma once

#include "Vector2D.h"
#define ITEM_MAX 3

class Item
{
private:
	//int image[3];
	Vector2D location;	//位置情報

	int item_image[3];
	struct ITEM {
		int flg;
		int type;
		int img;
		int x, y, w, h;
		int speed;
		int point;
	};

public:
	Item();
	~Item();
	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

	void ItemControl();
	int CreateItem();

	Vector2D GetLocation() const;		//位置情報の取得
	Vector2D GetBoxSize() const;		//当たり判定の大きさ

};