import numpy as np
import math
import networkx as nx
import matplotlib.pyplot as plt

def show_graph_with_labels(adjacency_matrix, mylabels, color_map):
    rows, cols = np.where(adjacency_matrix == 1)
    edges = zip(rows.tolist(), cols.tolist())
    gr = nx.Graph()
    all_rows = range(0, adjacency_matrix.shape[0])
    for n in all_rows:
        gr.add_node(n)
    gr.add_edges_from(edges)
    nx.draw(gr, node_size=200, labels=mylabels, with_labels=True, node_color=color_map)
    plt.show()


def read_file_bytes(filename, offset=0):
	file_bytes = bytearray()
	with open(filename, 'rb') as f:
		f.seek(offset)
		current_byte = f.read(1)
		while current_byte:
			file_bytes.extend(current_byte)
			current_byte = f.read(1)
	return file_bytes

def deserialize(filename):
	file_bytes = read_file_bytes('graph_first')
	count_element_in_adj_matrix = file_bytes[0]
	n_vertex = int(math.sqrt(count_element_in_adj_matrix))
	assert n_vertex * n_vertex == count_element_in_adj_matrix, "incorrect count element"
	adj_matrix = np.zeros((n_vertex, n_vertex), dtype=np.int64)
	idx = 0
	for i in range(n_vertex):
		for j in range(n_vertex):
			adj_matrix[i][j] = file_bytes[1 + idx]
			idx += 1

	print(adj_matrix)
	num_to_label = lambda x: 'x'
	labels = {e:num_to_label(e) for e in range(n_vertex)}
	show_graph_with_labels(adj_matrix, labels, ['red'] * adj_matrix.shape[0])
	show_graph_with_labels(adj_matrix, labels, ['red'] * adj_matrix.shape[0])

deserialize('graph_first')