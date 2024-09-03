#pragma once
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Update();
	void Draw() const;

	// ƒV[ƒ“ˆ—‚ğI‚í‚ç‚¹‚é
	int NextScene();
};

