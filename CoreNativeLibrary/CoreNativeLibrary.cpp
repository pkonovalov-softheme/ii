// CoreNativeLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Header.h"

Entity& AchiveEffectivity()
{
	ChallengeManager* cm = new ChallengeManager();
	return cm->AchiveEffectivity(0.01);
}