#include "GameMain.h"
#include"DxLib.h"
#include"PadInput.h"
#include"FpsController.h"

GameMain::GameMain()
{
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	return this;
}

void GameMain::Draw() const
{
	SetFontSize(20);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "GameMain");
}

