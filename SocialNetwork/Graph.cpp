#include "Header.h"

Vertex::Vertex(int newId)
{
	id = newId;
	infected = false;
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

bool Vertex::existEdgeTo(int idV2) {
	for (unsigned i=0; i<edges.size(); i++) {
		if (edges[i]->pDestV->id == idV2) {
			return true;
		}
	}
	return false;
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

Edge* Graph::addEdge(int id1, int id2)
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
	pV1->edges.push_back(pE1);
	pV2->edges.push_back(pE2);
	
	return pE1;
}

Vertex* Graph::addVertex(int id)
{
	Vertex* pV = new Vertex(id);
	vertices.push_back(pV);
	return pV;
}

Vertex* Graph::findVertex(int id)
{
	Vertex* pV;

	for ( auto i = vertices.begin(); i != vertices.end(); i++ ) 
	{
		pV = *i;
		if(pV->id==id)
		{
			return pV;
		}	
	}
	return NULL;
}

Vertex* Graph::getVertexByIndex(int i)
{
	return vertices[i];;
}

void Graph::printEdges()
{
	std::cout << "===Edges===" << std::endl;
	for (unsigned i = 0; i < edges.size(); i++)
        edges[i]->print();
	std::cout << "===Edges===" << std::endl;
}

void Graph::printVertices()
{
	std::cout << "===Vertices===" << std::endl;
	for (unsigned i = 0; i < vertices.size(); i++)
        vertices[i]->print();
	std::cout << "===Vertices===" << std::endl;
}

std::map<unsigned long, unsigned long> Graph::computeDegreeDistribution() {
	clock_t timeElapsed = clock();
	std::map<unsigned long, unsigned long> resultMap;
	for (unsigned i = 0; i < vertices.size(); i++) {
		resultMap[vertices[i]->getEdgeSize()]++;
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute degree distribution: " << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
	return resultMap;
}

std::vector<std::tuple<int, int, int>> Graph::getAllTriangles_brutal() {
	std::vector<std::tuple<int, int, int> > triangleTuples;
	clock_t timeElapsed = clock();
	for (unsigned i = 0; i < vertices.size(); i++) {
		Vertex* focalV = vertices[i];
		std::vector<Edge*> focalEdges = focalV->edges;
		for (unsigned j = 0; j < focalEdges.size(); j++) {
			Vertex* secondV = focalEdges[j] -> pDestV;
			for (unsigned k = j + 1; k < focalEdges.size(); k++) {
				Vertex* thirdV = focalEdges[k] -> pDestV;
				if (secondV->existEdgeTo(thirdV->id)) {
					std::tuple<int, int, int> aNode = createTriangleNode(focalV->id, secondV->id, thirdV->id);
					if (std::find(triangleTuples.begin(), triangleTuples.end(),aNode) == triangleTuples.end()) {
						triangleTuples.push_back(aNode);
					}
				}
			}
		}
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute degree distribution: "
			<< ((float) timeElapsed) / CLOCKS_PER_SEC << " second(s)\n";
	return triangleTuples;
}
