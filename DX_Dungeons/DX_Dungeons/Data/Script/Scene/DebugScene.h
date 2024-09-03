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

    // ƒV[ƒ“ˆ—‚ğI‚í‚ç‚¹‚é
    int NextScene();
private:
};

