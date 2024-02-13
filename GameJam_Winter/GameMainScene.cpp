#include "GameMainScene.h"
#include "DxLib.h"
#include <math.h>

GameMainScene::GameMainScene() : back_ground(NULL),
barrier_image(NULL), mileage(0), player(nullptr)
{
	
}

GameMainScene::~GameMainScene()
{

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
	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	

	

			//�����蔻��̊m�F
			if (IsHitCheck(player))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				
			}
			return this;
}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	

	////�v���C���[�̕`��
	//player->Draw();

	////UI�̕`��
	//DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	//SetFontSize(16);
	//
	//DrawFormatString(510, 200, GetColor(0, 0, 0), "���s����");
	//DrawFormatString(555, 220, GetColor(255, 255, 255), "%08d", mileage / 10);
	//DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	//DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f", player->GetSpeed());

	//

	////�R���Q�[�W�̕`��
	//float fx = 510.0f;
	//float fy = 390.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	////�̗̓Q�[�W�̕`��
	//fx = 510.0f;
	//fy = 430.0f;
	//DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	//DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f, GetColor(255, 0, 0), TRUE);
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0), FALSE);
}

//�I��������
//���݃V�[�������擾



//�����蔻�菈��(�v���C���[�ƓG)
bool GameMainScene::IsHitCheck(Player* p)
{
	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	

	//�ʒu���̍������擾
	//Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	//Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�q���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	//return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

