#include "Title.h"
#include "PadInput.h"
#include"DxLib.h"
#include<iostream>
#include"Help.h"
#include"GameMainScene.h"

#define SCREEN_WIDTH 1280

TitleScene::TitleScene()
{
	//MenuFont = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 32, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 3);
	//�摜�ǂݍ���
    background_image = LoadGraph("Resource/images/Title.png");
	menu_image_Start = LoadGraph("Resource/images/start_m.bmp");
	menu_image_Help  = LoadGraph("Resource/images/help_m.bmp");
	menu_image_End   = LoadGraph("Resource/images/end_m.bmp");
	//	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.png������܂���\n");
	}
	now_menu = static_cast<int>(TITLE_MENU::GAME_START);
	input_margin = 0;
	//�^�C�g���J�ڎ��^�C�g���pBGM�����[�v�ŗ���
	PlaySoundFile("Resource/BGM/maou_bgm_neorock76.mp3", DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{

}

AbstractScene* TitleScene::Update()
{	// ����Ԋu����
	const int max_input_margin = 15;
	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin) {
		input_margin++;
	}
	else {
		// �X�e�B�b�N��Y���W���擾
		int stick_y1 = PAD_INPUT::GetLStick1().ThumbY;
		int stick_y2 = PAD_INPUT::GetLStick2().ThumbY;

		if (std::abs(stick_y1) > stick_sensitivity || std::abs(stick_y2) > stick_sensitivity) {
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_y1 > 0 || stick_y2 > 0) {
				// ���j���[�I��������O�Ɉړ�
				now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			//�X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_y1 < 0 || stick_y2 < 0) {
				// ���j���[�I����������Ɉړ�
				now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
			}
			input_margin = 0;
		}
	}
	// �\���L�[��Ɉړ������ꍇ
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_DPAD_UP) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_DPAD_UP) == true)) {
		// ���j���[�I��������O�Ɉړ�
		now_menu = (now_menu - 1 + static_cast<int>(TITLE_MENU::TITLE_SIZE)) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
	}
	//�\���L�[���Ɉړ������ꍇ
	else if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_DPAD_DOWN) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_DPAD_DOWN) == true)) {
		// ���j���[�I����������Ɉړ�
		now_menu = (now_menu + 1) % static_cast<int>(TITLE_MENU::TITLE_SIZE);
	}

	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_A) == true))
	{
		input_margin = 0;
		TITLE_MENU current_select = static_cast<TITLE_MENU>(now_menu);
		switch (current_select)
		{
		case TITLE_MENU::GAME_START:
			return new GameMainScene();
			break;
		case TITLE_MENU::GAME_HELP:
			return new HelpScene();
			break;
		case TITLE_MENU::GAME_END:
			return nullptr;
			break;
		default:
			printfDx("�������ȋ@�\�ł��B\n");
			break;
		}
	}

	return this;

}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, TRUE);

	// �_�ŏ����p�̕ϐ�
	static int BrinkCounter;

	// �_�ŗp�̕ϐ��� 1 �𑫂�
	BrinkCounter++;

	// �_�ŗp�̕ϐ��� 60 �ɂȂ��Ă����� 0 �ɂ���
	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", BrinkCounter);

	for (int i = 0; i < static_cast<int>(TITLE_MENU::TITLE_SIZE); i++)
	{
		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (now_menu == i) {
			// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ�����START,HELP,END��`�悷��
			if (BrinkCounter < 30)
			{
				if (now_menu == 0) {
					SetFontSize(90);
					DrawString(100, 250, "    START  ", GetColor(255, 255, 255));
				}
				if (now_menu == 1) {
					SetFontSize(90);
					DrawString(100, 400, "    HELP   ", GetColor(255, 255, 255));
				}
				if (now_menu == 2) {
					SetFontSize(90);
					DrawString(100, 550, "    END    ", GetColor(255, 255, 255));
				}
			}
				if (now_menu != 0) {
					SetFontSize(90);
					DrawString(100, 250, "    START  ", GetColor(255, 255, 255));
				}
				if (now_menu != 1) {
					SetFontSize(90);
					DrawString(100, 400, "    HELP   ", GetColor(255, 255, 255));
				}
				if (now_menu  != 2) {
					SetFontSize(90);
					DrawString(100, 550, "    END    ", GetColor(255, 255, 255));
				}
		}
	}
}