#include "Config.h"


StickInput Config::GetStick(int num)
{
	// LR�X�e�B�b�N�ȊO�Ȃ�Ύ~�߂�
	assert(num == STICK_L || num == STICK_R);

	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);
	if (num == STICK_L)			// L�X�e�B�b�N
	{
		return { m_pad.X, m_pad.Y };
	}
	else if (num == STICK_R)	// R�X�e�B�b�N
	{
		return { m_pad.Rx, m_pad.Ry };
	}
	else
	{
		assert(false);
	}
}

int Config::GetStickDown(int num, bool isX)
{
	// LR�X�e�B�b�N�ȊO�Ȃ�Ύ~�߂�
	assert(num == STICK_L || num == STICK_R);
	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);

	if (!m_isLastStick)
	{
		if (num == STICK_L)			// L�X�e�B�b�N
		{
			if (isX == true)
			{
				if (m_pad.X != 0)
				{
					m_isLastStick = true;
				}
				return  m_pad.X;
			}
			else
			{
				if (m_pad.Y != 0)
				{
					m_isLastStick = true;
				}
				return m_pad.Y;
			}
		}
		else if (num == STICK_R)	// R�X�e�B�b�N
		{
			if (isX == true)
			{
				if (m_pad.Rx != 0)
				{
					m_isLastStick = true;
				}
				return  m_pad.Rx;
			}
			else
			{
				if (m_pad.Ry != 0)
				{
					m_isLastStick = true;
				}
				return m_pad.Ry;
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		if (num == STICK_L)			// L�X�e�B�b�N
		{
			if (isX == true && m_pad.X == 0)
			{
				m_isLastStick = false;
			}
			else if(isX = false && m_pad.Y == 0)
			{
				m_isLastStick = false;
			}
		}
		else if (num == STICK_R)	// R�X�e�B�b�N
		{
			if (isX == true && m_pad.Rx == 0)
			{
				m_isLastStick = false;
			}
			else if (isX = false && m_pad.Ry == 0)
			{
				m_isLastStick = false;
			}
		}
		else
		{
			assert(false);
		}
	}

	return 0;
}

bool Config::GetInputStay(int num)
{
	// �w�肵�Ă���{�^���ȊO�Ȃ�Ύ~�߂�
	assert(num >= 0 && num < Game::kButtonNum);


	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);
	// �{�^�����͂����̂܂�bool�Ƃ��ĕԂ�
	return m_pad.Buttons[num];
}

bool Config::GetInputDown(int num)
{
	// �w�肵�Ă���{�^���ȊO�Ȃ�Ύ~�߂�
	assert(num >= 0 && num < Game::kButtonNum);


	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);
	// ���O����ŉ�����Ă��Ȃ��Ƃ�
	if (!m_isLastHit[num])
	{
		// �����󋵂����̂܂�bool�ɂ��ĕԂ�
		m_isLastHit[num] = m_pad.Buttons[num];
		return m_isLastHit[num];
	}
	// ���O����ŉ�����Ă�����
	else
	{
		// ���݃t���[���ŉ�����Ă��Ȃ����false��
		m_isLastHit[num] = m_pad.Buttons[num];
		// �Ԃ�l�͊֌W�Ȃ�false
		return false;
	}
}

bool Config::GetInputUp(int num)
{
	// �w�肵�Ă���{�^���ȊO�Ȃ�Ύ~�߂�
	assert(num >= 0 && num < Game::kButtonNum);

	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_pad);
	// ���O����ŉ�����Ă����Ƃ�
	if (m_isLastHit[num])
	{
		// �����󋵂��t�ɂ��ĕԂ�
		m_isLastHit[num] = m_pad.Buttons[num];
		return !m_isLastHit[num];
	}
	// ���O����ŉ�����Ă��Ȃ���
	else
	{
		// ���݃t���[���ŉ�����Ă��Ȃ����false��
		m_isLastHit[num] = m_pad.Buttons[num];
		// �Ԃ�l�͊֌W�Ȃ�false
		return false;
	}
}
