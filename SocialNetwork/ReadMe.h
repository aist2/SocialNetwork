#include <string>

using namespace std;
string readMe = string("Please run the program with following arguments: \n\n ")
		+ string("SocialNetwork <graph_gen_type> <graph_input_file> <algo_option> \n\n")
		+ string("graph_gen_type: \n")
		+ string("0: random graph \n")
		+ string("1: preferential graph \n")
		+ string("2: load real graph from file (we assume the delimiter is space) \n\n")
		+ string("graph_input_file: \n")
		+ string("for random graph/ preferential graph, put node size here. \n")
		+ string("for real graph, put file path. \n\n")
		+ string("prob: \n")
		+ string("int probability for random/preferential graph, placeholder if read from file \n\n" )
		+ string("algo_option: \n")
		+ string("0: degree distribution \n")
		+ string("1: triangle_brutal \n")
		+ string("2: triangle_forward \n")
		+ string("3: find_connected_components_DFS \n")
		+ string("4: find_connected_components_BFS \n")
		+ string("5: diameter_brutal \n")
		+ string("6: diameter_approximation \n")
		+ string("7: virus_propagate \n");
