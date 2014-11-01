#include "Graph.h"

Vertex::Vertex(int newId)
{
	id = newId;
	visited = false;
	edges = new std::vector<Edge*>;
}

Vertex::~Vertex()
{
}

void Vertex::print()
{
	std::cout << id;
    std::cout << std::endl;
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
	return vertices.size();
}

int Graph::getEdgeSize()
{
	return edges.size();
}

void Graph::addEdge(int id1, int id2)
{
	Vertex* pV1;
	Vertex* pV2;
	
	pV1 = findVertex(id1);
	if (pV1 == NULL)
	{
		pV1=new Vertex(id1);
		vertices.push_back(pV1);
	}

	pV2 = findVertex(id2);
	if (pV2 == NULL)
	{
		pV2 = new Vertex(id2);
		vertices.push_back(pV2);
	}

	Edge* pE1 = new Edge(pV1,pV2);
	Edge* pE2 = new Edge(pV2,pV1);

	edges.push_back(pE1);
	pV1->edges->push_back(pE1);
	pV2->edges->push_back(pE2);
}

void Graph::addVertex(int id)
{
	Vertex* pV = new Vertex(id);
	vertices.push_back(pV);
}

Vertex* Graph::findVertex(int id)
{
	Vertex* pV = NULL;

	for (int i=0; i < vertices.size(); i++)
	{
		if(vertices[i]->id==id)
			pV = vertices[i];
	}
	return pV;
}

void Graph::printEdges()
{
	std::cout << "===Edges===" << std::endl;
	for (int i = 0; i < edges.size(); i++)
        edges[i]->print();
	std::cout << "===Edges===" << std::endl;
}

void Graph::printVertices()
{
	std::cout << "===Vertices===" << std::endl;
	for (int i = 0; i < vertices.size(); i++)
        vertices[i]->print();
	std::cout << "===Vertices===" << std::endl;
}
