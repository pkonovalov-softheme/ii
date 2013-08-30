#pragma once

#include "ChannelOperator.h"
#include "../Entity.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				class IsChannelExists : public ChannelOperator
				{
					/// <summary>
					/// Returns "1" if channel between two Entities(with respect to contact number) exists and "0" if not.
					/// </summary>
				public:
					IsChannelExists(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
