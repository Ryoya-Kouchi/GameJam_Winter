#pragma once
#include"DxLib.h"

#define BUTTONS 16

//�X�e�B�b�N
struct Stick
{

	short ThumbX;	//�����l
	short ThumbY;	//�c���l
};

class PAD_INPUT
{
private:
	static char NowKey1[BUTTONS]; //����̓��̓L�[
	static char OldKey1[BUTTONS]; //�O��̓��̓L�[
	static XINPUT_STATE Input1; //�p�b�h
	static Stick Rstick1; //�E�X�e�B�b�N
	static Stick Lstick1; //���X�e�B�b�N

	static XINPUT_STATE Input2; //�p�b�h
	static char NowKey2[BUTTONS]; //����̓��̓L�[
	static char OldKey2[BUTTONS]; //�O��̓��̓L�[
	static Stick Rstick2; //�E�X�e�B�b�N
	static Stick Lstick2; //���X�e�B�b�N


private:
	//�R���X�g���N�^
	PAD_INPUT() = default;
public:
	//�p�b�h���̍X�V
	static void UpdateKey()
	{
		// ���̓L�[�擾
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input1);
		GetJoypadXInputState(DX_INPUT_KEY_PAD2, &Input2);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey1[i] = NowKey1[i];
			NowKey1[i] = Input1.Buttons[i];

			OldKey2[i] = NowKey2[i];
			NowKey2[i] = Input2.Buttons[i];

		}

		//�E�X�e�B�b�N
		Rstick1.ThumbX = Input1.ThumbRX;
		Rstick1.ThumbY = Input1.ThumbRY;

		//���X�e�B�b�N
		Lstick1.ThumbX = Input1.ThumbLX;
		Lstick1.ThumbY = Input1.ThumbLY;

		//�E�X�e�B�b�N
		Rstick2.ThumbX = Input2.ThumbRX;
		Rstick2.ThumbY = Input2.ThumbRY;

		//���X�e�B�b�N
		Lstick2.ThumbX = Input2.ThumbLX;
		Lstick2.ThumbY = Input2.ThumbLY;
	}

	//�{�^���������ꂽ�u��
	static bool OnButton1(int button)
	{
		bool ret = (NowKey1[button] == 1 && OldKey1[button] == 0);
		return ret;
	}

	//�{�^���������Ă��
	static bool OnPressed1(int button)
	{
		bool ret = (NowKey1[button] == 1);
		return ret;
	}

	//�{�^���𗣂����u��
	static bool OnRelease1(int button)
	{
		bool ret = (NowKey1[button] == 0 && OldKey1[button] == 1);
		return ret;
	}

	//�{�^���������ꂽ�u��
	static bool OnButton2(int button)
	{
		bool ret = (NowKey2[button] == 1 && OldKey2[button] == 0);
		return ret;
	}

	//�{�^���������Ă��
	static bool OnPressed2(int button)
	{
		bool ret = (NowKey2[button] == 1);
		return ret;
	}

	//�{�^���𗣂����u��
	static bool OnRelease2(int button)
	{
		bool ret = (NowKey2[button] == 0 && OldKey2[button] == 1);
		return ret;
	}

	//�E�X�e�B�b�N�̎擾
	static Stick GetRStick1()
	{
		return Rstick1;
	}

	//���X�e�B�b�N�̎擾
	static Stick GetLStick1()
	{
		return Lstick1;
	}

	static Stick GetRStick2()
	{
		return Rstick2;
	}

	//���X�e�B�b�N�̎擾
	static Stick GetLStick2()
	{
		return Lstick2;
	}

	static char GetNowKey1(const int i)
	{
		return NowKey1[i];
	}

	static char GetOldKey1(const int i)
	{
		return OldKey1[i];
	}

	static char GetNowKey2(const int i)
	{
		return NowKey2[i];
	}
	static char GetOldKey2(const int i)
	{
		return OldKey2[i];
	}
};
