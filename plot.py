from pygraphviz import *
import os

map_int = lambda list_: list(map(int, list_.strip().split()))
color = 'green'

def draw_graph():
    input_list = sorted(os.listdir('test/input'))
    output_list = sorted(os.listdir('test/output'))

    for idx, (in_file, out_file) in enumerate(zip(input_list, output_list)):
        img_name = 'graph{}.png'.format(idx)
        graph = AGraph(strict=True, directed=True)

        with open(os.path.join('./test/input', in_file), 'r') as f:
            n_node, n_edge = map_int(f.readline())
            node_list = [i for i in range(1, n_node+1)]
            graph.add_nodes_from(node_list)

            edge_list = [map_int(f.readline()) for i in range(n_edge)]
            graph.add_edges_from(edge_list)
        
        with open(os.path.join('./test/output', out_file), 'r') as f:
            for line in f.readlines():
                if len(line.strip().split()) > 1:
                    node_list = map_int(line)
                    for node_idx in node_list:
                        node = graph.get_node(node_idx)
                        node.attr['color'] = color
                        node.attr['style'] = 'filled'

        graph.draw(os.path.join('./test/plot', img_name), prog='circo')

if __name__ == "__main__":
    draw_graph()
