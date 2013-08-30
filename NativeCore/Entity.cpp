#include "Entity.h"

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

		Entity::Entity() : _channelsTable(new ChannelsTable()), _operators(new Operators())
		{
		}

		const AI::Core::ChannelsImplimentation::ChannelsTable &Entity::getChannelsTable() const
		{
			return _channelsTable;
		}

		const AI::Core::OperatorsImplimentation::Operators &Entity::getOperators() const
		{
			return _operators;
		}
	}
}
