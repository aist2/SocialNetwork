// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "graph.h"

int main()
{
	Graph g = Graph();

	g.addEdge(1,2);

	g.addEdge(2,3);

	g.printEdges();

	g.printVertices();

	system("PAUSE");
	return 0;
}

