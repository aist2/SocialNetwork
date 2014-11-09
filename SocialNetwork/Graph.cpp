#include "Header.h"

Vertex::Vertex(int newId)
{
	id = newId;
	infected = false;
	popularity = -1;
	mark = false;
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

/*
 * This is a brutal force triangle-finding algorithm.. takes ages to complete using facebook_combined.txt
 */
std::vector<std::tuple<int, int, int>> Graph::getAllTriangles_brutal() {
	std::vector<std::tuple<int, int, int> > triangleTuples;
	clock_t timeElapsed = clock();
	for (auto i = vertexMap.begin(); i != vertexMap.end(); ++i) {
		Vertex* focalV = i->second;
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
 * Refer to Algorithm 1 �C forward. Lists all the triangles in a graph [25, 26] in <triangles_short.pdf>
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


void Graph::outputEdges(std::string path, char delim)
{
	std::string line;
	std::ofstream file;
	file.open (path);
	
	for (auto i = edgeMap.begin(); i != edgeMap.end(); ++i)
	{
		file << i->second->pOriginV->id;
		file << delim;
		file << i->second->pDestV->id;
		file << "\n";
	}
	file.close();
}