#pragma once
#include "SceneBase.h"

enum GameState
{
	STARTING,
	PLAYING,
	PAUSE
};

class GameScene :
    public SceneBase
{
public:
	GameScene();
	~GameScene();
	void Init();
	void Update();
	void Draw() const;

	// シーン処理を終わらせる
	int NextScene();

private:
	int m_gameState;

	int m_startTimer;
};

