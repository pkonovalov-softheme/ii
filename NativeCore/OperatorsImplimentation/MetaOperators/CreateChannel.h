#pragma once

#include "ChannelOperator.h"
#include "../Entity.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				class CreateChannel : public ChannelOperator
				{
					/// <summary>
					/// Creates Channel between two Entities
					/// </summary>
				public:
					CreateChannel(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
