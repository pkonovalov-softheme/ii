// CoreNativeLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Header.h"

Entity& AchiveEffectivity()
{
	ChallengeManager* cm = new ChallengeManager(); //Leak!
	Entity& targetEntity = cm->AchiveEffectivity(0.99);
	return targetEntity;
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