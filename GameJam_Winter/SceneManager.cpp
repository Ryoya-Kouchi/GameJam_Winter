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

//シーンマネージャー機能：初期化処理
void SceneManager::Initialize()
{
	//ウィンドウのタイトルを設定
	SetMainWindowText("Drive&Avoid");

	//ウィンドウモードで起動
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("ウィンドウモードで起動できませんでした\n");
	}

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		throw("Dxライブラリが初期化できませんでした\n");
	}

	//描画先指定処理
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("描画先の指定ができませんでした\n");
	}

	//タイトルシーンから始める
	ChangeScene(eAbstractSceneType::E_TITLE);
}

//シーンマネージャー機能：更新処理
void SceneManager::Update()
{
	//フレーム開始時間（マイクロ秒）を取得
	LONGLONG start_time = GetNowHiPerformanceCount();

	//メインループ
	while (ProcessMessage() != -1)
	{
		//現在時間を取得
		LONGLONG now_time = GetNowHiPerformanceCount();

		//1フレーム当たりの時間に到達したら、更新および描画処理を行う
		if ((now_time - start_time) >= DELTA_SECOND)
		{

			//1フレーム当たりの時間を更新する
			start_time = now_time;

			//入力機能：更新処理
			InputControl::Update();

			//更新処理(戻り値は次のシーン情報)
			eAbstractSceneType next = current_scene->Update();

			//描画処理
			Draw();

			//エンドが選択されていたら、ゲームを終了する
			if (next == eAbstractSceneType::E_END)
			{
				break;
			}
			//現在のシーンと次のシーンが違っていたら、切り替え処理を行う
			if (next != current_scene->GetNowScene())
			{
				ChangeScene(next);
			}
		}
		//ESCAPEキーが押されたら、ゲームを終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE) || InputControl::GetButtonUp(XINPUT_BUTTON_BACK))
		{
			break;
		}

	}

}
//シーンマネージャー機能：終了時処理
void SceneManager::Finalize()
{
	//シーン情報の削除
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//DXライブラリの使用を終了する
	DxLib_End();
}

//シーンマネージャー機能：描画処理
void SceneManager::Draw() const
{
	//画面の初期化
	ClearDrawScreen();

	//シーンの描画
	current_scene->Draw();

	//裏画面の内容を表画面に反映
	ScreenFlip();
}

//シーン切り替え処理
void SceneManager::ChangeScene(eAbstractSceneType scene_type)
{
	//シーンを生成する（AbstractSceneが継承されているか？）
	AbstractScene* new_scene = dynamic_cast<AbstractScene*>(CreateScene(scene_type));


	//エラーチェック
	if (new_scene == nullptr)
	{
		throw("シーンが生成できませんでした。\n");
	}

	//前回シーンの終了時処理を行う
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//新しく生成したシーンの初期化を行う
	new_scene->Initialize();

	//現在シーンの更新
	current_scene = new_scene;
}

//シーン生成処理
AbstractScene* SceneManager::CreateScene(eAbstractSceneType scene_type)
{
	//引数（シーンタイプ）によって、生成するシーンを決定する
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
