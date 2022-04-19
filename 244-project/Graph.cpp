/*
 * Graph.cpp
 *
 *  Created on: Mar. 12, 2022
 *      Author: timothymoore
 */

#include "Graph.h"

Graph::Graph() {
	nodes = nullptr;
	edges = nullptr;
	no_vertices = 0;
	no_edges = 0;
}

Graph::~Graph() {}

size_t Graph::getNoVertices() const {
	return no_vertices;
}

size_t Graph::getNoEdges() const {
	return no_edges;
}

Vertex** Graph::getNodes() const {
	return nodes;
}

Edge** Graph::getEdges() const {
	return edges;
}

// Essentially copy and paste of display, but overloads << operator

ostream& operator<<(ostream &output, const Graph &g) {
	if (g.no_vertices == 0) {
		output << "Graph is empty\nV = empty set\nE = empty set" << endl;
		return output;
	}
	output << "V = {";
	for (int i = 0; i < g.no_vertices - 1; ++i)
		output << "(" << g.nodes[i]->getValue() << ", " 
		<< g.nodes[i]->getAirport() << "), ";

	output << "(" << g.nodes[g.no_vertices - 1]->getValue() << ", " 
		<< g.nodes[g.no_vertices - 1]->getAirport() << ")}" << endl;

	if (g.no_edges == 0) {
		output << "E = empty set" << endl;
		return output;
	}
	output << "E = {";
	for (int i = 0; i < g.no_edges - 1; ++i) {
		g.edges[i]->print();
		output << ", ";
	}
	g.edges[g.no_edges - 1]->print();
	output << "}" << endl;
	return output;
}
