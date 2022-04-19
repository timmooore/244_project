
#include "UndirectedGraph.h"

// Default constructor creates arrays of Vertex and Edge pointers
// of sizes MAX_NO_VERTICES and MAX_NO_EDGES defined in Graph header
UndirectedGraph::UndirectedGraph() {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
}

// Copy constructor creates new arrays and adds vertices and edges from
// UndirectedGraph to be copied

UndirectedGraph::UndirectedGraph(const UndirectedGraph& udg) {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
	for (int i = 0; i < udg.no_vertices; ++i) addVertex(*udg.nodes[i]);
	//for (int i = 0; i < udg.no_edges; ++i) addEdge(*udg.edges[i]);
}

// Virtual destructor destroys all of the dynamically allocted vertices
// and edges that are allocated in functions addVertex and addEdge,
// the deletes the pointer arrays

UndirectedGraph::~UndirectedGraph() {
	for (int i = 0; i < no_vertices; ++i)
		delete nodes[i];
	for (int i = 0; i < no_edges; ++i)
		delete edges[i];
	delete[] nodes;
	delete[] edges;
}

// addVertex dynamically allocates Vertex objects in the Vertex pointer
// array nodes if the no of vertices is less than MAX_NO_VERTICES and returns
// true. Also increments the number of vertices.

bool UndirectedGraph::addVertex(Vertex& v) {
	if (no_vertices >= MAX_NO_EDGES)
		return false;
	nodes[no_vertices++] = new Vertex(v.getValue());
	return true;
}

vector<vector<Edge> > DirectedGraph::getPaths(Vertex<int> &v,
		unordered_map<int, bool> is_visited) {
	// cout << "Calling getPaths for node " << v.getValue() << endl;
	unordered_map<int, bool> new_visited = is_visited;
	new_visited[v.getValue()] = true;
	vector<vector<Edge> > paths;
	vector<Edge> pt;
	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()
				&& new_visited[edges[i]->getDest()->getValue()] == false) {
			//new_visited[edges[i]->getDest()->getValue()] = true;
			pt.push_back(*edges[i]);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getDest(),
					new_visited);
			// if (!childPaths.isEmpty())
			for (int j = 0; j < childPaths.size(); ++j) {
				for (Edge e : childPaths[j]) pt.push_back(e);
				paths.push_back(pt);
				pt.clear();
				pt.push_back(*edges[i]);
			}
			pt.clear();
		} else if (edges[i]->getDest()->getValue() == v.getValue()
				&& new_visited[edges[i]->getSource()->getValue()] == false) {
			//new_visited[edges[i]->getSource()->getValue()] = true;
			Edge e(edges[i]->getDest(), edges[i]->getSource(), edges[i]->getWeight());
			pt.push_back(e);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getSource(),
					new_visited);
			// if (!childPaths.isEmpty())
			for (int j = 0; j < childPaths.size(); ++j) {
				for (Edge e : childPaths[j]) pt.push_back(e);
				paths.push_back(pt);
				pt.clear();
				pt.push_back(e);
			}
			pt.clear();
		}
	}
	return paths;
}

vector< vector<Edge> > getPaths(Vertex<int>&, unordered_map<int, bool>);


