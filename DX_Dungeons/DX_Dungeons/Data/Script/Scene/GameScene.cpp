#include "GameScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Boss.h"

GameScene::GameScene()
{
	m_sceneModelHandle = MV1LoadModel("Data/Model/Stage/BossRoom.mv1");
	MV1SetPosition(m_sceneModelHandle, VGet(0, 0, 0));
	m_pPlayer = std::make_shared<Player>();
	m_pBoss = std::make_shared<Boss>();
	m_gameState = GameState::STARTING;
	m_startTimer = 240;
}

GameScene::~GameScene()
{
	MV1DeleteModel(m_sceneModelHandle);
}

void GameScene::Init()
{
	m_pCamera->Init(VGet(0, 400.0f, -900.0f));
	m_pPlayer->Init(VGet(0, 0, -800.0f));
	m_UIManager.SetUIPanel(m_pPlayer->GetUI());
	m_pBoss->Init();
	m_UIManager.SetUIPanel(m_pBoss->GetUI());
	m_pLight->Init(m_pCamera->GetPos(), m_pPlayer->GetPos());


}

void GameScene::Update()
{
	// �Q�[���V�[�����ł̏�Ԗ��̏���
	// �V�[���ڍs��ŏ��̏���
	if (m_gameState == GameState::STARTING)
	{
		m_pCamera->SetTargetPos(m_pPlayer->GetPos());
		m_pCamera->Update(false);
		if (m_startTimer > 0)
		{
			m_startTimer--;
		}
		else
		{
			m_gameState = GameState::PLAYING;
		}
	}
	// �v���C���[����\���̏���
	else if(m_gameState == GameState::PLAYING)
	{
		m_pPlayer->Update(m_pCamera->GetPos());
		m_pBoss->Update(m_pPlayer->GetPos());
		m_pCamera->SetTargetPos(m_pPlayer->GetPos());
		m_pCamera->Update(true);

	}
	// �|�[�Y���i�Q�[����~���j�̏���
	else if (m_gameState == GameState::PAUSE)
	{

	}
	else
	{
		assert(false);
	}



	m_pLight->Update(m_pCamera->GetPos(), m_pPlayer->GetPos());

	// SetShadowMapLightDirection(shadowHandle, VSub(m_pPlayer->GetPos(), m_pCamera->GetPos()));
	auto tempPos = m_pPlayer->GetPos();
	/*SetShadowMapDrawArea(shadowHandle,
		VGet(tempPos.x - 1000, tempPos.y - 100, tempPos.z - 1000),
		VGet(tempPos.x + 1000, tempPos.y + 500, tempPos.z + 1000));*/
}

void GameScene::Draw() const
{
	// �e��ԋ��ʂŕ\��
	MV1DrawModel(m_sceneModelHandle);
	m_pPlayer->Draw();
	m_pBoss->Draw();

	// �Q�[���V�[�����ł̏�Ԗ��̏���
	// �V�[���ڍs��ŏ��̏���
	if (m_gameState == GameState::STARTING)
	{
		if(m_startTimer > 60)
			DrawFormatString(Game::kScreenHalfWidth, Game::kScreenHalfHeight, 0xffff00, "%d", (m_startTimer / 60));
		else
			DrawFormatString(Game::kScreenHalfWidth, Game::kScreenHalfHeight, 0xffff00, "START!!");

	}
	// �v���C���[����\���̏���
	else if (m_gameState == GameState::PLAYING)
	{
	}
	// �|�[�Y���i�Q�[����~���j�̏���
	else if (m_gameState == GameState::PAUSE)
	{
	}
	else
	{
		assert(false);
	}

	// �Q�[���p�b�h����̉�]����
	DINPUT_JOYSTATE pad;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &pad);
	for (int i = 0; i < 32; i++)
	{
		DrawFormatString(10, 10 * i + 10, 0xffffff, "%d", pad.Buttons[i]);
	}
	
	// UI�\��
	m_UIManager.Draw();

	// ���E��
	DrawLine3D(VGet(-800, 0, -1150), VGet(800, 0, -1150), 0xff0000);
	DrawLine3D(VGet(-800, 0, 1150), VGet(800, 0, 1150), 0xff0000);
	DrawLine3D(VGet(-1150, 0, -800 ), VGet(-1150, 0, 800 ), 0xff0000);
	DrawLine3D(VGet(1150, 0, -800 ), VGet(1150, 0, 800 ), 0xff0000);


	DrawLine3D(VGet(-800, 0, 1150), VGet(-1150, 0, 800), 0xff0000);
	DrawLine3D(VGet(800, 0, 1150), VGet(1150, 0, 800), 0xff0000);
	DrawLine3D(VGet(-800, 0, -1150), VGet(-1150, 0, -800), 0xff0000);
	DrawLine3D(VGet(800, 0, -1150), VGet(1150, 0, -800), 0xff0000);
}


int GameScene::NextScene()
{
	return 0;
}
