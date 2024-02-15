#include "Player2.h"
#include "PadInput.h"
#include "Dxlib.h"
#include<iostream>

float Player2::X2;	//player2のｘ座標

//float Vector2D::x;
Player2::Player2():is_active(false), image(NULL), /*location2(0.0f)*/  box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{
	//画像読込
	player2 = LoadGraph("Resource/images/Player2.bmp");

	
	is_active = true;
	location2 = Vector2D(700.0f, 380.0f);
	box_size = Vector2D(32.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 10000;
	fuel = 20000;
	barrier_count = 3;
}

Player2::~Player2()
{

}

//初期化処理
//void Player::Initialize()
//{
//	is_active = true;
//	location = Vector2D(320.0f, 380.0f);
//	box_size = Vector2D(32.0f, 60.0f);
//	angle = 0.0f;
//	speed = 3.0f;
//	hp = 2000;
//	fuel = 20000;
//	barrier_count = 3;
//
//	//画像読み込み
//	//image = LoadGraph("Resource/images/ca.bmp");
//
//	Player2 = LoadGraph("Resource/images/Player2.bmp");
//
//	//エラーチェック
//	if (Player2 == -2)
//	{
//		throw("Resource/image/car2pol.bmpがありません\n");
//	}
//}

//更新処理
void Player2::Update()
{
	int x2;
	//操作不可能状態であれば、自身を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;

		if (angle >= DX_PI_F * 4.0f)
		{
			//右から当たった場合
			if (Player::x <= location2.x) {
				x2 = location2.x + 300.0f;
				while (location2.x <= x2) {
					move += Vector2D(+30.0, 0.0f);
					location2 += move;
					if (location2.x <= x2 || location2.x >= x2)
					{
						location2.x = x2;
						break;
					}
				}
				if (location2.x == x2) {
					is_active = true;
				}
			}
			//左から当たった場合
			else if (Player::x >= location2.x) {
				x2 = location2.x - 300.0f;

				while (location2.x >= x2) {
					move += Vector2D(-30.0, 0.0f);
					location2 += move;
					if (location2.x <= x2 || location2.x >= x2)
					{
						location2.x = x2;
						break;
					}
				}
				if (location2.x == x2) {
					is_active = true;
				}
			}
		}
		return;
	}
	//燃料の消費
	fuel -= speed;

	//移動処理
	Movement();

	X2 = location2.x;


	//加減速処理
	Acceleration();

	if (location2.x < 0) {
		location2.x = 0;
	}
	if (location2.x > 1000) {
		location2.x = 1000;
	}
	if (location2.y < 0) {
		location2.y = 0;
	}
	if (location2.y > 720) {
		location2.y = 720;
	}

	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//バリア処理
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_B) && barrier_count > 0)
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
void Player2::Draw()
{
	//プレイヤー画像の描画
	DrawRotaGraph(location2.x, location2.y, 1.5, angle, player2, TRUE);

	////バリアが生成されていたら、描画を行う
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}
}

//終了時処理
void Player2::Finalize()
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
void Player2::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player2::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player2::GetLocation()const
{
	return this->location2;
}

//当たり判定の大きさ取得処理
Vector2D Player2::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player2::GetSpeed()const
{
	return this->speed;
}

//燃料取得処理
float Player2::GetFuel()const
{
	return this->fuel;
}

//体力取得処理
float Player2::GetHp()const
{
	return this->hp;
}

//バリア枚数取得処理
int Player2::GetBarriarCount()const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player2::IsBarrier()const
{
	return(barrier != nullptr);
}

//移動処理
void Player2::Movement()
{
	Vector2D move2 = Vector2D(0.0f);
	angle = 0.0f;


	// 操作間隔時間
	const int max_input_margin = 20;
	// スティックの感度
	const int stick_sensitivity = 20000;

	int stick_y2 = PAD_INPUT::GetLStick2().ThumbY;
	int stick_x2 = PAD_INPUT::GetLStick2().ThumbX;

	if (std::abs(stick_y2) > stick_sensitivity) {
		// スティックが上に移動した場合
		if (stick_y2 > 0) {
			move2 += Vector2D(0.0f, -2.0f);
		}
		//スティックが下に移動した場合
		else if (stick_y2 < 0) {
			move2 += Vector2D(0.0f, 2.0f);
		}
		input_margin = 0;
	}

	if (std::abs(stick_x2) > stick_sensitivity) {
		// スティックが右に移動した場合
		if (stick_x2 > 0) {
			move2 += Vector2D(2.0f, 0.0f);
			X2 = location2.x;
			angle = DX_PI_F / 28;
		}
		//スティックが左に移動した場合
		else if (stick_x2 < 0) {
			move2 += Vector2D(-2.0f, 0.0f);
			X2 = location2.x;
			angle = -DX_PI_F / 28;
		}
	}
	location2 += move2;




	//十字移動処理
	if (PAD_INPUT::OnPressed2(XINPUT_BUTTON_DPAD_LEFT) || PAD_INPUT::OnPressed2(XINPUT_BUTTON_DPAD_LEFT))
	{
		move2 += Vector2D(-2.0f, 0.0f);
		angle = -DX_PI_F / 28;
	}
	if (PAD_INPUT::OnPressed2(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move2 += Vector2D(2.0f, 0.0f);
		angle = DX_PI_F / 28;
	}
	if (PAD_INPUT::OnPressed2(XINPUT_BUTTON_DPAD_UP))
	{
		move2 += Vector2D(0.0f, -2.0f);
	}
	if (PAD_INPUT::OnPressed2(XINPUT_BUTTON_DPAD_DOWN))
	{
		move2 += Vector2D(0.0f, 2.0f);
	}

	location2 += move2;

	//画面外にいかないように制限する
	if ((location2.x < box_size.x) || (location2.x >= 2000.0f - 280.0f) || (location2.y < box_size.y) || (location2.y >= 480.0f - box_size.y))
	{
		location2-= move2;
	}
}

//加減速処理
void Player2::Acceleration()
{
	//LBボタンが押されたら、減速する
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 2.0f)
	{
		speed -= 2.0f;
	}

	//REボタンが押されたら、加速する
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 20.0f)
	{
		speed += 2.0f;
	}
}