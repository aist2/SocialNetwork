Please run the program with following arguments: 

SocialNetwork <graph_gen_type> <nodeSize|graph_input_file> <prob> <algo_option> 

graph_gen_type: 
0: random graph
1: preferential graph
2: load real graph from file (we assume the delimiter is space)

nodeSize|graph_input_file:
for random graph/ preferential graph, place node size here
for real graph, put file path

prob:
int probability for random/preferential graph, placeholder if read from file

algo_option:
0: degree distribution
1: triangle_brutal
2: triangle_forward
3: find_connected_components_DFS
4: find_connected_components_BFS
5: diameter_brutal
6: diameter_approximation
7: virus_propagate

