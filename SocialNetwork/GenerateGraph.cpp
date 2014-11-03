#include "Header.h"

Graph* generateRandomGraph(int nodeSize, int prob)
{
	std::cout << "Generating Random Graph..." << std::endl;
	clock_t timeElapsed = clock();
	Graph* pG = new Graph();

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
	timeElapsed = clock() - timeElapsed;
	std::cout << "Generating Random Graph DONE; time taken:" << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
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
			pVJ = pG->findVertex(j);
			degree = pVJ->getEdgeSize();
			if (sumDegree != 0)
			{
				newProb = int(prob * degree / sumDegree);
			}
			else
			{
				newProb = prob;
			}
			//cout << "i: " << i << " j: " << j << " prob: " << newProb << endl;
			if (isAddEdge(newProb))
			{
				pG->addEdge(j,i);
				//cout << "added edge i: " << i << " j: " << j << endl;
			}
		}
		sumDegree += pVI->getEdgeSize();
	}

	std::cout << "Generating Preferential Graph DONE" << std::endl;
	return pG;
}

Graph* readRealGraph(std::string path, char delim) {
	std::cout << "Reading Graph..." << std::endl;

	std::string line;
	std::ifstream file(path);
	std::string str;
	clock_t timeElapsed = clock();
	Graph* pG = new Graph();
	while (getline(file, str)) {
		//std::cout << "Reading new row..." << std::endl;
		std::vector<std::string> vertices = split(str, delim);
		int id_v1 = atoi(vertices.at(0).c_str());
		int id_v2 = atoi(vertices.at(1).c_str());
		pG->addEdge(id_v1,id_v2);
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Reading Graph DONE; time taken:" << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
	return pG;
}
