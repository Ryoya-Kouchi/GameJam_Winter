//#pragma once
//
//#include "AbstractScene.h"
//
//class ResultScene :public AbstractScene
//{
//private:
//	int back_ground;		//�w�i�摜
//	int score;				//�X�R�A
//	int enemy_count[3];		//�G�̃J�E���g
//	int enemy_image[3];		//�G�摜
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