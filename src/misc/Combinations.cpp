#include "Combinations.hpp"

namespace visualizer
{
	const int NUM_INDICES = 2;

	bool inc_indices(std::vector<unsigned int>& indices)
	{
		for (int i = indices.size()-1; i >= 0; i--)
		{
			indices[i]++;
			if (indices[i] >= NUM_INDICES)
			{
				indices[i] = 0;
			} else {
				return true;
			}
		}

		return false;
	}

	std::vector<int> get_by_indices(const std::vector<std::pair<int, int>>& vecvec, const std::vector<unsigned int>& indices)
	{
		std::vector<int> result;
		for (unsigned int i = 0; i < vecvec.size(); i++)
		{
			if (indices[i] == 0)
				result.push_back(vecvec[i].first);
			else
				result.push_back(vecvec[i].second);
		}

		return result;
	}

	std::vector<std::vector<int>> get_combinations(const std::vector<std::pair<int, int>>& vecvec)
	{
		std::vector<std::vector<int>> result;

		std::vector<unsigned int> indices(vecvec.size());

		do
		{
			result.push_back(get_by_indices(vecvec, indices));
		} while(inc_indices(indices));

		return result;
	}
}
