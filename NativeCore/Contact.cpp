#include "Contact.h"
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
using namespace AI::Core::OperatorsImplimentation;
namespace AI
{
	namespace Core
	{

		Contact::Contact(Operator *oper, unsigned long long contactNumber) : _oper(oper), _contactNumber(contactNumber)
		{
		}

		const unsigned long long &Contact::getContactNumber() const
		{
			return _contactNumber;
		}

		const AI::Core::OperatorsImplimentation::Operator &Contact::getOper() const
		{
			return _oper;
		}
	}
}
