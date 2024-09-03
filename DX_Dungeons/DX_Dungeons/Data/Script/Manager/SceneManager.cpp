#include "SceneManager.h"
#include "TitleScene.h"
#include "HubScene.h"
#include "GameScene.h"
#include "DebugScene.h"

SceneManager::SceneManager()
{
	m_sceneNum = Scene::DEBUG;
	m_pScene = std::make_unique<GameScene>();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_pScene->Init();
}

void SceneManager::Update()
{
	
	m_pScene->Update();
	m_pScene->Draw();

	if (m_config.GetInputDown(Input::START))
	{
		if (m_sceneNum == Scene::DEBUG)
		{
			m_sceneNum = Scene::TITLE;
			m_pScene = std::make_unique<DebugScene>();
			m_pScene->Init();
		}
		else if (m_sceneNum == Scene::TITLE)
		{
			m_sceneNum = Scene::HUB;
			m_pScene = std::make_unique<HubScene>();
			m_pScene->Init();
		}
		else if (m_sceneNum == Scene::HUB)
		{
			m_sceneNum = Scene::DUNGEON;
			m_pScene = std::make_unique<GameScene>();
			m_pScene->Init();
		}
		else if (m_sceneNum == Scene::DUNGEON)
		{
			m_sceneNum = Scene::DEBUG;
			m_pScene = std::make_unique<DebugScene>();
			m_pScene->Init();
		}
	}
}

void SceneManager::Draw()
{
}

void SceneManager::SceneUpdate()
{
	m_pScene.release();
	if (m_pScene->NextScene() == Scene::TITLE)
	{
		// m_pScene = std::make_unique<GameScene>();
	}
	else if(m_pScene->NextScene() == Scene::HUB)
	{
		m_pScene = std::make_unique<GameScene>();
	}
	else if (m_pScene->NextScene() == Scene::DUNGEON)
	{
		// m_pScene = std::make_unique<GameScene>();
	}
	m_pScene->Init();
}
