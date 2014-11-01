#include "Header.h"

Graph* generateRandomGraph(int nodeSize, int prob)
{
	std::cout << "Generating Random Graph..." << std::endl;

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

	std::cout << "Generating Random Graph DONE" << std::endl;
	return pG;
}

Graph* generatePreferentialGraph(int nodeSize, int prob)
{
	std::cout << "Generating Preferential Graph..." << std::endl;

	Graph* pG = new Graph();
	Vertex* pVI;
	Vertex* pVJ;
	int newProb;
	int degree;
	int sumDegree = 0;
	
	pG->addVertex(0);
	
	for (int i = 1; i < nodeSize; i++)
	{
		pVI = pG->addVertex(i);
		for (int j = 0; j < i; j++)
		{
			pVJ = pG->getVertexByIndex(j);
			degree = pVJ->getEdgeSize();
			if (sumDegree != 0)
			{
				newProb = int(prob * degree / sumDegree);
			}
			else
			{
				newProb = prob;
			}
			//std::cout << "i: " << i << " j: " << j << " prob: " << newProb << std::endl;
			if (isAddEdge(newProb))
			{
				pG->addEdge(j,i);
				//std::cout << "added edge i: " << i << " j: " << j << std::endl;
			}
		}
		sumDegree += pVI->getEdgeSize();
	}

	std::cout << "Generating Preferential Graph DONE" << std::endl;
	return pG;
}