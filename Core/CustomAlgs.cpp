#include "stdafx.h"
#include "CustomAlgs.h"

namespace Brans
{
	//Quick selection alhorithm. Selects the Kth MINIMAL value from the array according to the Effectiveness
	Entity* CustomAlgs::SelectKth(std::vector<Entity*>& arr, mainDataType k)
	{
		int from = 0, to = arr.size() - 1;

		// if from == to we reached the kth element
		while (from < to) {
			int r = from, w = to;
			double mid = arr[(r + w) / 2]->GetEffectiveness();

			// stop if the reader and writer meets
			while (r < w) {
				if (arr[r]->GetEffectiveness() >= mid) { // put the large values at the end
					Entity* tmp = arr[w];
					arr[w] = arr[r];
					arr[r] = tmp;
					w--;
				} else { // the value is smaller than the pivot, skip
					r++;
				}
			}

			// if we stepped up (r++) we need to step one down
			if (arr[r]->GetEffectiveness() > mid)
				r--;

			// the r pointer is on the end of the first k elements
			if (k <= r) {
				to = r;
			} else {
				from = r + 1;
			}
		}

		return arr[k];
	}

	//Returns vector n elements of the Entity
	std::vector<Entity*> CustomAlgs::SelectTopNs(std::vector<Entity*>& arr, mainDataType n)
	{
		std::vector<Entity*> retAr;
		retAr.reserve(n);

		Entity* targetEntity = SelectKth(arr, arr.size() - n);

		for (Entity* & ent : arr) {
			if (ent->GetEffectiveness() >= targetEntity->GetEffectiveness()) {
				retAr.push_back(ent);
				if (retAr.size() == n) return retAr;
			}
		}

		return retAr;
	}
}