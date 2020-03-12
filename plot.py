import networkx as nx
import random
import matplotlib.pyplot as plt
import os

map_int = lambda list_: list(map(int, list_.strip().split()))
colors = ['green', 'red', 'blue', 'pink', 'orange']
color_map = None

def draw_graph():
    input_list = sorted(os.listdir('test/input'))
    output_list = sorted(os.listdir('test/output'))
    graph = nx.DiGraph()

    for idx, (in_file, out_file) in enumerate(zip(input_list, output_list)):
        img_name = 'graph{}.png'.format(idx)
        graph.clear()
        with open(os.path.join('./test/input', in_file), 'r') as f:
            n_node, n_edge = map_int(f.readline())
            print ("Number of nodes : {} \t Number of edges : {}".format(n_node, n_edge))
            color_map = [colors[0] for i in range(n_node)]

            node_list = [i for i in range(n_node)]
            graph.add_nodes_from(node_list)

            edge_list = [map_int(f.readline()) for i in range (n_edge)]
            graph.add_edges_from(edge_list)

        with open(os.path.join('./test/output', out_file), 'r') as f:
            for line in f.readlines():
                if line[0].isalpha(): continue
                node_list = map_int(line)
                color = random.choice(colors)
                for node in node_list:
                    color_map[node] = color

        nx.draw_spring(graph, alpha=0.3, width=0.3,
                       linewidths=1.0, node_color=color_map,
                       arrows=True, node_size=50, with_labels=False)
        plt.savefig(os.path.join('./test/plot', img_name))

if __name__ == "__main__":
    a = draw_graph()
