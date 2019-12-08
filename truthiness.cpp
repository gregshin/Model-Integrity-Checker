#include <iostream>
#include <vector>
#include <string>
#include <list> 
#include <iterator> 
#include <string>

using namespace std;

// Data structure to store Adjacency list nodes
struct Node {
	int name;
	vector<char> truths;
	vector<Node*> edges;
};
struct Path {
	vector<int> path;
};	

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
bool shortestPath(vector<Node*> &graph, int n, int start, int dest, int pred[]){
	list<int> graphQueue;
	bool visited[n];

	for (int i = 0; i < n; i++) { 
		visited[i] = false;
		pred[i] = -1; 
	} 

	visited[start]=true;
	graphQueue.push_back(start);

	while (!graphQueue.empty()){
		// u is the location of whatever node is in the queue
		int u = graphQueue.front();
		// temp node to store the current node's pointer
		Node* temp = graph.at(u);
		// dequeues the visiting node
		graphQueue.pop_front();
		// iterate through edges of visiting node
		for (int i=0; i < temp->edges.size(); i++){
			 if (visited[temp->edges.at(i)->name] == false){
				 visited[temp->edges.at(i)->name] = true;
				 pred[temp->edges.at(i)->name] = u;
				 graphQueue.push_back(temp->edges.at(i)->name);

				 if (temp->edges.at(i)->name == dest){
					 return true;
				 }
			 }
		}

	}
	return false;

}
// A recursive function to print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void printAllPathsUtil(int u, int d, bool visited[], 
                            int path[], int &path_index, vector<Node*> graph, vector<Path*> paths) 
{ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    // If current vertex is same as destination, then print 
    // current path[] 
    if (u == d) 
    { 
		// vector<int> route;
		paths.push_back(new Path);
        for (int i = 0; i<path_index; i++) {
			paths.back()->path.push_back(path[i]);
		}
        cout << endl; 	
    } 
    else // If current vertex is not destination 
	{ 
		vector<Node*>::iterator i;
		for (i=graph.at(u)->edges.begin();i != graph.at(u)->edges.end(); ++i){
			
			Node* temp = *i;

			if (!visited[temp->name]){
				printAllPathsUtil(temp->name, d, visited, path, path_index, graph, paths);
			}
		}
    } 
  
  
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
}

// Prints all paths from 's' to 'd', num = # of vertices
void printAllPaths(int s, int d, int num, vector<Node*> graph, vector<Path*> paths) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[num]; 
  
    // Create an array to store paths 
    int *path = new int[num]; 
    int path_index = 0; // Initialize path[] as empty 
  
    // Initialize all vertices as not visited 
    for (int i = 0; i < num; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to print all paths 
    printAllPathsUtil(s, d, visited, path, path_index, graph, paths); 

	//print all paths

	for (int i=0;i<paths.size();i++){
		cout << "path " << i << "\n";
		for (int u=0;u<paths.at(i)->path.size();u++){
			cout << paths.at(i)->path.at(u);
		}
		cout << endl;
		
	}
	cout << endl;
} 

bool checkX(vector<Node*> graph, vector<Path*> paths, char p){
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// start at the 2nd node
		int node = paths.at(i)->path.at(1);
		// check how many truths are in the node we're checking
		int truthSize = graph.at(node)->truths.size();
		// for each truth, check if one of them matches p
		for (int u=0; u<truthSize;u++){
			if (graph.at(node)->truths.at(u) != p){
				return false;
			} 
		}
	}
	return true;
}

bool checkG(vector<Node*> graph, vector<Path*> paths, char p) {
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// for each node number in each path
		for (int g=0; g < paths.at(i)->path.size();g++){
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
				// if the truth != the given p, return false
				if (graph.at(node)->truths.at(h) != p) {
					return false;
				}
			}
		}
	}
	// return true if all the paths's truths have have checked
	return true;
}


// Graph Implementation in C++
int main()
{

	vector<Node*> graph;

	createNodes(graph);

	int size = graph.size();

	int pred[size]; 
	int start = 2;
	int dest = 3;

	vector<Path*> paths;

	printAllPaths(start, dest, size, graph, paths);

	return 0;
}