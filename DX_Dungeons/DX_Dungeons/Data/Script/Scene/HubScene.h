#pragma once
#include "SceneBase.h"
class HubScene :
    public SceneBase
{
public:
    HubScene();
    ~HubScene();

    void Init();
    void Update();
    void Draw() const;

    // �V�[���������I��点��
    int NextScene();

private:
    int m_backHandle;
    int m_cameraTargetNum;
    VECTOR m_cameraPos[3];
    VECTOR m_cameraTargetPos[3];
};

