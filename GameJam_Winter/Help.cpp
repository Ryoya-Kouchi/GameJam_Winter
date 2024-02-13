#include "Help.h"
#include "PadInput.h"
#include "DxLib.h"

HelpScene::HelpScene() :background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

////����������
//void HelpScene::Initialize()
//{
//	//�摜�ǂݍ���
//	background_image = LoadGraph("Resource/images/Title.bmp");
//
//	//�G���[�`�F�b�N
//	if (background_image == -1)
//	{
//		throw("Resource/images/Title.bmp������܂���\n");
//	}
//}

//�X�V����
AbstractScene* HelpScene::Update()
{
	return this;
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 180, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 200, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 220, "���񓖂���ƃQ�[���I�[�o�[�ł��B", 0xffffff, 0);

	DrawString(150, 450, "----�@B�{�^���������ă^�C�g���ɖ߂�@----", 0xffffff, 0);

}

