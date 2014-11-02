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
	
	pV1->adj.push_back(id2);
	pV2->adj.push_back(id1);
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
//	try
//	{
//		pV = vertices[id];
//		if (pV->id == id)
//		{
//			return pV;
//		}
//	}
//	catch (...)
//	{
//	}
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

/*
 * This is a brutal force triangle-finding algorithm.. takes ages to complete using facebook_combined.txt
 */
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
	std::cout << "Time taken to find triangles: "
			<< ((float) timeElapsed) / CLOCKS_PER_SEC << " second(s)\n";
	return triangleTuples;
}

bool compareVertice(Vertex* v1, Vertex* v2) { return v1->getEdgeSize() > v2->getEdgeSize();}


/*
 * Refer to Algorithm 1 ¨C forward. Lists all the triangles in a graph [25, 26] in <triangles_short.pdf>
 * This is a O(m3/2) algorithm
 */
std::vector <std::tuple<int,int,int>> Graph::getAllTriangles_forward() {
	 std::sort (vertices.begin(), vertices.end(), compareVertice);

	 for (unsigned i = 0; i < vertices.size(); i++) {
		 vertices[i]->resetNodeData();
	 }

	 std::vector<std::tuple<int, int, int> > triangleTuples;

	 clock_t timeElapsed = clock();
	 for (unsigned i = 0; i < vertices.size(); i++) {
		 Vertex* focalV = vertices[i];
		 // for all adjacent vertices
		 for (unsigned j = 0; j < focalV->edges.size(); j++) {
			 Vertex* secondV = focalV->edges[j]->pDestV;
			 // only consider smaller degree nodes
			 // if nodes are of same degree, only consider node with larger id
			 if ((secondV->getEdgeSize() < focalV->getEdgeSize()) ||
				 (secondV->getEdgeSize() == focalV->getEdgeSize() && focalV->id < secondV->id)){
				 // Add common element in nodeData to triangle
				 std::vector<int> result;
				 std::set_intersection (focalV->nodeData.begin(), focalV->nodeData.end(), secondV->nodeData.begin(), secondV->nodeData.end(), back_inserter(result));
				 for (unsigned k=0; k<result.size(); k++) {
					 std::tuple<int, int, int> aNode = createTriangleNode(focalV->id, secondV->id, result[k]);
					 triangleTuples.push_back(aNode);
				 }
				 // Add focalV into the nodeData of secondV
				 secondV->nodeData.push_back(focalV->id);
			 }
		 }
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to find triangles: " << ((float) timeElapsed) / CLOCKS_PER_SEC
			<< " second(s)\n";
	 return triangleTuples;
}

std::vector<Graph*> findConnectedComponents(Graph* pG) {

}

long computeDiameter() {

}
