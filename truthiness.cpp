#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Data structure to store Adjacency list nodes
struct Node {
	int name;
	vector<char> truths;
	vector<Node*> edges;
};

// class Graph
// {
// 	// number of nodes
// 	int N;

// public:
// 	// pointer to start of adjacency list
// 	Node**head;

// 	// constructor
// 	Graph(Node*headNode, int N){
// 		head = &headNode;
// 	}

// 	// Destructor
// 	~Graph() {
// 		delete head;
// 	}
// };

void createNodes(vector<Node*> &graph) {
	int n;
	cout << "Enter number of nodes\n";
	cin >> n;

	// create nodes and record truths
	for (int i=0;i<n;i++){
		// create new node and push it to the graph vector
		graph.push_back(new Node);
		Node* temp = graph.at(i);
		temp->name = i;
		// sentinal for while loop
		char cont;
		// ask if the node has any truths
		cout << "Does node " << i << " have any truths? y or n\n";
		cin >> cont;

		// while cont == y, keep adding truths to the vector
		while (cont == 'y'){
			// save reference to what node we're adding truths to
			Node* temp = graph.at(i);
			cout << "What is true?\n";
			// push truth to the node truth vector
			char truth;
			cin >> truth;
			temp->truths.push_back(truth);
			// ask if anything else is true
			cout << "\nIs anything else true? y or n\n";
			cin >> cont;
		}
	}

	// define the edges for each node
	for (int i=0;i<n;i++){
		// sentinel for while loop
		char cont;
		// ask if the node has any edges
		cout << "Does node " << i << " have any edges? y or n \n";
		cin >> cont;		

		// while cont == y, keep adding edges to the vector
		while (cont == 'y'){
			// save reference to what node we're adding truths to
			Node* temp = graph.at(i);
			// ask what node the edge connects to
			int edge;
			cout << "What node # does " << i << " connect to?\n";
			cin >> edge;
			// push the edge to the node edge vector
			temp->edges.push_back(graph.at(edge));
			// ask if there are any more edges
			cout << "Any more edges? y or n\n";
			cin >> cont;
		}
	}
}

// function to find shortest path of the graph
// n = number of nodes, start = starting node number, dest = destination node number
void shortestPath(int n, vector<Node*> &graph, int start, int dest){

}

// Graph Implementation in C++ without using STL
int main()
{

vector<Node*> graph;

createNodes(graph);

return 0;

}