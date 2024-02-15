#include "Help.h"
#include "PadInput.h"
#include "DxLib.h"
#include "Title.h"

HelpScene::HelpScene() :background_image(NULL)
{
//�摜�̓ǂݍ���

	barrier = LoadGraph("Resource/images/barrier.png");
	Health = LoadGraph("Resource/images/Health.bmp");
	Zone = LoadGraph("Resource/images/Zone.bmp");
	
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
	if (PAD_INPUT::GetNowKey1(XINPUT_BUTTON_B) && (PAD_INPUT::OnButton1(XINPUT_BUTTON_B) == true))
	{
		return new TitleScene();
	}

	return this;
}

//�`�揈��
void HelpScene::Draw() const
{
	

	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(30);
	
	DrawString(20, 70, "��������", GetColor(255, 0, 0), 0xffffff);
	DrawString(20, 110, "��ɃS�[�����邩����̔R����\n�[���ɂ��邱�ƁI�I", 0xffffff, 0);
	
	DrawString(20, 200, "������@",GetColor(128, 128, 128), 0xffffff);
	DrawString(20, 240, "�\���L�[�܂���\n���X�e�B�b�N�ňړ��I", 0xffffff, 0);

	//Barrier�̐���
	DrawRotaGraph(710, 90, 0.9, size, barrier, TRUE);

	DrawString(650, 200, "�o���A", GetColor(30, 144, 255), 0xffffff);
	DrawString(590, 240, "��x�����Ռ�����\n��邱�Ƃ��ł���I", 0xffffff, 0);

	//Health�̐���
	DrawRotaGraph(950, 90, 1.5,size, Health, TRUE);

	DrawString(930, 200, "��", GetColor(0, 250, 154), 0xffffff);
	DrawString(900, 240, "�R����\n�񕜂�����I", 0xffffff, 0);

	//Zone�̐���
	DrawRotaGraph(1150, 90, 1.5, size, Zone, TRUE);

	DrawString(1130, 200, "����", GetColor(135, 206, 250), 0xffffff);
	DrawString(1100, 240, "���x��\n�オ���I", 0xffffff, 0);

	//�~�b�V�����̐���
	DrawString(20, 350, "/******�~�b�V����************************/", GetColor(0, 255, 0), 0xffffff);
	DrawString(20, 390, "____________________________", 0xffffff, 0);

	

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
			DrawString(390, 610, "B�{�^���������ă^�C�g���ɖ߂�", 0xffffff, 0);
		}
		
	}
	if (Button == 0) 
	{
		//B�{�^���Ń^�C�g���ɖ߂����
		SetFontSize(30);
		DrawString(390, 610, "B�{�^���������ă^�C�g���ɖ߂�", 0xffffff, 0);
	}

	//�q���g
	SetFontSize(10);
	DrawString(1090, 700, "�X�e�B�b�N�̂ق����L������A�A",GetColor(192,192,192), 0xffffff);
}

