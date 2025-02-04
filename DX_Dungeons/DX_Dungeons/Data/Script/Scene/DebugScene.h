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

    // シーン処理を終わらせる
    int NextScene();
private:
};

