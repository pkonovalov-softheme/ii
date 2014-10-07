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
		Entity& GetEntity();
	private:
	    RandomValuesProvider _operatorsConProvider; //Connection providers for the entity internals operators, it generates connection with any entity operator and external inputs
		RandomValuesProvider _externalOutputsConProvider; //Connection providers for the external outputs, it generates connection with any entity operator (and not external inputs)

		Entity _entity;
		void GenerateConnections(mainDataType curOper);
		void CreateChannelIfAppropriate(mainDataType curOper, mainDataType curOperContactId, mainDataType fromOper);

		//0 mean - operators type are compatibile, 1 - incompatible.
		//bool _operatorsIncompatibility[OperatorsTypesCount][OperatorsTypesCount];
	};
}

