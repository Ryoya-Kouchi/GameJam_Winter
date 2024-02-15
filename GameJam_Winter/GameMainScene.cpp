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
		//�摜�̓ǂݍ���
	back_ground = LoadGraph("Resource/images/back2.png");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/barrier.png������܂���\n");
	}

	//�Q�[�����C���J�ڎ��Q�[�����C���pBGM�����[�v�ŗ���
	PlaySoundFile("Resource/BGM/maou_bgm_neorock70.mp3", DX_PLAYTYPE_LOOP);

	//�I�u�W�F�N�g�̏�����
	//player->Initialize();

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
	//�S�[���܂ł̋����̌���
	gaoldistance -= 1;
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
		static int BrinkCounter;
		BrinkCounter++;
		player->SetActive(false);
		player->DecreaseHp(-50.0f);
		player2->DecreaseHp(-50.0f);
		player2->SetActive(false);
		if (BrinkCounter < 30) {

		}
	}

	//�v���C���[�̔R�����̗͂��O�����Ȃ�A���U���g�ɑJ�ڂ���
	if (player->GetHp() < 0 &&  1050 >=fxe + (player->GetHp() * 100 / 10000) || gaoldistance <= 0)
	{
		// �Q�[�����C��BGM���~�߂�
		StopSoundFile();
		return new TitleScene();
	}

			return this;
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 720 - 720, back_ground, TRUE);
	DrawGraph(0, mileage % 720, back_ground, TRUE);

	//�v���C���[�̕`��
	player->Draw();
	
	//�v���C���[�Q�̕`��
	player2->Draw();


	//UI�̕`��
	DrawBox(1000, 0, 1280, 720, GetColor(0, 153, 0), TRUE);
	SetFontSize(38);
	
	DrawFormatString(1000, 10, GetColor(0, 0, 0), "�S�[���܂ł���");
	DrawFormatString(1000, 60, GetColor(0, 0, 0), "%d", gaoldistance);
	
	SetFontSize(30);
	//�R���E�̗̓Q�[�W�̕`��
	float fx = 1050.0f;
	float fy = 350.0f;

	float fxe = 1150.0f;
	float fye = 380.0f;
	
	fx = 1050.0f;
	fy = 450.0f;
	DrawFormatStringF(1050, 370, GetColor(0, 0, 0), "PLAYER1 HP");
	DrawBoxAA(fx, fy + 20.0f, fxe + (player->GetHp() * 100 / 10000), fye + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fxe + 100.0f, fye + 40.0f, GetColor(0, 0, 0), FALSE);

	//�R���E�̗̓Q�[�W�̕`��
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
//
