//#pragma once
//
//#include "AbstractScene.h"
//
//class ResultScene :public AbstractScene
//{
//private:
//	int back_ground;		//”wŒi‰æ‘œ
//	int score;				//ƒXƒRƒA
//	int enemy_count[3];		//“G‚ÌƒJƒEƒ“ƒg
//	int enemy_image[3];		//“G‰æ‘œ
//
//public:
//	ResultScene();
//	virtual~ResultScene();
//
//	virtual void Initialize() override;
//	virtual eAbstractSceneType Update() override;
//	virtual void Draw() const override;
//	virtual void Finalize() override;
//
//
//	virtual eAbstractSceneType GetNowScene() const override;
//
//private:
//	void ReadResultData();
//
//};