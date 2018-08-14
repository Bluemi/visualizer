#ifndef __PERLINNOISE_CLASS__
#define __PERLINNOISE_CLASS__

#include <vector>
#include <stdint.h>
#include <cmath>

// #include "Combinations.hpp"

namespace visualizer
{
	class Random
	{
		public:
			Random(unsigned int accuracy=1000)
				 : _accuracy(accuracy)
			{}

			int make_seed(const std::vector<int>& seeds)
			{
				int seed(0);
				for (int s : seeds)
				{
					seed += s;
				}
				return seed + 1;
			}

			float operator()(const std::vector<int>& seeds)
			{
				int x = make_seed(seeds);
				x ^= x >> 12;
				x ^= x << 25;
				x ^= x >> 27;
				return (static_cast<float>(x % (_accuracy*2+1)) - static_cast<float>(_accuracy)) / static_cast<float>(_accuracy);
			}

		private:
			unsigned int _version;
			unsigned int _accuracy;
	};

	/*
	 * This is not real PerlinNoise but a version which I can implement.
	 */
	class PerlinNoise
	{
		public:
			PerlinNoise(unsigned int octaves=4,
						float interval_start=1.f,
						float amplitude_start=1.f,
						float interval_step=0.5f,
						float amplitude_step=0.5f)
				: _octaves(octaves),
				  _interval_start(interval_start),
				  _amplitude_start(amplitude_start),
				  _interval_step(interval_step),
				  _amplitude_step(amplitude_step),
				  _allocated_dimensions(0)
			{}

			void allocate(unsigned int dimensions)
			{
				if (dimensions != _allocated_dimensions)
				{
					unsigned int two_high_dim = std::pow(2, dimensions);
					_indices.resize(dimensions, {0, 0});
					_values.resize(two_high_dim, 0);
					_inter_values.resize(two_high_dim, 0);
					_combinations.resize(two_high_dim, std::vector<int>(dimensions));

					_allocated_dimensions = dimensions;
				}
			}

			float operator()(const std::vector<float> seeds)
			{
				allocate(seeds.size());

				float interval = _interval_start;
				float amplitude = _amplitude_start;
				float sum = 0.f;
				for (unsigned int octave = 0; octave < _octaves; octave++)
				{
					sum += get_noise(seeds, interval) * amplitude;
					amplitude *= _amplitude_step;
					interval *= _interval_step;
				}

				return sum;
			}

			float get_noise(std::vector<float> seeds, float interval)
			{
				for (unsigned int i = 0; i < seeds.size(); i++)
				{
					int bot_index = get_bot_index(seeds[i], interval);

					_indices[i].first = bot_index;
					_indices[i].second = bot_index+1;
				}

				define_combinations(_indices);

				for (unsigned int i = 0; i < _combinations.size(); i++)
				{
					_values[i] = _random_generator(_combinations[i]);
				}

				return interpolate(seeds, _values);
			}

			float polynom_influence(float x)
			{
				//6x^5−15x^4+10x^3
				return 6.f*std::pow(x, 5) - 15.f*std::pow(x, 4) + 10.f*std::pow(x, 3);
			}

			float interp(float seed, float value1, float value2)
			{
				double int_part(0);
				float influence = polynom_influence(std::modf(seed, &int_part));
				const float res = influence*value2 + (1.f-influence)*value1;
				return res;
			}

			/*
			 * If n is the number of dimensions.
			 * points_in_space contains 2^n vectors with size n.
			 * seeds contains n indices.
			 * values contains 2^n values
			 */
			float interpolate(const std::vector<float>& seeds, std::vector<float> values)
			{
				for (int dim = seeds.size()-1; dim >= 0; dim--)
				{
					const unsigned int num_new_values = std::pow(2, dim);

					for (unsigned int i = 0; i < num_new_values; i++)
					{
						float inter_v = interp(seeds[dim], values[2*i], values[2*i+1]);
						_inter_values[i] = inter_v;
					}

					values = _inter_values;
				}

				return values[0];
			}

			int get_bot_index(float seed, float interval)
			{
				return std::floor(seed/interval);
			}

			const unsigned int NUM_INDICES = 2;

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

			void define_combinations(const std::vector<std::pair<int, int>>& vecvec)
			{
				std::vector<unsigned int> indices(vecvec.size());

				unsigned int i = 0;
				do
				{
					_combinations[i] = get_by_indices(vecvec, indices);
					i++;
				} while(inc_indices(indices));
			}

		private:
			Random _random_generator;
			unsigned int _octaves;
			float _interval_start;
			float _amplitude_start;
			float _interval_step;
			float _amplitude_step;

			unsigned int _allocated_dimensions;
			std::vector<std::pair<int, int>> _indices;
			std::vector<float> _values;
			std::vector<float> _inter_values;
			std::vector<std::vector<int>> _combinations;
	};
}

#endif
