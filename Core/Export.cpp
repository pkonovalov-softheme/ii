#include "stdafx.h"
#include "Export.h"

Entity& AchiveEffectivity()
{
	ChallengeManager* cm = new ChallengeManager();
	return cm->AchiveEffectivity(0.01);
}