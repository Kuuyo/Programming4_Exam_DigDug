#pragma once
#include <map>

namespace dae
{
	template <class F, class S>
	void RemoveFromMap(std::map<F, S> &map, F objectToRemove)
	{
		if (std::find_if(map.begin(), map.end(),
			[objectToRemove](std::pair<F, S> o)
		{
			return o.first == objectToRemove;
		})
			!= map.end())
		{
			map.erase(objectToRemove);
		}
	}

	template <class T>
	void EraseRemoveFromVector(std::vector<T> &vector, T objectToRemove)
	{
		vector.erase(std::remove(vector.begin(), vector.end(), objectToRemove), vector.end());
	}
}