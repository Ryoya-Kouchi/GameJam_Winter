#pragma once

//SceneBase.hの代わり

//シーン情報
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

// デフォルトの抽象シーンクラス
// ユーザーはこれを継承してシーンを実装すると楽
class AbstractScene {
public:
	AbstractScene() {}
    // デストラクタ
    virtual ~AbstractScene() {}

    // 更新処理を実装する
	virtual eAbstractSceneType Update()
	{
		return GetNowScene();
	}

    // 描画処理を実装する
    virtual void Draw() const {}

	//終了時処理
	virtual void Finalize() {}

	//現在シーン情報を取得
	virtual eAbstractSceneType GetNowScene() const = 0;
};
