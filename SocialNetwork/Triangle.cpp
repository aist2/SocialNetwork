/*
 * Triangle.cpp
 *
 *  Created on: 8 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"
/*
 * This is a brutal force triangle-finding algorithm.. takes ages to complete using facebook_combined.txt
 */
std::vector<std::tuple<int, int, int>> getAllTriangles_brutal(Graph* pG) {
	std::vector<std::tuple<int, int, int> > triangleTuples;
	clock_t timeElapsed = clock();
	for (std::unordered_map<int, Vertex*>::iterator it = pG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
		Vertex* focalV = it->second;
		std::vector<Edge*> focalEdges = focalV->edges;
		for (unsigned j = 0; j < focalEdges.size(); j++) {
			Vertex* secondV = focalEdges[j]->pDestV;
			for (unsigned k = j + 1; k < focalEdges.size(); k++) {
				Vertex* thirdV = focalEdges[k]->pDestV;
				if (secondV->existEdgeTo(thirdV->id)) {
					std::tuple<int, int, int> aNode = createTriangleNode(focalV->id, secondV->id, thirdV->id);
					if (std::find(triangleTuples.begin(), triangleTuples.end(), aNode) == triangleTuples.end()) {
						triangleTuples.push_back(aNode);
					}
				}
			}
		}
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to find triangles: " << ((float) timeElapsed) / CLOCKS_PER_SEC << " second(s)\n";
	return triangleTuples;
}

// function f
//bool f(Vertex* v1, Vertex* v2) {
//	return ((v1->getEdgeSize() < v2->getEdgeSize()) || (v1->getEdgeSize() == v2->getEdgeSize() && v1->id < v2->id));
//}

double f(Vertex* v1) {
	return 100/(double)v1->getEdgeSize() + 100/((double)v1->id);
}

double compare(Vertex* v1, Vertex* v2) {
	return f(v1)<f(v2);
}

//bool sortVertice(Vertex* v1, Vertex* v2) {
//	return !f(v1,v2);
//}

/*
 * Refer to Algorithm 1 ¨C forward. Lists all the triangles in a graph [25, 26] in <triangles_short.pdf>
 * This is a O(m3/2) algorithm
 */
std::vector<std::tuple<int, int, int>> getAllTriangles_forward(Graph* pG) {

	std::vector <Vertex*> vertices;

	for(std::unordered_map<int, Vertex*>::iterator it = pG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
		vertices.push_back(it->second);
	}

	std::sort (vertices.begin(), vertices.end(), compare);

	std::vector<std::tuple<int, int, int> > triangleTuples;

	clock_t timeElapsed = clock();
	for (unsigned i = 0; i < vertices.size(); i++) {
		Vertex* focalV = vertices[i];
		// for all adjacent vertices
		for (unsigned j = 0; j < focalV->edges.size(); j++) {
			Vertex* secondV = focalV->edges[j]->pDestV;
			// only consider smaller degree nodes
			// if nodes are of same degree, only consider node with larger id
			if (f(secondV) > f(focalV)) {
				// Add common element in nodeData to triangle
				std::vector<int> result;
				std::set_intersection(focalV->nodeData.begin(), focalV->nodeData.end(), secondV->nodeData.begin(),
						secondV->nodeData.end(), back_inserter(result));
				for (unsigned k = 0; k < result.size(); k++) {
					std::tuple<int, int, int> aNode = createTriangleNode(focalV->id, secondV->id, result[k]);
					triangleTuples.push_back(aNode);
				}
				// Add focalV into the nodeData of secondV
				secondV->nodeData.push_back(focalV->id);
			}
		}
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to find triangles: " << ((float) timeElapsed) / CLOCKS_PER_SEC << " second(s)\n";
	return triangleTuples;
}

