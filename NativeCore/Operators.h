#pragma once

#include "Operator.h"
#include <unordered_map>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			/// <summary>
			/// Dictionary collection of Entity Operators
			/// </summary>
			class Operators : public std::unordered_map<unsigned long long, Operator*>
			{
			private:
				unsigned long long _currentId;

				/// <summary>
				/// Returns new unique Operator Id that is used for Operator creation and for Operator adding to Operators dictionary
				/// </summary>
			public:
				unsigned long long GetNewUniqueId();

			private:
				void InitializeInstanceFields();

public:
				Operators()
				{
					InitializeInstanceFields();
				}
			};
		}
	}
}
