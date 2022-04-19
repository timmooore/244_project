/*
 * DirectedGraph.cpp
 *
 *  Created on: Mar. 15, 2022
 *      Author: timothymoore
 */

#include "DirectedGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include <vector>

// Default constructor creates arrays of Vertex and Edge pointers
// of sizes MAX_NO_VERTICES and MAX_NO_EDGES defined in DirectedGraph header

DirectedGraph::DirectedGraph() {
	nodes = new Vertex*[MAX_NO_VERTICES];
	edges = new Edge*[MAX_NO_EDGES];
}

// Copy constructor creates new arrays and adds vertices and edges from
// DirectedGraph to be copied

DirectedGraph::DirectedGraph(const DirectedGraph& dg) {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
	for (int i = 0; i < dg.no_vertices; ++i) addVertex(*dg.nodes[i]);
	for (int i = 0; i < dg.no_edges; ++i) addEdge(*dg.edges[i]);
}

// Virtual destructor destroys all of the dynamically allocted vertices
// and edges that are allocated in functions addVertex and addEdge,
// the deletes the pointer arrays

DirectedGraph::~DirectedGraph() {
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

bool DirectedGraph::addVertex(Vertex &v) {
	if (no_vertices >= MAX_NO_EDGES)
		return false;
	nodes[no_vertices++] = new Vertex(v.getValue());
	return true;
}

// Similar to addVertex, the same function is performed but using an
// array of Vertex pointers as input and the number of vertices to be added

bool DirectedGraph::addVertices(Vertex *vArray, int no_vertices) {
	if (this->no_vertices + no_vertices >= MAX_NO_VERTICES)
		return false;
	for (int i = 0; i < no_vertices; ++i) {
		nodes[this->no_vertices++] = new Vertex(vArray[i].getValue());
	}
	return true;
}

// searchVertex iterates through the array of Vertex pointers and checks
// if the values match the value of the vertex passed to the function.
// Returns true if found and false otherwise

bool DirectedGraph::searchVertex(const Vertex &v) {
	for (int i = 0; i < no_vertices; ++i) {
		if (nodes[i]->getValue() == v.getValue())
			return true;
	}
	return false;
}

// Similarly to searchVertex, searchEdge checks that both the source
// and dest vertices in the edge have the same values of those as the
// edge passed as a parameter

bool DirectedGraph::searchEdge(const Edge &e) {
	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getDest()->getValue() == e.getDest()->getValue()
				&& edges[i]->getSource()->getValue()
						== e.getSource()->getValue()
				&& edges[i]->getWeight() == e.getWeight())
			return true;
	}
	return false;
}

// Remove vertex is tricky. First it checks if the vertex is in the graph,
// using searchVertex, and returns false if it is not. If the vertex is found,
// it deallocates the memory and removes it from the nodes array. Then, it
// searches for each edge containing the deleted vertex as either source or
// dest, and removes those edges from the graph.

bool DirectedGraph::removeVertex(Vertex &v) {
	if (searchVertex(v) == false)
		return false;
	int index = 0;
	for (; index < no_vertices; ++index) {
		if (nodes[index]->getValue() == v.getValue()) {
			break;
		}
	}
	delete nodes[index];
	for (; index < no_vertices - 1; ++index) {
		nodes[index] = nodes[index + 1];
	}
	nodes[index] = nullptr;
	no_vertices--;

	// Need to delete all edges associated with this vertex

	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()
				|| edges[i]->getDest()->getValue() == v.getValue()) {
			remove(*edges[i]);
			i--;
		}

	}
	return true;
}

// Displays the graph as a set of integer values corresponding to the
// values of the vertices and a second set of sets of an ordered pair of
// vertices corresponding to the source and dest vertices, and an integer
// value corresponding to the weight.

void DirectedGraph::display() const {
	if (no_vertices == 0) {
		cout << "Graph is empty\nV = empty set\nE = empty set" << endl;
		return;
	}
	cout << "V = {";
	for (int i = 0; i < no_vertices - 1; ++i)
		cout << nodes[i]->getValue() << ", ";

	cout << nodes[no_vertices - 1]->getValue() << "}" << endl;

	if (no_edges == 0) {
		cout << "E = empty set" << endl;
		return;
	}
	cout << "E = {";
	for (int i = 0; i < no_edges - 1; ++i) {
		edges[i]->print();
		cout << ", ";
	}
	edges[no_edges - 1]->print();
	cout << "}" << endl;
}

