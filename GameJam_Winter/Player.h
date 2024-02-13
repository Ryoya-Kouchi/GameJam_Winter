#pragma once

#include"Vector.h"
class Player 
{
private:
	bool is_active;			//�L����Ԃ��H
	int image;				//�摜�f�[�^
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��傫��
	float angle;			//�p�x
	float speed;			//����
	float hp;				//�̗�
	float fuel;				//�R��
	int barrier_count;		//�o���A�̖���
	//Barrier* barrier;		//�o���A

	void Movement();				//�ړ�����
	void Acceleration();			//��������
public:
	Player();
	~Player();
	void Update();     //
	void Draw()const;  //�`��

	void Initialize();		//����������
	void Finalize();		//�I��������

	void SetActive(bool flg);		//�L���t���O�ݒ�
	void DecreaseHp(float value);	//�̗͌�������
	Vector2D GetLocation() const;	//�ʒu���W�擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫���擾
	float GetSpeed() const;			//�����擾����
	float GetFuel() const;			//�R���擾
	float GetHp() const;			//�̗͎擾
	int GetBarriarCount() const;	//�o���A�̖����擾
	bool IsBarrier() const;			//�o���A�L�����H���擾


};