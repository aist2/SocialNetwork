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
#include <queue>
#include <unordered_map>
#include <set>

//Graph
class Edge;

class Vertex
{
public:
	int id;
	bool infected;
	bool disconnected;
	double popularity;
	std::vector <Edge*> edges;
	std::vector <int> adj;
	std::vector <int> nodeData; // this field is used by triangle algo only.. no need to touch it during vertex creation
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
	Edge* addEdge(Vertex*, Vertex*);
	Vertex* addVertex(int);
	Vertex* findVertex(int);
	Edge* findEdge(Vertex*,Vertex*);
	void printEdges();
	void printVertices();
	Graph* shallowCopy();
	void removeEdge(Edge*);

	// should ideally move these out of Graph class..
	std::map<long, long> computeDegreeDistribution();

	//std::vector <Edge*> edges;
	std::vector <Vertex*> vertices;
	std::unordered_map<int, Vertex*> vertexMap;
	std::unordered_map<std::string, Edge*> edgeMap;
};

// Generate Graph
Graph* generateRandomGraph(int, int);

Graph* generatePreferentialGraph(int, int);

Graph* readRealGraph(std::string, char);

//Util
bool isAddEdge(int);

std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);

std::vector<std::string> split(const std::string&, char);

std::string int_to_string(int i);

std::tuple<int,int,int> createTriangleNode (int , int , int );

//Virus Propagate
int virusPropagate(Graph*, int, bool);

void infectIt(Vertex*, std::vector <Vertex*> *);

Vertex* pickOneFriend(Vertex*);

Vertex* randomPick(std::vector <Vertex*>*);

void beFriendToAll(Graph*, Vertex*);

void initializeMonitor(Graph*);

void monitorGraph(Graph*, bool);

std::map<double, int> computePopularityDistribution(Graph*);

std::unordered_map<int,int> Dijkstra(Graph*, Vertex*);

std::map<double,int> computeShortestPath(Graph*);

void printDistribution(std::map<double, int>, std::string);

//Triangle, Diameter and connected component
std::vector<Graph*> findConnectedComponentsDFS(Graph* pG);
std::vector<Graph*> findConnectedComponentsBFS(Graph* pG);


// Diameter.cpp
long computeDiameter_brutal(Graph* pG);
long computeDiameter(Graph* pG, int s);

// Triangle.cpp
std::vector<std::tuple<int, int, int>> getAllTriangles_brutal(Graph* pG); // find all triangles by testing each vertex and its adjacent vetices. Complexity: O power 3
std::vector <std::tuple<int,int,int>> getAllTriangles_forward(Graph* pG);

// Maxflow.cpp
bool bfs(Graph*, Vertex*, Vertex*, std::unordered_map<Vertex*,Vertex*>*);