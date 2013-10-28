#pragma once
#include "Entity.h"

namespace Brans
{
	class EntityStats
	{
	public:
		EntityStats();
		EntityStats(Entity id);
		~EntityStats();
		void AddAnswer(bool result);
		Entity GetEntity();
		void CalculateEffectiveness(mainDataType totalAnswersCount);
		mainDataType GetEffectiveness();
		void SetEntity(Entity id);

	private:
		Entity _id;
		mainDataType _correctAnswersCount;
		double _effectiveness;
	};
}

