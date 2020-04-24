#include<bits/stdc++.h>

#define ll long long
#define pb push_back

using namespace std;

//! Contains graph-related operations
/*!
    Consists of class functions and helper methods for implementing Ford Fulkerson Algorithm
*/

class Graph {

private:

    /*! Graph stored in form of adjacency list*/
    vector<vector<int>> graph;
    /*! Residual graph stored in form of adjacency list*/
    vector<vector<int>> res_graph;
    /*! Array for storing the path and indegree of nodes*/
    vector<int> path, indegree;
    /*! Initializing max_flow to 0 */
    int max_flow = 0;
    int s, t, no_of_vertex;
    int delta = 1 << 20;

    //! Utility function which uses BFS to check node t is reachable from source s*/
    /*!
        \return True if the node t is reachable from source s, else False
    */
    bool breadth_first_search() {

        vector<int> visited(no_of_vertex, 0);
        queue<int> q;
        q.push(s);
        visited[s] = 1;
        path[s] = -1;

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            for (int i = 0; i < no_of_vertex; i++) {
                if (visited[i] == 0 and res_graph[u][i] > delta) {
                    path[i] = u;
                    q.push(i);
                    visited[i] = 1;
                }
            }

        }

        if (visited[t] == 1)
            return true;
        else
            return false;

    }

public:

    //! Graph constructor for initializing the graph
    /*!
        \param n the number of vertices present in the graph
    */
    Graph(int n) {
        graph.resize(n + 2, vector<int>(n + 2, 0));
        res_graph.resize(n + 2, vector<int>(n + 2, 0));
        no_of_vertex = n;
        path.resize(n + 2, -1);
        indegree.resize(n + 2, 0);
    }

    //! Member function for adding edge to the graph
    /*!
        \param a node 1
        \param b node 2
        \param capacity the edge weight between node a and b
    */
    void add_edge(int a, int b, int capacity) {
        graph[a][b] = capacity;
        indegree[b]++;
    }

    //! Member function to build residual graph from a given graph
    void build_residual_graph() {
        for (int i = 0; i < no_of_vertex; i++)
            for (int j = 0; j < no_of_vertex; j++)
                res_graph[i][j] = graph[i][j];

    }

    //! Member function to implement ford-fulkerson algorithm
    /*!
        \param start The starting node
        \param end The end node
        \return The resulting max flow between the nodes
    */
    int ford_fulkerson(int start, int end) {
        s = start;
        t = end;
        delta = 1 << 20;

        while (breadth_first_search() == true or delta > 0) {
            if (breadth_first_search() == false) {
                delta /= 2;
                continue;
            }

            int flow = INT_MAX;

            for (int v = t; v != s; v = path[v]) {
                int u = path[v];
                flow = min(flow, res_graph[u][v]);
            }

            for (int v = t; v != s; v = path[v]) {
                int u = path[v];
                res_graph[u][v] -= flow;
                res_graph[v][u] += flow;
            }
            max_flow += flow;

        }
        return max_flow;
    }

    //! Member function to find the minimum st-cut of a flow graph
    /*!
        \return Edges corresponding to the minimum st-cut of the given network flow graph
    */
    vector<pair<int, int>> find_st_cut() {
        vector<int> s_set(no_of_vertex, 0);

        queue<int> q;
        q.push(s);
        s_set[s] = 1;

        while(!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < no_of_vertex; i++) {
                if (s_set[i] == 0 and res_graph[u][i] > 0) {
                    s_set[i] = 1;
                    q.push(i);
                }
            }
        }

        vector<pair<int, int>> edges;
        for (int i = 0; i < no_of_vertex; i++)
            for (int j = 0; j < no_of_vertex; j++)
                if (s_set[i] == 1 and s_set[j] == 0 and graph[i][j] > 0)
                    edges.push_back(make_pair(i, j));

        return edges;
    }

    //! Member function for solving max bipartite matching problem
    /*!
        \return Edges corresponding to the bipartite matching
    */
    vector<pair<int, int>> max_bipartite_matching() {
        // no_of_vertex, no_of_vertex + 1

        int start = no_of_vertex;
        int end = no_of_vertex + 1;

        for (int i = 0; i < no_of_vertex; i++) {
            if (indegree[i] == 0)
                graph[start][i] = 1;
            else
                graph[i][end] = 1;
        }

        no_of_vertex += 2;

        build_residual_graph();
        cout << "max flow: " << ford_fulkerson(start, end) << endl;

        vector<pair<int, int>> edges;
        for (int i = 0; i < no_of_vertex - 2; i++)
            for (int j = 0; j < no_of_vertex - 2; j++)
                if (res_graph[j][i] > 0 and graph[i][j] > 0)
                    edges.push_back(make_pair(i, j));

        return edges;


    }

};

void task2(Graph graph){
    auto st_cut_edges = graph.find_st_cut();
    for (auto edge: st_cut_edges)
        cout << edge.first << " " << edge.second << endl;

}

void task1(){
    int n, m;
    cin >> n >> m;

    int start, end;
    cin >> start >> end;

    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int a, b, cap;
        cin >> a >> b >> cap;
        graph.add_edge(a, b, cap);
    }

    graph.build_residual_graph();
    cout << "max flow: " << graph.ford_fulkerson(start, end) << endl;

    task2(graph);
}

void task3(){
    int e, n, m;
    cin >> e >> n >> m;

    Graph graph(n + m);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph.add_edge(a - 1, n + b - 1, 1);
        // graph.add_edge(n + b - 1, a - 1, 1);
    }

    auto mbpm_edges = graph.max_bipartite_matching();
    for (auto edge: mbpm_edges)
        cout << edge.first << " " << edge.second << endl;

    task2(graph);
}

int main() {

    //Using text files for input output
    #ifndef ONLINE_JUDGE
    freopen("./test/input/task3b.txt", "r", stdin);
    freopen("./test/output/task3b.txt", "w", stdout);
    #endif

	auto start = std::chrono::steady_clock::now();
    // task1();
    task3();
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
    cout << "Execution Time: " << std::chrono::duration <double, milli> (diff).count() << "ms" << endl;
    return 0;
}