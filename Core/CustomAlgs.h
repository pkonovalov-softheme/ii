#pragma once
#include "Entity.h"
#include <vector>

namespace Brans
{
	class CustomAlgs
	{
	private:
		static  Entity* SelectKth(std::vector<Entity*>& arr, mainDataType k,
			mainDataType arrayElementsCount); /*Selects K'th from bottom (lowest)*/
	public:
		static std::vector<Entity*> SelectTopNs(std::vector<Entity*>& arr, mainDataType n, mainDataType arrayElementsCount);
			/* Returns top N positions of the array of int*/
	};
}