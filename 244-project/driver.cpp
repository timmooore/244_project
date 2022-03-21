/*
 * main.cpp
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#include "Vertex.h"
#include "Edge.h"
#include "DirectedGraph.h"

int main() {
	cout << "Creating vertices and edges..." << endl
			<< "-----------------------------------" << endl;
	Vertex v1(1);
	Vertex v2(2);
	Vertex v3(3);
	Vertex v4(4);
	Vertex v5(5);
	Vertex v6(6);

	Vertex v_arr[3] = { Vertex(10), Vertex(20), Vertex(30) };

	Edge e1(&v1, &v2);
	Edge e2(&v1, &v4, 1);
	Edge e3(&v2, &v3, 3);
	Edge e4(&v2, &v4, 5);
	Edge e5(&v2, &v5, 7);
	Edge e6(&v3, &v4, 11);
	Edge e7(&v5, &v3, 13);
	Edge e8(&v6, &v3, 17);
	Edge e9(&v6, &v5, 19);

	cout << "Creating directed graph..." << endl
			<< "-----------------------------------" << endl;
	DirectedGraph dg;

	cout << "Testing adding a vertices..." << endl
			<< "-----------------------------------" << endl;

	dg.addVertex(v1);
	dg.addVertex(v2);
	dg.addVertex(v3);
	dg.addVertex(v4);
	dg.addVertex(v5);
	dg.addVertex(v6);

	cout << "Displaying directed graph..." << endl
			<< "-----------------------------------" << endl;

	dg.display();
	cout << endl;

	cout << "Adding an edge..." << endl << "-----------------------------------"
			<< endl;

	dg.addEdge(e1);
	dg.addEdge(e2);
	dg.addEdge(e3);
	dg.addEdge(e4);
	dg.addEdge(e5);
	dg.addEdge(e6);
	dg.addEdge(e7);
	dg.addEdge(e8);
	dg.addEdge(e9);

	dg.display();
	cout << endl;

	cout << "Removing a vertex..." << endl
			<< "-----------------------------------" << endl;
	dg.removeVertex(v1);

	dg.display();
	cout << endl;

	cout << "Trying to add an edge from a vertex not in the graph..." << endl
			<< "-----------------------------------" << endl;
	if (!dg.addEdge(e1))
		cout << "Failed to add edge..." << endl;

	cout << "Adding the right vertex and retrying to add edge..." << endl
			<< "-----------------------------------" << endl;

	dg.addVertex(v1);
	dg.addEdge(e1);

	dg.display();
	cout << endl;

	cout << "Converting the graph to a string and printing out the string..."
			<< endl << "-----------------------------------" << endl;

	string s = dg.toString();
	cout << s << endl;

	cout << "Creating a second directed graph..." << endl
			<< "Testing the assignment operator..." << endl
			<< "--------------------------------------" << endl;

	DirectedGraph dg2;
	dg2 = dg;
	dg2.display();
	cout << endl;
	cout << "Testing compare..." << endl;

	if (dg == dg2) {
		cout << "The graphs are the same..." << endl
				<< "-----------------------------------" << endl;
	}

	cout << "Removing a vertex from the new graph and testing the compare "
			<< "operator..." << endl;
	dg2.removeVertex(v3);
	if (!(dg == dg2)) {
		cout << "The graphs are no longer the same..." << endl
				<< "-----------------------------------" << endl;
	}
	dg2.display();
	cout << endl;

	cout << "Testing prefix and post increments..." << endl;
	++dg2;
	cout << "After prefix increment:" << endl;
	dg2++.display();
	cout << endl;
	cout << "After postfix increment:" << endl;
	dg2.display();
	cout << endl;

	cout << "Creating two new graphs and adding then together..." << endl
			<< "Also testing adding vertices from array for new graph..."
			<< endl << "----------------------------------" << endl;

	DirectedGraph dg3;

	dg3.addVertices(v_arr, 3);
	dg3.addEdge(e4);

	cout << "Graph 3 is: " << endl << dg3 << endl;

	DirectedGraph dg4;
	dg4.addVertex(v1);
	dg4.addVertex(v3);
	dg4.addVertex(v5);
	dg4.addEdge(e7);

	cout << "Graph 4 is: " << endl << dg4 << endl;

	cout << "Adding graph 3 and 4 and assigning it to graph 2 gives:" << endl;
	dg2 = dg3 + dg4;

	cout << dg2 << endl;
	
	cout << "Testing get all paths on original directed graph..." << endl
			<< "-----------------------------------" << endl;
	vector<vector<Edge> > paths;

	paths = dg.getPaths(v1, paths);

	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}
	paths.clear();
	paths = dg.getPaths(v2, paths);
	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}
	paths.clear();
	paths = dg.getPaths(v3, paths);
	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}
	paths.clear();
	paths = dg.getPaths(v4, paths);
	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}
	paths.clear();
	paths = dg.getPaths(v5, paths);
	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}
	paths.clear();
	paths = dg.getPaths(v6, paths);
	for (vector<Edge> path : paths) {
		for (Edge e : path) {
			cout << e.getSource()->getValue() << " -> ";
		}
		cout << path.back().getDest()->getValue();
		cout << endl;
	}

	cout << endl;

	paths.clear();
	for (int i = 0; i < dg2.getNoVertices(); ++i) {
		paths = dg2.getPaths(*dg2.getNodes()[i], paths);
		for (vector<Edge> path : paths) {
			for (Edge e : path) {
				cout << e.getSource()->getValue() << " -> ";
			}
			cout << path.back().getDest()->getValue();
			cout << endl;
		}
		paths.clear();
	}
	
	return EXIT_SUCCESS;
}

