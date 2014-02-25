// CoreNativeLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Header.h"

ChallengeManager& CreateChallengeManager()
{
	return *(new ChallengeManager());
}

Entity& AchiveEffectivity(ChallengeManager& cm)
{
	return cm.AchiveEffectivity(0.01);
}

mainDataType* GetOperatorsPtr(Entity* ent)
{
	return ent->GetOperatorsPtr();
}

mainDataType* GetInputsPtr(ChallengeManager& cm)
{
	return cm.GetInputsPtr();
}

mainDataType* GetCorrectAnswersPtr(ChallengeManager& cm)
{
	return cm.GetCorrectAnswersPtr();
}