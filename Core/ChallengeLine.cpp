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
		case (Zero):
			_inputContactsCount = 0;
			break;
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
		case (Nothing):
			_inputContactsCount = 0;
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
		for (mainDataType i = 0; i < ExternalInputsCount; i++)
		{
			_inputs[_currentLine][i] = RandomProvider::GetNextValue(5);
		}
	}

	void ChallengeLine::FillAnswers()
	{
		for (mainDataType i = 0; i < ExternalInputsCount; i++)
		{
			#define fContValue _inputs[_currentLine][i] //value of first contact
			#define sContValue _inputs[_currentLine][i + 1] //value of second contact
			#define tContValue _inputs[_currentLine][i + 2] //value of third contact

			#define outValue _correctAnswers[_currentLine][_currentLine] //value of third contact

			switch (_challangeType)
			{
			case (Zero):
				outValue = 0;
				break;
			case (Division):
				outValue = fContValue / sContValue;
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
			case (Nothing):
				break;
			default:
				throw "Not implemented";
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

}
