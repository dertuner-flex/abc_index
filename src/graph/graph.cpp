#include "graph.h"

UndirectedGraph::UndirectedGraph(const std::vector<std::vector<int>>& adj_list) : adj_list_(adj_list) {
	count_vertex_ = static_cast<int>(adj_list_.size());
	count_edge_ = CalculateCountEdge();
}

int UndirectedGraph::CountVertex() const {
	return count_vertex_;
}

int UndirectedGraph::CountEdge() const {
	return count_edge_;
}

int UndirectedGraph::CalculateCountEdge() const {
	int count = 0;
	for (const auto& vertex_adj_list : adj_list_) {
		for (const auto& vertex : vertex_adj_list) {
			++count;
		}
	}
	return count / 2;
}

std::vector<int> UndirectedGraph::AllDegrees() const {
	std::vector<int> result;
	for (size_t i = 0; i < adj_list_.size(); ++i) {
		result.push_back(adj_list_[i].size());
	}
	return result;
}

std::vector<std::vector<int>> UndirectedGraph::AdjMatrix() const {
	std::vector<std::vector<int>> adj_matrix(count_vertex_, std::vector<int>(count_vertex_));
	for (size_t i = 0; i < adj_list_.size(); ++i) {
		for (size_t j = 0; j < adj_list_[i].size(); ++j) {
			adj_matrix[i][j] = 1;
		}
	}
	return adj_matrix;
}
