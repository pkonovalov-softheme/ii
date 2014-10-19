#pragma once
#include "..\Core\ChallengeManager.h"

using namespace Brans;

extern "C" {
	__declspec(dllexport) Entity& AchiveEffectivity(double effectivity);
	__declspec(dllexport) mainDataType* GetOperatorsPtr(Entity* ent);
	__declspec(dllexport) mainDataType* GetInputsPtr(ChallengeManager& cm);
	__declspec(dllexport) mainDataType* GetCorrectAnswersPtr(ChallengeManager& cm);
}