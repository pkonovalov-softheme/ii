#include "stdafx.h"
#include "ChallengeManager.h"
#include <vector>

namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

#if defined(PERFOMANCE_TESTING)
	mainDataType EntetiesToProcessCount = 200000000;
#endif

	ChallengeManager::ChallengeManager() : _inputs(), _correctAnswers(), _rvp(RandomUpperLimit), _currentLine(0), _goodPopulation()
	{
		_curChallangeType = ChallengeTypes::One;
		_chManager = this;
		_entityGenerator = new EntityGenerator();
		srand_sse();
		//_currentLine = 0;
	}

	ChallengeManager::~ChallengeManager()
	{
	   delete (_entityGenerator);
	}

	void ChallengeManager::SetChallengeType(ChallengeTypes chType)
	{
		_curChallangeType = chType;
	}

	void ChallengeManager::GenerateRandomInputs()
	{
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < ExternalInputsCount; i++)
			{
				_inputs[cline][i] = _rvp.GetNextValue();
			}
		}
	}

	void ChallengeManager::FillAnswers()
	{
		static const unsigned short rex = ExternalOutputsCount - 1;

		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < rex;)
			{
				mainDataType nextI = i + 1;
				#define fContValue _inputs[cline][i] //value of first contact
				#define sContValue _inputs[cline][nextI] //value of second contact
				#define outValue _correctAnswers[cline][i] //value of third contact

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
				case (If) :
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
		while (true)
		{
			Entity& ent = _entityGenerator->GenerateEntity();
			for (int pr = 0; pr < EntityProcessCount; pr++) {
				ent.mProcessAll();
			}

			ent.CalculateEffectiveness(EntityProcessCount);
			if (ent.GetEffectiveness() > targetEffectivity) {
				return ent;
			}
		}
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
		//srand_sse();
		//mainDataType res = GetRandom(0, 100);

		GenerateRandomInputs();
		FillAnswers();
		return SelectGoodEntity(targetEffectivity);
		//Here we need to impliment testing with different _currentLine (=different inputs-correct answers)
		//now i don't clear _goodPopulation but in future i need to impliment
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}
}

