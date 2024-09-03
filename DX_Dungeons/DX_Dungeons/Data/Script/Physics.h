#pragma once
#include "DxLib.h"

class Physics
{
public:
	Physics();
	~Physics();

	void gravityMove();
	void collision();

private:
	VECTOR moveVec;
};

