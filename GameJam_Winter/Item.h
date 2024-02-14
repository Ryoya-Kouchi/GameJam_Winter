#pragma once

#include "Vector2D.h"

class Item
{
private:
	int barrier_image;
	int helth_image;
	int supana_image;
	Vector2D location;	//�ʒu���

public:
	Item();
	~Item();
	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();
	Vector2D GetLocation() const;		//�ʒu���̎擾
	Vector2D GetBoxSize() const;		//�����蔻��̑傫��

};