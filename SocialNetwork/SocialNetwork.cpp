// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "Header.h"

int main()
{
	Graph* pG;
	pG = generatePreferentialGraph(3, 0.5);

	pG->printEdges();
	pG->printVertices();

	system("PAUSE");
	return 0;
}

