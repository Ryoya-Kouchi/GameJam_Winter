#pragma once
#pragma once

#include "Vector2D.h"
#include "Barrier.h"
#include"PadInput.h"

class Player2
{
private:
	bool is_active;			//有効状態か？
	int image;
	Vector2D location2;//画像データ
	Vector2D box_size;		//当たり判定大きさ
	float angle;			//角度
	float speed;			//速さ
	float hp;				//体力
	float fuel;				//燃料
	int barrier_count;		//バリアの枚数
	Barrier* barrier;		//バリア
	
	int player2;
	int input_margin;
	int stick_y2;
	int stick_x2;
public:
	Player2();
	~Player2();

	void Initialize();		//初期化処理
	void Update();			//更新処理
	void Draw();			//描画処理
	void Finalize();		//終了時処理

public:
	static float X2;
	static float Y2;
	//static float Vector2D::x;
	void SetActive(bool flg);		//有効フラグ設定
	void DecreaseHp(float value);	//体力減少処理
	Vector2D GetLocation() const;	//位置座標取得
	Vector2D GetBoxSize() const;	//当たり判定の大きさ取得
	float GetSpeed() const;			//速さ取得処理
	float GetFuel() const;			//燃料取得
	float GetHp() const;			//体力取得
	int GetBarriarCount() const;	//バリアの枚数取得
	bool IsBarrier() const;			//バリア有効か？を取得

private:
	void Movement();				//移動処理
	void Acceleration();			//加速処理

};