#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Draw()const
{
	for (auto i : m_UIs)
	{
		i.Draw();
	}
}

void UIManager::SetUIPanel(UIPanel& ui)
{
	m_UIs.push_back(ui);
}
