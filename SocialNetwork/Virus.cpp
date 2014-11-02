#include "Header.h"

void virusPropagate(Graph* pG, int startVertexId)
{
	std::cout << "Virus propagating..." << std::endl;

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
	while (endInfectSize > startInfectSize)
	{
		round++;
		std::cout << "Round " << round << std::endl;
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

	std::cout << "Virus propagating DONE" << std::endl;
	return;
}

void infectIt(Vertex* pV, std::vector <Vertex*> * pList)
{
 		pV->infected = true;
		pList->push_back(pV);
		std::cout << "Infecting " << pV->id << std::endl;
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