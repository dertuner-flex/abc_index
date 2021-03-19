#include <iostream>
#include <fstream>
#include "graph.h"
#include "isomorphism.h"
#include "abc_index.h"

int main() {
	const double EPS = 1e-6;
	auto all_graph = GenerateAllSimpleGraph(6);
	
	for (size_t i = 0; i < all_graph.size(); ++i) {
		for (size_t j = 0; j < all_graph.size(); ++j) {
			if (i == j) {
				continue;
			}
			double index_first = abc_index(all_graph[i]);
			double index_second = abc_index(all_graph[j]);

			if (all_graph[i].CountEdge() == all_graph[j].CountEdge() && std::fabs(index_first - index_second) < EPS 
				&& !check_isomorphism(all_graph[i], all_graph[j])) {
				std::cout << "different graph with same ABC-index" << std::endl;
				std::cout << "first graph:" << std::endl;
				all_graph[i].PrintAdjMatrix();
				std::cout << "second graph:" << std::endl;
				all_graph[j].PrintAdjMatrix();
				std::cout << std::endl;
			}
		}
	}
	
	//for (const auto& graph : all_graph) {
	//	graph.PrintAdjMatrix();
	//	std::cout << abc_index(graph) << std::endl;
	//}
	//std::ofstream fout("graph_first", std::ofstream::binary);
	//all_graph[1].Serialize(fout);
	//fout.close();
/*
	std::cout << "count graph: " << all_graph.size() << std::endl;
	for (const auto& graph : all_graph) {
		graph.PrintAdjMatrix();
		std::cout << std::endl;
	}
*/

/*
	int n_vertex, n_edge;
	std::cin >> n_vertex >> n_edge;
	std::vector<std::vector<int>> adj_list_first(n_vertex, std::vector<int>());
	std::vector<std::vector<int>> adj_list_second(n_vertex, std::vector<int>());
	std::cout << "input first graph:\n" << std::endl;
	for (int i = 0; i < n_edge; ++i) {
		int u, v;
		std::cin >> u >> v;
		adj_list_first[u].push_back(v);
		adj_list_first[v].push_back(u);
	}

	std::cout << "input second graph:\n" << std::endl;
	for (int i = 0; i < n_edge; ++i) {
		int u, v;
		std::cin >> u >> v;
		adj_list_second[u].push_back(v);
		adj_list_second[v].push_back(u);
	}

	UndirectedGraph g_first(adj_list_first);
	UndirectedGraph g_second(adj_list_second);

	std::cout << "isomorphism = " << check_isomorphism(g_first, g_second) << std::endl;
*/
	return 0;
}