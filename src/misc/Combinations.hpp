#ifndef __COMBINATIONS_CLASS__
#define __COMBINATIONS_CLASS__

#include <vector>

namespace visualizer
{
	bool inc_indices(std::vector<unsigned int>& indices, const std::vector<unsigned int>& sizes);
	std::vector<int> get_by_indices(const std::vector<std::vector<int>>& vecvec, const std::vector<unsigned int>& indices);
	std::vector<std::vector<int>> get_combinations(const std::vector<std::pair<int, int>>& vecvec);
}

#endif
