// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "Header.h"

int main()
{
	Graph* pG;
	//pG = generatePreferentialGraph(1000, 100);
	pG = readRealGraph("../data/facebook_combined.txt", ' ');
	//pG->printEdges();
	//pG->printVertices();

	std::cout << "Number of nodes: " << pG->getVertexSize() << std::endl;
	std::cout << "Number of edges: " << pG->getEdgeSize() << std::endl;

	pG->printDegreeDistribution();
	//system("PAUSE");
	return 0;
}

