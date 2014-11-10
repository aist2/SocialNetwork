#include "Header.h"

bool bfs(Graph* pG, Vertex* s, Vertex* t, std::unordered_map<Vertex*,Vertex*>* pParent)
{
	std::unordered_map<int,bool> visited;
	for (auto it = pG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
		visited[it->first] = false;
	}
	std::set<Vertex*> vertex_queue;
	vertex_queue.insert(s);
	visited[s->id] = true;
	(*pParent)[s] = NULL;

	while (!vertex_queue.empty())
	{
		Vertex* pV = *(vertex_queue.begin());
        vertex_queue.erase(vertex_queue.begin());

		for (auto it = pV->edges.begin(); it != pV->edges.end(); it++) {
			Vertex* vNext = (*it)->pDestV;
			if (visited[vNext->id]==false)
			{
				vertex_queue.insert(vNext);
				(*pParent)[vNext] = pV;
				visited[vNext->id]=true;
			}
		}
	}

	return (visited[t->id]==true);
}