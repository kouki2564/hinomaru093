#include "CharacterBase.h"
#include "Game.h"
#include <math.h>

void CharacterBase::HitWall(float charaSize)
{
	VECTOR Point1ToChara;
	VECTOR Point1ToPoint2;

	/*
		ai_norm = np.dot(ap, ab)/norm(ab)
        neighbor_point = a + (ab)/norm(ab)*ai_norm
        distance = norm(p - neighbor_point)
	*/

	if (m_pos.x < 0 && m_pos.z < 0)
	{/*
		Point1ToChara = VSub(m_pos, VGet(0, 0, -1950));
		Point1ToPoint2 = VSub(VGet(-1950, 0, 0), VGet(0, 0, -1950));
		auto CharaToNear = VDot(Point1ToChara, Point1ToPoint2) / VNorm()*/
	}
	else if (m_pos.x < 0 && m_pos.z > 0)
	{

	}
	else if (m_pos.x > 0 && m_pos.z < 0)
	{

	}
	else if (m_pos.x > 0 && m_pos.z > 0)
	{

	}

	if (m_pos.x + charaSize > Game::kFloorSize)
	{
		m_pos.x -= (m_pos.x + charaSize) - Game::kFloorSize;
	}
	else if (m_pos.x - charaSize < -Game::kFloorSize)
	{
		m_pos.x -= (m_pos.x - charaSize) + Game::kFloorSize;
	}

	if (m_pos.z + charaSize > Game::kFloorSize)
	{
		m_pos.z -= (m_pos.z + charaSize) - Game::kFloorSize;
	}
	else if (m_pos.z - charaSize < -Game::kFloorSize)
	{
		m_pos.z -= (m_pos.z - charaSize) + Game::kFloorSize;
	}
}

void CharacterBase::Rotation()
{
	// ���f����]
	MV1SetRotationXYZ(m_handle, VGet(0, atan2(-m_dir.x, -m_dir.z), 0));
}

void CharacterBase::WeponMove(int attachFrame)
{
	if (m_handle != -1 && m_weponHandle != -1)
	{
		VECTOR AttachSuruFrame1Position;
		MATRIX TransMat;
		MATRIX AttachSareruFrame10Mat;
		MATRIX MixMatrix;
		
		// �A�^�b�`���郂�f���� MV1SetMatrix �̐ݒ�𖳌�������
		MV1SetMatrix(m_weponHandle, MGetIdent());

		// �A�^�b�`���郂�f���̃t���[���̍��W���擾����
		AttachSuruFrame1Position = MV1GetFramePosition(m_weponHandle, 0);

		// �A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s����쐬
		TransMat = MGetTranslate(VScale(AttachSuruFrame1Position, -1.0f));

		// �A�^�b�`����郂�f���̃t���[���̍s����擾
		AttachSareruFrame10Mat = MV1GetFrameLocalWorldMatrix(m_handle, attachFrame);

		// �A�^�b�`���郂�f�����t���[���̍��W�����_�ɂ��邽�߂̕��s�ړ��s��ƁA
		// �A�^�b�`����郂�f���̃t���[���̍s�������
		MixMatrix = MMult(MGetRotAxis(VGet(0, 1, 0), 1.0f * DX_PI_F),	// �p�x����
					MMult(MGetScale(VGet(0.005f, 0.005f, 0.005f)),		// �X�P�[���l����
					MMult(TransMat, AttachSareruFrame10Mat)));			// �ړ��ʐݒ�
		// ���������s����A�^�b�`���郂�f���ɃZ�b�g
		MV1SetMatrix(m_weponHandle, MixMatrix);
	}
}
