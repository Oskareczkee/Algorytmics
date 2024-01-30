#pragma once
#include <random>

// Class providing simple interface to generate pseudo random numbers
class Random
{
private:
	std::random_device rd;
	std::mt19937 mt;
public:
	Random(): rd(), mt(std::mt19937(rd())){}

	//Generates pseudo random number in range [left,right)
	int Next(const int& left, const int& right)
	{
		if (right <= left)
			return left-1;
		return std::uniform_int_distribution<int>(left, right-1)(rd);
	}

	//Generated pseudo random double in range [left, right]
	double NextDouble(const double& left, const double& right)
	{
		if (right <= left)
			return left;
		return std::uniform_real_distribution<double>(left, right)(rd);
	}

	//rolls a dice, given a chance, if roll was a success returns true, otherwise false
	bool Roll(const double& chance)
	{
		if (chance >= 1) return true;
		else if (chance <= 0) return false;

		double random = std::uniform_real_distribution<double>(0.0, 1.0)(rd);

		if (random < chance) return true;
		else return false;
	}
};


//Static Random generator, provides simple interface to generate pseudo random nubmers
class StaticRandom
{
private:
	static std::random_device rd;
	static std::mt19937 mt;
public:

	//Generates pseudo random number in range [left,right)
	static int Next(const int& left, const int& right)
	{
		if (right <= left)
			return left-1;
		return std::uniform_int_distribution<int>(left, right-1)(rd);
	}

	//Generated pseudo random double in range [left, right]
	static double NextDouble(const double& left, const double& right)
	{
		if (right <= left)
			return left;
		return std::uniform_real_distribution<double>(left, right)(rd);
	}

	//rolls a dice, given a chance, if roll was a success returns true, otherwise false
	static bool Roll(const double& chance)
	{
		if (chance >= 1) return true;
		else if (chance <= 0) return false;

		double random = std::uniform_real_distribution<double>(0.0, 1.0)(rd);

		if (random < chance) return true;
		else return false;
	}
};

std::random_device StaticRandom::rd;
std::mt19937 StaticRandom::mt = std::mt19937(rd());
