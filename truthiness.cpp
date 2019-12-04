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

	for (int i=0;i<n;i++){
		graph.push_back(new Node);

		char cont;
		
		cout << "Does node " << i << " have any truths? y or \n\n";
		cin >> cont;

		while (cont == 'y'){
			Node* temp = graph.at(i);
			cout << "What is true? ";
			
			char truth;
			cin >> truth;
			temp->truths.push_back(truth);

			cout << "\nIs anything else true? y or n";
			cin >> cont;

		}


	}
}


// Graph Implementation in C++ without using STL
int main()
{

vector<Node*> graph;

createNodes(graph);

return 0;

}