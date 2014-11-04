/*
 * ConnectedComponent.cpp
 *
 *  Created on: 4 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"

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
	neighbours.push(v);
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		neighbours.pop();
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!vNext->mark) {
				newG->addEdge(vCurr->id, vNext->id);
				neighbours.push(vNext);
				vNext->mark = true;
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


