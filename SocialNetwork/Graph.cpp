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

		edges.push_back(pE1);
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
	for (unsigned i = 0; i < edges.size(); i++)
        edges[i]->print();
//	std::cout << "===Edges===" << std::endl;
}

void Graph::printVertices()
{
	std::cout << "===Vertices===" << std::endl;
	for (unsigned i = 0; i < vertices.size(); i++)
        vertices[i]->print();
	std::cout << "===Vertices===" << std::endl;
}

Graph* Graph::shallowCopy(){
	Graph* newG = new Graph();
	newG->edges = edges;
	newG->vertices = vertices;
	return newG;
}


//////////////////////////////////////////////////
/** Triangle, Diameter and connected component **/
//////////////////////////////////////////////////

////////////////
/** Triangle **/
////////////////

std::map<long, long> Graph::computeDegreeDistribution() {
	clock_t timeElapsed = clock();
	std::map<long, long> resultMap;
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

////////////////////////////////////////
/** Connected Component and traverse **/
////////////////////////////////////////

// helper method
Vertex* findUnmarkedVertex(Graph* pG) {
	for (unsigned i = 0 ; i < pG->vertices.size(); i++) {
		if (!pG->vertices[i]->mark) {
			return pG->vertices[i];
		}
	}
	return NULL;
}

// helper method
void dfs(Vertex* v, Graph* newG) {
	v->mark = true;
	for (unsigned i = 0; i < v->edges.size(); i++) {
		Vertex* v2 = v->edges[i]->pDestV;
		if (!v2->mark) {
			newG->addEdge(v->id, v2->id);
		}
	}
	for (unsigned i = 0; i < v->edges.size(); i++) {
		Vertex* v2 = v->edges[i]->pDestV;
		if (!v2->mark) {
			dfs(v2, newG);
		}
	}
}

// in facebook_combined.txt, the graph is connected (only 1 component)
std::vector<Graph*> findConnectedComponentsDFS(Graph* pG) {
	// unmark all vertices
	for (unsigned i = 0 ; i < pG->vertices.size(); i++) {
		pG->vertices[i]->mark = false;
	}
	std::vector<Graph*> result;
	clock_t timeElapsed = clock();
	// Keep dfs until all of pG's vertices are marked
	Vertex* currV = findUnmarkedVertex(pG);
	while (currV != NULL) {
		Graph* newG = new Graph();
		dfs(currV, newG);
		currV = findUnmarkedVertex(pG);
		result.push_back(newG);
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to dfs: " << ((float) timeElapsed) / CLOCKS_PER_SEC
				<< " second(s)\n";
	return result;
}

// helper method
void bfs(Vertex* v, Graph* newG) {
	v->mark = true;
	std::queue<Vertex*> neighbours;
	for (unsigned i = 0; i < v->edges.size(); i++) {
		Vertex* v2 = v->edges[i]->pDestV;
		if (!v2->mark) {
			newG->addEdge(v->id, v2->id);
			neighbours.push(v2);
		}
	}
	while (!neighbours.empty()) {
		Vertex* v3 = neighbours.front();
		neighbours.pop();
		for (unsigned i = 0; i < v3->edges.size(); i++) {
			v3->mark = true;
			Vertex* v4 = v3->edges[i]->pDestV;
			if (!v4->mark) {
				newG->addEdge(v3->id, v4->id);
				neighbours.push(v4);
			}
		}
	}
}

// find connected graph using BFS
std::vector<Graph*> findConnectedComponentsBFS(Graph* pG) {
	// unmark all vertices
	for (unsigned i = 0 ; i < pG->vertices.size(); i++) {
		pG->vertices[i]->mark = false;
	}
	std::vector<Graph*> result;
	clock_t timeElapsed = clock();
	// Keep dfs until copyG's vertices becomes 0
	Vertex* currV = findUnmarkedVertex(pG);
	while (currV != NULL) {
		Graph* newG = new Graph();
		bfs(currV, newG);
		currV = findUnmarkedVertex(pG);
		result.push_back(newG);
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to bfs: " << ((float) timeElapsed) / CLOCKS_PER_SEC
					<< " second(s)\n";
	return result;
}


////////////////
/** Diameter **/
////////////////
//larger s: more accuracy, more time
long computeDiameter(Graph* pG, int s) {
	return  1;
}
