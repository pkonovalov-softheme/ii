#pragma once
#include "EntityStats.h"

namespace Brans
{
	class CustomAlgs
	{
	private:
		static  EntityStats SelectKth(EntityStats* arr, mainDataType k, 
			mainDataType arrayElementsCount); /*Selects K'th from bottom (lowest)*/
	public:
		static EntityStats* SelectTopNs(EntityStats* arr, mainDataType n, mainDataType arrayElementsCount);
			/* Returns top N positions of the array of int*/
	};
}