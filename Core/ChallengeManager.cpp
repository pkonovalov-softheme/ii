#include "stdafx.h"
#include "ChallengeManager.h"
#include <vector>


namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

	ChallengeManager::ChallengeManager() : _inputs(), _correctAnswers(), _entityGenerator(), _rvp(RandomUpperLimit),
		_curEntityId(0), _currentLine(0), _population(), _goodPopulation()
	{
		_curChallangeType = ChallengeTypes::One;
		_chManager = this;
		_population.reserve(EntitiesStartPopulation);
		srand_sse();
	}

	ChallengeManager::~ChallengeManager()
	{
		ClearPopulation();
	}

	void ChallengeManager::ClearPopulation()
	{
		while (!_population.empty()) {
			delete _population.back();
			_population.pop_back();
		}
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
				case (Division):
					if (sContValue != 0) {
						outValue = fContValue / sContValue;
					}
					break;
				case (Equal):
					outValue = fContValue;
					break;
				case (If):
					if (fContValue > sContValue){
						outValue = 1;}
					else{
						outValue = 0;}
					break;
				case (Minus):
					outValue = fContValue - sContValue;
					break;
				case (Multiplication):
						outValue = fContValue * sContValue;
					break;
				case (One):
					outValue = 1;
					break;
				case (Plus):
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

	//void ChallengeManager::StartSelection()
	//{
	//	GenerateRandomInputs();
	//	FillAnswers();
	//	ClearPopulation();

	//	GenerateEntities();
	//	ProcessEnteties();
	//	CalculateEffectiveness();
	//	std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(_population, 3);
	//}

	Entity* ChallengeManager::AchiveEffectivity(double targetEffectivity)
	{
		GenerateRandomInputs();
		FillAnswers();

		while (true)
		{
			GenerateEntities();
			ProcessEnteties();
			CalculateEffectiveness();
			if (_goodPopulation.size() > 0)
			{
				Entity* targetEntity = CustomAlgs::SelectKth(_goodPopulation, _goodPopulation.size());
				if (targetEntity->GetEffectiveness() >= targetEffectivity) return targetEntity;

				//std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(_goodPopulation, 1);
				/*if (vinners.size() > 0)
				{*/
					//if (vinners[0]->GetEffectiveness() >= targetEffectivity) return vinners[0];
					//_population.push_back(vinners[0]);
				/*}*/
			}

			//now i don't clear _goodPopulation but in future i need to impliment
			ClearPopulation();
		}
	}

	void ChallengeManager::GenerateEntities()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			//Is it ioptimal structure for perfomance?
			_population.push_back(&_entityGenerator.GenerateEntity());
		}
	}

	void ChallengeManager::ProcessEnteties()
	{
		for (_currentLine = 0; _currentLine < ChallangesCount; _currentLine++)
		{
			mainDataType s = _population.size();
			for (_curEntityId = 0; _curEntityId < s; _curEntityId++)
			{
				for (int pr = 0; pr < EntityProcessCount; pr++)
				{
					_population[_curEntityId]->mProcessAll();
				}
			}
		}
	}

	void ChallengeManager::CalculateEffectiveness()
	{
		for (size_t i = 0, s = _population.size(); i < s; i++)
		{
			const unsigned int totalTry = ChallangesCount * EntityProcessCount;
			_population[i]->CalculateEffectiveness(totalTry);
			if (_population[i]->GetEffectiveness() > 0) {
				_goodPopulation.push_back(_population[i]);
			}
			
		}
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}
}
