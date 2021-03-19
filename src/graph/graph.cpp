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
			adj_matrix[i][adj_list_[i][j]] = 1;
		}
	}
	return adj_matrix;
}

std::vector<std::vector<int>> UndirectedGraph::ConvertAdjMatrixToAdjList(const std::vector<std::vector<int>>& adj_matrix) {
	int n_vertex = static_cast<int>(adj_matrix.size());
	std::vector<std::vector<int>> adj_list(n_vertex, std::vector<int>());
	for (int i = 0; i < n_vertex; ++i) {
		for (int j = 0; j < n_vertex; ++j) {
			if (adj_matrix[i][j] == 1) {
				adj_list[i].push_back(j);
			}
		}
	}
	return adj_list;
}

std::vector<std::vector<int>> UndirectedGraph::ConvertAdjListToAdjMatrix(const std::vector<std::vector<int>>& adj_list) {
	int n_vertex = static_cast<int>(adj_list.size());
	std::vector<std::vector<int>> adj_matrix;
	for (int i = 0; i < n_vertex; ++i) {
		for (int j = 0; j < adj_list[i].size(); ++j) {
			int vertex = i, to = adj_list[i][j];
			adj_matrix[vertex][to] = 1;
		}
	}
	return adj_matrix;
}

void UndirectedGraph::PrintAdjMatrix(std::ostream& out) const {
	auto adj_matrix = AdjMatrix();
	for (const auto& row : adj_matrix) {
		for (const auto& element : row) {
			out << element << " ";
		}
		out << std::endl;
	}
}

void UndirectedGraph::Serialize(std::ostream& out) {
	const int max_possible_size = 127;
	int count_element_in_adj_matrix = count_vertex_ * count_vertex_;
	assert(count_element_in_adj_matrix <= max_possible_size);
	char len = static_cast<char>(count_element_in_adj_matrix);
	auto adj_matrix = AdjMatrix();
	out.write(&len, 1);
	for (int i = 0; i < count_vertex_; ++i) {
		for (int j = 0; j < count_vertex_; ++j) {
			char current_byte = 0;
			if (adj_matrix[i][j] == 1) {
				current_byte = 1;
			}
			out.write(&current_byte, 1);
		}
	}
}

const std::vector<std::vector<int>> UndirectedGraph::AdjList() const {
	return adj_list_;
}


UndirectedGraph GenerateKthSimpleGraph(int n_vertex, uint64_t bit_representation) {
	assert(n_vertex <= 8);
	uint64_t step = 0;
	std::vector<std::vector<int>> adj_matrix(n_vertex, std::vector<int>(n_vertex, 0));
	for (int i = 0; i < n_vertex; ++i) {
		for (int j = i + 1; j < n_vertex; ++j) {

			adj_matrix[i][j] = (bit_representation >> step) & 1;
			++step;
			adj_matrix[j][i] = adj_matrix[i][j];
		}
	}
	auto adj_list = UndirectedGraph::ConvertAdjMatrixToAdjList(adj_matrix);
	return UndirectedGraph(adj_list);
}

std::vector<UndirectedGraph> GenerateAllSimpleGraph(int n_vertex) {
	uint64_t max_number_edge = (n_vertex) * (n_vertex - 1) / 2;
	uint64_t count_simple_graph = (1 << (max_number_edge));
	std::vector<UndirectedGraph> result;
	for (uint64_t current_representation = 0; current_representation < count_simple_graph; ++current_representation) {
		result.push_back(GenerateKthSimpleGraph(n_vertex, current_representation));
	}
	return result;
}
