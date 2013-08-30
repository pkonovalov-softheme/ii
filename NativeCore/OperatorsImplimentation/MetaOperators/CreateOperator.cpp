#include "CreateOperator.h"
#include "OperatorsImplimentation/BasicOperators/Division.h"
#include "OperatorsImplimentation/BasicOperators/Equal.h"
#include "OperatorsImplimentation/BasicOperators/Minus.h"
#include "OperatorsImplimentation/BasicOperators/Multiplication.h"
#include "OperatorsImplimentation/BasicOperators/One.h"
#include "OperatorsImplimentation/BasicOperators/Plus.h"
#include "OperatorsImplimentation/BasicOperators/Power.h"
#include "OperatorsImplimentation/BasicOperators/RandomNumber.h"
#include "OperatorsImplimentation/BasicOperators/Time.h"
#include "OperatorsImplimentation/MetaOperators/CreateChannel.h"
#include "OperatorsImplimentation/MetaOperators/DeleteChannel.h"
#include "OperatorsImplimentation/MetaOperators/GetTypeOfOperator.h"
#include "OperatorsImplimentation/MetaOperators/IsChannelExists.h"
#include "OperatorsImplimentation/MetaOperators/RemoveOperator.h"
#include "OperatorsImplimentation/MetaOperators/GetOperatorId.h"

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
					return EnterContacts[0]->Value;
				}

				private *CreateOperator::operator CreateOperatorInternal()
				{
					switch (static_cast<OperatorsTypes>(getOperatorTypeToAdd()))
					{
						case (Division):
							return new Division(getThisEntity());
						case (Equal):
							return new Equal(getThisEntity());
						case (Minus):
							return new Minus(getThisEntity());
						case (Multiplication):
							return new Multiplication(getThisEntity());
						case (One):
							return new One(getThisEntity());
						case (Plus):
							return new Plus(getThisEntity());
						case (Power):
							return new Power(getThisEntity());
						case (RandomNumber):
							return new RandomNumber(getThisEntity());
						case (Time):
							return new Time(getThisEntity());
						case (CreateChannel):
							return new CreateChannel(getThisEntity());
						case (CreateOperator):
							return new CreateOperator(getThisEntity());
						case (DeleteChannel):
							return new DeleteChannel(getThisEntity());
						case (GetTypeOfOperator):
							return new GetTypeOfOperator(getThisEntity());
						case (IsChannelExists):
							return new IsChannelExists(getThisEntity());
						case (RemoveOperator):
							return new RemoveOperator(getThisEntity());
						case (GetOperatorId):
							return new GetOperatorId(getThisEntity());
						default:
							return nullptr;
					}
				}
			}
		}
	}
}
