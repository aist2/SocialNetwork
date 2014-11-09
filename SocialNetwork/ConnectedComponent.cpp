/*
 * ConnectedComponent.cpp
 *
 *  Created on: 4 Nov, 2014
 *      Author: Chloe Lu
 */
#include "Header.h"

// helper method
//Vertex* findUnmarkedVertex(Graph* pG) {
//	for (std::unordered_map<int, Vertex*>::iterator it = pG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
//		if (!it->second->mark) {
//			return it->second;
//		}
//	}
//	return NULL;
//}

Vertex* findUnmarkedVertex(Graph* pG, std::map<int, bool>* marks) {
	for (std::unordered_map<int, Vertex*>::iterator it = pG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
		if (!(*marks)[it->second->id]) {
			return it->second;
		}
	}
	return NULL;
}

// helper method
void dfs(Vertex* v, std::map<int, bool>* marks, Graph* newG) {
	(*marks)[v->id] = true;
	for (unsigned i = 0; i < v->edges.size(); i++) {
		Vertex* v2 = v->edges[i]->pDestV;
		if (!(*marks)[v2->id]) {
			newG->addEdge(v->id, v2->id);
		}
	}
	for (unsigned i = 0; i < v->edges.size(); i++) {
		Vertex* v2 = v->edges[i]->pDestV;
		if (!(*marks)[v2->id]) {
			dfs(v2, marks, newG);
		}
	}
}

// in facebook_combined.txt, the graph is connected (only 1 component)
std::vector<Graph*> findConnectedComponentsDFS(Graph* pG) {
	std::map<int, bool> vMarks;
	std::map<int, bool> *marks = &vMarks;
	std::vector<Graph*> result;
	clock_t timeElapsed = clock();
	// Keep dfs until all of pG's vertices are marked
	Vertex* currV = findUnmarkedVertex(pG, marks);
	while (currV != NULL) {
		Graph* newG = new Graph();
		dfs(currV, marks, newG);
		currV = findUnmarkedVertex(pG, marks);
		result.push_back(newG);
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to dfs: " << ((float) timeElapsed) / CLOCKS_PER_SEC
				<< " second(s)\n";
	return result;
}

// helper method
void bfs(Vertex* v, std::map<int, bool>* marks, Graph* newG) {
	(*marks)[v->id] = true;
	std::queue<Vertex*> neighbours;
	neighbours.push(v);
	while (!neighbours.empty()) {
		Vertex* vCurr = neighbours.front();
		neighbours.pop();
		for (unsigned i = 0; i < vCurr->edges.size(); i++) {
			Vertex* vNext = vCurr->edges[i]->pDestV;
			if (!(*marks)[vNext->id]) {
				newG->addEdge(vCurr->id, vNext->id);
				neighbours.push(vNext);
				(*marks)[vNext->id] = true;
			}
		}
	}
}

// find connected graph using BFS
std::vector<Graph*> findConnectedComponentsBFS(Graph* pG) {
	std::map<int, bool> vMarks;
	std::map<int, bool> *marks = &vMarks;
	std::vector<Graph*> result;
	clock_t timeElapsed = clock();
	// Keep dfs until copyG's vertices becomes 0
	Vertex* currV = findUnmarkedVertex(pG, marks);
	while (currV != NULL) {
		Graph* newG = new Graph();
		bfs(currV, marks, newG);
		currV = findUnmarkedVertex(pG, marks);
		result.push_back(newG);
	}
	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to bfs: " << ((float) timeElapsed) / CLOCKS_PER_SEC
					<< " second(s)\n";
	return result;
}


