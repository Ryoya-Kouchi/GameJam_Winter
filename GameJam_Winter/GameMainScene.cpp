#include "GameMainScene.h"
#include "DxLib.h"
#include <math.h>
#include"Player.h"
#include"Player2.h"
#include "Item.h"
#include"Title.h"

GameMainScene::GameMainScene() : back_ground(NULL),
barrier_image(NULL), mileage(0),mileage2(0),player(nullptr)
{
	gaoldistance = 1000;
	player = new Player();
	player2 = new Player2();
		//画像の読み込み
	back_ground = LoadGraph("Resource/images/back2.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}

	//ゲームメイン遷移時ゲームメイン用BGMをループで流す
	PlaySoundFile("Resource/BGM/maou_bgm_neorock70.mp3", DX_PLAYTYPE_LOOP);

	//オブジェクトの初期化
	//player->Initialize();

}

GameMainScene::~GameMainScene()
{
	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

}

//初期化処理
//void GameMainScene::Initialize()
//{
//	
//
//	//画像の読み込み
//	back_ground = LoadGraph("Resource/images/back.bmp");
//	
//
//	//エラーチェック
//	if (back_ground == -1)
//	{
//		throw("Resource/images/back.bmpがありません\n");
//	}
//
//	
//
//	//オブジェクト生成
//	player = new Player;
//	
//
//	//オブジェクトの初期化
//	player->Initialize();
//
//	
//}

//更新処理
AbstractScene* GameMainScene::Update()
{
	//ゴールまでの距離の減少
	gaoldistance -= 1;
	//プレイヤーの更新
	player->Update();
	player2->Update();
	//移動処理の更新
	mileage += (int)player->GetSpeed() + 5;
	//移動処理の更新
	mileage2 += (int)player2->GetSpeed() + 5;

	//当たり判定の確認
	if (IsHitCheck(player, player2))
	{
		static int BrinkCounter;
		BrinkCounter++;
		player->SetActive(false);
		player->DecreaseHp(-50.0f);
		player2->DecreaseHp(-50.0f);
		player2->SetActive(false);
		if (BrinkCounter < 30) {

		}
	}

	//プレイヤーの燃料か体力が０未満なら、リザルトに遷移する
	if (player->GetHp() < 0 &&  1050 >=fxe + (player->GetHp() * 100 / 10000) || gaoldistance <= 0)
	{
		// ゲームメインBGMを止める
		StopSoundFile();
		return new TitleScene();
	}

			return this;
}

//描画処理
void GameMainScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//プレイヤーの描画
	player->Draw();
	
	//プレイヤー２の描画
	player2->Draw();


	//UIの描画
	DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	SetFontSize(38);
	
	DrawFormatString(1000, 10, GetColor(0, 0, 0), "ゴールまであと");
	DrawFormatString(1000, 60, GetColor(0, 0, 0), "%d", gaoldistance);
	
	SetFontSize(30);
	//燃料・体力ゲージの描画
	float fx = 1050.0f;
	float fy = 350.0f;

	float fxe = 1150.0f;
	float fye = 380.0f;
	
	fx = 1050.0f;
	fy = 450.0f;
	DrawFormatStringF(1050, 370, GetColor(0, 0, 0), "PLAYER1 HP");
	DrawBoxAA(fx, fy + 20.0f, fxe + (player->GetHp() * 100 / 10000), fye + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fxe + 100.0f, fye + 40.0f, GetColor(0, 0, 0), FALSE);

	//燃料・体力ゲージの描画
	float fxx = 1050.0f;
	float fyy = 550.0f;

	//DrawFormatString(1050,300, GetColor(0, 0, 0), "%d", player->GetHp());

	float fxxe = 1150.0f;
	float fyye = 580.0f;
	
	fxx = 1050.0f;
	fyy = 650.0f;
	DrawFormatStringF(1050, 570, GetColor(0, 0, 0), "PLAYER2 HP");
	DrawBoxAA(fxx, fyy + 20.0f, fxxe + (player->GetHp() * 100 / 10000), fyye + 40.0f, GetColor(0, 0, 255), TRUE);
	DrawBoxAA(fxx, fyy + 20.0f, fxxe + 100.0f, fyye + 40.0f, GetColor(0, 0, 0), FALSE);
}


//終了時処理
//現在シーン情報を取得

bool GameMainScene::IsHitCheck(Player* p, Player2* p2)
{
	//プレイヤーがバリアを貼っていたら、当たり判定を無視する
	if (p->IsBarrier())
	{
		return false;
	}

	//敵情報がなければ、当たり判定を無視する
	if (p2 == nullptr)
	{
		return false;
	}

	//位置情報の差分を取得
	Vector2D diff_location = p->GetLocation() - p2->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + p2->GetBoxSize();

	//子リジョンデータより位置情報の差分が小さいなら、ヒット判定とする
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}


////当たり判定処理(プレイヤーと敵)
//bool GameMainScene::IsHitCheck(Player* p)
//{
//	//プレイヤーがバリアを貼っていたら、当たり判定を無視する
//	if (p->IsBarrier())
//	{
//		return false;
//	}
//
//	
//
//	//位置情報の差分を取得
//	//Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//当たり判定サイズの大きさを取得
//	//Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//子リジョンデータより位置情報の差分が小さいなら、ヒット判定とする
//	//return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}
//
