#pragma once

#include "Vector2D.h"
#define ITEM_MAX 3

class Item
{
private:
	//int image[3];
	Vector2D location;	//ˆÊ’uî•ñ

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

	Vector2D GetLocation() const;		//ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;		//“–‚½‚è”»’è‚Ì‘å‚«‚³

};