/*
 * Graph.h
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include "Edge.h"

#define MAX_NO_VERTICES 20
#define MAX_NO_EDGES 50

class Graph {
protected://Change this back after
	Vertex** nodes;
	Edge** edges;
	size_t no_vertices;
	size_t no_edges;

public:
	Graph();
	virtual ~Graph();
	size_t getNoEdges() const;
	size_t getNoVertices() const;
	Vertex** getNodes() const;
	Edge** getEdges() const;
//add in one vertex; bool returns if it is added successfully.
	virtual bool addVertex(Vertex &v)=0;
	virtual bool addVertices(Vertex *vArray, int) = 0;
//the edges that has connection with this vertex need to be removed;
	virtual bool removeVertex(Vertex &v)= 0;
//remove a edge;  as a result, some node may remain as orphan.
	virtual bool addEdge(Edge &e) = 0;
// remove the edge
	virtual bool remove(Edge &e)=0;
// return bool if a vertex exists in a graph;
	virtual bool searchVertex(const Vertex &v) = 0;
	// return bool if a Edge exists in a graph;
	virtual bool searchEdge(const Edge& e) =0;
	// display the whole graph with your own defined format
	virtual void display() const = 0;
	// convert the whole graph to a string such as 1‐2‐4‐5; 1‐3‐5; each path is separated by ';'
	// or just print the edges of the graph as a list
	// define your own format of a string representation of the graph.
	virtual string toString () const = 0;
	//remove all the vertices and edges;
	/////////////////virtual bool clean() = 0;
	// you may consider the following in your project:
	// add/remove a set of edge; as a result, some node may remain as orphan.
	//virtual bool addEdges(Edge* eArray) = 0;
	//virtual bool removeEdges(Edge* eArray) = 0;
	// display the path that contains the vertex;
	// virtual void display(Vertex& v) const = 0;
	// display the path that contains the edge;
	// virtual void display(Edge& e) const = 0;

	friend ostream& operator<<(ostream &,const Graph &);
};


#endif /* GRAPH_H_ */
