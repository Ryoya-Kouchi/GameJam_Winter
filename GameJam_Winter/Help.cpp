#include "Help.h"
#include"DxLib.h"
#include"PadInput.h"
#include"Title.h"
Help::Help()
{
}

Help::~Help()
{
}

AbstractScene* Help::Update()
{
	return this;
}

void Help::Draw() const
{
	DrawFormatString(100, 0, GetColor(255, 0, 0), "ƒwƒ‹ƒv‰æ–Ê");
}
