#ifndef __PERLINNOISE_CLASS__
#define __PERLINNOISE_CLASS__

#include <vector>
#include <random>

#include "Combinations.hpp"

namespace visualizer
{
	class Random
	{
		public:
			Random(unsigned int accuracy=1000)
				 : _dis(-accuracy, accuracy), _accuracy(accuracy)
			{}

			float operator()(const std::vector<int>& seeds)
			{
				int s = 0;
				for (int seed : seeds)
				{
					s += random(seed);
				}

				return random(s) / static_cast<float>(_accuracy);
			}

			float random(int seed)
			{
				_gen.seed(seed);
				return _dis(_gen);
			}

		private:
			std::mt19937 _gen;
			std::uniform_int_distribution<> _dis;
			unsigned int _version;
			unsigned int _accuracy;
	};

	/*
	 * This is not real PerlinNoise but an version which I can implement.
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
				  _amplitude_step(amplitude_step)
			{}

			float operator()(const std::vector<float> seeds)
			{
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
				std::vector<std::vector<int>> indices;
				indices.reserve(seeds.size());
				for (float seed : seeds)
				{
					int bot_index = get_bot_index(seed, interval);

					indices.push_back({bot_index, bot_index+1});
				}

				std::vector<std::vector<int>> combinations = get_combinations(indices);
				std::vector<float> values;

				for (const std::vector<int>& point_in_space : combinations)
				{
					float value = _random_generator(point_in_space);
					values.push_back(value);
				}

				return interpolate(seeds, values);
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
					std::vector<float> inter_values;
					inter_values.reserve(num_new_values);

					for (unsigned int i = 0; i < num_new_values; i++)
					{
						float inter_v = interp(seeds[dim], values[2*i], values[2*i+1]);
						inter_values.push_back(inter_v);
					}

					values = inter_values;
				}

				return values[0];
			}

			int get_bot_index(float seed, float interval)
			{
				return std::floor(seed/interval);
			}

		private:
			Random _random_generator;
			unsigned int _octaves;
			float _interval_start;
			float _amplitude_start;
			float _interval_step;
			float _amplitude_step;
	};
}

#endif
