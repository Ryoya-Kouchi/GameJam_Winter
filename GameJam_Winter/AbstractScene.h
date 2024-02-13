#pragma once

//SceneBase.h�̑���

//�V�[�����
enum eAbstractSceneType
{
	E_TITLE,
	E_MAIN,
	E_HELP,
	E_RANKING_DISP,
	E_RANKING_INPUT,
	E_RESULT,
	E_END
};

// �f�t�H���g�̒��ۃV�[���N���X
// ���[�U�[�͂�����p�����ăV�[������������Ɗy
class AbstractScene {
public:
	AbstractScene() {}
    // �f�X�g���N�^
    virtual ~AbstractScene() {}

    // �X�V��������������
	virtual eAbstractSceneType Update()
	{
		return GetNowScene();
	}

    // �`�揈������������
    virtual void Draw() const {}

	//�I��������
	virtual void Finalize() {}

	//���݃V�[�������擾
	virtual eAbstractSceneType GetNowScene() const = 0;
};
