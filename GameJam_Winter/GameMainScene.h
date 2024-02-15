#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "Item.h"
#include"Player2.h"
#include"Enemy.h"

class GameMainScene :public AbstractScene
{
private:
	int back_ground;			//背景画像
	int barrier_image;			//バリア画像
	int mileage;				//走行距離
	int mileage2;
	int enemy_image[3];			//敵画像
	int enemy_count[3];			//通り過ぎた敵カウント
	Player* player;				//プレイヤー
	Player2* player2;
	Item* item;
	Enemy** enemy;				//敵

public:
	GameMainScene();
	virtual ~GameMainScene();

	//virtual void Initialize() override;
	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
	//virtual void Finalize() override;

	//virtual eAbstractSceneType GetNowScene() const override;

private:
	////ハイスコア読み込み処理
	//void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Player2* p2);


};