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
		static mainDataType GetOperTypeContactsCount(OperatorsTypes ot);
		Entity& GetEntity();
	private:
	    RandomValuesProvider* _conProvider;
		Entity _entity;
	};
}

