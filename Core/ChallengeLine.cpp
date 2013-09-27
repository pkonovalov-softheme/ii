#include "stdafx.h"
#include "ChallengeLine.h"

namespace Brans
{
	ChallengeLine::ChallengeLine(mainDataType challangeType, mainDataType answersCount)
	{
		_correctAnswers = new mainDataType[answersCount];
		_challangeType = challangeType;
	}

	ChallengeLine::~ChallengeLine()
	{

	}

	ChallengeLine& ChallengeLine::GenerateNextChalangesLine(mainDataType challangeType, mainDataType answersCount)
	{
		ChallengeLine* line = new ChallengeLine(challangeType, answersCount);
		for (mainDataType i = 0; i < answersCount; i++)
		{

		}
	}

	void GenerateRandomInputs()
	{

	}
}
