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
int num;

cout << "Enter number of nodes\n";
cin >> num;

vector<Node*> graph(num);


return 0;
}