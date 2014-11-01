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

class Edge;

class Vertex
{
public:
	int id;
	bool visited;
	std::vector <Edge*>* edges;

	Vertex(int);
	~Vertex();
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
	void addEdge(int,int);
	void addVertex(int);
	Vertex* findVertex(int);
	void printEdges();
	void printVertices();

private:
	std::vector <Edge*> edges;
	std::vector <Vertex*> vertices;
};
