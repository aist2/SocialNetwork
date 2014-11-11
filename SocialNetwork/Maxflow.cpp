#include "Header.h"

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
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
		Vertex* pU = *(vertex_queue.begin());
        vertex_queue.erase(vertex_queue.begin());

		for (auto it = pU->edges.begin(); it != pU->edges.end(); it++) 
		{
			Edge* pE = *it;
			Vertex* pV = pE->pDestV;
			if (visited[pV->id]==false && pE->capacity > 0)
			{
				vertex_queue.insert(pV);
				(*pParent)[pV] = pU;
				visited[pV->id]=true;
			}
		}
	}

	return (visited[t->id]==true);
}

// A DFS based function to find all reachable vertices from s.  The function
// marks visited[i] as true if i is reachable from s.  The initial values in
// visited[] must be false. We can also use BFS to find reachable vertices
void dfs(Graph* pG, Vertex* s, std::unordered_map<int,bool>* pVisited)
{
    (*pVisited)[s->id] = true;
    for (auto it=s->edges.begin();it!=s->edges.end();it++)
	{
		Edge* pE = *it;
		Vertex* pV = pE->pDestV;
		
		if (!(*pVisited)[pV->id] && (pE->capacity > 0))
			dfs(pG, pV, pVisited);
	}
}

// Prints the minimum s-t cut
void minCut(Graph* pG, Vertex* s, Vertex* t)
{
	Vertex* pV;
	Vertex* pU;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    Graph* pRG; // rGraph[i][j] indicates residual capacity of edge i-j
	pRG = pG;
	
	pRG->directed = true;
	for (auto it=pRG->edgeMap.begin();it!=pRG->edgeMap.end();it++)
	{
		Edge* pE = it->second;
		pE->capacity = 1;
	}

	pRG->edgeMap.clear();
	for (auto it=pRG->vertexMap.begin();it!=pRG->vertexMap.end();it++)
	{
		Vertex* pV = it->second;
		for (auto it2=pV->edges.begin();it2!=pV->edges.end();it2++)
		{
			Edge* pE = *it2;
			std::string key = int_to_string(pE->pOriginV->id) + "," + int_to_string(pE->pDestV->id);
			pRG->edgeMap[key] = pE;
		}
	}
 
    std::unordered_map<Vertex*,Vertex*> parent;  // This array is filled by BFS and to store path
 
    // Augment the flow while there is path from source to sink
    while (bfs(pRG, s, t, &parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (pV=t; pV!=s; pV=parent[pV])
        {
            pU = parent[pV];
			Edge* pE = pRG->findEdge(pU,pV);
            path_flow = std::min(path_flow, pE->capacity);
			std::cout << pE->pOriginV->id << "\t->t" << pE->pDestV->id << std::endl;
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (pV=t; pV != s; pV=parent[pV])
        {
            pU = parent[pV];
			Edge* pE1 = pRG->findEdge(pU,pV);
			Edge* pE2 = pRG->findEdge(pV,pU);
            pE1->capacity -= path_flow;
            pE2->capacity += path_flow;
        }
    }
 
    // Flow is maximum now, find vertices reachable from s
    std::unordered_map<int,bool> visited;
	for (auto it = pRG->vertexMap.begin(); it != pG->vertexMap.end(); it++) {
		visited[it->first] = false;
	}
    dfs(pRG, s, &visited);
 
    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
	/*
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
         if (visited[i] && !visited[j] && graph[i][j])
              cout << i << " - " << j << endl;
	*/

	for (auto it=pRG->edgeMap.begin();it!=pRG->edgeMap.end();it++)
	{
		Edge* pE = it->second;
		std::cout << it->first << "\t residual capacity\t" << pE->capacity << std::endl;
	}
    return;
}