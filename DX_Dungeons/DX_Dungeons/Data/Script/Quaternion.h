#pragma once
#include "DxLib.h"
#include <cmath>

class Quaternion
{
public:
	Quaternion()
	{
		Qu.w = 1;
		Qu.x = 0;
		Qu.y = 0;
		Qu.z = 0;
		vec = VGet(0, 0, 0);
	};
	virtual ~Quaternion() {}

private:
	struct Q
	{
		float w;
		float x;
		float y;
		float z;


		Q operator * (const Q& _q) const
		{
			Q tempQ;

			/*�N�I�[�^�j�I���̊|���Z*/
			//�����ʂ�ł��B
			tempQ.w = w * _q.w - x * _q.x - y * _q.y - z * _q.z;//����
			tempQ.x = w * _q.x + x * _q.w + y * _q.z - z * _q.y;//����x
			tempQ.y = w * _q.y + y * _q.w + z * _q.x - x * _q.z;//����y
			tempQ.z = w * _q.z + z * _q.w + x * _q.y - y * _q.x;//����z

			return tempQ;
		}
	};

	Q Qu;
	VECTOR vec;

public:
	/// <summary>
	/// �ړ��ʂ̐ݒ�
	/// </summary>
	/// <param name="_angle"> 1�t���[��������̊p�x ( ���W�A���l ) </param>
	/// <param name="_axis"> ��]�̎��x�N�g�� </param>
	/// <param name="_moveVec"> ���s�ړ��x�N�g�� </param>
	void SetMove(float& _angle, VECTOR& _axis, VECTOR& _moveVec)
	{
		Qu.w = cos(_angle / 2.0f);//����
		Qu.x = _axis.x * sin(_angle / 2.0f);
		Qu.y = _axis.y * sin(_angle / 2.0f);
		Qu.z = _axis.z * sin(_angle / 2.0f);
		vec = _moveVec;
	}

	/// <summary>
	/// �N�H�[�^�j�I���ɂ����ړ�
	/// </summary>
	/// <param name="_rotPoint"> ��]���钆�S�̍��W </param>
	/// <param name="_pos"> ��]������̂̍��W </param>
	/// <returns> ��]��̍��W </returns>
	VECTOR Move(VECTOR& _rotPoint, VECTOR& _pos)
	{
		Q qPos, qInv;
		VECTOR vPos;

		//3�������W���N�I�[�^�j�I���ɕϊ�
		qPos.w = 1.0f;
		qPos.x = _pos.x - _rotPoint.x;
		qPos.y = _pos.y - _rotPoint.y;
		qPos.z = _pos.z - _rotPoint.z;

		//��]�N�H�[�^�j�I���̃C���o�[�X�̍쐬
		//�t�N�H�[�^�j�I�����o���̂͑�ςȂ̂ŁA
		//3�������Ɠ����l�ɂȂ鋤���N�I�[�^�j�I���ō쐬(���������}�C�i�X���])
		qInv.w = Qu.w;
		qInv.x = -Qu.x;
		qInv.y = -Qu.y;
		qInv.z = -Qu.z;

		//��]��̃N�I�[�^�j�I���̍쐬
		qPos = Qu * qPos * qInv;

		//�R�������W�ɖ߂�
		vPos.x = qPos.x + _rotPoint.x;
		vPos.y = qPos.y + _rotPoint.y;
		vPos.z = qPos.z + _rotPoint.z;

		// ��]��Ɉړ�
		vPos.x += vec.x;
		vPos.y += vec.y;
		vPos.z += vec.z;

		return vPos;
	}
};

