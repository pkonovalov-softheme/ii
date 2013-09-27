#pragma once
#include "BransGlobals.h"

namespace Brans
{
	class ChallengeLine
	{

		enum ChallengeTypes
		{
			Zero, Division, Equal, If, Minus, Multiplication, One, Plus, Nothing
		};

	private:
		mainDataType _answersCount;
		mainDataType _challangeType;
		mainDataType* _correctAnswers;
		ChallengeLine(mainDataType challangeType, mainDataType answersCount);
		void GenerateRandomInputs();

	public:
		static ChallengeLine& GenerateNextChalangesLine(mainDataType challangeType, mainDataType answersCount);
		mainDataType GetChallangeType();
		mainDataType GetAnswersCount(mainDataType challangeType, mainDataType answersCount);
		~ChallengeLine();
	};
}

