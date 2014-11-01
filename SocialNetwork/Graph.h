#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <map>

class Edge;

class Vertex
{
public:
	int id;
	bool visited;
	std::vector <Edge*> edges;

	Vertex(int);
	~Vertex();
	int getEdgeSize();
	void print();
};

class Edge
{
public:
	Edge(Vertex*, Vertex*);
	~Edge();
	Vertex* pOriginV;
	Vertex* pDestV;
	void print();
};

class Graph
{
public:
	Graph();
	~Graph();
	int getVertexSize();
	int getEdgeSize();
	Edge* addEdge(int,int);
	Vertex* addVertex(int);
	Vertex* findVertex(int);
	Vertex* getVertexByIndex(int);
	void printEdges();
	void printVertices();

	std::map<unsigned long, unsigned long> computeDegreeDistribution();
	void printDegreeDistribution();
	long computeNumTriangles();
	long computeDiameter();

private:
	std::vector <Edge*> edges;
	std::vector <Vertex*> vertices;
};
