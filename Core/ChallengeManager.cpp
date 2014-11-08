#include "stdafx.h"
#include "ChallengeManager.h"
#include <vector>
#include <assert.h> 

namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

#if defined(PERFOMANCE_TESTING)
	mainDataType EntetiesToProcessCount = 200000000;
#endif

	ChallengeManager::ChallengeManager() : _inputs(), _correctAnswers(), _rvp(RandomUpperLimit), _currentLine(0), _goodPopulation()
	{
		_bestEntity = new Entity();
		_chManager = this;
		_entityGenerator = new EntityGenerator();
	}

	ChallengeManager::~ChallengeManager()
	{
	   delete(_entityGenerator);
	   delete(_bestEntity);
	}

	void ChallengeManager::SetChallengeType(ChallengeTypes chType)
	{
		_curChallangeType = chType;
	}

	void ChallengeManager::GenerateRandomInputs()
	{
		GenerateRandomInputs(0, ChallangesCount);
	}

	void ChallengeManager::GenerateRandomInputs(mainDataType startChallange, mainDataType curChallangesCount)
	{
		for (mainDataType cline = startChallange; cline < curChallangesCount; cline++)
		{
			_inputs[cline][0] = _curChallangeType; //Setting up challenge type in zero contact 

			for (mainDataType i = Entity::FirstContact; i < ExternalInputsCount; i++)
			{
				_inputs[cline][i] = _rvp.GetNextValue();
			}
		}
	}

	void ChallengeManager::FillAnswers()
	{
		FillAnswer(0, ChallangesCount);
	}

	void ChallengeManager::FillMixedAnswersAndInputs()
	{
		_chManager->SetChallengeType(Plus);
		GenerateRandomInputs(0, ChallangesCount / 2);
		FillAnswer(0, ChallangesCount / 2);
		_chManager->SetChallengeType(Multiplication);
		GenerateRandomInputs(ChallangesCount / 2, ChallangesCount);
		FillAnswer(ChallangesCount / 2, ChallangesCount);
	}

	void ChallengeManager::FillAnswer(mainDataType startChallange, mainDataType curChallangesCount)
	{
		for (mainDataType cline = startChallange; cline < curChallangesCount; cline++)
		{
			mainDataType nextI; //just for perf optimization, ToDo: test
			mainDataType prevI; //just for perf optimization, ToDo: test

			for (mainDataType i = Entity::FirstContact; i <= ExternalOutputsCount;)
			{
				nextI = i + 1;
				prevI = i - 1;
#define fContValue _inputs[cline][i] //value of first contact
#define sContValue _inputs[cline][nextI] //value of second contact
#define outValue _correctAnswers[cline][prevI] //value of third contact

				switch (_curChallangeType)
				{
				case (Division) :
					if (sContValue != 0) {
						outValue = fContValue / sContValue;
					}
					break;
				case (Equal) :
					outValue = fContValue;
					break;
				case (If) : //ToDo:Fix
					if (fContValue > sContValue){
						outValue = 1;
					}
					else{
						outValue = 0;
					}
					break;
				case (Minus) :
					outValue = fContValue - sContValue;
					break;
				case (Multiplication) :
					outValue = fContValue * sContValue;
					break;
				case (One) :
					outValue = 1;
					break;
				case (Plus) :
					outValue = fContValue + sContValue;
					break;
				default:
					throw L"Not implemented";
				}
				i = nextI;
			}
		}

	}

	mainDataType ChallengeManager::GetEntityExternalInput(mainDataType inputId)
	{
		return _inputs[_currentLine][inputId];
	}

	mainDataType ChallengeManager::GetCorrectAnswer(mainDataType inputId)
	{
		return _correctAnswers[_currentLine][inputId];
	}

	Entity& ChallengeManager::SelectGoodEntity(double targetEffectivity)
	{
		static ULONGLONG stat[EntityOperatorsCount][OperatorsTypesCount] = {};
		static ULONGLONG stat2[OperatorsTypesCount] = {};
		static ULONGLONG stat3[99] = {};
		static int prevOper = 0;

		Entity ent0;
		ent0.mCreateOperator(OperatorsTypes::Plus);
		const int PlusId = ent0.GetOperatorsCount();
		ent0.mCreateOperator(OperatorsTypes::Multiplication);
		const int MultId = ent0.GetOperatorsCount();
		ent0.mCreateOperator(OperatorsTypes::One); // returns really 6, not 1!
		const int OneId = ent0.GetOperatorsCount();
		ent0.mCreateOperator(OperatorsTypes::If);
		const int IfId = ent0.GetOperatorsCount();

		int const firstValueInput = Entity::FirstExtInputPos + Entity::FirstExternalValueInput;
		ent0.mCreateChannel(firstValueInput, IfId, Entity::FirstContact);
		ent0.mCreateChannel(OneId, IfId, Entity::SecondContact);
		ent0.mCreateChannel(PlusId, IfId, Entity::ThirdContact);
		ent0.mCreateChannel(MultId, IfId, Entity::FourthContact);
		ent0.mCreateChannel(IfId, Entity::FirstExtOutputPos, Entity::FirstContact);

		ent0.mCreateChannel(firstValueInput, MultId, Entity::FirstContact);
		ent0.mCreateChannel(firstValueInput + 1, MultId, Entity::SecondContact);

		ent0.mCreateChannel(firstValueInput, PlusId, Entity::FirstContact);
		ent0.mCreateChannel(firstValueInput + 1, PlusId, Entity::SecondContact);

		while (true)
		{
			Entity& ent = _entityGenerator->GenerateEntity();

			for (int operId = Entity::FirstInternalOper; operId < EntityOperatorsCount; ++operId)
			{
				int curOper = ent.GetContactValue(operId, 0);
				stat2[curOper]++;
				stat[operId][curOper]++;
				stat3[(prevOper * 10) + curOper]++;
				prevOper = curOper;
			}

			if (ent0.IsEqual(&ent))
			{
				int one = 1;
			}

			for (; _currentLine < ChallangesCount; _currentLine++)
			{
				for (int pr = 0; pr < EntityProcessCount; pr++) {
					ent.mProcessAll();
				}

				ent.CalculateEffectiveness(EntityProcessCount * (_currentLine + 1)); //_currentLine starts from 0
				if (ent.GetEffectiveness() < targetEffectivity) {
					break;
				}
			}

			if (ent.GetEffectiveness() >= targetEffectivity) {
				return ent;
			}

			_currentLine = 0;
		}
	}

	Entity& ChallengeManager::SelectBestInTime(mainDataType seconds)
	{
		for (mainDataType startTime = time(NULL); time(NULL) - startTime < seconds;)
		{
			Entity& ent = _entityGenerator->GenerateEntity();

			for (; _currentLine < ChallangesCount; _currentLine++)
			{
				for (int pr = 0; pr < EntityProcessCount; pr++) {
					ent.mProcessAll();
				}

				ent.CalculateEffectiveness(EntityProcessCount * (_currentLine + 1)); //_currentLine starts from 0
				if (ent.GetEffectiveness() < MinEfect){
					break;
				}
			}

			if (ent.GetEffectiveness() > _bestEntity->GetEffectiveness()) {
				_bestEntity = &Entity(ent);
			}

			_currentLine = 0;
		}

		return *_bestEntity;
	}

	//bool ChallengeManager::SelectGoodEnteties(double targetEffectivity)
	//{
	//	for (size_t i = 0; i < EntitiesStartPopulation; i++)
	//	{
	//		Entity& ent = _entityGenerator->GenerateEntity();
	//		for (int pr = 0; pr < EntityProcessCount; pr++) {
	//			ent.mProcessAll();
	//		}

	//		const unsigned int totalTry = ChallangesCount * EntityProcessCount;
	//		ent.CalculateEffectiveness(totalTry);
	//		ent.CalculateEffectiveness(EntityProcessCount);
	//		if (ent.GetEffectiveness() > 0) {
	//			_goodPopulation.push_back(new Entity(ent));
	//			if (ent.GetEffectiveness() > targetEffectivity)
	//			{
	//				return true;
	//			}
	//		}
	//	}

	//	return false;
	//}

	//Entity* ChallengeManager::AchiveEffectivity(double targetEffectivity)
	//{
	//	GenerateRandomInputs();
	//	FillAnswers();

	//	while (true)
	//	{
	//		if (SelectGoodEntity(targetEffectivity)) {
	//			return _goodPopulation[_goodPopulation.size() - 1];
	//		}

	//		#if defined(PERFOMANCE_TESTING)
	//			if (EntetiesProcessed >= EntetiesToProcessCount) return NULL;
	//		#endif

	//		//Here we need to impliment testing with different _currentLine (=different inputs-correct answers)
	//		//now i don't clear _goodPopulation but in future i need to impliment
	//	}
	//}

	Entity& ChallengeManager::AchiveEffectivity(double targetEffectivity)
	{
		FillMixedAnswersAndInputs();
		//FillAnswers();
		Entity& targetEntity = SelectGoodEntity(targetEffectivity);
		return targetEntity;
		//Here we need to impliment testing with different _currentLine (=different inputs-correct answers)
		//now i don't clear _goodPopulation but in future i need to impliment
	}
	

	Entity& ChallengeManager::SelectBest(mainDataType timeToWait) //returns most successful entity in specific time
	{
		GenerateRandomInputs();
		FillAnswers();
		return SelectBestInTime(timeToWait);
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}

	mainDataType* ChallengeManager::GetCorrectAnswersPtr()
	{
		return *_correctAnswers;
	}

	mainDataType* ChallengeManager::GetInputsPtr()
	{
		return *_inputs;
	}
}

