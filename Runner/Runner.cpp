// Runner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Core\ChallengeManager.h"
using namespace Brans;

int _tmain(int argc, _TCHAR* argv[])
{
	ChallengeManager* cm = new ChallengeManager();
	cm->StartSelection();
	return 0;
}

