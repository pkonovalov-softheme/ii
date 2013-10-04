#pragma once
#include "Entity.h"

namespace Brans 
{
	class EntityGenerator
	{
	public:
		EntityGenerator(mainDataType operatorsCount);
		~EntityGenerator(void);
		Entity& GenerateEntity();
	private:
		RandomValuesProvider* _conProvider;
		mainDataType _operatorsCount;
	};
}

