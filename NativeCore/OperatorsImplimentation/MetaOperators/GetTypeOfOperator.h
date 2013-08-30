﻿#pragma once

#include "ChannelOperator.h"
#include "../Entity.h"

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

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				class GetTypeOfOperator : public ChannelOperator
				{
				public:
					GetTypeOfOperator(Entity *thisEntity);

					virtual void Action() override;

				private:
					const unsigned long long &getTargetOperatorId() const;
				};
			}
		}
	}
}
