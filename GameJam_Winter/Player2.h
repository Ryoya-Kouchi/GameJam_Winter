#pragma once
#pragma once

#include "Vector2D.h"
#include "Barrier.h"
#include"PadInput.h"

class Player2
{
private:
	bool is_active;			//�L����Ԃ��H
	int image;
	Vector2D location2;//�摜�f�[�^
	Vector2D box_size;		//�����蔻��傫��
	float angle;			//�p�x
	float speed;			//����
	float hp;				//�̗�
	float fuel;				//�R��
	int barrier_count;		//�o���A�̖���
	Barrier* barrier;		//�o���A
	
	int player2;
	int input_margin;
	int stick_y2;
	int stick_x2;
public:
	Player2();
	~Player2();

	void Initialize();		//����������
	void Update();			//�X�V����
	void Draw();			//�`�揈��
	void Finalize();		//�I��������

public:
	static float X2;
	static float Y2;
	//static float Vector2D::x;
	void SetActive(bool flg);		//�L���t���O�ݒ�
	void DecreaseHp(float value);	//�̗͌�������
	Vector2D GetLocation() const;	//�ʒu���W�擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫���擾
	float GetSpeed() const;			//�����擾����
	float GetFuel() const;			//�R���擾
	float GetHp() const;			//�̗͎擾
	int GetBarriarCount() const;	//�o���A�̖����擾
	bool IsBarrier() const;			//�o���A�L�����H���擾

private:
	void Movement();				//�ړ�����
	void Acceleration();			//��������

};