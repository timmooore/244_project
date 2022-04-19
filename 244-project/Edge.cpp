/*
 * Edge.cpp
 *
 *  Created on: Mar. 12, 2022
 *      Author: timothymoore
 */

#include <iostream>
#include "Edge.h"

using namespace std;

Edge::Edge(Vertex* source, Vertex* dest, int weight) {
	this->source = source;
	this->dest = dest;
	this->weight = weight;
}

Vertex* Edge::getSource() const {
	return source;
}

Vertex* Edge::getDest() const {
	return dest;
}

int Edge::getWeight() const {
	return weight;
}

void Edge::setWeight(const int weight) {
	this->weight = weight;
}

void Edge::print() const {
	cout << "{(" << source->getValue() << ", " << dest->getValue()
			<< "), " << weight << "}";
}

// printUD prints edges with curly "{}" brackets to denote that the order
// of the edge is not important. Used for Undirected Graphs

void Edge::printUD() const {
	cout << "{{" << source->getValue() << ", " << dest->getValue()
		<< "}, " << weight << "}";
}
