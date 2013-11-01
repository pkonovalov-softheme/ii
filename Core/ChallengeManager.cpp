#include "stdafx.h"
#include "ChallengeManager.h"
#include <vector>

namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

	ChallengeManager::ChallengeManager() : _inputs(), 
		_correctAnswers(), _entityGenerator(), _rvp(RandomUpperLimit), _curEntityId(0), _currentLine(0), _population()
	{
		_curChallangeType = ChallengeTypes::Plus;
		_chManager = this;
		_population.reserve(EntitiesStartPopulation);
	}

	ChallengeManager::~ChallengeManager()
	{
		while (!_population.empty()) {
			delete &_population.back();
			_population.pop_back();
		}
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
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < ExternalInputsCount;)
			{
				#define fContValue _inputs[cline][i] //value of first contact
				#define sContValue _inputs[cline][i + 1] //value of second contact
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
				i++;
			}
		}
	}

	//ChallengeManager& ChallengeManager::GenerateNextChalangesLine(mainDataType challangeType)
	//{
	//	ChallengeManager* cm = new ChallengeManager(challangeType);
	//	cm->GenerateRandomInputs();
	//	cm->FillAnswers();
	//	return *cm;
	//}

	mainDataType ChallengeManager::GetEntityExternalInput(mainDataType inputId)
	{
		return _inputs[_currentLine][inputId];
	}

	mainDataType ChallengeManager::GetCorrectAnswer(mainDataType inputId)
	{
		return _correctAnswers[_currentLine][inputId];
	}

	void ChallengeManager::StartSelection()
	{
		GenerateRandomInputs();
		FillAnswers();
		GenerateEntities();
		ProcessEnteties();
		CalculateEffectiveness();
		std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(_population, 3, EntitiesStartPopulation);
	}

	void ChallengeManager::GenerateEntities()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			//Is it ioptimal structure for perfomance?
			_population.push_back(new Entity(_entityGenerator.GenerateEntity()));
		}
	}

	void ChallengeManager::ProcessEnteties()
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

	void ChallengeManager::CalculateEffectiveness()
	{
		for (size_t i = 0, s = _population.size(); i < s; i++)
		{
			_population[i]->CalculateEffectiveness(EntityProcessCount);
		}
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}
}
