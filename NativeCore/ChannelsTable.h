#pragma once

#include "Operator.h"
#include "Channel.h"

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
			class ChannelTableKey
			{
		  public:
			  Operator *const FromOperator;
			  Operator *const ToOperator;
			  ChannelTableKey(Operator *fromOperator, Operator *toOperator);
			};

			class ChannelsTable
			{
			private:
//C# TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, C# to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: private Channel[] _channels;
				Channel *_channels;


			};

		}
	}
}
