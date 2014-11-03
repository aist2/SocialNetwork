/*
 * Diameter.cpp
 *
 *  Created on: 4 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"

// helper
long bfsRaw(Vertex* v, int numVertices) {
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
long bfs(Vertex* v, int numVertices) {
	if (numVertices < 0) {
		return -1;
	} else if (numVertices <= 1) {
		return 0;
	} else {
		bfsRaw(v, numVertices);
	}
	return 1;
}

// traverse entire component
long bfs(Vertex* v) {
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
	return bfs(pG->vertexMap.begin()->second, 2);
}

