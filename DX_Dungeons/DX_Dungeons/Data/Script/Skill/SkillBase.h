#pragma once
#include "DxLib.h"
#include <memory>

class SkillBase :
	public std::enable_shared_from_this<SkillBase>
{
public:
	// �Z�̔���
	virtual void Start() = 0;
	// �Z�̓r����~
	virtual void Cancel() = 0;
	// ���̋Z�ւ̔h��
	virtual void Conect() = 0;

protected:
	// �Z�̓���
	virtual void Update() = 0;

	// �Z�̔����n�_
	VECTOR m_appPos;
	// �Z�Ďg�p�\�܂ł̃N�[���^�C��
	int m_coolTimer;
};

