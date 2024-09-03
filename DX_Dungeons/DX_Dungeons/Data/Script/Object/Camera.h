#pragma once
#include "ObjectBase.h"
#include "Config.h"

class Camera :
    public ObjectBase
{
public:
	Camera();
	~Camera();

	void Init(VECTOR firstPos);
	void Update(bool isRotate);
	void Draw() const{}

	void SetCameraPos(VECTOR cameraPos) { m_pos = cameraPos; }
	void SetTargetPos(VECTOR targetPos) { m_targetPos = targetPos; }
	float Rotate();

private:
	// �J���������ʒu
	VECTOR m_firstPos;
	// �J�����̃^�[�Q�b�g�ʒu
	VECTOR m_targetPos;
	// ���O�t���[���̃^�[�Q�b�g�ʒu
	VECTOR m_lastObjPos;
	// �J�����ƃ^�[�Q�b�g��XZ���ʏ�̋���
	float m_distanceXZ;

	float m_debugMove;

	Config m_config;
};