// addEdge checks that both the vertices of the edges it is attempting
// to add exist in the graph and that the number of edges is less than the
// maximum. If so it dynamically allocates memory for the new edge in the
// array of Edge pointers. Uses isPath function to check that there isn't
// already a patch from the destination of input Edge e to the source of
// input Edge e, since this would result in a cycle in e was added

bool DirectedGraph::addEdge(Edge &e) {
	if (no_edges >= MAX_NO_EDGES || !searchVertex(*e.getSource())
			|| !searchVertex(*e.getDest()) || searchEdge(e))
		return false;
	if (isPath(*e.getDest(), *e.getSource())) {
		cout << "Cannot add edge: adding this edge creates a cycle..." << endl;
		return false;
	}
	edges[no_edges++] = new Edge(e.getSource(), e.getDest(), e.getWeight());
	return true;
}

// removeEdge checks whether the edge exists and removes it

bool DirectedGraph::remove(Edge &e) {
	if (searchEdge(e) == false) return false;
	int index = 0;
	for (; index < no_edges; ++index) {
		if (edges[index]->getSource()->getValue() == e.getSource()->getValue()
				&& edges[index]->getDest()->getValue()
						== e.getDest()->getValue()
				&& edges[index]->getWeight() == e.getWeight())
			break;
	}
	delete edges[index];
	for (; index < no_edges - 1; ++index) {
		edges[index] = edges[index + 1];
	}
	edges[index] = nullptr;
	no_edges--;
	return true;
}

// toString implemented the same as display but all elements are passed to
// a string instead of cout

string DirectedGraph::toString() const {
	string s = "";
	if (no_vertices == 0) {
		s = "V = empty set\nE = empty set";
		return s;
	}
	s = "V = {";
	for (int i = 0; i < no_vertices - 1; ++i)
		s = s + to_string(nodes[i]->getValue()) + ", ";
	s = s + to_string(nodes[no_vertices - 1]->getValue()) + "}\n";

	if (no_edges == 0) {
		s += "E = empty set";
		return s;
	}
	s += "E = {";
	for (int i = 0; i < no_edges - 1; ++i) {
		s = s + "{(" + to_string(edges[i]->getSource()->getValue()) + ", "
				+ to_string(edges[i]->getDest()->getValue()) + "), "
				+ to_string(edges[i]->getWeight()) + "}, ";
	}
	s = s + "{(" + to_string(edges[no_edges - 1]->getSource()->getValue())
			+ ", " + to_string(edges[no_edges - 1]->getDest()->getValue())
			+ "), " + to_string(edges[no_edges - 1]->getWeight()) + "}}";
	return s;
}



vector<vector<Edge> > DirectedGraph::getPaths(Vertex &v) {
	vector<vector<Edge> > paths;
	vector<Edge> pt;
	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()) {
			pt.push_back(*edges[i]);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getDest());
			for (int j = 0; j < childPaths.size(); ++j) {
				for(Edge& e : childPaths[j]) pt.push_back(e);
				paths.push_back(pt);
				pt.clear();
				pt.push_back(*edges[i]);
			}
			pt.clear();
		}
	}
	return paths;
}

bool DirectedGraph::isPath(Vertex& u, Vertex& v) {
	vector< vector<Edge> > paths;
	paths = getPaths(u);
	for (vector<Edge> path : paths) {
		if (path.back().getDest()->getValue() == v.getValue()) return true;
	}
	return false;
}

void DirectedGraph::printAllPaths() {
	vector< vector< Edge > > paths;
	for (int i = 0; i < no_vertices; ++i) {
		paths = getPaths(*nodes[i]);
		for (vector<Edge> path : paths) {
			for (Edge& e : path) {
				cout << e.getSource()->getValue() << " -> ";
			}
			cout << path.back().getDest()->getValue();
			cout << endl;
		}
		paths.clear();
	}
}

bool DirectedGraph::clean() {
	while (no_vertices > 0) {
		if (removeVertex(*nodes[no_vertices - 1]) == false)
			return false;
	}
	return true;
}

// comparison operator uses arrays of booleans corresponding to each
// vertex and edge of the graphs to be compared. It first checks if the
// number of edges and vertices are the same and if so it assigns true
// to each index in the bool array of there is an identical edge or
// vertex in both graphs. It finally checks whether all values in each
// array are set to true, and returns true if so

