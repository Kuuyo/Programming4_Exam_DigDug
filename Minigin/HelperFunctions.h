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
	bool EraseRemoveFromVector(std::vector<T> &vector, T objectToRemove)
	{
		const auto size = vector.size();
		vector.erase(std::remove(vector.begin(), vector.end(), objectToRemove), vector.end());

		return size == vector.size();
	}

	class Random
	{
	public:
		static float GetRandomFloat(float min, float max);
	};
}