#pragma once
#include <algorithm>

class MathHelper
{
public:
	// Basic math operations
	static float square_root(float val);
	static int absolute_value(const int value);

	// Clamping functions
	static void clamp_int_no_return(int& value, const int& min, const int& max)
	{
		value = (std::max)(min, value);
		value = (std::min)(max, value);
	}

	static int clamp_int(int value, const int& min, const int& max)
	{
		return (std::min)((std::max)(min, value), max);
	}

	static float clamp_float(float value, const float& min, const float& max) 
	{
		return (std::min)((std::max)(min, value), max);
	}

	static float zero_one(float value) 
	{
		return clamp_float(value, 0.0f, 1.0f);
	}

	// Range mapping functions
	static void map_clamp_ranged_int(int& value, const int& old_min, const int& old_max,
		const int& newMin, const int& newMax)
	{
		const float old_range = static_cast<float>(old_max - old_min);
		const float new_range = static_cast<float>(newMax - newMin);
		value = static_cast<int>((((value - old_min) * new_range) / old_range) + newMin);
	}

	static float map_clamp_ranged(const float& value, const float& old_min, const float& old_max,
		const float& new_min, const float& new_max)
	{
		const float old_range = (old_max - old_min);
		const float new_range = (new_max - new_min);
		return (((value - old_min) * new_range) / old_range) + new_min;
	}

	// Random number generation
	static int random_int_in_range(int min, int max);
	static float random_float_in_range(float min, float max) {
		return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}

	// Utility functions
	static void swap_vector_element(int* a, int* b)
	{
		if (a && b) {
			const int temp = *a;
			*a = *b;
			*b = temp;
		}
	}

private:
	// Prevent instantiation
	MathHelper() = delete;
};