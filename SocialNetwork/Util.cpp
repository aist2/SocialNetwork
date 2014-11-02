#include "Util.h"

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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::tuple<int,int,int> createTriangleNode (int i1, int i2, int i3) {
	if (i1 > i2)
		std::swap(i1, i2); //now a can't be the highest and b not the lowest, so: a: 1|2  b: 2|3  c: 1|2|3
	if (i2 > i3)
		std::swap(i2, i3); //now b can't be the highest and c not the lowest, so: a: 1|2  b: 1|2  c: 3 (sole remaining candidate)
	if (i1 > i2)
		std::swap(i1, i2);
	std::tuple<int, int, int> result(i1, i2, i3);
	return result;
}