bool DirectedGraph::operator==(const DirectedGraph &dg) {
	if (no_vertices != dg.getNoVertices())
		return false;
	if (no_edges != dg.getNoEdges())
		return false;
	bool vertex_present[MAX_NO_VERTICES];
	bool edge_present[MAX_NO_EDGES];
	for (int i = 0; i < no_vertices; ++i)
		vertex_present[i] = false;
	for (int i = 0; i < no_edges; ++i)
		edge_present[i] = false;
	for (int i = 0; i < no_vertices; ++i) {
		for (int j = 0; j < no_vertices; ++j) {
			if (nodes[i]->getValue() == dg.getNodes()[j]->getValue()) {
				vertex_present[i] = true;
			}
		}
	}

	for (int i = 0; i < no_edges; ++i) {
		for (int j = 0; j < no_edges; ++j) {
			if (edges[i]->getSource()->getValue()
					== dg.getEdges()[j]->getSource()->getValue()
					&& edges[i]->getDest()->getValue()
							== dg.getEdges()[j]->getSource()->getValue()) {
				edge_present[i] = true;
			}
		}
	}
	for (int i = 0; i < no_vertices; ++i) {
		if (vertex_present[i] == false)
			return false;
	}
	for (int i = 0; i < no_edges; ++i) {
		if (edge_present[i] == false)
			return false;
	}
	return true;
}

// Deallocates the memory of the graph to be assigned to, then
// adds edges and vertices back to the graph from the graph to
// be assigned from

DirectedGraph& DirectedGraph::operator=(const DirectedGraph &dg) {
	if (no_vertices != 0) {
		for (int i = 0; i < no_vertices; ++i) {
			removeVertex(*nodes[i]);
			i--;
		}
	}
	if (no_edges != 0) {
		for (int i = 0; i < no_edges; ++i) {
			remove(*edges[i]);
			i--;
		}
	}
	for (int i = 0; i < dg.getNoVertices(); ++i)
		addVertex(*(dg.getNodes()[i]));

	for (int i = 0; i < dg.getNoEdges(); ++i)
		addEdge(*(dg.getEdges()[i]));

	return *this;
}

// Iterates over all edges and increments the weight using
// setWeight

DirectedGraph& DirectedGraph::operator++() {
	for (int i = 0; i < no_edges; ++i) {
		int w = edges[i]->getWeight();
		edges[i]->setWeight(++w);
	}
	return *this;
}

// Creates a copy of the graph to return the original values,
// then increments the weights of all the edges in the graph
// the postfix increment was called from

DirectedGraph DirectedGraph::operator++(int) {
	DirectedGraph og;
	og = *this;
	for (int i = 0; i < no_edges; ++i) {
		int w = edges[i]->getWeight();
		edges[i]->setWeight(++w);
	}
	return og;
}

// Creates new graph and adds edges and vertices from each of the
// two graphs to be added.

DirectedGraph DirectedGraph::operator+(const DirectedGraph &dg) {
	if (this->no_vertices + dg.no_vertices > MAX_NO_VERTICES
			|| this->no_edges +dg.no_edges > MAX_NO_EDGES)
		throw "Cannot add graphs, sum of vertices or sum of edges is greater "
		"than maximum allowed size.";
	DirectedGraph new_graph;
	for (int i = 0; i < no_vertices; ++i)
		new_graph.addVertex(*nodes[i]);

	for (int i = 0; i < dg.getNoVertices(); ++i)
		new_graph.addVertex(*dg.getNodes()[i]);

	for (int i = 0; i < no_edges; ++i)
		new_graph.addEdge(*edges[i]);

	for (int i = 0; i < dg.getNoEdges(); ++i) new_graph.addEdge(*dg.getEdges()[i]);
		
	return new_graph;
}

// Sums the weights of all the edges and compares

bool DirectedGraph::operator>(const DirectedGraph &dg) {
	int left_sum = 0;
	int right_sum = 0;

	for (int i = 0; i < no_edges; ++i)
		left_sum += edges[i]->getWeight();

	for (int i = 0; i < dg.getNoEdges(); ++i)
		right_sum += dg.getEdges()[i]->getWeight();

	return left_sum > right_sum;
}



