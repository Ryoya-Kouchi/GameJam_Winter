#include"SceneManager.h"
#include"PadInput.h"
#include"DxLib.h"
#include"Title.h"
#include"GameMainScene.h"
#include"Result.h"
#include"Help.h"

SceneManager::SceneManager() :current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

//�V�[���}�l�[�W���[�@�\�F����������
void SceneManager::Initialize()
{
	//�E�B���h�E�̃^�C�g����ݒ�
	SetMainWindowText("Drive&Avoid");

	//�E�B���h�E���[�h�ŋN��
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������ł��܂���ł���\n");
	}

	//�`���w�菈��
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�`���̎w�肪�ł��܂���ł���\n");
	}

	//�^�C�g���V�[������n�߂�
	ChangeScene(eAbstractSceneType::E_TITLE);
}

//�V�[���}�l�[�W���[�@�\�F�X�V����
void SceneManager::Update()
{
	//�t���[���J�n���ԁi�}�C�N���b�j���擾
	LONGLONG start_time = GetNowHiPerformanceCount();

	//���C�����[�v
	while (ProcessMessage() != -1)
	{
		//���ݎ��Ԃ��擾
		LONGLONG now_time = GetNowHiPerformanceCount();

		//1�t���[��������̎��Ԃɓ��B������A�X�V����ѕ`�揈�����s��
		if ((now_time - start_time) >= DELTA_SECOND)
		{

			//1�t���[��������̎��Ԃ��X�V����
			start_time = now_time;

			//���͋@�\�F�X�V����
			InputControl::Update();

			//�X�V����(�߂�l�͎��̃V�[�����)
			eAbstractSceneType next = current_scene->Update();

			//�`�揈��
			Draw();

			//�G���h���I������Ă�����A�Q�[�����I������
			if (next == eAbstractSceneType::E_END)
			{
				break;
			}
			//���݂̃V�[���Ǝ��̃V�[��������Ă�����A�؂�ւ��������s��
			if (next != current_scene->GetNowScene())
			{
				ChangeScene(next);
			}
		}
		//ESCAPE�L�[�������ꂽ��A�Q�[�����I������
		if (CheckHitKey(KEY_INPUT_ESCAPE) || InputControl::GetButtonUp(XINPUT_BUTTON_BACK))
		{
			break;
		}

	}

}
//�V�[���}�l�[�W���[�@�\�F�I��������
void SceneManager::Finalize()
{
	//�V�[�����̍폜
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//DX���C�u�����̎g�p���I������
	DxLib_End();
}

//�V�[���}�l�[�W���[�@�\�F�`�揈��
void SceneManager::Draw() const
{
	//��ʂ̏�����
	ClearDrawScreen();

	//�V�[���̕`��
	current_scene->Draw();

	//����ʂ̓��e��\��ʂɔ��f
	ScreenFlip();
}

//�V�[���؂�ւ�����
void SceneManager::ChangeScene(eAbstractSceneType scene_type)
{
	//�V�[���𐶐�����iAbstractScene���p������Ă��邩�H�j
	AbstractScene* new_scene = dynamic_cast<AbstractScene*>(CreateScene(scene_type));


	//�G���[�`�F�b�N
	if (new_scene == nullptr)
	{
		throw("�V�[���������ł��܂���ł����B\n");
	}

	//�O��V�[���̏I�����������s��
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//�V�������������V�[���̏��������s��
	new_scene->Initialize();

	//���݃V�[���̍X�V
	current_scene = new_scene;
}

//�V�[����������
AbstractScene* SceneManager::CreateScene(eAbstractSceneType scene_type)
{
	//�����i�V�[���^�C�v�j�ɂ���āA��������V�[�������肷��
	switch (scene_type)
	{
	case eAbstractSceneType::E_TITLE:
		return new TitleScene;
	case eAbstractSceneType::E_MAIN:
		return new GameMainScene;
	case eAbstractSceneType::E_HELP:
		return new HelpScene;
	
	default:
		return nullptr;
	}
}
