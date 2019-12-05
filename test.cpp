#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
	int name;
	vector<char> truths;
	vector<Node*> edges;
};

int main()
{

int num;

// cout << "Enter number of nodes\n";
// cin >> num;

// vector<Node*> graph;

// for (int i=0;i<num;i++){
// 	graph.push_back(new Node);
// }

// cout << "graph has " << graph.size() << " nodes\n\n";

// Node* temp = graph.at(0);

// temp->name=5;

// cout << "node name: " << temp->name << "\n\n";

// cout << "truth vector size: " << temp->truths.size() << "\n\n";

// char temp2 = 'a';

// temp->truths.push_back(temp2);
// cout << "truth vector size: " << temp->truths.size() << "\n\n";

// cout << temp->truths.at(0);

vector<Node*> graph;

int n=4;

for (int i=0;i<n;i++){
	graph.push_back(new Node);
}

return 0;
}