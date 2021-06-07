#include "abc_index.h"

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

bool operator<(const UndirectedGraph& first, const UndirectedGraph& second) {
	return first.CountVertex() < second.CountVertex();
}

int FianAllKekTree(int count_vertex) {
	auto all_graph = GenerateAllSimpleGraph(count_vertex);
	std::vector<UndirectedGraph> all_tree;
	
	for (const auto& graph : all_graph) {
		if (IsTree(graph)) {
			all_tree.push_back(graph);
		}
	}
	
	std::vector<std::pair<double, UndirectedGraph>> idx;
	for (const auto& graph : all_tree) {
		idx.push_back({abc_index(graph), graph});
	}
	int cnt = 0;
	std::sort(idx.begin(), idx.end());
	for (int i = 1; i < static_cast<int>(idx.size()); ++i) {
		if (std::fabs(idx[i].first - idx[i - 1].first) < 1e-6) {
			auto g_first = idx[i - 1].second;
			auto g_second = idx[i].second;
			if (g_first.CountEdge() == g_second.CountEdge() && !check_isomorphism(g_first, g_second)) {
				++cnt;
				std::cout << "first graph:" << std::endl;
				g_first.PrintAdjMatrix();
				std::cout << "second graph:" << std::endl;
				g_second.PrintAdjMatrix();

			}
		}
	}
	
	return cnt;
}
