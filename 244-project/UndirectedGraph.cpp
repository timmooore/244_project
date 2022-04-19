
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
	//for (int i = 0; i < udg.no_edges; ++i) addEdge(*udg.edges[i]);
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
	nodes[no_vertices++] = new Vertex(v.getValue());
	return true;
}

// Similar to addVertex, the same function is performed but using an
// array of Vertex pointers as input and the number of vertices to be added

bool UndirectedGraph::addVertices(Vertex* vArray, int no_vertices) {
	if (this->no_vertices + no_vertices >= MAX_NO_VERTICES)
		return false;
	for (int i = 0; i < no_vertices; ++i) {
		nodes[this->no_vertices++] = new Vertex(vArray[i].getValue(), vArray[i].getAirport());
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
				(edges[i]->getDest()->getValue() == e.getDest()->getValue()
					&& edges[i]->getSource()->getValue()
					== e.getSource()->getValue())
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



