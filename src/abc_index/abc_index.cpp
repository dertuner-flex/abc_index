#include "abc_index.h"
#include "graph.h"

double abc_index(const UndirectedGraph& graph) {
	auto degrees = graph.AllDegrees();
	auto f = [](double x, double y) {
		return sqrt((x + y - 2) / (x * y));
	};
	double index = 0;
	auto adj_list = graph.AdjList();
	for (int i = 0; i < adj_list.size(); ++i) {
		for (int j = 0; j < adj_list[i].size(); ++j) {
			int u = i, v = adj_list[i][j];
			index += f(degrees[u], degrees[v]);
		}
	}

	return index / 2;
}

std::vector<std::pair<UndirectedGraph, UndirectedGraph>> FindAllPairNonIsomorphicGraphWithSameABCIndex(int count_vertex) {
	const double EPS = 1e-6;
	auto all_graph = GenerateAllSimpleGraph(count_vertex);
	
	for (int i = static_cast<int>(all_graph.size()) - 1; i >= 0; --i) {
		for (int j = static_cast<int>(all_graph.size()) - 1; j >= 0; --j) {
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

}
