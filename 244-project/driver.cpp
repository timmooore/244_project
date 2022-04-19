/*
 * main.cpp
 *
 *  Created on: Mar. 11, 2022
 *      Author: timothymoore
 */

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "DirectedGraph.h"
#include "UndirectedGraph.h"

int main() {
	cout << "Creating vertices and edges..." << endl
			<< "-----------------------------------" << endl;
	Vertex v1(1, "Montreal");
	Vertex v2(2, "Toronto");
	Vertex v3(3, "Milan");
	Vertex v4(4, "New York");
	Vertex v5(5, "Los Angeles");
	Vertex v6(6, "Tokyo");

	Vertex v_arr[3] = { 
		Vertex(10, "Paris"), 
		Vertex(20, "Seoul"), 
		Vertex(30, "Sydney")
	};

	Edge e1(&v1, &v2);
	Edge e2(&v1, &v4, 1);
	Edge e3(&v2, &v3, 3);
	Edge e4(&v2, &v4, 5);
	Edge e5(&v2, &v5, 7);
	Edge e6(&v3, &v4, 11);
	Edge e7(&v5, &v3, 13);
	Edge e8(&v6, &v3, 17);
	Edge e9(&v6, &v5, 19);

	cout << "V1 = ";
	v1.print();
	cout << endl << "V2 = ";
	v2.print();
	cout << endl << "V3 = ";
	v3.print();
	cout << endl << "V4 = ";
	v4.print();
	cout << endl << "V5 = ";
	v5.print();
	cout << endl << "V6 = ";
	v6.print();
	cout << endl << endl;

	cout << "E1 = ";
	e1.print();
	cout << endl << "E2 = ";
	e2.print();
	cout << endl << "E3 = ";
	e3.print();
	cout << endl << "E4 = ";
	e4.print();
	cout << endl << "E5 = ";
	e5.print();
	cout << endl << "E6 = ";
	e6.print();
	cout << endl << "E7 = ";
	e7.print();
	cout << endl << "E8 = ";
	e8.print();
	cout << endl << "E9 = ";
	e9.print();
	cout << endl << endl;

	cout << "Creating directed graph..." << endl
			<< "-----------------------------------" << endl;
	DirectedGraph dg;

	cout << "Testing if the graph can be empty..." << endl
			<< "-----------------------------------" << endl;
	cout << dg;
	cout << endl;

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

	cout << "Adding edges..." << endl << "-----------------------------------"
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

	cout << "Attempting to add an edge that creates a cycle..." << endl
			<< "-----------------------------------" << endl;

	Edge e10(&v5, &v1, 21);

	if (!dg.addEdge(e10)) cout << "Adding edge failed..." << endl;

	cout << "Removing a vertex..." << endl
			<< "-----------------------------------" << endl;
	dg.removeVertex(v1);

	dg.display();
	cout << endl;

	cout << "Trying to add an edge from a vertex not in the graph..." << endl
			<< "-----------------------------------" << endl;
	if (!dg.addEdge(e1)) cout << "Failed to add edge..." << endl;

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

	cout << endl << "Creating a second directed graph..." << endl
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
	try {
		dg2 = dg3 + dg4;
	}
	catch(string& err_msg) {
		cout << err_msg << endl;
		exit(EXIT_FAILURE);
	}

	cout << dg2 << endl;
	
	cout << "Testing getPaths on vertex V6 in original directed graph..."
			<< endl << "-----------------------------------" << endl;

	vector< vector< Edge > > paths = dg.getPaths(v6);
	for (vector< Edge > path : paths) {
		for (Edge& e : path) cout << e.getSource()->getValue() << " -> ";
		cout << path.back().getDest()->getValue();
		cout << endl;
	}

	cout << endl;
	cout << "Testing printAllPaths on original directed graph..." << endl
			<< "-----------------------------------" << endl;

	dg.printAllPaths();

	cout << endl << "Testing printAllPaths on Graph 2..." << endl
			<< "-----------------------------------" << endl;

	dg2.printAllPaths();
	
	UndirectedGraph udg;

	Edge e11(&v4, &v6, 99);
		udg.addEdge(e11);

	return EXIT_SUCCESS;
}

