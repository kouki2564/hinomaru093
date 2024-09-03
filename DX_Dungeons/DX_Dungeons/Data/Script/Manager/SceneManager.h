#pragma once
#include <memory>
#include "Config.h"

class SceneBase;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();

private:
	// ƒV[ƒ“‘JˆÚ
	void SceneUpdate();

	int m_sceneNum;

	Config m_config;

	std::unique_ptr<SceneBase> m_pScene;

};

