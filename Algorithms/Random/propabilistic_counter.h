#pragma once
#include "random.h"


/// <summary>
/// Robert Morris propabilistic counter implementation
/// Allows for change of base, default is base=2
/// </summary>
class PropabilisticCounter
{
private:
	int _base = 2;
	int _counter = 0;
public:
	PropabilisticCounter() : _base(2), _counter(0) {}

	PropabilisticCounter(const int& base)
	{
		if (base>=2)
			_base = base;
	}

	//constructor with initial base and initial counter value
	PropabilisticCounter(const int& base, const int& counter)
	{
		if (base>=2)
			_base = base;
		if (counter >= 0)
			_counter = counter;
	}

	int GetBase() { return _base; }
	int GetCounter() { return _counter; }

	//increments the counter with the propability of 1/base^counter
	void Increment()
	{
		if (StaticRandom::Roll(1 / pow(_base, _counter)))
			_counter++;
	}

	//returns approximated value
	long long Approximation()
	{
		return pow(_base, _counter);
	}

	//returns expcted value
	long long Expected()
	{
		return pow(_base, _counter + 1) - _base;
	}
};
