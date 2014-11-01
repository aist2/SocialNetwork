#include "Header.h"

Graph* generatePreferentialGraph(int nodeSize, double prob)
{
	Graph* pG = new Graph();

	for (int i = 0; i < nodeSize; i++)
	{
		pG->addVertex(i);
	}

	return pG;
}
