#pragma once
#include "..\Core\ChallengeManager.h"

using namespace Brans;

extern "C" {
	__declspec(dllexport) Entity& AchiveEffectivity();
	__declspec(dllexport) mainDataType* GetOperatorsPtr(Entity* ent);
}