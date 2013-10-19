#pragma once
#include "Entity.h"

namespace Brans 
{
	class EntityGenerator
	{
	public:
		EntityGenerator();
		~EntityGenerator(void);
		Entity& GenerateEntity();
	private:
	    RandomValuesProvider* _conProvider;
		static mainDataType GetOperTypeContactsCount(OperatorsTypes ot);
	};
}

