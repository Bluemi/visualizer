#include "Combinations.hpp"

namespace visualizer
{
	bool inc_indices(std::vector<unsigned int>& indices, const std::vector<unsigned int>& sizes)
	{
		for (int i = indices.size()-1; i >= 0; i--)
		{
			indices[i]++;
			if (indices[i] >= sizes[i])
			{
				indices[i] = 0;
			} else {
				return true;
			}
		}

		return false;
	}

	std::vector<int> get_by_indices(const std::vector<std::vector<int>>& vecvec, const std::vector<unsigned int>& indices)
	{
		std::vector<int> result;
		for (unsigned int i = 0; i < vecvec.size(); i++)
		{
			result.push_back(vecvec[i][indices[i]]);
		}

		return result;
	}

	std::vector<std::vector<int>> get_combinations(const std::vector<std::vector<int>>& vecvec)
	{
		std::vector<std::vector<int>> result;
		std::vector<unsigned int> sizes;
		for (const std::vector<int>& v : vecvec)
		{
			sizes.push_back(v.size());
		}

		std::vector<unsigned int> indices(vecvec.size());

		do
		{
			result.push_back(get_by_indices(vecvec, indices));
		} while(inc_indices(indices, sizes));

		return result;
	}
}
