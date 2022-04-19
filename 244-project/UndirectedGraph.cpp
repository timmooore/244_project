
#include "UndirectedGraph.h"

// Default constructor creates arrays of Vertex and Edge pointers
// of sizes MAX_NO_VERTICES and MAX_NO_EDGES defined in Graph header
UndirectedGraph::UndirectedGraph() {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
}

// Copy constructor creates new arrays and adds vertices and edges from
// UndirectedGraph to be copied

UndirectedGraph::UndirectedGraph(const UndirectedGraph& udg) {
	nodes = new Vertex * [MAX_NO_VERTICES];
	edges = new Edge * [MAX_NO_EDGES];
	for (int i = 0; i < udg.no_vertices; ++i) addVertex(*udg.nodes[i]);
	for (int i = 0; i < udg.no_edges; ++i) addEdge(*udg.edges[i]);
}

// Virtual destructor destroys all of the dynamically allocted vertices
// and edges that are allocated in functions addVertex and addEdge,
// the deletes the pointer arrays

UndirectedGraph::~UndirectedGraph() {
	for (int i = 0; i < no_vertices; ++i)
		delete nodes[i];
	for (int i = 0; i < no_edges; ++i)
		delete edges[i];
	delete[] nodes;
	delete[] edges;
}

// addVertex dynamically allocates Vertex objects in the Vertex pointer
// array nodes if the no of vertices is less than MAX_NO_VERTICES and returns
// true. Also increments the number of vertices.

bool UndirectedGraph::addVertex(Vertex& v) {
	if (no_vertices >= MAX_NO_EDGES)
		return false;
	nodes[no_vertices++] = new Vertex(v.getValue(), v.getAirport());
	return true;
}

// Similar to addVertex, the same function is performed but using an
// array of Vertex pointers as input and the number of vertices to be added

bool UndirectedGraph::addVertices(Vertex* vArray, int no_vertices) {
	if (this->no_vertices + no_vertices >= MAX_NO_VERTICES)
		return false;
	for (int i = 0; i < no_vertices; ++i) {
		nodes[this->no_vertices++] 
			= new Vertex(vArray[i].getValue(), vArray[i].getAirport());
	}
	return true;
}

// searchVertex iterates through the array of Vertex pointers and checks
// if the values match the value of the vertex passed to the function.
// Returns true if found and false otherwise

bool UndirectedGraph::searchVertex(const Vertex& v) {
	for (int i = 0; i < no_vertices; ++i) {
		if (nodes[i]->getValue() == v.getValue())
			return true;
	}
	return false;
}

// searchEdge checks that both the source and dest vertices in the edge have
// the same values of those as the edge passed as a parameter. It also checks
// whether the dest vertex matches the source of the parameter edge and the 
// source vertex matches the dest vertex of the parameter edge since the 
// graph is undirected and those edges would therefore be equivalent

bool UndirectedGraph::searchEdge(const Edge& e) {
	for (int i = 0; i < no_edges; ++i) {
		if (
			(
				(edges[i]->getSource()->getValue() == e.getSource()->getValue()
					&& edges[i]->getDest()->getValue()
					== e.getDest()->getValue())
				|| (edges[i]->getSource()->getValue()
					== e.getDest()->getValue()
					&& edges[i]->getDest()->getValue()
					== e.getSource()->getValue())
				) && edges[i]->getWeight() == e.getWeight()
			) return true;
	}
	return false;
}

// Remove vertex is tricky. First it checks if the vertex is in the graph,
// using searchVertex, and returns false if it is not. If the vertex is found,
// it deallocates the memory and removes it from the nodes array. Then, it
// searches for each edge containing the deleted vertex as either source or
// dest, and removes those edges from the graph.

bool UndirectedGraph::removeVertex(Vertex& v) {
	if (searchVertex(v) == false)
		return false;
	int index = 0;
	for (; index < no_vertices; ++index) {
		if (nodes[index]->getValue() == v.getValue()) {
			break;
		}
	}
	delete nodes[index];
	for (; index < no_vertices - 1; ++index) {
		nodes[index] = nodes[index + 1];
	}
	nodes[index] = nullptr;
	no_vertices--;

	// Need to delete all edges associated with this vertex

	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()
			|| edges[i]->getDest()->getValue() == v.getValue()) {
			remove(*edges[i]);
			i--;
		}

	}
	return true;
}

