#pragma once
#include "DxLib.h"
#include <memory>

class SkillBase :
	public std::enable_shared_from_this<SkillBase>
{
public:
	// 技の発生
	virtual void Start() = 0;
	// 技の途中停止
	virtual void Cancel() = 0;
	// 次の技への派生
	virtual void Conect() = 0;

protected:
	// 技の動作
	virtual void Update() = 0;

	// 技の発生地点
	VECTOR m_appPos;
	// 技再使用可能までのクールタイム
	int m_coolTimer;
};

