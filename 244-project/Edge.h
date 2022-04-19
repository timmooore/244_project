/*
 * Edge.h
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"

class Edge {
private:
	Vertex* source;
	Vertex* dest;
	int weight;
public:
	Edge(Vertex*, Vertex*, int = 0);
	Vertex* getSource() const;
	Vertex* getDest() const;
	int getWeight() const;
	void setWeight(const int);
	void print() const;
	void printUD() const;
};


#endif /* EDGE_H_ */
