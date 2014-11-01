#include "Header.h"

Graph* generateRandomGraph(int nodeSize, int prob)
{
	Graph* pG = new Graph();

	for (int i = 0; i < nodeSize; i++)
	{
		pG->addVertex(i);
	}

	for (int i = 0; i < nodeSize; i++)
	{
		for (int j = (i+1); j < nodeSize; j++)
		{
			if (isAddEdge(prob))
			{
				pG->addEdge(i,j);
			}
		}
	}

	return pG;
}

Graph* generatePreferentialGraph(int nodeSize, int prob)
{
	Graph* pG = new Graph();

	for (int i = 0; i < nodeSize; i++)
	{
		pG->addVertex(i);
	}

	for (int i = 0; i < nodeSize; i++)
	{
		for (int j = (i+1); j < nodeSize; j++)
		{
			if (isAddEdge(prob))
			{
				pG->addEdge(i,j);
			}
		}
	}

	return pG;
}