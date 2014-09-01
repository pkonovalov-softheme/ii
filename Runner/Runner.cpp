// Runner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "..\Core\ChallengeManager.h"
using namespace Brans;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Searhing for entity..." << endl;
	ChallengeManager* cm = new ChallengeManager();
	//Entity& ent = cm->AchiveEffectivity(0.99);
	Entity& ent = cm->SelectBest(30);
	cout << "Entity was founded successfuly!" << endl;
	delete (cm);
	return 0;
}

