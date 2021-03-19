#include <iostream>
#include "graph.h"
#include "isomorphism.h"

int main() {
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
	return 0;
}