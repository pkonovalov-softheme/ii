#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"
#include "../ChannelsImplimentation/Channel.h"

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

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				/// <summary>
				/// Returns Id of operator from witch channel is enter. Value in channel is ignored.
				/// </summary>
				class GetOperatorId : public Operator
				{
				public:
					GetOperatorId(Entity *thisEntity);

					virtual void Action() override;

				private:
					const Channel &getEnterChannel() const;
				};
			}
		}
	}
}
