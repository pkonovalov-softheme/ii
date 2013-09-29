#pragma once
#include "BransGlobals.h"
#include "RandomProvider.h"

namespace Brans
{
	class ChallengeLine
	{
		enum ChallengeTypes
		{
			Zero, Division, Equal, If, Minus, Multiplication, One, Plus, Nothing
		};

	private:
		mainDataType _challangeType;
		mainDataType _inputContactsCount;

		static const mainDataType ChallangesCount = 500;
		mainDataType _correctAnswers[ChallangesCount][ExternalOutputsCount];
		mainDataType _inputs[ChallangesCount][ExternalInputsCount];
		mainDataType _currentLine;
		ChallengeLine(mainDataType challangeType);
		void GenerateRandomInputs();
		void FillAnswers();
		mainDataType GetCorrectAnswer(mainDataType inputId);
		void SetContactsCount();

	public:
		ChallengeLine& ChallengeLine::GenerateNextChalangesLine(mainDataType challangeType);
		mainDataType GetChallangeType();
		mainDataType GetAnswersCount(mainDataType challangeType, mainDataType answersCount);
		void AddAnswer();
		~ChallengeLine();
	};
}

