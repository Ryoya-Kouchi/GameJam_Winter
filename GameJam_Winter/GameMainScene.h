#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "Item.h"
#include"Player2.h"
#include"Enemy.h"

class GameMainScene :public AbstractScene
{
private:
	int back_ground;			//�w�i�摜
	int barrier_image;			//�o���A�摜
	int mileage;				//���s����
	int mileage2;
	int enemy_image[3];			//�G�摜
	int enemy_count[3];			//�ʂ�߂����G�J�E���g
	Player* player;				//�v���C���[
	Player2* player2;
	Item* item;
	Enemy** enemy;				//�G

public:
	GameMainScene();
	virtual ~GameMainScene();

	//virtual void Initialize() override;
	virtual AbstractScene* Update() override;
	virtual void Draw() const override;
	//virtual void Finalize() override;

	//virtual eAbstractSceneType GetNowScene() const override;

private:
	////�n�C�X�R�A�ǂݍ��ݏ���
	//void ReadHighScore();
	//�����蔻��
	bool IsHitCheck(Player* p, Player2* p2);


};