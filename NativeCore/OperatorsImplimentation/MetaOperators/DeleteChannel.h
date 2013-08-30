#pragma once

#include "ChannelOperator.h"
#include "../Entity.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				class DeleteChannel : public ChannelOperator
				{
					/// <summary>
					/// Delete Channel
					/// </summary>
				public:
					DeleteChannel(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
