#pragma once
#include "ObjectBase.h"
#include "AnimationManager.h"
#include "UIPanel.h"

enum class State
{
	IDLE,
	MOVE,
	DODGE,
	ATTACK,
	SKILL,
	NOCKBACK,
	DOWN
};

class CharacterBase :
    public ObjectBase
{
public:
    CharacterBase(){
		m_weponHandle = -1;
		m_weponAttachFrameNum = -1;
		m_hpBarHandle = -1;
		m_state = State::IDLE;
		m_dir = VGet(0.0f, 0.0f, 0.0f);
		m_pushVec = VGet(0.0f, 0.0f, 0.0f);
		m_actionTimer = 0;
		m_moveVecInFrame = VGet(0.0f, 0.0f, 0.0f);
	}
	virtual ~CharacterBase() { DeleteGraph(m_hpBarHandle); }

	virtual void Draw() const = 0;

	void HitWall(float charaSize);

	// �����o���x�N�g����ݒ�
	void SetPushVec(VECTOR vec) { m_pushVec = vec; }


	UIPanel& GetUI() { return m_UI; }

private:
	virtual void AnimationUpdate() = 0;

protected:
	/// <summary>
	/// ���f���̉�]
	/// </summary>
	/// <param name="moveVec">��]��̐��ʕ���</param>
	void Rotation();

	void WeponMove(int attachFrame);


	int m_weponHandle;
	int m_weponAttachFrameNum;

	State m_state;

	// ����
	VECTOR m_dir;

	VECTOR m_moveVecInFrame;

	AnimationManager m_animation;

	int m_actionTimer;

	// ���t���[���Ԍ��܂��������ɉ����o���ׂ̃x�N�g��
	VECTOR m_pushVec;

	UIPanel m_UI;
	int m_hpBarHandle;
};

