/*
 * Diameter.cpp
 *
 *  Created on: 4 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"

// helper
long bfsFindHeightRaw(Vertex* v, int numVertices) {
	std::map<int, long> vHeightMap;
	v->mark = true;
	std::queue<Vertex*> neighbours;
	neighbours.push(v);
	vHeightMap[v->id] = 0;
	int count = 0;
	long maxHeight = 0;
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		count ++;
		if (count > numVertices) {
			break;
		}
		long currHeight = vHeightMap[vCurr->id];
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
		}
		neighbours.pop();
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			vCurr->mark = true;
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!vNext->mark) {
				neighbours.push(vNext);
				vHeightMap[vNext->id] = currHeight + 1;
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
	v->mark = true;
	std::queue<Vertex*> neighbours;
	std::vector<Vertex*> result;
	neighbours.push(v);
	int count = 0;
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		count ++;
		if (count > numVertices) {
			break;
		}
		neighbours.pop();
		result.push_back(vCurr);
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			vCurr->mark = true;
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!vNext->mark) {
				neighbours.push(vNext);
			}
		}
	}
	return result;
}

// traverse entire component
long bfsFindHeight(Vertex* v) {
	std::map<int, long> vHeightMap;
	v->mark = true;
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
			vCurr->mark = true;
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!vNext->mark) {
				neighbours.push(vNext);
				vHeightMap[vNext->id] = currHeight + 1;
			}
		}
	}
	return maxHeight;
}

// the only public method
long computeDiameter(Graph* pG, int s) {
	// unmark all vertices
	for (unsigned i = 0; i < pG->vertices.size(); i++) {
		pG->vertices[i]->mark = false;
	}

	Vertex* selectedV;
	long maxHeight = -1;

	//// compute d(out)(s)(w)
	// find v
	for (unsigned i = 0 ; i < pG->vertices.size(); i++) {
		long currHeight = bfsFindHeight(pG->vertices[i], s);
		if (currHeight > maxHeight) {
			maxHeight = currHeight;
			selectedV = pG->vertices[i];
		}
	}

	// unmark all vertices again
	for (unsigned i = 0; i < pG->vertices.size(); i++) {
		pG->vertices[i]->mark = false;
	}

	// find neighbours of v (including v), bfs
	long maxHeightVN = -1; //reuse
	std::vector<Vertex*> vNeighbours = bfsFindNeighboursSelfInclusive(selectedV, s);
	for (unsigned i = 0 ; i < vNeighbours.size(); i++) {
		long currHeight = bfsFindHeight(vNeighbours[i]);
		if (currHeight > maxHeightVN) {
			maxHeightVN = currHeight;
		}
	}



	return maxHeightVN;
	//return bfsFindHeight(pG->vertexMap.begin()->second, 2);
}

