#include "stdafx.h"
#include "ChallengeManager.h"

namespace Brans
{
	ChallengeManager::ChallengeManager() : _inputs(), 
		_correctAnswers(), _entityGenerator(), _population()
	{
	}

	void ChallengeManager::SetContactsCount()
	{
		switch (_curChallangeType)
		{
		case (Division):
			_inputContactsCount = 2;
			break;
		case (Equal):
			_inputContactsCount = 1;
			break;
		case (If):
			_inputContactsCount = 2;
			break;
		case (Minus):
			_inputContactsCount = 2;
			break;
		case (Multiplication):
			_inputContactsCount = 2;
			break;
		case (One):
			_inputContactsCount = 0;
			break;
		case (Plus):
			_inputContactsCount = 2;
			break;
			break;
		default:
			throw;
		}
	}

	ChallengeManager::~ChallengeManager()
	{

	}

	void ChallengeManager::GenerateRandomInputs()
	{
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 1; i <= ExternalInputsCount; i++)
			{
				_inputs[cline][i] = RandomValuesProvider::GetNextValue(RandomUpperLimit);
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
					outValue = fContValue / sContValue;
					i = i + 2;
					break;
				case (Equal):
					outValue = fContValue;
					i++;
					break;
				case (If):
					if (fContValue > sContValue){
						outValue = 1;}
					else{
						outValue = 0;}
					i = i + 2;
					break;
				case (Minus):
					outValue = fContValue - sContValue;
					i = i + 2;
					break;
				case (Multiplication):
						outValue = fContValue * sContValue;
						i = i + 2;
					break;
				case (One):
					outValue = 1;
					i++;
					break;
				case (Plus):
					outValue = fContValue + sContValue;
					i = i + 2;
					break;
				default:
					throw "Not implemented";
				}
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
		EntityStats* vinners = CustomAlgs::SelectTopNs(_population, 3, EntitiesStartPopulation);

	}

	void ChallengeManager::GenerateEntities()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			//_population[i].id = &_entityGenerator.GenerateEntity();
		}
	}

	void ChallengeManager::ProcessEnteties()
	{
		for (int i = 0; i < EntitiesStartPopulation; i++)
		{
			for (int pr = 0; pr < EntityProcessCount; pr++)
			{
				//_population[i].id->mProcessAll();
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
}
