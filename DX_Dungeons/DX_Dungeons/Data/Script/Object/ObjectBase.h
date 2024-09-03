#pragma once
#include "Game.h"
#include "DxLib.h"
#include <memory>

class ObjectBase :
	public std::enable_shared_from_this<ObjectBase>
{
public:
	ObjectBase()
	{
		m_pos = VGet(0.0f, 0.0f, 0.0f);
		m_rot = VGet(0.0f, 0.0f, 0.0f);
		m_scale = VGet(1.0f, 1.0f, 1.0f);
		m_handle = 0;
	}
	virtual ~ObjectBase() {}

	// �I�u�W�F�N�g�`��
	virtual void Draw() const = 0;

	// ���W�擾
	const VECTOR GetPos() const { return m_pos; }
	// �n���h���擾
	const int GetHandle() const { return m_handle; }

protected:
	// ���W
	VECTOR m_pos;
	// ���f���̉�]�p
	VECTOR m_rot;
	// ���f���̑傫���̔{��
	VECTOR m_scale;
	// �f���v���P�C�g�n���h��
	int m_handle;

};

