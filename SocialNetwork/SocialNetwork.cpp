// SocialNetwork.cpp : Defines the entry point for the console application.
//
#include "Header.h"
#include "ReadMe.h"
using namespace std;

/**
 * Print Functions
 */
void printDegreeDistribution(map<long, long> result) {
	cout << "===Degree Distribution===" << endl;
	cout << "Degree\tCount" << endl;
	map<long, long>::iterator iter;
	for (iter = result.begin(); iter != result.end(); ++iter)
		cout << iter->first << '\t' << iter->second << '\n';
	cout << "===Degree Distribution===" << endl;
}

void printTriangles(vector<tuple<int, int, int>> result) {
	cout << "===Triangles===" << endl;
	for (unsigned i = 0; i < result.size(); i++) {
		tuple<int, int, int> triangleNode = result[i];
		cout << "(" << get < 0 > (triangleNode) << ", " << get < 1 > (triangleNode) << ", " << get < 2
				> (triangleNode) << ")\n";
	}
	cout << "Number of triangles in total: " << result.size() << endl;
	cout << "===Triangles===" << endl;
}

void printConnectedComponents(vector<Graph*> result) {
	cout << "The graph has " << result.size() << " connected components; they are:\n";
	for (unsigned i = 0; i < result.size(); i++) {
		cout << "=== Component " << i + 1 << " ===" << endl;
		result[i]->printEdges();
		cout << endl;
	}
}

Graph* readGraphInMain(string arg1, string arg2, string arg3) {
	int i = atoi(arg1.c_str());

	switch (i) {
	case 1:
	{
		int nodeSize = atoi(arg2.c_str());
		int prob = atoi(arg3.c_str());
		return generateRandomGraph(nodeSize, prob);
		break;
	}
	case 2:
	{
		int nodeSize = atoi(arg2.c_str());
		int prob = atoi(arg3.c_str());
		return generatePreferentialGraph(nodeSize, prob);
		break;
	}
	case 3:
		return readRealGraph(arg2, ' ');
		break;
	default:
		cout << "invalid option; please specify 1/2/3 for graph generation type";
		exit(0);
	}
}

void runAlgoInMain(string arg, Graph* pG) {
	int i = atoi(arg.c_str());
	switch (i) {
	case 0:
		printDegreeDistribution(pG->computeDegreeDistribution());
		break;
	case 1:
	{
		vector<tuple<int, int, int>> triangles = getAllTriangles_brutal(pG);
		printTriangles(triangles);
		break;
	}
	case 2:
	{
		vector<tuple<int, int, int>> triangles = getAllTriangles_forward(pG);
		printTriangles(triangles);
		break;
	}
	case 3:
	{
		vector<Graph*> connectedComponents = findConnectedComponentsDFS(pG);
		printConnectedComponents(connectedComponents);
		break;
	}
	case 4:
	{
		vector<Graph*> connectedComponents = findConnectedComponentsBFS(pG);
		printConnectedComponents(connectedComponents);
		break;
	}
	case 5:
		cout << "Diameter by brutal force: " << computeDiameter_brutal(pG) << endl;
		break;
	case 6:
		cout << "Diameter by approximation: " << computeDiameter(pG, 3) << endl;
		break;
	case 7:
		virusPropagate(pG, 0);
		break;
	default:
		cout << "invalid option; please specify 1/2/3/4/5/6/7 for algo type";
		exit(0);
	}
}
/**
 * Main
 */
int main(int argc, const char* argv[]) {
	Graph* pG;
	//pG = generateRandomGraph(1000, 5);
	//pG = generatePreferentialGraph(500, 75);
	if (argc < 5) {
		cout << readMe;
		exit(0);
	}
	//pG = readRealGraph(argv[1], ' ');
	//pG->printEdges();
	//pG->printVertices();
	pG = readGraphInMain(argv[1], argv[2], argv[3]);
	cout << "Number of nodes: " << pG->getVertexSize() << endl;
	cout << "Number of edges: " << pG->getEdgeSize() << endl;

	runAlgoInMain(argv[4], pG);
	//vector<Graph*> connectedComponents = findConnectedComponentsBFS(pG);
	//printConnectedComponents(connectedComponents);
	//cout << "Diameter by brutal force: " << computeDiameter_brutal(pG) << endl;
	//cout << "Diameter by approximation: " << computeDiameter(pG, 3) << endl;
	//vector<Graph*> connectedComponents = findConnectedComponentsDFS(pG);
	//std::cout << "Diameter by brutal force: " << computeDiameter_brutal(pG) << std::endl;
	//std::cout << "Diameter by approximation: " << computeDiameter(pG, 3) << std::endl;
	//printDegreeDistribution(pG->computeDegreeDistribution());
	//std::vector<Graph*> connectedComponents = findConnectedComponentsBFS(pG);
	//printConnectedComponents(connectedComponents);
	//printDegreeDistribution(pG->computeDegreeDistribution());
	//vector <tuple<int,int,int>> triangles = getAllTriangles_brutal(pG);
	//vector<tuple<int, int, int>> triangles = getAllTriangles_forward(pG);
	//printTriangles(triangles);
	virusPropagate(pG,11);
	//printDegreeDistribution(computePopularity(pG));
	//system("PAUSE");
	return 0;
}

