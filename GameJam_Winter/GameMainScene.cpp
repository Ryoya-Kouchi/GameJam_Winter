#include "GameMainScene.h"
#include "DxLib.h"
#include <math.h>
#include"Player.h"
#include"Player2.h"6
#include "Item.h"

GameMainScene::GameMainScene() : back_ground(NULL),
barrier_image(NULL), mileage(0),mileage2(0)/*player(nullptr)*/,enemy(nullptr)
{
	goaldistance = 200;
	player = new Player();
	player2 = new Player2();
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back2.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/item2.bmp", 3, 3, 1, 63, 100, enemy_image);

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}
	


	//�I�u�W�F�N�g�̏�����
	//player->Initialize();
	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

}

GameMainScene::~GameMainScene()
{
	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

}

//����������
//void GameMainScene::Initialize()
//{
//	
//
//	//�摜�̓ǂݍ���
//	back_ground = LoadGraph("Resource/images/back.bmp");
//	
//
//	//�G���[�`�F�b�N
//	if (back_ground == -1)
//	{
//		throw("Resource/images/back.bmp������܂���\n");
//	}
//
//	
//
//	//�I�u�W�F�N�g����
//	player = new Player;
//	
//
//	//�I�u�W�F�N�g�̏�����
//	player->Initialize();
//
//	
//}

//�X�V����
AbstractScene* GameMainScene::Update()
{
	goaldistance -= 1;
	//�v���C���[�̍X�V
	player->Update();
	player2->Update();
	//�ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;
	//�ړ������̍X�V
	mileage2 += (int)player2->GetSpeed() + 5;

	//�����蔻��̊m�F
	if (IsHitCheck(player, player2))
	{
		player->SetActive(false);
		player->DecreaseHp(-50.0f);
		player2->DecreaseHp(-50.0f);
		player2->SetActive(false);
	}

	//�A�C�e����������
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

	//�A�C�e���̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			//��ʊO�ɍs������A�A�C�e�����폜���ăX�R�A���Z
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
			
			//�����蔻��̊m�F
			if (HitItemCheck(player, enemy[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}

			return this;
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//�A�C�e���̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}


	//�v���C���[�̕`��
	player->Draw();
	
	//�v���C���[�Q�̕`��
	player2->Draw();


	//UI�̕`��
	DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	SetFontSize(38);
	
	DrawFormatString(1000, 10, GetColor(0, 0, 0), "�S�[���܂ł���");
	DrawFormatString(1000, 60, GetColor(0, 0, 0), "%d", goaldistance);
	//DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	//DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());
	
	

	////�R���Q�[�W�̕`��
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	
	////�̗̓Q�[�W�̕`��
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

//�I��������
//���݃V�[�������擾

bool GameMainScene::IsHitCheck(Player* p, Player2* p2)
{
	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (p2 == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - p2->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + p2->GetBoxSize();

	//�q���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));

}

//�����蔻�菈��(�v���C���[�ƃA�C�e��)
bool GameMainScene::HitItemCheck(Player* p, Enemy* e)
{
	//�v���C���[��񂪖�����Ζ�������
	if (e == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}


////�����蔻�菈��(�v���C���[�ƓG)
//bool GameMainScene::IsHitCheck(Player* p)
//{
//	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
//	if (p->IsBarrier())
//	{
//		return false;
//	}
//
//	
//
//	//�ʒu���̍������擾
//	//Vector2D diff_location = p->GetLocation() - e->GetLocation();
//
//	//�����蔻��T�C�Y�̑傫�����擾
//	//Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
//
//	//�q���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
//	//return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
//}

