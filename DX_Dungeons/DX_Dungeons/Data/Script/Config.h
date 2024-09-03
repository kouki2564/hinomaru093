#pragma once
#include "DxLib.h"
#include "Game.h"
#include <cassert>

 enum Input
{
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	LB = 4,
	RB = 5,
	BACK = 6,
	START = 7,
	STICK_L = 8,
	STICK_R = 9
};

/// <summary>
/// �X�e�B�b�N�̓��͒l�iint x, int y�j
/// </summary>
struct StickInput
{
	int x = 0;
	int y = 0;
};

class Config
{
public:
	Config()
	{
		GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);
		for (int i = 0; i < Game::kButtonNum; i++)
		{
			m_isLastHit[i] = false;
		}
		m_isLastStick = false;
	}

	/// <summary>
	/// �X�e�B�b�N����
	/// </summary>
	/// <param name="num">�X�e�B�b�N(enum Input)</param>
	/// <returns>int x (-1000�`1000), int y (-1000�`1000)</returns>
	StickInput GetStick(int num);

	/// <summary>
	/// �X�e�B�b�N���́iXY�����w��̒P�����j
	/// </summary>
	/// <param name="num"></param>
	/// <param name="isX"></param>
	/// <returns></returns>
	int GetStickDown(int num, bool isX);

	/// <summary>
	/// �{�^���̉������ςȂ�����i�X�e�B�b�N�͎g���܂���j
	/// </summary>
	/// <param name="num">�{�^��(enum Input)</param>
	/// <returns>true : �����Ă���, false : �����Ă��Ȃ�</returns>
	bool GetInputStay(int num);
	

	/// <summary>
	/// �{�^���̒P�����i�X�e�B�b�N�͎g���܂���j
	/// </summary>
	/// <param name="num">�{�^��(enum Input)</param>
	/// <returns>true : �����Ă���, false : �������ςȂ� or �����Ă��Ȃ�</returns>
	bool GetInputDown(int num);

	/// <summary>
	/// �{�^��������ԁ������i�X�e�B�b�N�͎g���܂���j
	/// </summary>
	/// <param name="num">�{�^��(enum Input)</param>
	/// <returns>true : ������, false : �������ςȂ� or �����Ă��Ȃ�</returns>
	bool GetInputUp(int num);

private:
	bool m_isLastHit[Game::kButtonNum];
	bool m_isLastStick;
	DINPUT_JOYSTATE m_pad;
};

