#pragma once

//�Q�[���S�̂Ŏg���萔���`

// �O���t�@�C������ڎw��
// �f�[�^�x�[�X
// �ݒ�t�@�C��
// �p�����[�^�l
// �Z�[�u�t�@�C��

// �X�N���v�g�t�@�C��(������O���f�[�^�̂ЂƂ�)

namespace Game
{
	//////////////
	// ��{�ݒ� //
	//////////////

	// ��ʕ�
	constexpr int kScreenWidth = 1280;      //��ʂ̉���
	constexpr int kScreenHeight = 720;     //��ʂ̏c��
	// �����T�C�Y
	constexpr int kScreenHalfWidth = kScreenWidth / 2;      //��ʂ̉���
	constexpr int kScreenHalfHeight = kScreenHeight / 2;     //��ʂ̏c��

	// �Q�[���F�[�x
	constexpr int kColorDepth = 32;        //16 or 32

	//////////////////////
	// �Q�[�����Ƃ̐ݒ� //
	//////////////////////

	// �t�B�[���h�̃O���t�B�b�N��
	constexpr int kFloorLine = 12;
	constexpr int kFloorRow = 12;
	// �P������̃T�C�Y
	constexpr float kModelSize = 160.0f;

	constexpr int kFloorSize = 1150;
	constexpr int kFloorSize2 = 800;

	// �ړ����W�͈�
	constexpr float kPosXMax = 900.0f;
	constexpr float kPosXMin = -900.0f;
	constexpr float kPosZMax = 900.0f;
	constexpr float kPosZMin = -900.0f;

	constexpr int kTarfgetNumMax = 25;

	// �S�̃V�[����
	constexpr int kSceneNum = 3;

	// �g�p�{�^����
	constexpr int kButtonNum = 8;

	// �T�E���h��
	constexpr int kBGMNum = 0;
	constexpr int kSENum = 0;

	// �v���C���[�ʏ�U����
	constexpr int kAttackCountMax = 3;
}