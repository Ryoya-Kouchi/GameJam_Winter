#include "GameMainScene.h"
#include "DxLib.h"
#include <math.h>
#include <stdlib.h> // rand()関数用
#include <time.h>   // time()関数用
#include"Player.h"
#include"Player2.h"
#include "Item.h"

GameMainScene::GameMainScene() : back_ground(NULL),
barrier_image(NULL), mileage(0),mileage2(0)/*player(nullptr)*/,enemy(nullptr)
{
	
	player = new Player();
	//player2 = new Player2();
	item = new Item();
		//画像の読み込み
	back_ground = LoadGraph("Resource/images/back2.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/item2.bmp", 3, 3, 1, 63, 100, enemy_image);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.pngがありません\n");
	}

	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません\n");
	}

	//オブジェクトの初期化
	//player->Initialize();
	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

}

GameMainScene::~GameMainScene()
{

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
	//プレイヤーの更新
	player->Update();
	//player2->Update();
	//移動処理の更新
	mileage += (int)player->GetSpeed() + 5;
	//移動処理の更新
	//mileage2 += (int)player2->GetSpeed() + 5;
	//item->Update();

	//double probability = 100.0; // 確率（1%）
	//srand((unsigned)time(NULL)); // 乱数の初期化

	//if ((double)rand() / RAND_MAX < probability) {
	//	// ここに処理を書く			
	//	item->CreateItem();
	//}
	
	//敵生成処理
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}

	//敵の更新と当たり判定チェック
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			//画面外に行ったら、敵を削除してスコア加算
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}

			////当たり判定の確認
			//if (IsHitCheck(player, enemy[i]))
			//{
			//	player->SetActive(false);
			//	player->DecreaseHp(-50.0f);
			//	enemy[i]->Finalize();
			//	delete enemy[i];
			//	enemy[i] = nullptr;
			//}
		}
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
	//player2->Draw();

	item->Draw();
	
	//敵の描画
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}


	//UIの描画
	DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	
	DrawFormatString(1110, 200, GetColor(0, 0, 0), "走行距離");
	DrawFormatString(1155, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	//DrawFormatString(1510, 240, GetColor(0, 0, 0), "スピード");
	//DrawFormatString(1155, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

	

	////燃料ゲージの描画
	//float fx = 510.0f;
	//float fy = 390.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	////体力ゲージの描画
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

//終了時処理
//現在シーン情報を取得



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
