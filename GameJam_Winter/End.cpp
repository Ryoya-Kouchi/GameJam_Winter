#include "End.h"
#include "PadInput.h"
#include "DxLib.h"
#include "Title.h"

EndScene::EndScene() :background_image(NULL)
{
	

}

EndScene::~EndScene()
{

}

//更新処理
AbstractScene* EndScene::Update()
{
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) == true))
	{
		StopSoundFile();
		return nullptr;
		
	}

	

	return this;
}
//描画処理
void EndScene::Draw() const
{
	//End画面
	SetFontSize(30);

	DrawString(20, 70, "製作者", GetColor(255, 0, 0), 0xffffff);
	DrawString(20, 110, "アカミネサン　りょうや　うっうー　すえきち", 0xffffff, 0);

	DrawString(20, 200, "BGM引用元", GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 240, "魔王魂様　https://maou.audio/bgm_neorock76/", 0xffffff, 0);

	DrawString(20, 330, "SE引用元", GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 370, "効果音ラボ様　https://soundeffect-lab.info/sound/button/", 0xffffff, 0);

	// 点滅処理用の変数
	static int BrinkCounter;

	// 点滅用の変数に 1 を足す
	BrinkCounter++;

	// 点滅用の変数が 60 になっていたら 0 にする
	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	// 点滅用の変数の値が 30より大きいときだけBボタンを押してタイトルに戻るを描画する
	if (BrinkCounter > 30)
	{
		if (Button != 0)
		{
			//Bボタンでタイトルに戻る説明
			SetFontSize(30);
			DrawString(390, 610, "Bボタンを押して終了", 0xffffff, 0);
		}

	}
	if (Button == 0)
	{
		//Bボタンでタイトルに戻る説明
		SetFontSize(30);
		DrawString(390, 610, "Bボタンを押して終了", 0xffffff, 0);
	}
}