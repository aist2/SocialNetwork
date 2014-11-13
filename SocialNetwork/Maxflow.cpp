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
	pParent->clear();
	(*pParent)[s] = NULL;

	while (!vertex_queue.empty())
	{
		Vertex* pU = *(vertex_queue.begin());
        vertex_queue.erase(vertex_queue.begin());

		for (auto it = pU->edges.begin(); it != pU->edges.end(); it++) 
		{
			Edge* pE = *it;
			Vertex* pV = pE->pDestV;
			int residual = pE->capacity - pE->flow;
			if (visited[pV->id]==false && residual > 0)
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
int maxFlow(Graph* pRG, Vertex* s, Vertex* t)
{
	Vertex* pV;
	Vertex* pU;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
	// rGraph[i][j] indicates residual capacity of edge i-j
	

 
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
			
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (pV=t; pV != s; pV=parent[pV])
        {
            pU = parent[pV];
			Edge* pE1 = pRG->findEdge(pU,pV);
			Edge* pE2 = pRG->findEdge(pV,pU);
            pE1->flow += path_flow;
            pE2->flow -= path_flow;
			//std::cout << pE1->pOriginV->id << "\t->\t" << pE1->pDestV->id << std::endl;
        }
    }
 
    // Flow is maximum now, find vertices reachable from s
	/*
    std::unordered_map<int,bool> visited;
	for (auto it = pRG->vertexMap.begin(); it != pRG->vertexMap.end(); it++) {
		visited[it->first] = false;
	}
    dfs(pRG, s, &visited);
	*/
    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
	/*
	for (auto it=pRG->vertexMap.begin();it!=pRG->vertexMap.end();it++)
	{
		for (auto it2=pRG->vertexMap.begin();it2!=pRG->vertexMap.end();it2++)
		{
			if (visited[it->first] && !visited[it2->first] && pRG->findEdge(it->second,it2->second))
			{
				std::cout << it->first << " -> " << it2->first << std::endl;
			}
		}
	}
	*/
	int sum = 0;
	for (auto it2=s->edges.begin();it2!=s->edges.end();it2++)
	{
		Edge* pE = *it2;
		sum+=pE->flow;
	}
	std::cout << s->id << " -> " << t->id << "\tmax flow\t" << sum << std::endl;
    return sum;
}

Graph* buildResidualGraph(Graph* pG)
{
	pG->directed = true;
	pG->edgeMap.clear();
	for (auto it=pG->vertexMap.begin();it!=pG->vertexMap.end();it++)
	{
		Vertex* pV = it->second;
		for (auto it2=pV->edges.begin();it2!=pV->edges.end();it2++)
		{
			Edge* pE = *it2;
			std::string key = int_to_string(pE->pOriginV->id) + "," + int_to_string(pE->pDestV->id);
			pG->edgeMap[key] = pE;
		}
	}
	return pG;
}

Graph* restoreResidualGraph(Graph* pG)
{
	for (auto it=pG->edgeMap.begin();it!=pG->edgeMap.end();it++)
	{
		Edge* pE = it->second;
		pE->flow = 0;
	}
	return pG;
}

void runMaxFlow(Graph* pG)
{
	Vertex* pU;
	Vertex* pV;
	Graph* pRG = buildResidualGraph(pG);
	std::unordered_map<int,int> maxFlowMap;
	int flow;

	for (int i = 0; i < pG->vertices.size(); i++)
	{
		pU = pG->vertices[i];
		for (int j = i; j < pG->vertices.size(); j++)
		{
			pV = pG->vertices[j];
			if (pU->id != pV->id)
			{
				flow = maxFlow(pRG, pU, pV);
				maxFlowMap[pU->id] += flow;
				maxFlowMap[pV->id] += flow;
				pRG = restoreResidualGraph(pRG);
			}
		}
	}

	std::map<double, int> distMap;

	std::cout << "Node\tMax Flow Score" << std::endl;
	for ( auto i = maxFlowMap.begin(); i != maxFlowMap.end(); i++ ) 
	{
		double flow = i->second;
		distMap[flow]++;
		std::cout << i->first << "\t" << i->second << std::endl;
	} 
}

void edgeConnectivity(Graph* pG)
{
	int minEdge = pG->getEdgeSize();
	Vertex* pS = pG->findVertex(0);

	Graph* pRG = buildResidualGraph(pG);
	
	for (auto it=pRG->vertexMap.begin();it!=pRG->vertexMap.end();it++)
	{
		Vertex* pV = it->second;
		if (pS->id != pV->id)
		{
			int flow = maxFlow(pRG, pS, pV);
			pRG = restoreResidualGraph(pRG);
			minEdge = std::min(minEdge,flow);
		}
	}
	std::cout << "Edge connectivity: " << minEdge;
}