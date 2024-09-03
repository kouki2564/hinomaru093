#include "Camera.h"
#include "DxLib.h"
#include "Quaternion.h"

namespace
{
	// �J�����ړ��ʂ̔{���i 0 �` 1.0f �j
	constexpr float kMoveScale = 0.3f;
	constexpr float kTempAngle = 0.000025f;
}

Camera::Camera():
	m_distanceXZ(0.0f),
	m_firstPos(VGet(0, 0, 0))
{
	m_pos = m_firstPos;
	m_targetPos = VGet(0, 0, 0);
	//���s0.1�`10000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 10000.0f);
}

Camera::~Camera()
{
}

void Camera::Init(VECTOR firstPos)
{
	m_firstPos = firstPos;
	m_pos = m_firstPos;
	m_distanceXZ = sqrtf(m_pos.x * m_pos.x + m_pos.z * m_pos.z);
	m_lastObjPos = VGet(0, 0, 0);
	m_debugMove = 1.0f;
}

void Camera::Update(bool isRotate)
{
	Quaternion moving;
	float angle = 0;
	if (isRotate)
	{
		angle = Rotate();
	}
	// �J�����̉�]���ݒ�
	VECTOR axis = VGet(0, 1, 0);

	// �J�����̈ړ��l�ݒ�
	VECTOR targetMove = VSub(m_targetPos, m_lastObjPos);

	// Quaternion�̐ݒ�
	moving.SetMove(angle, axis, targetMove);


	// ���ړ�
	m_pos = moving.Move(m_targetPos, m_pos);

	// �J���������S�ɂƂ炦����W
	VECTOR adjustTargetPos = VGet(m_targetPos.x, m_targetPos.y + 10.0f, m_targetPos.z);


	// �J�����ʒu�����X�ɂ���Ă����΍�
	// XZ���ʂ̈ʒu�␳
	VECTOR localPos = VSub(m_pos, adjustTargetPos);
	float tempDisXZ = sqrtf(localPos.x * localPos.x + localPos.z * localPos.z);
	if (tempDisXZ != m_distanceXZ)
	{
		localPos.x *= m_distanceXZ / tempDisXZ;
		localPos.z *= m_distanceXZ / tempDisXZ;
		m_pos = VAdd(localPos, adjustTargetPos);
	}
	// �����͌Œ�̈׏����ʒu��
	m_pos.y = m_firstPos.y;


	// �J�������f
	DxLib::SetCameraPositionAndTarget_UpVecY(m_pos, adjustTargetPos);

	// ���t���[���ň������O�t���[���̃J�����^�[�Q�b�g�ʒu
	m_lastObjPos = m_targetPos;
}

float Camera::Rotate()
{
	// �J�����̉�]�l�ݒ�
	// �Q�[���p�b�h����̉�]����
	StickInput inputState = m_config.GetStick(STICK_R);
	// ��]�p�̊m��
	return kTempAngle * inputState.x;

}
