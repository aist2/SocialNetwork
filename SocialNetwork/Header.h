#include <random>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
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

Graph* generateRandomGraph(int, int);

Graph* generatePreferentialGraph(int, int);

Graph* readRealGraph(std::string, char);

bool isAddEdge(int);

std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);

std::vector<std::string> split(const std::string&, char);

