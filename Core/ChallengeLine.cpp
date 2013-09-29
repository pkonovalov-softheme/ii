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
		for (mainDataType i = 0; i < InputsCount; i++)
		{
			_inputs[_currentLine][i] = RandomProvider::GetNextValue(5);
		}
	}

	void ChallengeLine::GenerateChallenges()
	{
		_challenges = new mainDataType*[challangesCount];
		_correctAnswers = new mainDataType*[_answersCount];

		for (mainDataType i = 0; i < challangesCount; i++)
		{
			_challenges[i] = GenerateRandomInputs();
			FillAnswers(i);
		}
	}

	void ChallengeLine::FillAnswers()
	{
		for (mainDataType i = 0; i < CorrectAnswersCount; i++)
		{
			_correctAnswers[_currentLine][i] = GetCorrectAnswer(i);
		}

		mainDataType answerId = 0;

		for (mainDataType i = 0; i < InputsCount; i++)
		{
			#define fContValue _inputs[_currentLine][i] //value of first contact
			#define sContValue _inputs[_currentLine][i + 1] //value of second contact
			#define tContValue _inputs[_currentLine][i + 2] //value of third contact

			#define outValue _correctAnswers[_currentLine][answerId] //value of third contact

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
	//ChallengeLine& ChallengeLine::GenerateNextChalangesLine(mainDataType challangeType, mainDataType answersCount)
	//{
	//	ChallengeLine* line = new ChallengeLine(challangeType, answersCount);
	//	for (mainDataType i = 0; i < answersCount; i++)
	//	{

	//	}
	//}

}
