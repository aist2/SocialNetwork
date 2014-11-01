#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

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

Graph* readRealGraph() {
	std::string line;
	std::ifstream file("facebook_combined.txt");
	std::string str;
	Graph* pG = new Graph();
	while (getline(file, str)) {
		std::vector<std::string> vertices = split(str, ' ');
		int id_v1 = atoi(vertices.at(0).c_str());
		int id_v2 = atoi(vertices.at(1).c_str());
		pG->addEdge(id_v1,id_v2);
	}
	return pG;
}
