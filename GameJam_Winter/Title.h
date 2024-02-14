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
	int background_image;			//�w�i�摜
	int menu_image_Start;			//���j���[�摜�X�^�[�g
	int menu_image_Help;            //���j���[�摜�w���v
	int menu_image_End;             //���j���[�摜�G���h
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
