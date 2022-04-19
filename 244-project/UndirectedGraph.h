/*
 * UndirectedGraph.h
 *
 *  Created on: Apr. 8, 2022
 *      Author: timothymoore
 */

#ifndef UNDIRECTEDGRAPH_H_
#define UNDIRECTEDGRAPH_H_

#include "Graph.h"

class UndirectedGraph : public Graph {
public:
	UndirectedGraph();
	UndirectedGraph(const UndirectedGraph&);
	~UndirectedGraph();
	virtual bool addVertex(Vertex &);
	/*virtual bool addVertices(Vertex*, int);
	virtual bool searchVertex(const Vertex&);
	virtual bool searchEdge(const Edge&);
	virtual bool removeVertex(Vertex&);
	virtual void display() const;
	virtual bool addEdge(Edge&);
	virtual bool remove(Edge&);
	virtual string toString() const;*/


};

#endif /* UNDIRECTEDGRAPH_H_ */
