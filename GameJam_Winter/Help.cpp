#include "Help.h"
#include "PadInput.h"
#include "DxLib.h"
#include "Title.h"

HelpScene::HelpScene() :background_image(NULL)
{
//画像の読み込み

	barrier = LoadGraph("Resource/images/barrier.png");
	Health = LoadGraph("Resource/images/Health.bmp");
	Zone = LoadGraph("Resource/images/Zone.bmp");
	
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
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) == true))
	{
		return new TitleScene();
	}

	return this;
}

//描画処理
void HelpScene::Draw() const
{
	

	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(30);
	
	DrawString(20, 70, "勝利条件", GetColor(255, 0, 0), 0xffffff);
	DrawString(20, 110, "先にゴールするか相手の燃料を\nゼロにすること！！", 0xffffff, 0);
	
	DrawString(20, 200, "操作方法",GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 240, "十字キーまたは\n左スティックで移動！", 0xffffff, 0);

	//Barrierの説明
	DrawRotaGraph(710, 90, 0.9, size, barrier, TRUE);

	DrawString(650, 200, "バリア", GetColor(30, 144, 255), 0xffffff);
	DrawString(590, 240, "一度だけ衝撃から\n守ることができる！", 0xffffff, 0);

	//Healthの説明
	DrawRotaGraph(950, 90, 1.5,size, Health, TRUE);

	DrawString(930, 200, "回復", GetColor(0, 250, 154), 0xffffff);
	DrawString(900, 240, "燃料を\n回復させる！", 0xffffff, 0);

	//Zoneの説明
	DrawRotaGraph(1150, 90, 1.5, size, Zone, TRUE);

	DrawString(1130, 200, "加速", GetColor(135, 206, 250), 0xffffff);
	DrawString(1100, 240, "速度が\n上がるよ！", 0xffffff, 0);

	//ミッションの説明
	DrawString(20, 350, "/******ミッション************************/", GetColor(0, 255, 0), 0xffffff);
	DrawString(20, 390, "____________________________", 0xffffff, 0);

	

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
			DrawString(390, 610, "Bボタンを押してタイトルに戻る", 0xffffff, 0);
		}
		
	}
	if (Button == 0) 
	{
		//Bボタンでタイトルに戻る説明
		SetFontSize(30);
		DrawString(390, 610, "Bボタンを押してタイトルに戻る", 0xffffff, 0);
	}

	//ヒント
	SetFontSize(10);
	DrawString(1090, 700, "スティックのほうが有利だよ、、",GetColor(192,192,192), 0xffffff);
}

