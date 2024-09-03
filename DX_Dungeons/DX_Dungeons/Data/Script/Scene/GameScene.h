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

	// �V�[���������I��点��
	int NextScene();

private:
	int m_gameState;

	int m_startTimer;
};

