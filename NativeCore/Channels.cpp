#include "Channels.h"
#include "stdafx.h"
#include "stdafx.h"

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

			Channels::Channels(int capacity)
			{
				//this. = Enumerable.Repeat((Channel)null, capacity).ToList();
				for (int i = 0; i < capacity; i++)
				{
					Add(nullptr);
				}
			}

			void Channels::SetValue(unsigned long long value)
			{
				for (auto currentChannel : this)
				{
					currentChannel->Value = value;
				}
			}

			AI::Core::ChannelsImplimentation::Channel &Channels::operator [](unsigned long long index)
			{
				return this->operator[](static_cast<int>(index));
			}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//			void Channels::setdefault(const unsigned long long &index, Channel *value)
//			{
//				this->operator[](safe_cast<int>(index)) = value;
//			}
		}
	}
}
