#include<bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

class Set {
public:
	static vector<ll> get_intersection(vector<ll> a, vector<ll> b) {
		ll result_size = a.size() + b.size();
		vector<ll> result(result_size, -1);
		vector<ll>::iterator it, st;
		it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), result.begin());
		return clear_output(result);
	}

	static vector<ll> get_union(vector<ll> a, vector<ll> b) {
		ll result_size = a.size() + b.size();
		vector<ll> result(result_size, -1);
		vector<ll>::iterator it, st;
		it = set_union(a.begin(), a.end(), b.begin(), b.end(), result.begin());
		return clear_output(result);
	}

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

class Graph {
public:
	ll no_of_vertices;
	ll no_of_edges;
	vector<vector<ll>> graph;
	vector<vector<ll>> graph_inverted;

	Graph(ll no_vertices, ll no_edges) {
		cout << "graph built using constructor.\n";
		no_of_vertices = no_vertices;
		no_of_edges = no_edges;

		for (ll i = 0; i < no_vertices; i++) {
			graph.pb(vector<ll>(0));
			graph_inverted.pb(vector<ll>(0));
		}
		cout << "graph size: " << graph.size() << endl;
	}

	void insert_edge(ll from, ll to) {
		cout << "inserting edge: " << from << " to " << to << endl; 
		graph[from].pb(to);
		graph_inverted[to].pb(from);
	}

	void print_vertices(vector<ll> vertex_set) {
		for (ll i = 0; i < vertex_set.size(); i++) {
			if (vertex_set[i] == 1)
				cout << i << " ";
		}
		cout << endl;
	}

	ll random_vertex(vector<ll> vertex_set) {
		for (ll i = 0; i < vertex_set.size(); i++)
			if (vertex_set[i] == 1)
				return i;
		return -1;
	}

	ll edge_count(vector<ll> vertex_set) {

		ll edge_c = 0;
		for (ll i = 0; i < no_of_vertices; i++)
			for (ll j = 0; j < graph[i].size(); j++)
				if (vertex_set[i] == 1 and vertex_set[graph[i][j]] == 1)
					edge_c++;
		return edge_c;
	}

	vector<ll> pred(vector<ll> vertex_set, ll v) {
		vector<ll> result;
		vector<ll> vis(no_of_vertices, 0);
		result.pb(v);
		vis[v] = 1;
		get_pred(v, vertex_set, result, vis);
		sort(result.begin(), result.end());
		return result;
	}

	vector<ll> desc(vector<ll> vertex_set, ll v) {
		vector<ll> result;
		vector<ll> vis(no_of_vertices, 0);
		result.pb(v);
		vis[v] = 1;
		get_descendent(v, vertex_set, result, vis);
		sort(result.begin(), result.end());
		return result;
	}

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
				result.pb(y);
				vis[y] = 1;
				get_descendent(y, vertex_set, result, vis);
			}
		}
	}

	void get_pred(ll v, vector<ll> vertex_set, vector<ll> &result, vector<ll> &vis) {
		for (ll i = 0; i < graph_inverted[v].size(); i++) {
			ll y = graph_inverted[v][i];
			if (vertex_set[y] == 1 and vis[y] == 0) {
				result.pb(y);
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

	cout << "vertex vector: ";
	print_vector(vertex_set);
	cout << endl;

	cout << "edge count: " << graph.edge_count(vertex_set) << endl;
	if (graph.edge_count(vertex_set) == 0) {
		
		cout << "Ans: ";
		graph.print_vertices(vertex_set);
	}
	else {
		ll v = graph.random_vertex(vertex_set);
		cout << "random vector: " << v << endl;
		cout << "pred: ";
		print_vector(graph.pred(vertex_set, v));
		cout << endl;

		cout << "desc: ";
		print_vector(graph.desc(vertex_set, v));
		cout << endl;

		vector<ll> scc = Set::get_intersection(graph.pred(vertex_set, v), graph.desc(vertex_set, v));
		cout << "Ans: ";
		print_vector(scc);
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
    return 0;
}