// Displays the graph as a set of integer values corresponding to the
// values of the vertices and a second set of sets of an ordered pair of
// vertices corresponding to the source and dest vertices, and an integer
// value corresponding to the weight.

void UndirectedGraph::display() const {
	if (no_vertices == 0) {
		cout << "Graph is empty\nV = empty set\nE = empty set" << endl;
		return;
	}
	cout << "V = {";
	for (int i = 0; i < no_vertices - 1; ++i)
		cout << "(" << nodes[i]->getValue() << ", "
		<< nodes[i]->getAirport() << "), ";

	cout << "(" << nodes[no_vertices - 1]->getValue() << ", "
		<< nodes[no_vertices - 1]->getAirport() << ")}" << endl;

	if (no_edges == 0) {
		cout << "E = empty set" << endl;
		return;
	}
	cout << "E = {";
	for (int i = 0; i < no_edges - 1; ++i) {
		edges[i]->printUD();
		cout << ", ";
	}
	edges[no_edges - 1]->printUD();
	cout << "}" << endl;
}

// addEdge checks that both the vertices of the edges it is attempting
// to add exist in the graph and that the number of edges is less than the
// maximum. If so it dynamically allocates memory for the new edge in the
// array of Edge pointers. Uses isPath function to check that there isn't
// already a patch from the destination of input Edge e to the source of
// input Edge e, since this would result in a cycle in e was added

bool UndirectedGraph::addEdge(Edge& e) {
	if (no_edges >= MAX_NO_EDGES || !searchVertex(*e.getSource())
		|| !searchVertex(*e.getDest()) || searchEdge(e))
		return false;
	if (isPath(*e.getDest(), *e.getSource())) {
		cout << "Cannot add edge: adding this edge creates a cycle..." << endl;
		return false;
	}
	edges[no_edges++] = new Edge(e.getSource(), e.getDest(), e.getWeight());
	return true;
}

// removeEdge checks whether the edge exists and removes it

bool UndirectedGraph::remove(Edge& e) {
	if (searchEdge(e) == false) return false;
	int index = 0;
	for (; index < no_edges; ++index) {
		if (
			(
				(edges[index]->getSource()->getValue()
					== e.getSource()->getValue()
					&& edges[index]->getDest()->getValue()
					== e.getDest()->getValue())
				|| (edges[index]->getSource()->getValue()
					== e.getDest()->getValue()
					&& edges[index]->getDest()->getValue()
					== e.getSource()->getValue())
				) && edges[index]->getWeight() == e.getWeight()
			) break;
	}
	delete edges[index];
	for (; index < no_edges - 1; ++index) {
		edges[index] = edges[index + 1];
	}
	edges[index] = nullptr;
	no_edges--;
	return true;
}

// toString implemented the same as display but all elements are passed to
// a string instead of cout

string UndirectedGraph::toString() const {
	string s = "";
	if (no_vertices == 0) {
		s = "V = empty set\nE = empty set";
		return s;
	}
	s = "V = {";
	for (int i = 0; i < no_vertices - 1; ++i)
		s = s + "(" + to_string(nodes[i]->getValue()) + ", "
		+ nodes[i]->getAirport() + "), ";
	s = s + "(" + to_string(nodes[no_vertices - 1]->getValue()) + ", "
		+ nodes[no_vertices - 1]->getAirport() + ")}\n";

	if (no_edges == 0) {
		s += "E = empty set";
		return s;
	}
	s += "E = {";
	for (int i = 0; i < no_edges - 1; ++i) {
		s = s + "{{" + to_string(edges[i]->getSource()->getValue()) + ", "
			+ to_string(edges[i]->getDest()->getValue()) + "}, "
			+ to_string(edges[i]->getWeight()) + "}, ";
	}
	s = s + "{{" + to_string(edges[no_edges - 1]->getSource()->getValue())
		+ ", " + to_string(edges[no_edges - 1]->getDest()->getValue())
		+ "}, " + to_string(edges[no_edges - 1]->getWeight()) + "}}";
	return s;
}

bool UndirectedGraph::clean() {
	while (no_vertices > 0) {
		if (removeVertex(*nodes[no_vertices - 1]) == false)
			return false;
	}
	return true;
}

