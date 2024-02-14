#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "Item.h"

class GameMainScene :public AbstractScene
{
private:
	int back_ground;			//背景画像
	int barrier_image;			//バリア画像
	int mileage;				//走行距離
	int enemy_count[3];			//通り過ぎた敵カウント
	Player* player;				//プレイヤー
	Item* item;

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
	//bool IsHitCheck(Player* p);


};