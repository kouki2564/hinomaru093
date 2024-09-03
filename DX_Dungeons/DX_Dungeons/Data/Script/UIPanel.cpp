#include "UIPanel.h"

UIPanel::UIPanel()
{
}

UIPanel::~UIPanel()
{
}

void UIPanel::Draw()
{
	for (const auto& i : m_UI)
	{
		if (i.isApp)
		{
			DrawExtendGraphF(i.extend_startX, i.extend_startY, i.extend_endX, i.extend_endY, i.handle, true);
		}
	}
}

void UIPanel::MoveUI(int GraphHandle, float extend_startX, float extend_startY, float extend_endX, float extend_endY)
{
	for (auto& i : m_UI)
	{
		if (i.handle == GraphHandle)
		{
			i.extend_startX = extend_startX;
			i.extend_endX = extend_endX;
			i.extend_startY = extend_startY;
			i.extend_endY = extend_endY;
		}
	}
}

void UIPanel::SetUI(int GraphHandle, float extend_startX, float extend_startY, float extend_endX, float extend_endY, bool isApp)
{
	UI temp;
	temp.handle			 = GraphHandle;
	temp.extend_startX	 = extend_startX;
	temp.extend_endX	 = extend_endX;
	temp.extend_startY	 = extend_startY;
	temp.extend_endY	 = extend_endY;
	temp.isApp = isApp;

	m_UI.push_back(temp);
}

void UIPanel::SetIsApp(int GraphHandle, bool isApp)
{
	for (auto& i : m_UI)
	{
		if (i.handle == GraphHandle)
		{
			i.isApp = isApp;
		}
	}
}

void UIPanel::SetAllIsApp(bool isApp)
{
	for (auto& i : m_UI)
	{
		i.isApp = isApp;
	}
}
