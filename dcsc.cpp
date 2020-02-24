#include<bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;
ll medge = 0;
ll mnodes = 1;

//! Contains set-related operations
/*! 
	Used for set operations like union, intersection, and difference. 
*/
class Set {
public:

	//! Finds the intersection of two given sets represented as vectors
	/*!
		\param a vector argument representing set 1
		\param b vector argument representing set 2
		\result Intersection of vectors a and b
	*/
	static vector<ll> get_intersection(vector<ll> a, vector<ll> b) {
		ll result_size = a.size() + b.size();
		vector<ll> result(result_size, -1);
		vector<ll>::iterator it, st;
		it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), result.begin());
		return clear_output(result);
	}

	//! Finds the union of the two given sets represented as vectors
	/*!
		\param a vector argument representing set 1
		\param b vector argument representing set 2
		\result Union of vectors a and b
	*/

	static vector<ll> get_union(vector<ll> a, vector<ll> b) {
		ll result_size = a.size() + b.size();
		vector<ll> result(result_size, -1);
		vector<ll>::iterator it, st;
		it = set_union(a.begin(), a.end(), b.begin(), b.end(), result.begin());
		return clear_output(result);
	}

	//! Finds the difference between two given sets represented as vectors
	/*!
		\param a vector argument representing set 1
		\param b vector argument representing set 2
		\result Difference between vectors a and b
	*/

	static vector<ll> get_subtract(vector<ll> a, vector<ll> b) {
		ll result_size = a.size() + b.size();
		vector<ll> result(result_size, -1);
		vector<ll>::iterator it, st;
		it = set_difference(a.begin(), a.end(), b.begin(), b.end(), result.begin());
		return clear_output(result);
	}

private:
	static vector<ll> clear_output(vector<ll> a) {
		vector<ll> result;
		for (ll i = 0; i < a.size(); i++)
			if (a[i] != -1)
				result.pb(a[i]);
		return result;
	}
};

//! Contains operations related to Graphs
/*!
	Consists of class functions and helper methods for implementing DCSC algorithm
*/

class Graph {
public:

	/*! Number of vertices present in graph */
	ll no_of_vertices;
	/*! Number of edges present in graph */
	ll no_of_edges;
	/*! Graph stored in form of adjacency list */
	vector<vector<ll>> graph;
	/*! Graph stored in an inverted fashion */
	vector<vector<ll>> graph_inverted;

	//! Constructor for initializing the graphs
	/*!
		\param no_vertices The total number of vertices present in the graph
		\param no_edged The total number of edges present in the graph
	*/
	Graph(ll no_vertices, ll no_edges) {
		// cout << "graph built using constructor.\n";
		no_of_vertices = no_vertices;
		no_of_edges = no_edges;

		for (ll i = 0; i < no_vertices; i++) {
			graph.pb(vector<ll>(0));
			graph_inverted.pb(vector<ll>(0));
		}
		// cout << "graph size: " << graph.size() << endl;
	}

	//! Member function for inserting edges between two vertices into the graph
	/*! 
		\param from Vertex 1
		\param to Vertex 2 
	*/
	void insert_edge(ll from, ll to) {
		// cout << "inserting edge: " << from << " to " << to << endl; 
		graph[from].pb(to);
		graph_inverted[to].pb(from);
	}

	//! Member function to print vertices present in the graph
	/*! 
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
	*/
	void print_vertices(vector<ll> vertex_set) {
		for (ll i = 0; i < vertex_set.size(); i++) {
			if (vertex_set[i] == 1)
				cout << i << " ";
		}
		cout << endl;
	}

	//! Member function to find a random vertex in the graph
	/*!
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
		\return Random vertex v
	*/

	ll random_vertex(vector<ll> vertex_set) {
		for (ll i = 0; i < vertex_set.size(); i++)
			if (vertex_set[i] == 1)
				return i;
		return -1;
	}

	//! Member function which returns total number of edges present in graph
	/*!
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
		\return Number of edges
	*/ 

	ll edge_count(vector<ll> vertex_set) {

		ll edge_c = 0;
		for (ll i = 0; i < no_of_vertices; i++)
			for (ll j = 0; j < graph[i].size(); j++)
				if (vertex_set[i] == 1 and vertex_set[graph[i][j]] == 1)
					edge_c++;
		return edge_c;
	}

	//! Member function to find predecessor vertices of a vertex v in a Graph
	/*!
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
		\param v Vertex v whose predecessors have to be calculated
		\return Vector consisting of vertices which are predecessors of vertex v
	*/

	vector<ll> pred(vector<ll> vertex_set, ll v) {
		vector<ll> result(no_of_vertices, 0);
		vector<ll> vis(no_of_vertices, 0);
		result[v] = 1;
		vis[v] = 1;
		get_pred(v, vertex_set, result, vis);
		std::vector<ll> result_set;
		for (ll i = 0; i < no_of_vertices; i++)
			if (result[i] == 1)
				result_set.pb(i);
		return result_set;
	}

