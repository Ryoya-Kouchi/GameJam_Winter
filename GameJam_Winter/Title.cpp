#include "Title.h"
#include "PadInput.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), menu_image(NULL), cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}


//����������
void TitleScene::Initialize()
{
	//�摜�ǂݍ���
	background_image = LoadGraph("Resource/images/Title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
}

		if (std::abs(stick_y1) > stick_sensitivity || std::abs(stick_y2) > stick_sensitivity) {
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_y1 > 0 || stick_y2 > 0 ) {
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
		switch (menu_cursor)
		{
		case 0:
			return eAbstractSceneType::E_MAIN;
		case 1:
			return eAbstractSceneType::E_RANKING_DISP;
		case 2:
			return eAbstractSceneType::E_HELP;
		default:
			return eAbstractSceneType::E_END;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//���j���[�摜�̕`��
	DrawGraph(120, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//���݂̃V�[�������擾
eAbstractSceneType TitleScene::GetNowScene() const
{
	return eAbstractSceneType::E_TITLE;
}
