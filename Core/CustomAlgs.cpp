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

	//Returns vector's top n elements(by the Effectivity) or zero if Effectivity not bigger then zero.
	std::vector<Entity*> CustomAlgs::SelectTopNs(std::vector<Entity*>& arr, mainDataType n)
	{
		std::vector<Entity*> retAr;
		Entity* targetEntity = SelectKth(arr, arr.size() - n);
		retAr.reserve(n);
		mainDataType size = arr.size();

		for (mainDataType i = 0; i < size; i++) 
		{
			if (arr[i]->GetEffectiveness() >= targetEntity->GetEffectiveness()) {
				retAr.push_back(arr[i]);
				arr[i] = nullptr; //Because later all vector's elements will be deleted
				if (retAr.size() == n) return retAr;
			}
		}

		return retAr;
	}
}