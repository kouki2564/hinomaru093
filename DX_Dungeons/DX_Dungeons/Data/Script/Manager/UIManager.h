#pragma once
#include "DxLib.h"
#include <vector>
#include "UIPanel.h"

class UIManager
{
public:
	UIManager();
	~UIManager();

	void Draw() const;

	void SetUIPanel(UIPanel& ui);

private:
	std::vector<UIPanel> m_UIs;
};

