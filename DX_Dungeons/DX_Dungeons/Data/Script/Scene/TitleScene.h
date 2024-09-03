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

	// シーン処理を終わらせる
	int NextScene();
};

