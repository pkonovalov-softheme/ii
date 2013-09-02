#include "CreateOperator.h"
#include "Division.h"
#include "Equal.h"
#include "Minus.h"
#include "Multiplication.h"
#include "One.h"
#include "Plus.h"
#include "Power.h"
#include "RandomNumber.h"
#include "Time.h"
#include "CreateChannel.h"
#include "DeleteChannel.h"
#include "GetTypeOfOperator.h"
#include "IsChannelExists.h"
#include "RemoveOperator.h"
#include "GetOperatorId.h"
#include "stdafx.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading::Tasks;
using namespace AI::Core::OperatorsImplimentation::BasicOperators;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				CreateOperator::CreateOperator(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(1);
				}

				void CreateOperator::Action()
				{
					Operator *oper = CreateOperatorInternal();
					//oper.OperatorType = OperatorTypeToAdd;
					getThisEntity()->getOperators()->insert(make_pair(oper->Id, CreateOperatorInternal()));
					ExitContacts->SetValue(oper->Id);
				}

				const unsigned long long &CreateOperator::getOperatorTypeToAdd() const
				{
					Channel * chan =  EnterContacts[0];

					return EnterContacts[0]->Value;
				}

				Operator * CreateOperatorInternal()
				{
					switch (static_cast<OperatorsTypes>(getOperatorTypeToAdd()))
					{
					case (OperatorsTypes::Division):
							return new Division(getThisEntity());
						case (OperatorsTypes::Equal):
							return new Equal(getThisEntity());
						case (OperatorsTypes::Minus):
							return new Minus(getThisEntity());
						case (OperatorsTypes::Multiplication):
							return new Multiplication(getThisEntity());
						case (OperatorsTypes::One):
							return new One(getThisEntity());
						case (OperatorsTypes::Plus):
							return new Plus(getThisEntity());
						case (OperatorsTypes::Power):
							return new Power(getThisEntity());
						case (OperatorsTypes::RandomNumber):
							return new RandomNumber(getThisEntity());
						case (OperatorsTypes::Time):
							return new Time(getThisEntity());
						case (OperatorsTypes::CreateChannel):
							return new CreateChannel(getThisEntity());
						case (OperatorsTypes::CreateOperator):
							return new CreateOperator(getThisEntity());
						case (OperatorsTypes::DeleteChannel):
							return new DeleteChannel(getThisEntity());
						case (OperatorsTypes::GetTypeOfOperator):
							return new GetTypeOfOperator(getThisEntity());
						case (OperatorsTypes::IsChannelExists):
							return new IsChannelExists(getThisEntity());
						case (OperatorsTypes::RemoveOperator):
							return new RemoveOperator(getThisEntity());
						case (OperatorsTypes::GetOperatorId):
							return new GetOperatorId(getThisEntity());
						default:
							return nullptr;
					}
				}
			}
		}
	}
}
