#include"DxLib.h"
#include"InputControl.h"

//katateigi
enum KEY_STATE {
	E_NONE,    //minyuryoku
	E_CLICK,   //ositasyunnkann
	E_PRESS,   //osituduketeru
	E_RELEASED,  //hanasita
	E_KEY_STATE_MAX  //
};

//変数宣言
KEY_STATE button_state1[XINPUT_BUTTON_MAX];  //各ボタン入力状態
KEY_STATE button_state2[XINPUT_BUTTON_MAX];  //各ボタン入力状態

//入力制御機能：初期化処理
//引数　　　　：無し
//戻り値　　　：無し
void InputControl_Initialize(void) {
	int i; //ループカウンタ

	//入力状態の初期化
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++) 
	{
		button_state1[i] = E_NONE;
		button_state2[i] = E_NONE;
	}
}

void InputControl_Update(void)
{
	int i;
	XINPUT_STATE player1_controller;
	XINPUT_STATE player2_controller;

	//GetJoypadInputState(DX_INPUT_PAD1, &player1_controller);
	//GetJoypadInputState(DX_INPUT_PAD2, &player2_controller);

	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		if (player1_controller.Buttons[i] == TRUE)
		{
			switch (button_state1[i])
			{


			case E_NONE:
			case E_RELEASED:
				button_state1[i] = E_CLICK;
				break;

			case E_CLICK:
			case E_PRESS:
				button_state1[i] = E_PRESS;
				break;

			default:
				button_state1[i] = E_NONE;
				break;
			}
		}
		else
		{
			switch (button_state1[i])
			{


			case E_NONE:
			case E_RELEASED:
				button_state1[i] = E_NONE;
				break;

			case E_CLICK:
			case E_PRESS:
				button_state1[i] = E_RELEASED;
				break;

			default:
				button_state1[i] = E_NONE;
				break;
			}

		}
		if (player2_controller.Buttons[i] == TRUE)
		{
			switch (button_state2[i])
			{


			case E_NONE:
			case E_RELEASED:
				button_state2[i] = E_CLICK;
				break;

			case E_CLICK:
			case E_PRESS:
				button_state2[i] = E_PRESS;
				break;

			default:
				button_state2[i] = E_NONE;
				break;
			}
		}
		else
		{
			switch (button_state2[i])
			{


			case E_NONE:
			case E_RELEASED:
				button_state2[i] = E_NONE;
				break;

			case E_CLICK:
			case E_PRESS:
				button_state2[i] = E_RELEASED;
				break;

			default:
				button_state2[i] = E_NONE;
				break;
			}

		}
	}
}
/*********************************
*入力制御機能：押されている判定の処理
*********************************/
int Get_ButtonDown_play1(int button)
{
	int ret = FALSE;
	if (button_state1[button] == E_CLICK)
	{
		ret = TRUE;
	}
	return ret;
}

int Get_ButtonDown_play2(int button)
{
	int ret = FALSE;
	if (button_state2[button] == E_CLICK)
	{
		ret = TRUE;
	}
	return ret;
}
