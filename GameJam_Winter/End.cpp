#include "End.h"
#include "PadInput.h"
#include "DxLib.h"
#include "Title.h"

EndScene::EndScene() :background_image(NULL)
{
	

}

EndScene::~EndScene()
{

}

//�X�V����
AbstractScene* EndScene::Update()
{
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) == true))
	{
		StopSoundFile();
		return nullptr;
		
	}

	

	return this;
}
//�`�揈��
void EndScene::Draw() const
{
	//End���
	SetFontSize(30);

	DrawString(20, 70, "�����", GetColor(255, 0, 0), 0xffffff);
	DrawString(20, 110, "�A�J�~�l�T���@��傤��@�������[�@��������", 0xffffff, 0);

	DrawString(20, 200, "BGM���p��", GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 240, "�������l�@https://maou.audio/bgm_neorock76/", 0xffffff, 0);

	DrawString(20, 330, "SE���p��", GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 370, "���ʉ����{�l�@https://soundeffect-lab.info/sound/button/", 0xffffff, 0);

	// �_�ŏ����p�̕ϐ�
	static int BrinkCounter;

	// �_�ŗp�̕ϐ��� 1 �𑫂�
	BrinkCounter++;

	// �_�ŗp�̕ϐ��� 60 �ɂȂ��Ă����� 0 �ɂ���
	if (BrinkCounter == 60)
	{
		BrinkCounter = 0;
	}

	// �_�ŗp�̕ϐ��̒l�� 30���傫���Ƃ�����B�{�^���������ă^�C�g���ɖ߂��`�悷��
	if (BrinkCounter > 30)
	{
		if (Button != 0)
		{
			//B�{�^���Ń^�C�g���ɖ߂����
			SetFontSize(30);
			DrawString(390, 610, "B�{�^���������ďI��", 0xffffff, 0);
		}

	}
	if (Button == 0)
	{
		//B�{�^���Ń^�C�g���ɖ߂����
		SetFontSize(30);
		DrawString(390, 610, "B�{�^���������ďI��", 0xffffff, 0);
	}
}