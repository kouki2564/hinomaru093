#include "Boss.h"
#include <cassert>

namespace
{
	// �s���ҋ@����
	constexpr int kMoveCoolTimeMax = 180;
	// �s�����x
	constexpr float kMoveSpeed = 10.0;
	// �^�b�N�����x
	constexpr float kRunSpeed = 30.0 / 240;
	// �ڋߍŒZ����
	constexpr float kNearFar = 300;
	constexpr float kLongFar = 750;
	// ���f���T�C�Y
	constexpr float kModelSize = 150;
}

enum Anima
{
	ENTRY = 72,
	IDLE = 94,
	MOVE = 93,
	PRELIMINARY = 42,
	ATTACK = 2,
	TACLE = 56,
	SRASH = 4
};

Boss::Boss():
	m_moveCoolTimer(0),
	m_isAction(false),
	m_attackCount(0)
	{
		m_handle = MV1LoadModel("Data/Model/Character/Golem.mv1");
		m_hpBarHandle = LoadGraph("Data/Graph/BarV6_ProgressBar.png");
		COLOR_F eyeDef = { 1.0f,0.2f,0.2f,0.8f };
		COLOR_F eyeSpc = { 1.0f,0.0f,0.0f,1.0f };
		COLOR_F eyeEmi = { 1.0f,0.0f,0.0f,1.0f };
		COLOR_F eyeAmb = { 0.0f,0.0f,0.0f,1.0f };

		MV1SetFrameDifColorScale(m_handle, 49, eyeDef);
		MV1SetFrameSpcColorScale(m_handle, 49, eyeSpc);
		MV1SetFrameEmiColorScale(m_handle, 49, eyeEmi);
		MV1SetFrameAmbColorScale(m_handle, 49, eyeAmb);

		m_animation.InitAnimation(m_handle, Anima::PRELIMINARY, 2, 0);

		/////////////////
		// ��������֘A
		/////////////////
		m_weponHandle = MV1LoadModel("Data/Model/Wepon/GolemAxe.mv1");

		m_state = State::IDLE;
		m_runDir = m_dir;

		// UI
		m_UI.SetUI(LoadGraph("Data/Graph/BarV6_Bar.png"),
			Game::kScreenHalfWidth * 0.5f,
			Game::kScreenHeight * 0.1f,
			Game::kScreenHalfWidth * 1.5f,
			Game::kScreenHeight * 0.12f,
			true);
		m_UI.SetUI(m_hpBarHandle,
			Game::kScreenHalfWidth * 0.5f,
			Game::kScreenHeight * 0.1f,
			Game::kScreenHalfWidth * 1.5f,
			Game::kScreenHeight * 0.12f,
			true);
		m_UI.SetUI(LoadGraph("Data/Graph/BarV1_ProgressBarBorder.png"),
			Game::kScreenHalfWidth * 0.5f,
			Game::kScreenHeight * 0.1f,
			Game::kScreenHalfWidth * 1.5f,
			Game::kScreenHeight * 0.12f,
			true);
	}

	Boss::~Boss()
	{
		MV1DeleteModel(m_handle);
		MV1DeleteModel(m_weponHandle);
	}

	void Boss::Init()
	{
		m_pos = VGet(0, 0, 900.0f);
		MV1SetScale(m_handle, VGet(80, 80, 80));
		MV1SetPosition(m_handle, m_pos);
		m_weponAttachFrameNum = MV1SearchFrame(m_handle, "handslot.r");
		WeponMove(m_weponAttachFrameNum);
	}

	void Boss::Update(VECTOR playerPos)
	{
		WeponMove(m_weponAttachFrameNum);

		// �s��
		VECTOR toPlayer = VSub(playerPos, m_pos);
		if (m_moveCoolTimer >= 120)
		{
			m_isAction = true;
			// �����̊m��
			toPlayer.y = 0;
			if (m_state == State::IDLE || m_state == State::MOVE)
				m_dir = VNorm(toPlayer);
			// ��]
			Rotation();
			// �s���͈͓��Ƀv���C���[�������ꍇ
			if (VSize(toPlayer) < kNearFar)
			{
				if (m_isAction)
				{
					NearAttack();
					if (m_attackCount < 2)
					{
						m_attackCount++;
					}
					else
					{
						m_attackCount = 0;
					}
				}
				m_moveCoolTimer = 0;
			}
			// ���ȏ㉓�������ꍇ
			else if (VSize(toPlayer) > kLongFar)
			{
				if (m_isAction)
				{
					m_state = State::SKILL;
				}
				m_moveCoolTimer = 0;
			}
			// ���̒��Ԃ̈ʒu�ɂ���ꍇ
			else
			{
				// �ǐ�
				Move();
			}
		}


		// ��ԍX�V
		if (m_state != State::IDLE && m_state != State::MOVE)
		{
			m_actionTimer++;
			if (m_state == State::ATTACK)
			{
				if (m_actionTimer > 60)
				{
					m_actionTimer = 0;
					m_state = State::IDLE;
					m_isAction = false;
					m_moveCoolTimer = 0;
				}
			}
			else if (m_state == State::SKILL)
			{
				LongAttack(toPlayer);
				
				if (m_actionTimer > 120)
					// || (m_actionTimer > 80 && VSize(toPlayer) < kNearFar))
				{
					m_actionTimer = 0;
					m_state = State::IDLE;
					m_isAction = false;
					m_moveCoolTimer = 0;
				}
		}
	}

		HitWall(kModelSize);

	// �s���N�[���^�C���X�V
	if (m_moveCoolTimer < 120)
	{
		m_moveCoolTimer++;
	}

	// �A�j���[�V�����X�V
	AnimationUpdate();
}

