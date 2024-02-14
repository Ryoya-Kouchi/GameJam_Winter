#include "item.h"
#include"DxLib.h"

Item::Item()
{
	barrier_image = LoadGraph("Resource / images / barrier.png");
	helth_image = LoadGraph("Resource / images / Helth.bmp");
	supana_image = LoadGraph("Resource / images /supana.bmp");

}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::Draw() const
{
}
