#include "HubScene.h"
#include "Config.h"

HubScene::HubScene()
{
	m_backHandle = LoadGraph("Data/Graph/sora.jpg");
	m_sceneModelHandle = MV1LoadModel("Data/Model/Stage/Hub.mv1");
	MV1SetPosition(m_sceneModelHandle, VGet(0, 0, 0));
	m_cameraTargetNum = 0;
	m_cameraPos[0] = VGet(-100, 200, -100);
	m_cameraPos[1] = VGet(100, 200, -100);
	m_cameraPos[2] = VGet(100, 200, 100);
	m_cameraTargetPos[0] = VGet(200, 150, 300);
	m_cameraTargetPos[1] = VGet(-150, 150, 300);
	m_cameraTargetPos[2] = VGet(-300, 150, -150);
}

HubScene::~HubScene()
{
	DeleteGraph(m_backHandle);
	MV1DeleteModel(m_sceneModelHandle);
}

void HubScene::Init()
{
	m_pCamera->Init(m_cameraPos[0]);
	m_pLight->Init(m_pCamera->GetPos(), m_cameraTargetPos[0]);
}

void HubScene::Update()
{
	int stickInput = m_config.GetStickDown(Input::STICK_L, true);

	if (stickInput < 0)
	{

		if (m_cameraTargetNum < 2)
			m_cameraTargetNum++;
		else
			m_cameraTargetNum = 0;
	}
	else if (stickInput > 0)
	{

		if (m_cameraTargetNum > 0)
			m_cameraTargetNum--;
		else
			m_cameraTargetNum = 2;
	}
	
	m_pCamera->SetCameraPos(m_cameraPos[m_cameraTargetNum]);
	m_pCamera->SetTargetPos(m_cameraTargetPos[m_cameraTargetNum]);
	m_pCamera->Update(false);
	m_pLight->Update(m_pCamera->GetPos(), m_cameraTargetPos[m_cameraTargetNum]);

	DrawFormatString(10, 30, 0xffffff, "stick : %d", stickInput);
}

void HubScene::Draw() const
{
	DrawExtendGraph(-10, 100,Game::kScreenWidth,Game::kScreenHeight, m_backHandle, false);
	MV1DrawModel(m_sceneModelHandle);

}

int HubScene::NextScene()
{
	return 0;
}
