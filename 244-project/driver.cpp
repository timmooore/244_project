/*
 * main.cpp
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#include "DirectedGraph.h"

int main() {
	Vertex v1(1);
	Vertex v2(2);
	Vertex v3(3);
	Vertex v4(4);
	Vertex v5(5);
	Vertex v6(6);

	Vertex v_arr[3] = {Vertex(10), Vertex(20), Vertex(30)};
	v1.print();
	cout << endl;
	v2.print();
	cout << endl;

	Edge e1(&v1, &v2);
	e1.print();
	cout << endl;

	Edge e2(&v1, &v4, 1);
	Edge e3(&v2, &v3, 3);
	Edge e4(&v2, &v4, 5);
	Edge e5(&v2, &v5, 7);
	Edge e6(&v3, &v4, 11);
	Edge e7(&v5, &v3, 13);
	Edge e8(&v6, &v3,17);
	Edge e9(&v6, &v5, 19);

	DirectedGraph dg;

	cout << "Testing adding a vertices..." << endl
			<< "-----------------------------------" << endl;

	dg.addVertex(v1);
	dg.addVertex(v2);
	dg.addVertex(v3);
	dg.addVertex(v4);
	dg.addVertex(v5);
	dg.addVertex(v6);

	dg.display();

	cout << dg.getNoVertices() << endl << dg.getNodes()[dg.getNoVertices() - 1]
			<< endl;

	dg.addEdge(e1);

	dg.display();

	dg.removeVertex(v1);

	dg.display();

	cout << dg.getNoVertices() << endl << dg.getNodes()[dg.getNoVertices()]
			<< endl;

	dg.addEdge(e1);

	dg.display();

	dg.addVertex(v1);
	dg.addEdge(e1);

	dg.display();

	string s = dg.toString();
	cout << s << endl;

	dg.addEdge(e2);
	dg.addEdge(e3);
	dg.addEdge(e4);
	dg.addEdge(e5);
	dg.addEdge(e6);
	dg.addEdge(e7);
	dg.addEdge(e8);
	dg.addEdge(e9);

	dg.display();

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
	DirectedGraph dg2;
	dg2 = dg;
	dg2.display();
	dg2.removeVertex(v3);
	dg2.display();
	if (dg2.searchEdge(e7)) cout << "Wtf why" << endl;


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
	++dg2;
	dg2++.display();
	dg2.display();

	DirectedGraph dg3;
	dg3.addVertices(v_arr, 3);
	dg3.addEdge(e4);

	DirectedGraph dg4;
	dg4.addVertex(v1);
	dg4.addVertex(v3);
	dg4.addVertex(v5);
	dg4.addEdge(e7);

	dg2 = dg3 + dg4;

	cout << "displaying dg2" << endl << dg2;
	dg2.display();




	return EXIT_SUCCESS;
}

