#include "stdafx.h"
#include "ChallengeManager.h"

namespace Brans
{
	ChallengeManager* ChallengeManager::_chManager;

	ChallengeManager::ChallengeManager() : _inputs(), 
		_correctAnswers(), _entityGenerator(), _population(), _rvp(RandomUpperLimit), _curEntityId(0), _currentLine(0)
	{
		_curChallangeType = ChallengeTypes::Plus;
		_chManager = this;
	}

	ChallengeManager::~ChallengeManager()
	{

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

	void ChallengeManager::ReportSuccess()
	{
		EntityStats* es = &_population[_curEntityId];
		es->results[es->curAnswerId]=true;
		es->curAnswerId++;
	}

	void ChallengeManager::ReportFailure()
	{
		EntityStats* es = &_population[_curEntityId];
		es->results[es->curAnswerId]=false;
		es->curAnswerId++;
	}

	void ChallengeManager::StartSelection()
	{
		GenerateRandomInputs();
		FillAnswers();
		GenerateEntities();
		ProcessEnteties();
		CalculateEffectiveness();
		EntityStats vinners = *CustomAlgs::SelectTopNs(_population, 3, EntitiesStartPopulation);

	}

	void ChallengeManager::GenerateEntities()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			//Is it ioptimal structure for perfomance?
			_population[i].id = _entityGenerator.GenerateEntity();
		}
	}

	void ChallengeManager::ProcessEnteties()
	{
		for (_curEntityId = 0; _curEntityId < EntitiesStartPopulation; _curEntityId++)
		{
			for (int pr = 0; pr < EntityProcessCount; pr++)
			{
				_population[_curEntityId].id.mProcessAll();
			}
		}
	}

	void ChallengeManager::CalculateEffectiveness()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			mainDataType sum = 0;
			for (int ca = 0; ca < TotalChallengesCount; ca++)
			{
				sum+=(mainDataType)_population[i].results[ca];
			}

			_population[i].effectiveness = (double)sum/TotalChallengesCount;
		}
	}

	ChallengeManager* ChallengeManager::GetChallangeManager()
	{
		return _chManager;
	}
}
