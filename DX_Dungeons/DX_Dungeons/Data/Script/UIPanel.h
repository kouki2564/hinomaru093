#pragma once
#include <vector>
#include "DxLib.h"

struct UI
{
	int handle;
	float extend_startX;
	float extend_endX;
	float extend_startY;
	float extend_endY;
	bool isApp;
};

class UIPanel
{
public:
	UIPanel();
	~UIPanel();

	void Draw();

	void MoveUI(int GraphHandle, float extend_startX, float extend_startY, float extend_endX, float extend_endY);
	void SetUI(int GraphHandle, float extend_startX, float extend_startY, float extend_endX, float extend_endY, bool isApp);
	void SetIsApp(int GraphHandle, bool isApp);
	void SetAllIsApp(bool isApp);
private:
	std::vector<UI> m_UI;
};

