#pragma once
#include "RandomProvider.h"
#include "EntityGenerator.h"
#include "CustomAlgs.h"
//#include "TemplateTimer.h"
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
		Entity& AchiveEffectivity(double targetEffectivity);
		Entity& SelectBest(mainDataType timeToWait); //returns most successful entity in specific time


		static ChallengeManager* GetChallangeManager();

		//Should be private(public only for tests):
		void GenerateEntities();
		void ClearPopulation();

		enum ChallengeTypes
		{
			Division, Equal, If, Minus, Multiplication, One, Plus
		};

		void SetChallengeType(ChallengeTypes chType);

		#if defined(RedefChallangesCount)
			static const mainDataType ChallangesCount = 500;
		#else
			static const mainDataType ChallangesCount = 6;
		#endif
		static const mainDataType RandomUpperLimit = 10; //max value for random for inputs
		mainDataType _curChallangeType;
		mainDataType _correctAnswers[ChallangesCount][ExternalOutputsCount];
		mainDataType _inputs[ChallangesCount][ExternalInputsCount];/*Generated random inputs for
																   entities testing. Based on 1, not 0 index!*/
		std::vector<Entity*> _goodPopulation;

		void GenerateRandomInputs(); //Filling inputs arrays with random values for all ChallangesCount
		void FillAnswers(); //Filling correct answers for generated random inputs (GenerateRandomInputs() should be called before)
		void SetContactsCount();
		void CalculateEffectiveness();
		mainDataType* GetCorrectAnswersPtr();
		mainDataType* GetInputsPtr();
		Entity& SelectGoodEntity(double targetEffectivity);

	private:
		Entity& ChallengeManager::SelectBestInTime(mainDataType seconds);
		void FillAnswer(mainDataType curChallangeType, mainDataType startChallange, mainDataType curChallangesCount);
		mainDataType _currentLine; //defines place where next real answers will be inserted
		EntityGenerator* _entityGenerator;
		RandomValuesProvider _rvp;
		static ChallengeManager* _chManager;
		//static const unsigned short FirstChangingInput = 1;
		Entity* _bestEntity;
		const double MinEfect = 0.3; //minimal efectivifness to not throw entity away
	};
}
