#pragma once
#include"DxLib.h"

#define BUTTONS 16

//スティック
struct Stick
{

	short ThumbX;	//横軸値
	short ThumbY;	//縦軸値
};

class PAD_INPUT
{
private:
	static char NowKey1[BUTTONS]; //今回の入力キー
	static char OldKey1[BUTTONS]; //前回の入力キー
	static XINPUT_STATE Input1; //パッド
	static Stick Rstick1; //右スティック
	static Stick Lstick1; //左スティック

	static XINPUT_STATE Input2; //パッド
	static char NowKey2[BUTTONS]; //今回の入力キー
	static char OldKey2[BUTTONS]; //前回の入力キー
	static Stick Rstick2; //右スティック
	static Stick Lstick2; //左スティック


private:
	//コンストラクタ
	PAD_INPUT() = default;
public:
	//パッド情報の更新
	static void UpdateKey()
	{
		// 入力キー取得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input1);
		GetJoypadXInputState(DX_INPUT_KEY_PAD2, &Input2);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey1[i] = NowKey1[i];
			NowKey1[i] = Input1.Buttons[i];

			OldKey2[i] = NowKey2[i];
			NowKey2[i] = Input2.Buttons[i];

		}

		//右スティック
		Rstick1.ThumbX = Input1.ThumbRX;
		Rstick1.ThumbY = Input1.ThumbRY;

		//左スティック
		Lstick1.ThumbX = Input1.ThumbLX;
		Lstick1.ThumbY = Input1.ThumbLY;

		//右スティック
		Rstick2.ThumbX = Input2.ThumbRX;
		Rstick2.ThumbY = Input2.ThumbRY;

		//左スティック
		Lstick2.ThumbX = Input2.ThumbLX;
		Lstick2.ThumbY = Input2.ThumbLY;
	}

	//ボタンを押された瞬間
	static bool OnButton1(int button)
	{
		bool ret = (NowKey1[button] == 1 && OldKey1[button] == 0);
		return ret;
	}

	//ボタンを押してる間
	static bool OnPressed1(int button)
	{
		bool ret = (NowKey1[button] == 1);
		return ret;
	}

	//ボタンを離した瞬間
	static bool OnRelease1(int button)
	{
		bool ret = (NowKey1[button] == 0 && OldKey1[button] == 1);
		return ret;
	}

	//ボタンを押された瞬間
	static bool OnButton2(int button)
	{
		bool ret = (NowKey2[button] == 1 && OldKey2[button] == 0);
		return ret;
	}

	//ボタンを押してる間
	static bool OnPressed2(int button)
	{
		bool ret = (NowKey2[button] == 1);
		return ret;
	}

	//ボタンを離した瞬間
	static bool OnRelease2(int button)
	{
		bool ret = (NowKey2[button] == 0 && OldKey2[button] == 1);
		return ret;
	}

	//右スティックの取得
	static Stick GetRStick1()
	{
		return Rstick1;
	}

	//左スティックの取得
	static Stick GetLStick1()
	{
		return Lstick1;
	}

	static Stick GetRStick2()
	{
		return Rstick2;
	}

	//左スティックの取得
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
