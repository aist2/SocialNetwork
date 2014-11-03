#include "Header.h"

int virusPropagate(Graph* pG, int startVertexId)
{
	//std::cout << "Virus propagating..." << std::endl;

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
	}

	//flush infected flag
	for ( auto i = infectedVertices.begin(); i != infectedVertices.end(); i++ ) 
	{
		Vertex* pV = *i;
		pV->infected = false;
	} 

	
	//std::cout << "Virus propagating DONE" << std::endl;
	std::cout << "id: " << startVertexId << ", degree: " << pVStart->getEdgeSize() << ", popularity: " << round << std::endl;
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

std::map<long, long> computePopularity(Graph* pG) {
	clock_t timeElapsed = clock();
	std::map<long, long> resultMap;
	//int popularity;

	for ( auto i = pG->vertices.begin(); i != pG->vertices.end(); i++ ) 
	{
		Vertex* pV = *i;
		pV->popularity = virusPropagate(pG, pV->id);
		resultMap[pV->popularity]++;
	} 

	timeElapsed = clock() - timeElapsed;
	std::cout << "Time taken to compute popularity: " << ((float)timeElapsed)/CLOCKS_PER_SEC << " second(s)\n";
	return resultMap;
}
