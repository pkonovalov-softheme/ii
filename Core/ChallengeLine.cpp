#include "stdafx.h"
#include "ChallengeLine.h"

namespace Brans
{
	ChallengeLine::ChallengeLine(mainDataType challangeType) : _inputs(), _correctAnswers()
	{
		_challangeType = challangeType;
		SetContactsCount();
	}

	void ChallengeLine::SetContactsCount()
	{
		switch (_challangeType)
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

	ChallengeLine::~ChallengeLine()
	{

	}

	void ChallengeLine::GenerateRandomInputs()
	{
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < ExternalInputsCount; i++)
			{
				_inputs[cline][i] = RandomValuesProvider::GetNextValue(RandomUpperLimit);
			}
		}
	}

	void ChallengeLine::FillAnswers()
	{
		for (mainDataType cline = 0; cline < ChallangesCount; cline++)
		{
			for (mainDataType i = 0; i < ExternalInputsCount;)
			{
				#define fContValue _inputs[cline][i] //value of first contact
				#define sContValue _inputs[cline][i + 1] //value of second contact
				#define outValue _correctAnswers[cline][i] //value of third contact

				switch (_challangeType)
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

	ChallengeLine& ChallengeLine::GenerateNextChalangesLine(mainDataType challangeType)
	{
		ChallengeLine* chline = new ChallengeLine(challangeType);
		chline->GenerateRandomInputs();
		chline->FillAnswers();
		return *chline;
	}

	mainDataType ChallengeLine::GetEntityExternalInput(mainDataType inputId)
	{
		return _inputs[_currentLine][inputId];
	}

	void ChallengeLine::SetEntityAnswer(mainDataType outputId, mainDataType value)
	{
		_inputs[_currentLine][outputId] = value;
	}

	void ChallengeLine::NextChallengeLine()
	{
		_currentLine++;
	}


}
