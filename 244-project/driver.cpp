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
		<< "-----------------------------------" << endl << endl;
	Vertex v1(1, "Montreal");
	Vertex v2(2, "Toronto");
	Vertex v3(3, "Milan");
	Vertex v4(4, "New York");
	Vertex v5(5, "Los Angeles");
	Vertex v6(6, "Tokyo");

	Vertex v_arr[3] = {
		Vertex(7, "Paris"),
		Vertex(8, "Seoul"),
		Vertex(9, "Sydney")
	};

	Edge e1(&v1, &v2, 316);
	Edge e2(&v1, &v4, 324);
	Edge e3(&v2, &v3, 4120);
	Edge e4(&v2, &v4, 357);
	Edge e5(&v2, &v5, 2175);
	Edge e6(&v3, &v4, 3995);
	Edge e7(&v5, &v3, 6066);
	Edge e8(&v6, &v3, 6072);
	Edge e9(&v6, &v5, 5479);

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

	cout << "Creating directed graph dg..." << endl
		<< "-----------------------------------" << endl << endl;
	DirectedGraph dg;

	cout << "Testing if the graph can be empty by displaying graph..." << endl
		<< "-----------------------------------" << endl << endl;
	cout << dg;
	cout << endl;

	cout << "Testing addVertex function by adding vertices V1 to V6..." << endl
		<< "-----------------------------------" << endl << endl;

	dg.addVertex(v1);
	dg.addVertex(v2);
	dg.addVertex(v3);
	dg.addVertex(v4);
	dg.addVertex(v5);
	dg.addVertex(v6);

	cout << "Displaying directed graph dg using display function after adding "
		"vertices..." << endl << "-----------------------------------" << endl
		<< endl;

	dg.display();
	cout << endl;

	cout << "Adding edges E1 to E9 to directed graph dg using addEdge "
		"function and displaying dg again..." << endl
		<< "-----------------------------------" << endl << endl;

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
		<< "-----------------------------------" << endl << endl;

	Edge e10(&v5, &v1, 2474);

	if (!dg.addEdge(e10)) cout << "Adding edge failed..." << endl;

	cout << endl << "Testing removing a vertex by removing V1..." << endl
		<< "-----------------------------------" << endl << endl;
	dg.removeVertex(v1);

	cout << "After removing vertex V1 directed graph dg is:" << endl << endl;
	dg.display();
	cout << endl;

	cout << "Trying to add an edge from vertex V1 that is not in the graph..."
		<< endl << "-----------------------------------" << endl << endl;
	if (!dg.addEdge(e1)) cout << "Failed to add edge..." << endl;

	cout << "Re-adding vertex V1 to the graph and retrying to add edge..."
		<< endl << "-----------------------------------" << endl << endl;

	dg.addVertex(v1);

	if (dg.addEdge(e1))
		cout << "Adding edge from vertex V1 was successful, displaying "
		"graph..." << endl << endl;

	dg.display();
	cout << endl;

	cout << "Converting the graph  dg to a string and printing out the "
		"string..." << endl << "-----------------------------------"
		<< endl << endl;

	string s = dg.toString();
	cout << s << endl;

	cout << endl << "Creating a second directed graph dg2..." << endl << endl
		<< "Testing the assignment operator by assigning dg to dg2 and\n"
		"printing dg2 using overloaded stream output operator<< ..." << endl
		<< "-----------------------------------" << endl << endl;

	DirectedGraph dg2;
	dg2 = dg;
	cout << dg2 << endl;
	cout << "Testing compare operator== for graphs dg and dg2, which are "
		"currently the same..." << endl  
		<< "-----------------------------------" << endl << endl;
	if (dg == dg2) {
		cout << "The graphs are the same..." << endl
			<< "-----------------------------------" << endl << endl;
	}

	cout << "Removing vertex V3 from the graph dg2 and testing the compare "
		<< "operator==..." << endl << endl;
	dg2.removeVertex(v3);
	if (!(dg == dg2)) {
		cout << "The graphs are no longer the same..." << endl
			<< "-----------------------------------" << endl << endl;
	}

	cout << "Displaying directed graph dg2 after removing the vertex..."
		<< endl << "-----------------------------------" << endl << endl;
	cout << dg2 << endl;

	cout << "Testing prefix and post increments on graph dg2. Prefix "
		"and postfix increment the weight of each edge by 1..." << endl
		<< "-----------------------------------" << endl << endl;
	++dg2;
	cout << "After prefix increment:" << endl;
	dg2++.display();
	cout << endl;
	cout << "After postfix increment:" << endl;
	dg2.display();
	cout << endl;

	cout << "Creating two new directed graphs dg3 and dg4 to test adding them "
		"together..." << endl << "-----------------------------------" << endl
		<< endl << "Testing adding vertices from array for new graph dg3..."
		<< endl << "-----------------------------------" << endl << endl;

	DirectedGraph dg3;

	dg3.addVertices(v_arr, 3);
	dg3.addEdge(e4);

	cout << "Graph dg3 is: " << endl << endl << dg3 << endl;

	DirectedGraph dg4;
	dg4.addVertex(v1);
	dg4.addVertex(v3);
	dg4.addVertex(v5);
	dg4.addEdge(e7);

	cout << "Graph dg4 is: " << endl << endl << dg4 << endl;

	cout << "Adding graph 3 and 4 and assigning it to graph 2 gives:" << endl
		<< endl;
	try {
		dg2 = dg3 + dg4;
	}
	catch (string& err_msg) {
		cout << err_msg << endl;
		exit(EXIT_FAILURE);
	}

	cout << dg2 << endl;

	cout << "Testing searching for vertex V3 with value 3 in graph dg..."
		<< endl << "-----------------------------------" << endl << endl;

	if (dg.searchVertex(v3)) 
		cout << "Vertex V3 is in graph dg..." << endl << endl;
	else cout << "Vertex V3 not found in graph dg..." << endl << endl;

	cout << "Testing searching for vertex V7, which is not contained in "
		"graph dg..." << endl << "-----------------------------------"
		<< endl << endl;

	if (dg.searchVertex(v_arr[0]))
		cout << "Vertex V7 is in graph dg..." << endl << endl;
	else cout << "Vertex V7 is not in graph dg..." << endl << endl;

	cout << "Testing searching for Edge E5 in graph dg..." << endl
		<< "-----------------------------------" << endl << endl;

	if (dg.searchEdge(e5)) cout << "Edge E5 is in graph dg..." << endl << endl;
	else cout << "Edge E5 not found in graph dg..." << endl << endl;

	cout << "Testing getPaths on vertex V6 in original directed graph dg..."
		<< endl << "-----------------------------------" << endl << endl;

	vector< vector< Edge > > paths = dg.getPaths(v6);
	for (vector< Edge > path : paths) {
		for (Edge& e : path) cout << e.getSource()->getAirport() << " -> ";
		cout << path.back().getDest()->getAirport();
		cout << endl;
	}

	cout << endl;
	cout << "Testing printAllPaths on original directed graph dg..." << endl
		<< "-----------------------------------" << endl << endl;

	dg.printAllPaths();

	cout << endl << "Testing printAllPaths on graph dg2..." << endl
		<< "-----------------------------------" << endl << endl;

	dg2.printAllPaths();

	cout << endl << "Testing printFlightPaths on directed graph dg for "
		"Toronto to New York.\nprintFlightPaths prints all the possible connecting "
		"flights\nfrom Toronto to New York and the total miles of the flight"
		<< endl << endl;

	dg.printFlightPaths(v2, v4);

	cout << endl << "Creating an undirected graph udg and adding vertices V1 "
		"to V6 and edges\nE1, E2, E3, E5, and new edge E11 using addVertex and "
		"addEdge functions..." << endl<< "-----------------------------------" 
		<< endl << endl;

	UndirectedGraph udg;
	udg.addVertex(v1);
	udg.addVertex(v2);
	udg.addVertex(v3);
	udg.addVertex(v4);
	udg.addVertex(v5);
	udg.addVertex(v6);

	Edge e11(&v4, &v6, 6745);

	udg.addEdge(e1);
	udg.addEdge(e2);
	udg.addEdge(e3);
	udg.addEdge(e5);
	udg.addEdge(e11);

	cout << "Displaying undirected graph udg using operator<<..." << endl
		<< "-----------------------------------" << endl << endl;

	cout << udg;

	cout << "Attempting to add edge E7 to graph udg which creates a cycle..."
		<< endl << "-----------------------------------" << endl << endl;

	if (!udg.addEdge(e7)) cout << "Adding edge E7 failed..." << endl << endl;

	cout << "Testing printing all possible paths in the undirected graph "
		"udg..." << endl << "-----------------------------------" << endl 
		<< endl;

	udg.printAllPaths();

	cout << endl << "Testing printFlightPaths from Montreal to LA..."
		<< endl << "-----------------------------------" << endl << endl;

	udg.printFlightPaths(v1, v5);

	cout << "Testing removing vertex V5 from undirected graph udg..." << endl
		<< "-----------------------------------" << endl << endl;

	udg.removeVertex(v5);

	cout << "Displaying graph udg after removing vertex..." << endl
		<< "-----------------------------------" << endl << endl;

	return EXIT_SUCCESS;
}