	//! Member function to find descendant vertices of a vertex v in a Graph
	/*!
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
		\param v Vertex v whose descendants have to be calculated
		\return Vector consisting of vertices which are descendants of vertex v
	*/

	vector<ll> desc(vector<ll> vertex_set, ll v) {
		vector<ll> result(no_of_vertices, 0);
		vector<ll> vis(no_of_vertices, 0);
		result[v] = 1;
		vis[v] = 1;
		get_descendent(v, vertex_set, result, vis);
		std::vector<ll> result_set;
		for (ll i = 0; i < no_of_vertices; i++)
			if (result[i] == 1)
				result_set.pb(i);
		return result_set;
	}

	//! Member function which returns vertices corresponding to a given vertex_set
	/*!
		\param vertex_set A vector representing vertices in terms of 1 and 0, 1 if the vertex is present in graph and 0 otherwise
		\return Set of vertices represented by the vertex_set
	*/

	vector<ll> get_vector_set(vector<ll> vertex_set) {
		std::vector<ll> ans;
		for (ll i = 0; i < vertex_set.size(); i++)
			if (vertex_set[i] == 1)
				ans.pb(i);
		return ans;
	} 

private:
	void get_descendent(ll v, vector<ll> vertex_set, vector<ll> &result, vector<ll> &vis) {
		
		for (ll i = 0; i < graph[v].size(); i++) {
			ll y = graph[v][i];
			if (vertex_set[y] == 1 and vis[y] == 0) {
				result[y] = 1;
				vis[y] = 1;
				get_descendent(y, vertex_set, result, vis);
			}
		}
	}

	void get_pred(ll v, vector<ll> vertex_set, vector<ll> &result, vector<ll> &vis) {
		for (ll i = 0; i < graph_inverted[v].size(); i++) {
			ll y = graph_inverted[v][i];
			if (vertex_set[y] == 1 and vis[y] == 0) {
				result[y] = 1;
				vis[y] = 1;
				get_pred(y, vertex_set, result, vis);
			}
		}
	}
};

void print_vector(std::vector<ll> v) {
	for (ll i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

void dcsc(Graph graph, vector<ll> vertex_vector) {

	std::vector<ll> vertex_set(graph.no_of_vertices, 0);
	for (ll i = 0; i < vertex_vector.size(); i++)
		vertex_set[vertex_vector[i]] = 1;

	// cout << "vertex vector: ";
	// print_vector(vertex_set);
	// cout << endl;

	// cout << "edge count: " << graph.edge_count(vertex_set) << endl;
	if (graph.edge_count(vertex_set) == 0) {
		
		// cout << "Ans: ";
		for (ll i = 0; i < vertex_set.size(); i++)
			if (vertex_set[i] == 1)
				cout << i << endl;
	}
	else {
		ll v = graph.random_vertex(vertex_set);
		// cout << "random vector: " << v << endl;
		// cout << "pred: ";
		// print_vector(graph.pred(vertex_set, v));
		// cout << endl;

		// cout << "desc: ";
		// print_vector(graph.desc(vertex_set, v));
		// cout << endl;

		vector<ll> scc = Set::get_intersection(graph.pred(vertex_set, v), graph.desc(vertex_set, v));
		// cout << "Ans: ";
		print_vector(scc);

		std::vector<ll> temp_vertex_set(graph.no_of_vertices, 0);
		for (ll i = 0; i < scc.size(); i++)
			temp_vertex_set[scc[i]] = 1;
		medge = max(medge, graph.edge_count(temp_vertex_set));
		mnodes = max(mnodes, (ll)scc.size());

		dcsc(graph, Set::get_subtract(graph.pred(vertex_set, v), scc));
		dcsc(graph, Set::get_subtract(graph.desc(vertex_set, v), scc));
		vector<ll> rem = Set::get_subtract(graph.get_vector_set(vertex_set), Set::get_union(graph.pred(vertex_set, v), graph.desc(vertex_set, v)));
		dcsc(graph, rem);
	}

}

int main() {

    //Using text files for input output
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ll n, m;
    cin >> n >> m;
    Graph graph(n, m);
    std::vector<ll> vertex_set;
    for (ll i = 0; i < n; i++)
    	vertex_set.pb(i);

    for (ll i = 0; i < m; i++) {
    	ll a, b;
    	cin >> a >> b;
    	graph.insert_edge(a, b);
    }

    dcsc(graph, vertex_set);
    // cout << "medge: " << medge << endl;
    // cout << "mnodes: " << mnodes << endl;
    return 0;
}