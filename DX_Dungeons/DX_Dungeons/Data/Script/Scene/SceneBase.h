#pragma once
#include <memory>
#include <map>
#include <string>
#include "Camera.h"
#include "Light.h"
#include "Config.h"
#include "UIManager.h"

class Player;
class Boss;

enum Scene
{
	TITLE,		// タイトル
	HUB,		// 拠点
	DUNGEON,	// ダンジョン
	DEBUG = 99	// デバック
};

class SceneBase :
	public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase()
	{
		m_pCamera = std::make_shared<Camera>();
		m_pLight = std::make_shared<Light>();
		m_sceneModelHandle = -1;
	}
	virtual ~SceneBase(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;

	// シーン処理を終わらせる
	virtual int NextScene() = 0;

protected:
	// オブジェクト関連をすべてmap配列としてまとめようか考えたが、
	// 視認性とメモリ使用量を懸念して、
	// 一旦コンポーネントベースに...
	// std::map<std::string, std::shared_ptr<ObjectBase>> m_pObjects;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Light> m_pLight;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Boss> m_pBoss;
	UIManager m_UIManager;
	Config m_config;


	int m_sceneModelHandle;
};

