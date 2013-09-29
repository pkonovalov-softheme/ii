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

		static const mainDataType InputsCount = 10;
		static const mainDataType CorrectAnswersCount = 10;
		static const mainDataType ChallangesCount = 500;
		mainDataType _correctAnswers[ChallangesCount][CorrectAnswersCount];
		mainDataType _inputs[ChallangesCount][InputsCount];
		mainDataType _currentLine;
		void GenerateChallenges();
		ChallengeLine(mainDataType challangeType);
		void GenerateRandomInputs();
		void FillAnswers();
		mainDataType GetCorrectAnswer(mainDataType inputId);
		void SetContactsCount();

	public:
		mainDataType GetChallangeType();
		mainDataType GetAnswersCount(mainDataType challangeType, mainDataType answersCount);
		~ChallengeLine();
	};
}

