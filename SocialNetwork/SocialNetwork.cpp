// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "Header.h"

int main()
{
	Graph* pG;
	pG = generateRandomGraph(100, 1);

	//pG->printEdges();
	//pG->printVertices();

	std::cout << "Number of nodes: " << pG->getVertexSize() << std::endl;
	std::cout << "Number of edges: " << pG->getEdgeSize() << std::endl;

	//system("PAUSE");
	return 0;
}

