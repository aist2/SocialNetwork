#include "Header.h"

int virusPropagate(Graph* pG, int startVertexId)
{
	std::cout << "id " << startVertexId << " virus propagating..." << std::endl;

	int nodeSize = pG->getVertexSize();
	int startInfectSize;
	int endInfectSize;
	int round;
	std::vector <Vertex*> infectedVertices;
	Vertex* pVStart = pG->findVertex(startVertexId);
	if (pVStart == NULL)
	{
		throw "Start node not found!";
	}
	infectIt(pVStart, &infectedVertices);
	startInfectSize = 0;
	endInfectSize = 1;
	round = 0;

	if (pVStart->getEdgeSize() == 0)
	{
		std::cout << "Isolated vertex." << std::endl;
		return -1;
	}

	while (endInfectSize > startInfectSize)
	{
		round++;
		//std::cout << "Round " << round << std::endl;
		startInfectSize = infectedVertices.size();
		std::vector <Vertex*> newInfectedVertices;
		for ( auto i = infectedVertices.begin(); i != infectedVertices.end(); i++ ) 
		{
			Vertex* pV = *i;
			Vertex* pVFriend = pickOneFriend(pV);
			if (pVFriend == NULL)
			{
				continue;
			}
			infectIt(pVFriend, &newInfectedVertices);
		}
		infectedVertices.reserve( infectedVertices.size() + newInfectedVertices.size() ); // preallocate memory
		infectedVertices.insert( infectedVertices.end(), newInfectedVertices.begin(), newInfectedVertices.end() );
		endInfectSize = infectedVertices.size();
		//std::cout << "Round " << round << "\tinfected nodes " << (endInfectSize) << std::endl;
	}

	//flush infected flag
	for ( auto i = infectedVertices.begin(); i != infectedVertices.end(); i++ ) 
	{
		Vertex* pV = *i;
		pV->infected = false;
	} 

	std::cout << "id: " << startVertexId << ", degree: " << pVStart->getEdgeSize() << ", rounds: " << round << std::endl;

	pVStart->popularity = int(40000/double(round));
	return round;
}

void infectIt(Vertex* pV, std::vector <Vertex*> * pList)
{
 		pV->infected = true;
		pList->push_back(pV);
		//std::cout << "Infecting " << pV->id << std::endl;
		return;
}

Vertex* pickOneFriend(Vertex* pV)
{
	std::vector <Vertex*> uninfectedFriends;

	for ( auto i = pV->edges.begin(); i != pV->edges.end(); i++ ) 
	{
		Edge* pE = *i;
		Vertex* pVTemp = pE->pDestV;
		if (!pVTemp->infected)
		{
			uninfectedFriends.push_back(pVTemp);
		}
	}
	if (uninfectedFriends.size() > 0)
	{
		return randomPick(&uninfectedFriends);
	}
	else
	{
		return NULL;
	}
}

Vertex* randomPick(std::vector <Vertex*>* pVector)
{
	srand ( time(NULL) );
	int randomIndex = rand() % pVector->size();
	return (*pVector)[randomIndex];
}

std::map<double, int> computePopularityDistribution(Graph* pG) {
	clock_t timeElapsed = clock();
	std::map<double, int> resultMap;

	for ( auto i = pG->vertexMap.begin(); i != pG->vertexMap.end(); i++ ) 
	{
		Vertex* pV = i->second;
		//pV->popularity = virusPropagate(pG, pV->id);
		virusPropagate(pG, pV->id);
		resultMap[pV->popularity]++;
	} 

	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute popularity: " << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
	return resultMap;
}

void printDistribution(std::map<double, int> result, std::string tag) {
	std::cout.precision(5);
	std::cout << "===" << tag << " Distribution===" << std::endl;
	std::cout << tag << "\tCount" << std::endl;
	for (auto iter = result.begin(); iter != result.end(); ++iter)
		std::cout << std::fixed << iter->first << '\t' << iter->second << '\n';
	std::cout << "===" << tag << " Distribution===" << std::endl;
}

std::unordered_map<int,int> Dijkstra(Graph* pG, Vertex* pVS)
{
	int max_weight = std::numeric_limits<int>::max();
    std::unordered_map<int,int> min_distance;
    std::unordered_map<int,Vertex*> previous;
    
    min_distance[pVS->id] = 0;
    
    std::set<std::pair<int, Vertex*> > vertex_queue;
	for (auto it=pG->vertexMap.begin(); it!=pG->vertexMap.end();it++)
	{
		if (it->second->id != pVS->id)
		{
			min_distance[it->second->id] = max_weight;
			previous[it->second->id] = NULL;
		}
		vertex_queue.insert(std::make_pair(min_distance[it->second->id], it->second));
	}
    while (!vertex_queue.empty()) 
    {
        int dist = vertex_queue.begin()->first;
        Vertex* pU = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
		for ( auto i = pU->edges.begin(); i != pU->edges.end(); i++ ) 
		{
			Vertex* pV = (*i)->pDestV;
			
            int distance_through_u = dist + 1;
			if (distance_through_u < min_distance[pV->id]) {
				vertex_queue.erase(std::make_pair(min_distance[pV->id], pV));
 
				min_distance[pV->id] = distance_through_u;
				previous[pV->id] = pU;
				vertex_queue.insert(std::make_pair(min_distance[pV->id], pV));
			}
        }
    }
	return min_distance;
}

std::map<double,int> computeShortestPath(Graph* pG)
{
	std::map<int,int> farness;
	std::map<int,double> closeness;
	std::map<double,int> closenessDistribution;
	std::map<double,int> farnessDistribution;

	std::cout.precision(5);
	for ( auto i = pG->vertexMap.begin(); i != pG->vertexMap.end(); i++ ) 
	{
		Vertex* pV = i->second;
		farness[pV->id] = 0;
		std::unordered_map<int,int> min_distance = Dijkstra(pG,pV);
		for (auto it=min_distance.begin(); it != min_distance.end();it++)
		{
			//std::cout << "id\t" << pV->id << "\tto\t" << it->first << "\tis\t" << it->second << std::endl;
			farness[pV->id] += it->second;
		}
	}

	for ( auto i = farness.begin(); i != farness.end(); i++ ) 
	{
		closeness[i->first] = int(200000/double(i->second));
		std::cout << "id\t" << i->first << "\tFarness\t" << i->second << 
			"\tcloseness\t" << std::fixed << closeness[i->first] << std::endl;
	}

	for ( auto i = closeness.begin(); i != closeness.end(); i++ ) 
	{
		closenessDistribution[i->second]++;
	}
	
	for ( auto i = farness.begin(); i != farness.end(); i++ ) 
	{
		farnessDistribution[i->second]++;
	}
	return closenessDistribution;
}