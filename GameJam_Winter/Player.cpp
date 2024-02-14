#include "Player.h"
#include "PadInput.h"
#include "Dxlib.h"
#include<iostream>
#include"Player2.h"
Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{
	//�摜�Ǎ�
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

//����������
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
//	//�摜�ǂݍ���
//	//image = LoadGraph("Resource/images/ca.bmp");
//
//	Player1 = LoadGraph("Resource/images/Player1.bmp");
//
//	//�G���[�`�F�b�N
//	if (Player1 == -1)
//	{
//		throw("Resource/image/car1pol.bmp������܂���\n");
//	}
//}

//�X�V����
void Player::Update()
{
	Hit();
	//����s�\��Ԃł���΁A���g����]������
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

	//�R���̏���
	fuel -= speed;

	//�ړ�����
	Movement();

	//����������
	Acceleration();

	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//�o���A����
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraph(location.x, location.y, 1.5, angle, Player1, TRUE);
	//��
	DrawLine(location.x - 30, location.y + 80, location.x -30, location.y - 30,GetColor(0, 255, 0), FALSE);
	//�E
	DrawLine(location.x + 30, location.y + 80, location.x + 30, location.y - 30, GetColor(0, 255, 0), FALSE);

	DrawFormatString(100, 100, GetColor(255, 0, 0), "flg:%d", flg);
	////�o���A����������Ă�����A�`����s��
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}
}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation()const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed()const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel()const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp()const
{
	return this->hp;
}

//�o���A�����擾����
int Player::GetBarriarCount()const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier()const
{
	return(barrier != nullptr);
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;


	// ����Ԋu����
	const int max_input_margin = 10;
	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	int stick_y1 = PAD_INPUT::GetLStick1().ThumbY;
	int stick_x1 = PAD_INPUT::GetLStick1().ThumbX;
	
		if (std::abs(stick_y1) > stick_sensitivity ) {
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_y1 > 0) {
				move += Vector2D(0.0f, -1.0f);
			}
			//�X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_y1 < 0 ) {
				move += Vector2D(0.0f, 1.0f);
			}
			input_margin = 0;
		}
	
		if (std::abs(stick_x1) > stick_sensitivity) {
			// �X�e�B�b�N���E�Ɉړ������ꍇ
			if (stick_x1 > 0) {
				move += Vector2D(1.0f, 0.0f);
				angle = DX_PI_F / 18;
			}
			//�X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x1 < 0 ) {
				move += Vector2D(-1.0f, 0.0f);
				angle = -DX_PI_F / 18;
			}
	}
	location += move;


	

	//�\���ړ�����
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

	//��ʊO�ɂ����Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 1000.0f - 180.0f) || (location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//RE�{�^���������ꂽ��A��������
	if (PAD_INPUT::OnButton1(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}
void Player::Hit()
{
	//����
	int playerX1 = location.x - 30;
	//�E��
	int playerX2 = location.x + 30;
	//�㕝
	int playerY1 = location.y + 80;
	//����
	int playerY2 = location.y - 80;

	//�v���C���[�Q
	//����
	int player2X1 = Player2::X2 - 30;
	//�E��
	int player2X2 = Player2::X2 + 30;
	//�㕝
	int player2Y1 = Player2::Y2 + 80;
	//����
	int player2Y2 = Player2::Y2 - 80;

	if (playerX1 == player2X2  && playerY1 == player2Y1 && playerY2 == player2Y2 ||  //��
		playerX2 == player2X1 &&  playerY1 == player2Y1 && playerY2 == player2Y2)    //�E
	{
		flg = 1;
	}
}