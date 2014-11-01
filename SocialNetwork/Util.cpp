#include "Header.h"

bool isAddEdge(int prob)
{
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(1, 100);
	std::mt19937 engine(rd()); // Mersenne twister MT19937
	int value = distribution(engine);
	//std::cout << "prob value " << value << std::endl;
	if(value <= prob)
	{
		return true;
	}
	else
	{
		return false;
	}
}