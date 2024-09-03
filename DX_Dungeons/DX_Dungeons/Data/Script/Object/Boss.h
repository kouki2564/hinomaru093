#pragma once
#include "CharacterBase.h"
class Boss :
    public CharacterBase
{
public:
    Boss();
    ~Boss();

    void Init();
    void Update(VECTOR playerPos);
    void Draw() const;

private:
    void Move();
    void NearAttack();
    void LongAttack(VECTOR toPlayer);
    // void Summon();

private:
    void AnimationUpdate();
    
    int m_moveCoolTimer;
    bool m_isAction;
    VECTOR m_runDir;

    int m_attackCount;
};

