/*
 * DirectedGraph.h
 *
 *  Created on: Mar. 12, 2022
 *      Author: timothymoore
 */

#ifndef DIRECTEDGRAPH_H_
#define DIRECTEDGRAPH_H_

#include "Graph.h"
#include <vector>

class DirectedGraph : public Graph {
public:
	DirectedGraph();
	DirectedGraph(const DirectedGraph&);
	virtual ~DirectedGraph();
	virtual bool addVertex(Vertex &v);
	virtual bool addVertices(Vertex* vArray, int);
	virtual bool searchVertex(const Vertex& v);
	virtual bool searchEdge(const Edge& e);
	virtual bool removeVertex(Vertex& v);
	virtual void display() const;
	virtual bool addEdge(Edge& e);
	virtual bool remove(Edge &e);
	virtual string toString () const;
	//vector<vector<Edge> > getPaths(Vertex& v, vector<vector<Edge> >);
	vector< vector<Edge> > getPaths(Vertex&);
	bool isPath(Vertex&, Vertex&);

	bool operator==(const DirectedGraph&);
	DirectedGraph& operator=(const DirectedGraph&);
	DirectedGraph& operator++();
	DirectedGraph operator++(int);
	DirectedGraph operator+(const DirectedGraph&);
	bool operator>(const DirectedGraph&);

};





#endif /* DIRECTEDGRAPH_H_ */
