#pragma once
#include "RandomProvider.h"
#include "EntityGenerator.h"
#include "CustomAlgs.h"
//#include "Entity.h"

namespace Brans
{
	class ChallengeManager
	{
		enum ChallengeTypes
		{
			Division, Equal, If, Minus, Multiplication, One, Plus
		};


	public:
		ChallengeManager();
		//static ChallengeManager& GenerateNextChalangesLine(mainDataType challangeType);
		~ChallengeManager();
		mainDataType GetEntityExternalInput(mainDataType inputId); //return value of the external input for entity
		mainDataType GetCorrectAnswer(mainDataType inputId);
		void ReportSuccess(); //Entity reports that current answers were correct
		void ReportFailure(); //Entity reports that current answers were incorrect
		void StartSelection(); //Start "natural" selection

		void GenerateEntities();

		//Should be private(public only for tests):
		mainDataType _inputContactsCount;
		mainDataType _currentLine; //defines place where next real answers will be inserted
		mainDataType _curEntityId;

		static const mainDataType ChallangesCount = 500;
		static const mainDataType RandomUpperLimit = 10; //max value for random for inputs
		mainDataType _correctAnswers[ChallangesCount][ExternalOutputsCount];
		mainDataType _inputs[ChallangesCount][ExternalInputsCount];/*Generated random inputs for
																   entities testing. Based on 1, not 0 index!*/

		mainDataType _curChallangeType;
		EntityStats _population[EntitiesStartPopulation];
		EntityGenerator _entityGenerator;
		void GenerateRandomInputs(); //Filling inputs arrays with random values for all ChallangesCount
		void FillAnswers(); //Filling correct answers for generated random inputs (GenerateRandomInputs() should be called before)
		void SetContactsCount();
		void ProcessEnteties();
		void CalculateEffectiveness();
		RandomValuesProvider _rvp;
	};
}

