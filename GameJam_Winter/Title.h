#pragma once
#include"AbstractScene.h"

enum class TITLE_MENU
{
	GAME_START,
	GAME_END,
	TITLE_SIZE
};
class Title :public AbstractScene
{
private:
	const char* menu_items[static_cast<int>(TITLE_MENU::TITLE_SIZE)] = {
   "�����[��",
   "�����"
	};
	int now_menu; //���ݑI�����Ă郁�j���[
	int MenuFont; //���j���[�p�̃t�H���g
	int input_margin;  //���쎞�ԊԊu

public:
	//�R���X�g���N�^
	Title();

	//�f�X�g���N�^
	virtual ~Title();

	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update()override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;
};
