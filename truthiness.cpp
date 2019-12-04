#include <iostream>
#include <vector>
using namespace std;

// Data structure to store Adjacency list nodes
struct Node {
	int name;
	vector<char> truths;
	vector<Node*> edges;
};

class Graph
{
	// number of nodes
	int N;

public:
	// pointer to start of adjacency list
	Node**head;

	// constructor
	Graph(Node*headNode, int N){
		head = &headNode;
	}

	// Destructor
	~Graph() {
		delete head;
	}
};

void createNodes(int N) {

}


// Graph Implementation in C++ without using STL
int main()
{

}