
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


