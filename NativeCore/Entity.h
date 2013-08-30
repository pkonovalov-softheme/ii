#pragma once

#include "ChannelsImplimentation/ChannelsTable.h"
#include "OperatorsImplimentation/Operators.h"

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
using namespace AI::Core::ChannelsImplimentation;
using namespace AI::Core::OperatorsImplimentation;

namespace AI
{
	namespace Core
	{
		/// <summary>
		/// 
		/// </summary>
		class Entity
		{
		private:
			AI::Core::ChannelsImplimentation::ChannelsTable *const _channelsTable;
			AI::Core::OperatorsImplimentation::Operators *const _operators;

		public:
			Entity();

			const AI::Core::ChannelsImplimentation::ChannelsTable &getChannelsTable() const;

			const AI::Core::OperatorsImplimentation::Operators &getOperators() const;
		};
	}
}
