#include "Help.h"
#include "PadInput.h"
#include "DxLib.h"

HelpScene::HelpScene() :background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

////初期化処理
//void HelpScene::Initialize()
//{
//	//画像読み込み
//	background_image = LoadGraph("Resource/images/Title.bmp");
//
//	//エラーチェック
//	if (background_image == -1)
//	{
//		throw("Resource/images/Title.bmpがありません\n");
//	}
//}

//更新処理
AbstractScene* HelpScene::Update()
{
	return this;
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);

	DrawString(20, 160, "これは2人プレイの走り続けながら", 0xffffff, 0);
	DrawString(20, 180, "carバトルゲームです!!", 0xffffff, 0);
	DrawString(20, 200, "相手より先にゴールするか相手のHPをゼロにすると", 0xffffff, 0);
	DrawString(20, 220, "勝利です^_^", 0xffffff, 0);
	DrawString(20, 240, "燃料が尽きるか自分のHPがゼロになると", 0xffffff, 0);
	DrawString(20, 260, "ゲームオーバーです", 0xffffff, 0);
	

	DrawString(150, 450, "----　Bボタンを押してタイトルに戻る　----", 0xffffff, 0);

}

