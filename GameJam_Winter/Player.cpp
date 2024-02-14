#include "Player.h"
#include "PadInput.h"
#include "Dxlib.h"
#include<iostream>
#include"Player2.h"
Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{
	//画像読込
	Player1 = LoadGraph("Resource/images/Player1.bmp");


	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;
}

Player::~Player()
{

}

//初期化処理
//void Player::Initialize()
//{
//	is_active = true;
//	location = Vector2D(320.0f, 380.0f);
//	box_size = Vector2D(31.0f, 60.0f);
//	angle = 0.0f;
//	speed = 3.0f;
//	hp = 1000;
//	fuel = 20000;
//	barrier_count = 3;
//
//	//画像読み込み
//	//image = LoadGraph("Resource/images/ca.bmp");
//
//	Player1 = LoadGraph("Resource/images/Player1.bmp");
//
//	//エラーチェック
//	if (Player1 == -1)
//	{
//		throw("Resource/image/car1pol.bmpがありません\n");
//	}
//}

//更新処理
void Player::Update()
{
	Hit();
	//操作不可能状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//燃料の消費
	fuel -= speed;

	//移動処理
	Movement();

	//加減速処理
	Acceleration();

	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//バリア処理
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraph(location.x, location.y, 1.5, angle, Player1, TRUE);
	//左
	DrawLine(location.x - 30, location.y + 80, location.x -30, location.y - 30,GetColor(0, 255, 0), FALSE);
	//右
	DrawLine(location.x + 30, location.y + 80, location.x + 30, location.y - 30, GetColor(0, 255, 0), FALSE);

	DrawFormatString(100, 100, GetColor(255, 0, 0), "flg:%d", flg);
	////バリアが生成されていたら、描画を行う
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}
}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel()const
{
	return this->fuel;
}

//体力取得処理
float Player::GetHp()const
{
	return this->hp;
}

//バリア枚数取得処理
int Player::GetBarriarCount()const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier()const
{
	return(barrier != nullptr);
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;


	// 操作間隔時間
	const int max_input_margin = 10;
	// スティックの感度
	const int stick_sensitivity = 20000;

	int stick_y1 = PAD_INPUT::GetLStick1().ThumbY;
	int stick_x1 = PAD_INPUT::GetLStick1().ThumbX;
	
		if (std::abs(stick_y1) > stick_sensitivity ) {
			// スティックが上に移動した場合
			if (stick_y1 > 0) {
				move += Vector2D(0.0f, -1.0f);
			}
			//スティックが下に移動した場合
			else if (stick_y1 < 0 ) {
				move += Vector2D(0.0f, 1.0f);
			}
			input_margin = 0;
		}
	
		if (std::abs(stick_x1) > stick_sensitivity) {
			// スティックが右に移動した場合
			if (stick_x1 > 0) {
				move += Vector2D(1.0f, 0.0f);
				angle = DX_PI_F / 18;
			}
			//スティックが左に移動した場合
			else if (stick_x1 < 0 ) {
				move += Vector2D(-1.0f, 0.0f);
				angle = -DX_PI_F / 18;
			}
	}
	location += move;


	

	//十字移動処理
	if (PAD_INPUT::OnPressed1(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-1.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (PAD_INPUT::OnPressed1(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(1.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (PAD_INPUT::OnPressed1(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -1.0f);
	}
	if (PAD_INPUT::OnPressed1(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 1.0f);
	}

	location += move;

	//画面外にいかないように制限する
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	//LBボタンが押されたら、減速する
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//REボタンが押されたら、加速する
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}
void Player::Hit()
{
	//左幅
	int playerX1 = location.x - 30;
	//右幅
	int playerX2 = location.x + 30;
	//上幅
	int playerY1 = location.y + 80;
	//下幅
	int playerY2 = location.y - 80;

	//プレイヤー２
	//左幅
	int player2X1 = Player2::X2 - 30;
	//右幅
	int player2X2 = Player2::X2 + 30;
	//上幅
	int player2Y1 = Player2::Y2 + 80;
	//下幅
	int player2Y2 = Player2::Y2 - 80;

	if (playerX1 == player2X2  && playerY1 == player2Y1 && playerY2 == player2Y2 ||  //左
		playerX2 == player2X1 &&  playerY1 == player2Y1 && playerY2 == player2Y2)    //右
	{
		flg = 1;
	}
}