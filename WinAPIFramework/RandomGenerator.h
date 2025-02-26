#pragma once

#include <random>
#include <algorithm>
#include <span>

template<typename C>
concept RandomType = requires(C c)
{
	std::same_as<C, int> | std::same_as<C, float>;
};

class RandomGenerator
{
	DECLARE_SINGLE(RandomGenerator)

public:
	BOOL Initialize()
	{
		return TRUE;
	}

	template <RandomType T>
	T GenerateRandom(T min, T max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		T res = 0;

		if constexpr (std::is_same_v<T, int>)
		{
			std::uniform_int_distribution<T> dis(min, max);
			res = dis(gen);
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			std::uniform_real_distribution<T> dis(min, max);
			res = dis(gen);
		}
		else
		{
			__debugbreak();
		}

		return res;
	}

	COLORREF GenerateRandomColor()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		BYTE rgb[3] = { 0,0,0 };
		for (int i = 0; i < 3; i++)
		{
			std::uniform_int_distribution<int> dis(0, 255);
			rgb[i] = static_cast<BYTE>(dis(gen));
		}

		return RGB(rgb[0], rgb[1], rgb[2]);
	}

	POINT GenerateRandomPoint(int min = 0, int max = 100)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(min, max);

		POINT p;
		p.x = static_cast<LONG>(dis(gen));
		p.y = static_cast<LONG>(dis(gen));

		return p;
	}

	std::vector<int> GenerateRandomIntegerSequence(int min = 0, int max = 100)
	{
		std::vector<int> vec;
		for (int i = min; i <= max; i++)
		{
			vec.push_back(i);
		}

		std::random_device rd;
		std::mt19937 gen(rd());

		std::shuffle(vec.begin(), vec.end(), gen);

		return vec;
	}

};


