#include "Operators.h"
#include "stdafx.h"


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{

			unsigned long long Operators::GetNewUniqueId()
			{
				do
				{
					_currentId++;
				} while (ContainsKey(_currentId));

				return _currentId;
			}

			void Operators::InitializeInstanceFields()
			{
				_currentId = 0;
			}
		}
	}
}
