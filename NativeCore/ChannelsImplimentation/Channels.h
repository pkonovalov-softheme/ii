#pragma once

#include "Channel.h"
#include <vector>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Data;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;

namespace AI
{
	namespace Core
	{
		namespace ChannelsImplimentation
		{
			class Channels final : public std::vector<Channel*>
			{
			public:
				Channels(int capacity);

				/// <summary>
				/// Setting up values for all channels
				/// </summary>
				void SetValue(unsigned long long value);

				/// <summary>
				/// Index with ulong instead of int
				/// </summary>
				Channel &operator [](unsigned long long index);
			};
		}
	}
}
