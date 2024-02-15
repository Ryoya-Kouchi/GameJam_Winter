#pragma once

#include "Vector2D.h"
#define ITEM_MAX 3

class Item
{
private:
	//int image[3];
	Vector2D location;	//�ʒu���

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

	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫��

};