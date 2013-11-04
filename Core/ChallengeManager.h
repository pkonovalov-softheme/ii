#pragma once
#include "RandomProvider.h"
#include "EntityGenerator.h"
#include "CustomAlgs.h"
//#include "Entity.h"

namespace Brans
{
	class ChallengeManager
	{

	public:
		ChallengeManager();
		//static ChallengeManager& GenerateNextChalangesLine(mainDataType challangeType);
		~ChallengeManager();
		mainDataType GetEntityExternalInput(mainDataType inputId); //return value of the external input for entity
		mainDataType GetCorrectAnswer(mainDataType inputId);
		void StartSelection(); //Start "natural" selection
		Entity* AchiveEffectivity(double targetEffectivity);

		static ChallengeManager* GetChallangeManager();

		//Should be private(public only for tests):
		void GenerateEntities();
		void ClearPopulation();

		enum ChallengeTypes
		{
			Division, Equal, If, Minus, Multiplication, One, Plus
		};

		void SetChallengeType(ChallengeTypes chType);

		mainDataType _currentLine; //defines place where next real answers will be inserted
		mainDataType _curEntityId;

		/*#ifdef RedefChallangesCount
		static const mainDataType ChallangesCount = 500;
		#undef RedefChallangesCount
		#else*/
		static const mainDataType ChallangesCount = 1;
		/*#endif */ 
		static const mainDataType RandomUpperLimit = 10; //max value for random for inputs
		mainDataType _correctAnswers[ChallangesCount][ExternalOutputsCount - 1];
		mainDataType _inputs[ChallangesCount][ExternalInputsCount];/*Generated random inputs for
																   entities testing. Based on 1, not 0 index!*/

		mainDataType _curChallangeType;
		std::vector<Entity*> _population;
		EntityGenerator _entityGenerator;
		void GenerateRandomInputs(); //Filling inputs arrays with random values for all ChallangesCount
		void FillAnswers(); //Filling correct answers for generated random inputs (GenerateRandomInputs() should be called before)
		void SetContactsCount();
		void ProcessEnteties();
		void CalculateEffectiveness();
		RandomValuesProvider _rvp;
		static ChallengeManager* _chManager;
	};
}

