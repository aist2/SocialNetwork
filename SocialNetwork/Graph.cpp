#include "Header.h"

Vertex::Vertex(int newId)
{
	id = newId;
	infected = false;
	popularity = -1;
}

Vertex::~Vertex()
{
}

int Vertex::getEdgeSize()
{
	return edges.size();

}

void Vertex::print()
{
	std::cout << "id: " << id;
	std::cout << "; degree: " << getEdgeSize();
	std::cout << std::endl;
}

bool Vertex::existEdgeTo(Vertex* v2) {
	for (unsigned i=0; i<edges.size(); i++) {
		if (edges[i]->pDestV->id == v2->id) {
			return true;
		}
	}
	return false;
}

bool Vertex::existEdgeTo(int idV2) {
		return std::find(adj.begin(), adj.end(), idV2) != adj.end();
}

void Vertex::resetNodeData(){
	nodeData.clear();
}

Edge::Edge(Vertex* pV1, Vertex* pV2)
{
	pOriginV = pV1;
	pDestV = pV2;
}

Edge::~Edge()
{
}

void Edge::print()
{
	std::cout << pOriginV->id << ", " << pDestV->id << std::endl;
}

Graph::Graph()
{
}

Graph::~Graph()
{
}

int Graph::getVertexSize()
{
	return vertexMap.size();
}

int Graph::getEdgeSize()
{
	return edgeMap.size();
}



Edge* Graph::addEdge(int id1, int id2)
{
	Vertex* pV1;
	Vertex* pV2;
	Edge* pE1 = NULL;
	Edge* pE2 = NULL;
			
	if(id1 > id2)
	{
		int temp = id2;
		id2 = id1;
		id1 = temp;
	}

	pV1 = findVertex(id1);
	pV2 = findVertex(id2);

	if (pV1 != NULL && pV2 != NULL)
	{
		pE1 = findEdge(pV1,pV2);
	}

	if (pV1 == NULL)
	{
		pV1 = addVertex(id1);
	}

	
	if (pV2 == NULL)
	{
		pV2 = addVertex(id2);
	}
	
	if (pE1 == NULL)
	{

		pE1 = new Edge(pV1,pV2);
		pE2 = new Edge(pV2,pV1);

		//edges.push_back(pE1);
		pV1->edges.push_back(pE1);
		pV2->edges.push_back(pE2);
	
		pV1->adj.push_back(id2);
		pV2->adj.push_back(id1);

		std::string key = int_to_string(id1) + "," + int_to_string(id2);
		edgeMap[key] = pE1;
	}
	return pE1;
}

Vertex* Graph::addVertex(int id)
{
	Vertex* pV = new Vertex(id);
	vertices.push_back(pV);
	vertexMap[id] = pV;
	return pV;
}

Vertex* Graph::findVertex(int id)
{
	std::unordered_map<int,Vertex*>::const_iterator iter = vertexMap.find(id);
	if ( iter == vertexMap.end() )
		return NULL;
	else
		return iter->second;
}

Edge* Graph::findEdge(Vertex* pV1,Vertex* pV2)
{
	//Edge* pE;

	int id1 = pV1->id;
	int id2 = pV2->id;
	int temp;
	std::string key;

	if (id1 > id2)
	{
		temp = id2;
		id2 = id1;
		id1 = temp;
	}

	key = int_to_string(id1) + "," + int_to_string(id2);

	std::unordered_map<std::string,Edge*>::const_iterator iter = edgeMap.find(key);
	if ( iter == edgeMap.end() )
		return NULL;
	else
		return iter->second;

}

void Graph::printEdges()
{
//	std::cout << "===Edges===" << std::endl;
	for (auto i = edgeMap.begin(); i != edgeMap.end(); ++i)
        i->second->print();
//	std::cout << "===Edges===" << std::endl;
}

void Graph::printVertices()
{
	std::cout << "===Vertices===" << std::endl;
	for (auto i = vertexMap.begin(); i != vertexMap.end(); ++i)
        i->second->print();
	std::cout << "===Vertices===" << std::endl;
}

/*
Graph* Graph::shallowCopy(){
	Graph* newG = new Graph();
	newG->edges = edges;
	newG->vertices = vertices;
	return newG;
}
*/

//////////////////////////////////////////////////
/** Triangle, Diameter and connected component **/
//////////////////////////////////////////////////

////////////////
/** Triangle **/
////////////////

std::map<long, long> Graph::computeDegreeDistribution() {
	clock_t timeElapsed = clock();
	std::map<long, long> resultMap;
	for (auto i = vertexMap.begin(); i != vertexMap.end(); ++i) {
		resultMap[i->second->getEdgeSize()]++;
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute degree distribution: " << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
	return resultMap;
}
