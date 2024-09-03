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
	TITLE,		// �^�C�g��
	HUB,		// ���_
	DUNGEON,	// �_���W����
	DEBUG = 99	// �f�o�b�N
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

	// �V�[���������I��点��
	virtual int NextScene() = 0;

protected:
	// �I�u�W�F�N�g�֘A�����ׂ�map�z��Ƃ��Ă܂Ƃ߂悤���l�������A
	// ���F���ƃ������g�p�ʂ����O���āA
	// ��U�R���|�[�l���g�x�[�X��...
	// std::map<std::string, std::shared_ptr<ObjectBase>> m_pObjects;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Light> m_pLight;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Boss> m_pBoss;
	UIManager m_UIManager;
	Config m_config;


	int m_sceneModelHandle;
};

