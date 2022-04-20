/*
 * UndirectedGraph.h
 *
 *  Created on: Apr. 8, 2022
 *      Author: timothymoore
 */

#ifndef UNDIRECTEDGRAPH_H_
#define UNDIRECTEDGRAPH_H_

#include "Graph.h"
#include <vector>
#include <unordered_map>

class UndirectedGraph : public Graph {
public:
	UndirectedGraph();
	UndirectedGraph(const UndirectedGraph&);
	UndirectedGraph(Vertex*, Edge*, int, int);
	~UndirectedGraph();
	virtual bool addVertex(Vertex &);
	virtual bool addVertices(Vertex*, int);
	virtual bool searchVertex(const Vertex&);
	virtual bool searchEdge(const Edge&);
	virtual bool removeVertex(Vertex&);
	virtual void display() const;
	virtual bool addEdge(Edge&);
	virtual bool remove(Edge&);
	virtual string toString() const;
	virtual bool clean();
	vector< vector<Edge> > getPaths(Vertex&, unordered_map<int, bool>);
	bool isPath(Vertex&, Vertex&);
	void printAllPaths();
	void printFlightPaths(Vertex&, Vertex&);
	friend ostream& operator<<(ostream&, const UndirectedGraph&);


};

#endif /* UNDIRECTEDGRAPH_H_ */
