#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include "graph.h"
#include "isomorphism.h"
#include "abc_index.h"


std::vector<std::string> read_lines(std::ifstream& in) {
	std::string buffer;
	std::vector<std::string> result;
	for (std::string line; std::getline(in, line); ) {
		if (!line.empty()) {
			result.push_back(line);
		}
	}

	return result;
}

std::vector<std::string> split_by_del(std::string s, std::string delim) {
    std::vector<std::string> result;
    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
    	result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    result.push_back(s.substr(start, end));
	return result;
}

std::vector<std::string> split_by_graph_token(const std::vector<std::string>& lines) {
	auto is_header = [](const std::string& str) {return str.find("Graph") == 0; };
	size_t current_idx = 0;
	std::vector<std::string> result;
	while (current_idx < lines.size()) {
		while (current_idx < lines.size() && !is_header(lines[current_idx])) {
			++current_idx;			
		}
		if (current_idx == lines.size()) {
			break;
		}
		auto order = lines[current_idx].substr(lines[current_idx].find("order") + 5 + 1);
		order.erase(--order.end());
//		++current_idx;
		std::string current_graph;
		for (int i = 0; i < std::stoi(order); ++i) {
			++current_idx;
			current_graph += lines[current_idx];
		}
		result.push_back(current_graph);
	}


	return result;
} 

std::string remove_space(std::string str) {
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

std::vector<std::vector<int>> construct_graph(std::string graph) {
	auto adj_list = split_by_del(graph, ";");
	int nvertex = 0;
	for (const auto& vertex : adj_list) {
		auto start_and_to = split_by_del(vertex, ":");
		if (start_and_to.size() == 2) {
			++nvertex;
		}
	}
	std::vector<std::vector<int>> result(nvertex, std::vector<int>());
	auto delete_space = [](const std::string& s) {};
	for (const auto& vertex : adj_list) {
		auto start_and_to = split_by_del(vertex, ":");
		if (start_and_to.size() != 2) {
			break;
		}
		auto from = std::stoi(remove_space(start_and_to[0]));
		auto to_list = split_by_del(start_and_to[1], " ");
		
		for (const auto& to : to_list) {
			auto value = remove_space(to);
			if (!value.empty()) {
				result[from].push_back(std::stoi(value));
//				std::cout << std::stoi(remove_space(to)) << " ";
			}
		}
	}
	

	return result;
}

std::vector<std::vector<std::vector<int>>> parse_graphs(const std::string& filename) {
	std::ifstream fin(filename);
	auto lines = read_lines(fin);
	auto tokens = split_by_graph_token(lines);
	
	std::vector<std::vector<std::vector<int>>> result;
	for (const auto& token : tokens) {
		result.push_back(construct_graph(token));
	}

	return result;
}

int64_t factorial(int n) {
	int64_t result = 1;
	for (int i = 2; i <= n; ++i) {
		result *= i;
	}
	return result;
}

int64_t cnk(int64_t n, int64_t k) {
	if (k == 2) {
		return n * (n - 1) / 2;
	} else {
		return factorial(n) / (factorial(n - k) * factorial(k));
	}
}


template<typename T>
T identity(const T& x) {
	return x;
}

template<typename T, typename U>
T get_first_element(const std::pair<T, U>& element) {
	return element.first;
}

template<typename T, typename U>
U get_second_element(const std::pair<T, U>& element) {
	return element.second;
}

bool is_equal(double first, double second, double EPS = 1e-6) {
	return std::fabs(first - second) < EPS;
}

template<typename T, typename Getter, typename Equals>
std::vector<int> split_into_groups(const std::vector<T>& elements, Getter getter, Equals equal) {
	if (elements.empty()) {
		return {};
	}
	std::vector<int> groups_size;
	auto last_element = getter(elements[0]);
	int current_size = 0;
	for (const auto& element : elements) {
		auto current = getter(element);
		if (equal(current, last_element, 1e-6)) {
			++current_size;
		} else {
			groups_size.push_back(current_size);
			current_size = 1;
		}
		last_element = current;
	}
	groups_size.push_back(current_size);
	return groups_size;
}



template<typename Index>
double accuracy(const std::vector<UndirectedGraph>& graphs, const Index& topological_index) {
	std::vector<std::pair<double, int>> values;
	int current_idx = 0;
	for (const auto& graph : graphs) {
		values.emplace_back(topological_index(graph), current_idx);
		++current_idx;
	}
	std::sort(values.begin(), values.end());

	for (const auto [value, number] : values) {
		std::cout << value << " " << number << std::endl;
	}
	std::cout << std::endl;

	auto groups_size = split_into_groups(values, get_first_element<double, int>, is_equal);
	int64_t degeneration_count_pair = 0;
	for (const auto& group_size : groups_size) {
		degeneration_count_pair += cnk(group_size, 2);
	}
	std::cout << "deg pair = " << degeneration_count_pair << " all pair = " <<  cnk(graphs.size(), 2) << std::endl;
	double accuracy_final = static_cast<double>(degeneration_count_pair) / cnk(graphs.size(), 2);
	return accuracy_final;

}
int main() {
	const double EPS = 1e-6;
	auto raw_graphs = parse_graphs("data");
	std::vector<UndirectedGraph> graphs;
	for (const auto& raw_graph : raw_graphs) {
		graphs.push_back(UndirectedGraph(raw_graph));
	}

	std::cout << "accuracy = " << accuracy(graphs, abc_index) << std::endl;
	return 0;

/*
	for (int i = static_cast<int>(all_graph.size()) - 1; i >= 0; --i) {
		for (int j = static_cast<int>(all_graph.size()) - 1; j >= 0; --j) {
			if (i == j) {
				continue;
			}
			double index_first = abc_index(all_graph[i]);
			double index_second = abc_index(all_graph[j]);

			if (all_graph[i].CountEdge() == all_graph[j].CountEdge() && IsTree(all_graph[i]) && IsTree(all_graph[j]) 
				&& std::fabs(index_first - index_second) < EPS  
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
*/

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