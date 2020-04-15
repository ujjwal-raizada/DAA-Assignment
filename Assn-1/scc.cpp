#include <bits/stdc++.h>
#include <iostream> 
using namespace std;

class Graph
{
    /*! No. of vertices */
    int V;
    /*! An adjacency list for the graph */
    vector<vector<int> > adj;
    //! A function to get vertices in increasing order of discovery and finishing times according to DFS
    /*!
        \param v Vertex from which DFS has been started
        \param Stack A utility stack to keep record of vertices processed in order
        \param visited array to keep record of visited nodes
    */
    void makeorder(int v,vector<int> &Stack, int visited[]); 

    //! A recursive function to print vertices inorder of their DFS starting from v
    /*!
        \param visited An array to keep record of visited vertices
        \param v Starting vertex
    */
    void DFS(int visited[],int v); // A recursive function to print vertices inorder of their DFS starting from v

    public:
        //! Constructor for the graph
        /*!
            \param V total number of vertices present in the graph
        */
        Graph(int V); 
        //! Function to add an edge to the adjacency list of the graph
        /*!
            \param v Vertex 1
            \param w Vertex 2
        */
        void Edge(int v, int w); 
        /*! Function to calculate strongly connected components */
        void SCCs(); 
         /*! Function to get transpose of our graph */
        Graph getTranspose();
};

Graph::Graph(int v) //Constructor for the graph with no. of vertices as input
{ 
    V = v; 
    vector<int> x;
    for(int i=0;i<V;i++)
    {
    adj.push_back(x); //Adjacent each vertex push an empty list
    }
}  

void Graph::DFS(int visited[],int v) // A recursive function to print vertices inorder of their DFS starting from v 
{  
    visited[v] = 1; // Mark v as visited and also print it
    cout << v << " "; 
      
    for(int i= 0;i<adj[v].size();i++) // Recursive call of DFS function for all the vertices reachable from this vertex
    {
        if(visited[adj[v][i]]!=1)
            DFS(visited,adj[v][i]);
    } 
}
 
Graph Graph::getTranspose() //This function gets transpose of the graph
{ 
    Graph g(V); 
    for (int v = 0; v < V; v++) 
    { 
        for(int i= 0;i<adj[v].size();i++) //A vertex adj[v][i] was in adjacency list of v, we need to add v to adjacency list of adj[v][i]
        { 
            g.adj[adj[v][i]].push_back(v);
        }
 
    } 
    return g; 
}


void Graph::Edge(int v, int w) //A function to add an edge in the graph
{ 
    adj[v].push_back(w); // Adding w to v’s adjacency list 
} 

void Graph::makeorder(int v, vector<int> &Stack, int visited[])
{
    visited[v] = 1; // Mark v as visited 

    for(int i=0;i<adj[v].size();i++) // Recursively call makeorder function for all the vertices reachable from this vertex
    {
        if(visited[adj[v][i]]!=1)
            makeorder(adj[v][i],Stack,visited);
    } 
  
    Stack.push_back(v);  // Push v into the stack since all vertices adjacent to v are processed
}
 
void Graph::SCCs() // A function that finds and prints all strongly connected components
{ 
    vector<int> Stack; //Use a stack for storing the finish times of the vertices

    int visited[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = 0; // Initialize the visited array as not visited (all zeros)  

    for(int i = 0; i < V; i++) 
        if(visited[i] == 0) 
            makeorder(i,Stack,visited); // Call the makeorder function for each unvisited vertex to fill vertices in stack according to their finishing times 
   
    Graph graph_transpose = getTranspose(); //Get the transpose of the graph 
  
    for(int i = 0; i < V; i++) 
        visited[i] = 0; // Initialize the visited array as not visited (all zeros)
  
    while (Stack.empty() == 0) // Now process all vertices in order defined by Stack
    {
        int v = Stack.back(); 
        Stack.pop_back(); // Pop a vertex from stack 
        if (visited[v] == 0) // Print Strongly connected component of the popped vertex 
        { 
            graph_transpose.DFS(visited,v); 
            cout << endl; 
        }       
    } 
} 

int main()// Main 
{ 
    //Using text files for input output
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int vertices, edges;
    cin >> vertices >> edges; //take no. of vertices and edges as input
    Graph g(vertices); //Initialize the constructor for the graph
    for(int i = 0; i < edges; i++)
    {
        int a, b; 
        cin >> a >> b; // take the directed edge a->b as input
        g.Edge(a, b);  
    }
  
    cout << "The Following are strongly connected components in given graph \n"; 
    
    auto start = std::chrono::steady_clock::now();
    g.SCCs(); 
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Execution Time: " << std::chrono::duration <double, milli> (diff).count() << "ms" << endl;
    
  
    return 0; 
}