vector<vector<Edge> > UndirectedGraph::getPaths(Vertex &v,
		unordered_map<int, bool> is_visited) {
	// cout << "Calling getPaths for node " << v.getValue() << endl;
	unordered_map<int, bool> new_visited = is_visited;
	new_visited[v.getValue()] = true;
	vector<vector<Edge> > paths;
	vector<Edge> pt;
	for (int i = 0; i < no_edges; ++i) {
		if (edges[i]->getSource()->getValue() == v.getValue()
				&& new_visited[edges[i]->getDest()->getValue()] == false) {
			//new_visited[edges[i]->getDest()->getValue()] = true;
			pt.push_back(*edges[i]);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getDest(),
					new_visited);
			// if (!childPaths.isEmpty())
			for (int j = 0; j < childPaths.size(); ++j) {
				for (Edge& e : childPaths[j]) pt.push_back(e);
				paths.push_back(pt);
				pt.clear();
				pt.push_back(*edges[i]);
			}
			pt.clear();
		} else if (edges[i]->getDest()->getValue() == v.getValue()
				&& new_visited[edges[i]->getSource()->getValue()] == false) {
			//new_visited[edges[i]->getSource()->getValue()] = true;
			Edge e(edges[i]->getDest(), edges[i]->getSource(), edges[i]->getWeight());
			pt.push_back(e);
			paths.push_back(pt);
			vector<vector<Edge> > childPaths = getPaths(*edges[i]->getSource(),
					new_visited);
			// if (!childPaths.isEmpty())
			for (int j = 0; j < childPaths.size(); ++j) {
				for (Edge& e : childPaths[j]) pt.push_back(e);
				paths.push_back(pt);
				pt.clear();
				pt.push_back(e);
			}
			pt.clear();
		}
	}
	return paths;
}

bool UndirectedGraph::isPath(Vertex& u, Vertex& v) {
	vector< vector<Edge> > paths;
	unordered_map<int, bool> isVisited;
	for (int i = 0; i < no_vertices; ++i) {
		int value = nodes[i]->getValue();
		isVisited[value] = false;
	}
	paths = getPaths(u, isVisited);
	for (vector<Edge> path : paths) {
		if (path.back().getDest()->getValue() == v.getValue()) return true;
	}
	return false;
}

void UndirectedGraph::printAllPaths() {
	vector< vector< Edge > > paths;
	unordered_map<int, bool> isVisited;
	for (int i = 0; i < no_vertices; ++i) {
		int value = nodes[i]->getValue();
		isVisited[value] = false;
	}
	for (int i = 0; i < no_vertices; ++i) {
		paths = getPaths(*nodes[i], isVisited);
		for (vector<Edge> path : paths) {
			for (Edge& e : path) {
				cout << e.getSource()->getAirport() << " -> ";
			}
			cout << path.back().getDest()->getAirport();
			cout << endl;
		}
		paths.clear();
	}
}

void UndirectedGraph::printFlightPaths(Vertex& u, Vertex& v) {
	vector< vector< Edge > > paths;
	unordered_map<int, bool> isVisited;
	int miles;
	for (int i = 0; i < no_vertices; ++i) {
		int value = nodes[i]->getValue();
		isVisited[value] = false;
	}
	paths = getPaths(u, isVisited);
	for (vector<Edge> path : paths) {
		miles = 0;
		if (path.back().getDest()->getValue() == v.getValue()) {
			for (Edge& e : path) {
				miles += e.getWeight();
				cout << e.getSource()->getAirport() << " -> ";
			}
			cout << path.back().getDest()->getAirport() << ", " << miles << " miles";
			cout << endl;
		}
	}
	paths.clear();
}

ostream& operator<<(ostream& output, const UndirectedGraph& udg) {
	if (udg.no_vertices == 0) {
		output << "Graph is empty\nV = empty set\nE = empty set" << endl;
		return output;
	}
	output << "V = {";
	for (int i = 0; i < udg.no_vertices - 1; ++i)
		output << "(" << udg.nodes[i]->getValue() << ", "
		<< udg.nodes[i]->getAirport() << "), ";

	output << "(" << udg.nodes[udg.no_vertices - 1]->getValue() << ", "
		<< udg.nodes[udg.no_vertices - 1]->getAirport() << ")}" << endl;

	if (udg.no_edges == 0) {
		output << "E = empty set" << endl;
		return output;
	}
	output << "E = {";
	for (int i = 0; i < udg.no_edges - 1; ++i) {
		udg.edges[i]->printUD();
		output << ", ";
	}
	udg.edges[udg.no_edges - 1]->printUD();
	output << "}" << endl;
	return output;
}



