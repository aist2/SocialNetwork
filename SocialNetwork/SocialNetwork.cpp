// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "Header.h"

/**
 * Print Functions
 */
void printDegreeDistribution(std::map<long, long> result)
{
	std::cout << "===Degree Distribution===" << std::endl;
	std::cout << "Degree\tCount" << std::endl;
	std::map<long, long>::iterator iter;
	for (iter = result.begin(); iter != result.end(); ++iter)
		std::cout << iter->first << '\t' << iter->second << '\n';
	std::cout << "===Degree Distribution===" << std::endl;
}

void printTriangles(std::vector<std::tuple<int, int, int>> result)
{
	std::cout << "===Triangles===" << std::endl;
	for (unsigned i = 0; i < result.size(); i++) {
		std::tuple<int, int, int> triangleNode = result[i];
		std::cout << "(" << std::get<0>(triangleNode) << ", " << std::get<1>(triangleNode) << ", " << std::get<2>(
				triangleNode) << ")\n";
	}
	std::cout << "Number of triangles in total: " << result.size() << std::endl;
	std::cout << "===Triangles===" << std::endl;
}

void printConnectedComponents(std::vector<Graph*> result)
{
	std::cout << "The graph has " << result.size() << " connected components; they are:\n";
	for (unsigned i = 0; i < result.size(); i++) {
		std::cout << "=== Component " << i+1 << " ===" << std::endl;
		result[i]->printEdges();
		std::cout << std::endl;
	}
}

/**
 * Main
 */
int main(int argc, const char* argv[])
{
	Graph* pG;
	//pG = generateRandomGraph(10, 50);
	//pG = generatePreferentialGraph(500, 75);
	pG = readRealGraph(argv[1], ' ');
	//pG->printEdges();
	//pG->printVertices();

	std::cout << "Number of nodes: " << pG->getVertexSize() << std::endl;
	std::cout << "Number of edges: " << pG->getEdgeSize() << std::endl;

	std::vector<Graph*> connectedComponents = findConnectedComponentsDFS(pG);
	printConnectedComponents(connectedComponents);
	//printDegreeDistribution(pG->computeDegreeDistribution());
	//std::vector<Graph*> connectedComponents = findConnectedComponentsBFS(pG);
	//printConnectedComponents(connectedComponents);
	//printDegreeDistribution(pG->computeDegreeDistribution());
	//std::vector <std::tuple<int,int,int>> triangles = pG->getAllTriangles_brutal();
	//printTriangles(triangles);
	//virusPropagate(pG,0);
	//printDegreeDistribution(computePopularity(pG));
	//system("PAUSE");
	return 0;
}




