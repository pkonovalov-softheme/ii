#pragma once
#include "BransGlobals.h"
#include "RandomProvider.h"

namespace Brans
{
	class ChallengeLine
	{
		enum ChallengeTypes
		{
			Division, Equal, If, Minus, Multiplication, One, Plus
		};

	private:
		mainDataType _challangeType;
		mainDataType _inputContactsCount;
		mainDataType _currentLine; //defines place where next real answers will be inserted

		static const mainDataType ChallangesCount = 500;
		static const mainDataType RandomUpperLimit = 10; //max value for random's for inputs
		mainDataType _correctAnswers[ChallangesCount][ExternalOutputsCount];
		mainDataType _realAnswers[ChallangesCount][ExternalOutputsCount];
		mainDataType _inputs[ChallangesCount][ExternalInputsCount];
		ChallengeLine(mainDataType challangeType);
		void GenerateRandomInputs(); //Filling inputs arrays with random values for all ChallangesCount
		void FillAnswers(); //Filling correct answers for generated random inputs (GenerateRandomInputs() should be called before)
		mainDataType GetCorrectAnswer(mainDataType inputId);
		void SetContactsCount();

	public:
		ChallengeLine& ChallengeLine::GenerateNextChalangesLine(mainDataType challangeType);
		~ChallengeLine();
		mainDataType GetEntityExternalInput(mainDataType inputId); //return value of the external input for entity
		void SetEntityAnswer(mainDataType outputId, mainDataType value); //records answer of entity
		void NextChallengeLine();
	};
}