void Boss::Draw() const
{
	MV1DrawModel(m_weponHandle);
	MV1SetPosition(m_handle, m_pos);
	MV1DrawModel(m_handle);
	
	// debug
	DrawSphere3D(m_pos, kModelSize, 8, 0xff0000, 0xffffff, false);
	// �L����������
	if (m_state == State::IDLE)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : IDLE");
	}
	else if (m_state == State::ATTACK)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : ATTACK");
	}
	else if (m_state == State::DODGE)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : DODGE");
	}
	else if (m_state == State::MOVE)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : MOVE");
	}
	else if (m_state == State::SKILL)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : SKILL");
	}
	else if (m_state == State::DOWN)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : DOWN");
	}
	else if (m_state == State::NOCKBACK)
	{
		DrawFormatString(500, 60, 0xffffff, "BSTATE : KNOCKBACK");
	}
}

void Boss::Move()
{
	m_state = State::MOVE;
	// �����x�N�g���Ɉړ��ʕ��X�P�[������
	VECTOR moveVec = VScale(m_dir, kMoveSpeed);

	m_pos = VAdd(m_pos, moveVec);
}

void Boss::NearAttack()
{
	m_state = State::ATTACK;
}

void Boss::LongAttack(VECTOR toPlayer)
{
	m_state = State::SKILL;
	if (m_actionTimer < 80)
	{
		m_runDir = VScale(toPlayer, 0.15f);
		m_dir = VNorm(toPlayer);
		Rotation();
	}
	else
	{
		// �����x�N�g���Ɉړ��ʕ��X�P�[������
		m_runDir = VScale(m_runDir, 0.9f);
		VECTOR moveVec = m_runDir;
		// ���f
		m_pos = VAdd(m_pos, moveVec);
	}
}

void Boss::AnimationUpdate()
{
	if (m_state == State::IDLE)
	{
		m_animation.SetAnimation(Anima::IDLE, 2);
	}
	else if (m_state == State::MOVE)
	{
		m_animation.SetAnimation(Anima::MOVE, 10);
	}
	else if (m_state == State::ATTACK)
	{
		if (m_attackCount < 2)
		{
			m_animation.SetAnimation(Anima::SRASH, 6);
		}
		else
		{
			m_animation.SetAnimation(Anima::ATTACK, 8);
		}
	}
	else if (m_state == State::SKILL)
	{
		if(m_actionTimer < 80)
			m_animation.SetAnimation(Anima::PRELIMINARY, 8);
		else
			m_animation.SetAnimation(Anima::TACLE, 8);
	}
	else if (m_actionTimer < 270)
	{

	}
	else if (m_actionTimer < 300)
	{

	}
	// �A�j���[�V�����Đ�
	m_animation.Play();
}
