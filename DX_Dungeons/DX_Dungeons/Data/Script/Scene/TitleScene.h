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

	// �V�[���������I��点��
	int NextScene();
};

