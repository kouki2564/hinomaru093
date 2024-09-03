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
/// スティックの入力値（int x, int y）
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
	/// スティック入力
	/// </summary>
	/// <param name="num">スティック(enum Input)</param>
	/// <returns>int x (-1000～1000), int y (-1000～1000)</returns>
	StickInput GetStick(int num);

	/// <summary>
	/// スティック入力（XY方向指定の単押し）
	/// </summary>
	/// <param name="num"></param>
	/// <param name="isX"></param>
	/// <returns></returns>
	int GetStickDown(int num, bool isX);

	/// <summary>
	/// ボタンの押しっぱなし判定（スティックは使えません）
	/// </summary>
	/// <param name="num">ボタン(enum Input)</param>
	/// <returns>true : 押している, false : 押していない</returns>
	bool GetInputStay(int num);
	

	/// <summary>
	/// ボタンの単押し（スティックは使えません）
	/// </summary>
	/// <param name="num">ボタン(enum Input)</param>
	/// <returns>true : 押している, false : 押しっぱなし or 押していない</returns>
	bool GetInputDown(int num);

	/// <summary>
	/// ボタン押し状態→離し（スティックは使えません）
	/// </summary>
	/// <param name="num">ボタン(enum Input)</param>
	/// <returns>true : 離した, false : 押しっぱなし or 押していない</returns>
	bool GetInputUp(int num);

private:
	bool m_isLastHit[Game::kButtonNum];
	bool m_isLastStick;
	DINPUT_JOYSTATE m_pad;
};

