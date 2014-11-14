/*
 * Diameter.cpp
 *
 *  Created on: 4 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"

double compareEdgeDest(Edge* e1, Edge* e2) {
	return (e1->pDestV->id) < (e2->pDestV->id);
}

// helper
long bfsFindHeightRaw(Vertex* v, int numVertices) {
	std::map<int, long> vHeightMap;
	std::map<int, bool> marks;
	marks[v->id] = true;
	std::queue<Vertex*> neighbours;
	neighbours.push(v);
	vHeightMap[v->id] = 0;
	int count = 0;
	long maxHeight = 0;
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		count++;
		if (count > numVertices) {
			break;
		}
		long currHeight = vHeightMap[vCurr->id];
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		neighbours.pop();
		// sort edges in increasing dest id order
		std::sort(vCurr->edges.begin(), vCurr->edges.end(), compareEdgeDest);
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!marks[vNext->id]) {
				neighbours.push(vNext);
				vHeightMap[vNext->id] = currHeight + 1;
				marks[vNext->id] = true;
			}
		}
	}
	return maxHeight;
}

// return height + specify number nodes to traverse
long bfsFindHeight(Vertex* v, int numVertices) {
	if (numVertices < 0) {
		return -1;
	} else if (numVertices <= 1) {
		return 0;
	} else {
		bfsFindHeightRaw(v, numVertices);
	}
	return 1;
}

// helper
std::vector<Vertex*> bfsFindNeighboursSelfInclusive(Vertex* v, int numVertices) {
	std::map<int, bool> marks;
	marks[v->id] = true;
	std::queue<Vertex*> neighbours;
	std::vector<Vertex*> result;
	neighbours.push(v);
	int count = 0;
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		count++;
		if (count > numVertices) {
			break;
		}
		neighbours.pop();
		result.push_back(vCurr);
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!marks[vNext->id]) {
				neighbours.push(vNext);
				marks[vNext->id] = true;
			}
		}
	}
	return result;
}

// traverse entire component
long bfsFindHeight(Vertex* v) {
	std::map<int, long> vHeightMap;
	std::map<int, bool> marks;
	marks[v->id] = true;
	std::queue<Vertex*> neighbours;
	neighbours.push(v);
	vHeightMap[v->id] = 0;
	long maxHeight = 0;
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		long currHeight = vHeightMap[vCurr->id];
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		neighbours.pop();
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!marks[vNext->id]) {
				neighbours.push(vNext);
				vHeightMap[vNext->id] = currHeight + 1;
				marks[vNext->id] = true;
			}
		}
	}
	return maxHeight;
}

long computeDiameter_brutal(Graph* pG) {
	clock_t timeElapsed = clock();
	long maxHeight = -1;

	std::vector<Graph*> connectedComponents = findConnectedComponentsDFS(pG);
	for (unsigned i = 0; i < connectedComponents.size(); i++) {
		Graph* currentG = connectedComponents[i];
		for (std::unordered_map<int, Vertex*>::iterator it = currentG->vertexMap.begin();
				it != currentG->vertexMap.end(); it++) {
			// unmark all vertices
			long currHeight = bfsFindHeight(it->second);
			if (currHeight > maxHeight) {
				maxHeight = currHeight;
			}
		}
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute diameter using brutal force: " << ((float) timeElapsed) / CLOCKS_PER_SEC
			<< " second(s)\n";
	return maxHeight;
}

long computeDiameter(Graph* pG, int s) {
	clock_t timeElapsed = clock();
	Vertex* selectedV;

	std::vector<Graph*> connectedComponents = findConnectedComponentsDFS(pG);
	//// compute d(out)(s)(w)
	// find v
	long maxHeightResult = -1; //reuse
	for (unsigned i = 0; i < connectedComponents.size(); i++) {
		long maxHeight = -1;
		Graph* currentG = connectedComponents[i];
		for (std::unordered_map<int, Vertex*>::iterator it = currentG->vertexMap.begin(); it != currentG->vertexMap.end(); it++) {
			long currHeight = bfsFindHeight(it->second, s);
			if (currHeight >= maxHeight) {
				maxHeight = currHeight;
				selectedV = it->second;
			}
		}

		std::vector<Vertex*> vNeighbours = bfsFindNeighboursSelfInclusive(selectedV, s);

		for (unsigned i = 0; i < vNeighbours.size(); i++) {
			long currHeight = bfsFindHeight(vNeighbours[i]);
			if (currHeight > maxHeightResult) {
				maxHeightResult = currHeight;
			}
		}
	}

	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute diameter using approx algorithm: " << ((float) timeElapsed) / CLOCKS_PER_SEC
			<< " second(s)\n";
	return maxHeightResult;
	//return bfsFindHeight(pG->vertexMap.begin()->second, 2);
}

