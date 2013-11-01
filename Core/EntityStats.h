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
		double GetEffectiveness();

	private:
		Entity _id;
		mainDataType _correctAnswersCount;
		double _effectiveness;
	};
}

