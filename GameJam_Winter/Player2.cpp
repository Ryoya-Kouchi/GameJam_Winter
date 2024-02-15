#include "Player2.h"
#include "PadInput.h"
#include "Dxlib.h"
#include<iostream>

float Player2::X2;	//player2�̂����W

//float Vector2D::x;
Player2::Player2():is_active(false), image(NULL), /*location2(0.0f)*/  box_size(0.0f),
angle(0.0f), speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr)
{
	//�摜�Ǎ�
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

//����������
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
//	//�摜�ǂݍ���
//	//image = LoadGraph("Resource/images/ca.bmp");
//
//	Player2 = LoadGraph("Resource/images/Player2.bmp");
//
//	//�G���[�`�F�b�N
//	if (Player2 == -2)
//	{
//		throw("Resource/image/car2pol.bmp������܂���\n");
//	}
//}

//�X�V����
void Player2::Update()
{
	int x2;
	//����s�\��Ԃł���΁A���g����]������
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;

		if (angle >= DX_PI_F * 4.0f)
		{
			//�E���瓖�������ꍇ
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
			//�����瓖�������ꍇ
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
	//�R���̏���
	fuel -= speed;

	//�ړ�����
	Movement();

	X2 = location2.x;


	//����������
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

	//�o���A����
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_B) && barrier_count > 0)
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
void Player2::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraph(location2.x, location2.y, 1.5, angle, player2, TRUE);

	////�o���A����������Ă�����A�`����s��
	//if (barrier != nullptr)
	//{
	//	barrier->Draw(this->location);
	//}
}

//�I��������
void Player2::Finalize()
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
void Player2::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player2::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player2::GetLocation()const
{
	return this->location2;
}

//�����蔻��̑傫���擾����
Vector2D Player2::GetBoxSize()const
{
	return this->box_size;
}

//�����擾����
float Player2::GetSpeed()const
{
	return this->speed;
}

//�R���擾����
float Player2::GetFuel()const
{
	return this->fuel;
}

//�̗͎擾����
float Player2::GetHp()const
{
	return this->hp;
}

//�o���A�����擾����
int Player2::GetBarriarCount()const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player2::IsBarrier()const
{
	return(barrier != nullptr);
}

//�ړ�����
void Player2::Movement()
{
	Vector2D move2 = Vector2D(0.0f);
	angle = 0.0f;


	// ����Ԋu����
	const int max_input_margin = 20;
	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	int stick_y2 = PAD_INPUT::GetLStick2().ThumbY;
	int stick_x2 = PAD_INPUT::GetLStick2().ThumbX;

	if (std::abs(stick_y2) > stick_sensitivity) {
		// �X�e�B�b�N����Ɉړ������ꍇ
		if (stick_y2 > 0) {
			move2 += Vector2D(0.0f, -2.0f);
		}
		//�X�e�B�b�N�����Ɉړ������ꍇ
		else if (stick_y2 < 0) {
			move2 += Vector2D(0.0f, 2.0f);
		}
		input_margin = 0;
	}

	if (std::abs(stick_x2) > stick_sensitivity) {
		// �X�e�B�b�N���E�Ɉړ������ꍇ
		if (stick_x2 > 0) {
			move2 += Vector2D(2.0f, 0.0f);
			X2 = location2.x;
			angle = DX_PI_F / 28;
		}
		//�X�e�B�b�N�����Ɉړ������ꍇ
		else if (stick_x2 < 0) {
			move2 += Vector2D(-2.0f, 0.0f);
			X2 = location2.x;
			angle = -DX_PI_F / 28;
		}
	}
	location2 += move2;




	//�\���ړ�����
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

	//��ʊO�ɂ����Ȃ��悤�ɐ�������
	if ((location2.x < box_size.x) || (location2.x >= 2000.0f - 280.0f) || (location2.y < box_size.y) || (location2.y >= 480.0f - box_size.y))
	{
		location2-= move2;
	}
}

//����������
void Player2::Acceleration()
{
	//LB�{�^���������ꂽ��A��������
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 2.0f)
	{
		speed -= 2.0f;
	}

	//RE�{�^���������ꂽ��A��������
	if (PAD_INPUT::OnButton2(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 20.0f)
	{
		speed += 2.0f;
	}
}