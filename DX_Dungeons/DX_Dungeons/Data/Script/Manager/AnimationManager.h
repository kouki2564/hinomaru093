#pragma once
#include "DxLib.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	/// <summary>
	/// �A�j���[�V�����̃Z�b�g
	/// </summary>
	/// <param name="modelHandle">���������f���̃n���h��</param>
	/// <param name="animaNum">�A�j���[�V�����̔ԍ�</param>
	/// <param name="Speed">�A�j���[�V�����Đ����x(�����l�F30)</param>
	/// <param name="frame">�A�j���[�V�����̊J�n�t���[��(�����l�F0)</param>
	void InitAnimation(int modelHandle, int animaNum, float speed, float frame);


	/// <summary>
	/// �A�j���[�V�����̃t���[���𒲐�
	/// </summary>
	/// <param name="frame">�t���[���l</param>
	void SetFrame(float frame) { m_animaFrame = frame; }

	/// <summary>
	/// �A�j���[�V�����̕ύX
	/// </summary>
	/// <param name="animaNum">�A�j���[�V�����ԍ�</param>
	/// <param name="speed">�A�j���[�V�����Đ����x</param>
	void SetAnimation(int animaNum, float speed);

	// �A�j���[�V�����Đ�
	void Play();

	// �A�j���[�V�������ǂꂭ�炢�i�񂾂̂��̊������l��
	float GetAnimationProgress() { return (m_animaFrame/MV1GetAttachAnimTotalTime(m_modelHandle, m_nowIndex)); }

	// ���ݍĐ����̃A�j���[�V�����ԍ����l��
	int GetAnimationNum() { return MV1GetAttachAnim(m_modelHandle, m_nowIndex); }

private:
	void Animation();
	void AnimaRate();


	// �A�j���[�V�����֘A�ϐ�

	// �A�j���[�V�������̃��f���n���h��
	int m_modelHandle;
	// �A�j���[�V�������݃t���[��
	float m_animaFrame;
	// �A�j���[�V�����J��rate
	float m_animaRate;
	// �A�j���[�V�����C���f�b�N�X
	// �Đ����A�j���[�V����
	int m_nowIndex;
	// �ڍs��A�j���[�V����
	int m_nextIndex;
	// �A�j���[�V�������x
	float m_animaSpeed;
};

