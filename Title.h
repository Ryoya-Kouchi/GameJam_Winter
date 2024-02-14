#pragma once

#include "AbstractScene.h"

enum class TITLE_MENU
{
	GAME_START,
	GAME_HELP,
	GAME_END,
	TITLE_SIZE
};

class TitleScene :public AbstractScene
{
private:

private:
	/*const char* menu_items[static_cast<int>(TITLE_MENU::TITLE_SIZE)] = {
   "�����[��",
   "�w���v",
   "�����"
	};*/
	int background_image;			//�w�i�摜
	int now_menu;                   //���ݑI�����Ă郁�j���[
	int MenuFont;                   //���j���[�p�̃t�H���g
	int input_margin;               //���쎞�ԊԊu

public:
	TitleScene();
	~TitleScene();
	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};
