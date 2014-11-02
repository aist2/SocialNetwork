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
#include <time.h>
#include <ctime>
#include <tuple>
#include <algorithm>
//Graph
class Edge;

class Vertex
{
public:
	int id;
	bool infected;
	std::vector <Edge*> edges;
	std::vector <int> adj;
	std::vector <int> nodeData;
	Vertex(int);
	~Vertex();
	int getEdgeSize();
	bool existEdgeTo(Vertex* v2);
	bool existEdgeTo(int v2);
	void print();
	void resetNodeData();
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
	void printEdges();
	void printVertices();

	std::map<unsigned long, unsigned long> computeDegreeDistribution();
	std::vector <std::tuple<int,int,int>> getAllTriangles_brutal(); // find all triangles by testing each vertex and its adjacent vetices. Complexity: O power 3
	std::vector <std::tuple<int,int,int>> getAllTriangles_forward();
	long computeDiameter();

private:
	std::vector <Edge*> edges;
	std::vector <Vertex*> vertices;
};

// Generate Graph
Graph* generateRandomGraph(int, int);

Graph* generatePreferentialGraph(int, int);

Graph* readRealGraph(std::string, char);

//Util
bool isAddEdge(int);

std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);

std::vector<std::string> split(const std::string&, char);

std::tuple<int,int,int> createTriangleNode (int , int , int );

//Virus Propagate
void virusPropagate(Graph*, int);

void infectIt(Vertex*, std::vector <Vertex*> *);

Vertex* pickOneFriend(Vertex*);

Vertex* randomPick(std::vector <Vertex*>*);
