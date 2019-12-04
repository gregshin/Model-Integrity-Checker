#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int name;
	vector<char> truths;
	vector<Node*> edges;
};

int main()
{

int num=1;

cout << "Enter number of nodes\n";
cin >> num;

vector<Node*> graph;

for (int i=0;i<num;i++){
	graph.push_back(new Node);
}

cout << graph.size();

// Node* test = new Node;

// graph.push_back(test);

// Node* node = graph.at(0);

// node->name=1;
// cout << node->name << "\n";

return 0;
}