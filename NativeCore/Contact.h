#pragma once

#include "OperatorsImplimentation/Operator.h"

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
		/// <summary>
		/// Represent contact on the base of operator and contact order number
		/// </summary>
		class Contact
		{
		private:
			Operator *const _oper;
			const unsigned long long _contactNumber;
		public:
			Contact(Operator *oper, unsigned long long contactNumber);

			const unsigned long long &getContactNumber() const;

			const Operator &getOper() const;
		};
	}
}
