#include "ChannelsTable.h"
#include "stdafx.h"
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
		namespace ChannelsImplimentation
		{

			ChannelTableKey::ChannelTableKey(Operator *fromOperator, Operator *toOperator) : FromOperator(fromOperator), ToOperator(toOperator)
			{
			}
		}
	}
}
