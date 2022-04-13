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

DirectedGraph::DirectedGraph() {
	nodes = new Vertex*[MAX_NO_VERTICES];
	edges = new Edge*[MAX_NO_EDGES];
}

DirectedGraph::DirectedGraph(const DirectedGraph& dg) {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
	for (int i = 0; i < dg.no_vertices; ++i) addVertex(*dg.nodes[i]);
	for (int i = 0; i < dg.no_edges; ++i) addEdge(*dg.edges[i]);
}

DirectedGraph::~DirectedGraph() {
	for (int i = 0; i < no_vertices; ++i)
		delete nodes[i];
	for (int i = 0; i < no_edges; ++i)
		delete edges[i];
	delete[] nodes;
	delete[] edges;
}

bool DirectedGraph::addVertex(Vertex &v) {
	if (no_vertices >= MAX_NO_EDGES)
		return false;
	nodes[no_vertices++] = new Vertex(v.getValue());
	return true;
}

bool DirectedGraph::addVertices(Vertex *vArray, int no_vertices) {
	if (this->no_vertices + no_vertices >= MAX_NO_VERTICES)
		return false;
	for (int i = 0; i < no_vertices; ++i) {
		nodes[this->no_vertices++] = new Vertex(vArray[i].getValue());
	}
	return true;
}

bool DirectedGraph::searchVertex(const Vertex &v) {
	for (int i = 0; i < no_vertices; ++i) {
		if (nodes[i]->getValue() == v.getValue())
			return true;
	}
	return false;
}

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

// Need to fix so that it doesn't add cycles
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
	// cout << "Calling getPaths for node " << v.getValue() << endl;
	vector<vector<Edge> > paths;
	vector<Edge> pt;
	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()) {
			pt.push_back(*edges[i]);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getDest());
			// if (!childPaths.isEmpty())
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

DirectedGraph& DirectedGraph::operator++() {
	for (int i = 0; i < no_edges; ++i) {
		int w = edges[i]->getWeight();
		edges[i]->setWeight(++w);
	}
	return *this;
}

DirectedGraph DirectedGraph::operator++(int) {
	DirectedGraph og;
	og = *this;
	for (int i = 0; i < no_edges; ++i) {
		int w = edges[i]->getWeight();
		edges[i]->setWeight(++w);
	}
	return og;
}

DirectedGraph DirectedGraph::operator+(const DirectedGraph &dg) {
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

bool DirectedGraph::operator>(const DirectedGraph &dg) {
	int left_sum = 0;
	int right_sum = 0;

	for (int i = 0; i < no_edges; ++i)
		left_sum += edges[i]->getWeight();

	for (int i = 0; i < dg.getNoEdges(); ++i)
		right_sum += dg.getEdges()[i]->getWeight();

	return left_sum > right_sum;
}



