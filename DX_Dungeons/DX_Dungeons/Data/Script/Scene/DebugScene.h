#pragma once
#include "SceneBase.h"
class DebugScene :
    public SceneBase
{
public:
    DebugScene();
    ~DebugScene();

    void Init();
    void Update();
    void Draw() const;

    // �V�[���������I��点��
    int NextScene();
private:
};

