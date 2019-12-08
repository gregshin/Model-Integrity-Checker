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
// function to create graph populated by nodes
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
			cout << "Is anything else true? y or n\n";
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
// saving for later
bool shortestPath(vector<Node*> &graph, int n, int start, int dest, int pred[]){
	list<int> graphQueue;
	bool visited[n];
	// loop through # of nodes
	// fill visited with false
	// populate pred with -1
	for (int i = 0; i < n; i++) { 
		visited[i] = false;
		pred[i] = -1; 
	} 
	// mark the starting node as visited
	// push starting node to the queue
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
				// retrun true if we're at the destination
				if (temp->edges.at(i)->name == dest){
					return true;
				}
			}
		}

	}
	return false;
}
// print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void printAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index, vector<Node*> &graph, vector<Path*> &paths){ 
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
    // If current vertex is not destination
	} else { 
		// initialize vector iterator
		vector<Node*>::iterator i;
		// iterate through edges of node
		for (i=graph.at(u)->edges.begin();i != graph.at(u)->edges.end(); ++i){
			Node* temp = *i;
			// recurse with the child node as starting node
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
void printAllPaths(int s, int d, int num, vector<Node*> &graph, vector<Path*> &paths){ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[num];  
    // Create an array to store paths 
    int *path = new int[num]; 
	// Initialize path[] as empty 
    int path_index = 0; 
    // Initialize all vertices as not visited 
    for (int i = 0; i < num; i++){
        visited[i] = false; 
	}
    // Call the utility function to print all paths 
    printAllPathsUtil(s, d, visited, path, path_index, graph, paths); 
	//print all paths
	for (int i=0;i<paths.size();i++){
		cout << "path " << i << ": ";
		for (int u=0;u<paths.at(i)->path.size();u++){
			cout << paths.at(i)->path.at(u) << "->";
		}
		cout << endl;
	}
	cout << endl;
} 

// Next
bool checkX(vector<Node*> &graph, vector<Path*> &paths, char p){
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// start at the 2nd node
		int node = paths.at(i)->path.at(1);
		// check how many truths are in the node we're checking
		int truthSize = graph.at(node)->truths.size();
		// for each truth, check if one of them matches p
		for (int u=0; u<truthSize;u++){
			if (graph.at(node)->truths.at(u) == p){
				return true;
			} 
		}
	}
	return false;
}
// Global
bool checkG(vector<Node*> &graph, vector<Path*> &paths, char p) {
	bool valid = false;
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// for each node number in each path
		for (int g=0; g < paths.at(i)->path.size();g++){
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
				// if the truth != the given p, return false
				if (graph.at(node)->truths.at(h) == p) {
					// if the desired truth is found, change valid to true and break the loop
					valid = true;
					break;
				} 
			}
		}
		// if a valid path is found, return true
		if (valid == true){
			return true;
		}
	}
	// return true if all the paths's truths have have checked
	return false;
}
// Future
bool checkF (vector<Node*> &graph, vector<Path*> &paths, char p){
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// for each node number in each path
		for (int g=0; g < paths.at(i)->path.size();g++){
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
				// if the truth != the given p, return false
				if (graph.at(node)->truths.at(h) == p) {
					return true;
				}
			}
		}
	}
	// return true if all the paths's truths have have checked
	return false;
}
bool checkU (vector<Node*> &graph, vector<Path*> &paths, char p, char q){
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// for each node number in each path
		for (int g=0; g < paths.at(i)->path.size();g++){
			// setinel boolean for if the truths are valid at the node
			bool valid = false;
			bool pExists;
			char currTruth = p;
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
				pExists = false;

				if (g==0 && graph.at(node)->truths.at(h) == q){
					valid = false;
					break;
				} else if (g==0 && graph.at(node)->truths.at(h) == p){
					pExists = true;
					valid = true;
				}
				// break if both p and q are true at the same time
				if (g!=0 && graph.at(node)->truths.at(h) == p && currTruth == q){
					valid = false;
					break;
				} else if (g!=0 && graph.at(node)->truths.at(h) == p && currTruth == p){
					pExists = true;
					valid = true;
				} else if (g!=0 && graph.at(node)->truths.at(h) == q && currTruth == p){
					currTruth = q;
					valid = true;
					// note: does not just return true because we need to check to sese if p exists at the same time
				}

				if (pExists == false){
					valid = false;
					break;
				}
			}
			if (g==0 && currTruth != p){
				valid = false;
				break;
			}
			// put stuff outside the truth loop to compute
			if (valid == true && currTruth == q){
				return true;
			}
		}
	}
	// return true if all the paths's truths have have checked
	return false;
}
// check w
bool checkW (vector<Node*> &graph, vector<Path*> &paths, char p, char q){
	// for each Path in paths
	for (int i=0; i<paths.size();i++){
		// for each node number in each path
		char currTruth = p;
		bool valid = false;
		for (int g=0; g < paths.at(i)->path.size();g++){
			// setinel boolean for if the truths are valid at the node
			currTruth = p;
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
				bool pExist = false;

				if (g==0 && graph.at(node)->truths.at(h) == q){
					valid = false;
					break;
				} else if (g==0 && graph.at(node)->truths.at(h) == p){
					valid = true;
					pExist = true;
				}
				// break if both p and q are true at the same time
				if (g!=0 && graph.at(node)->truths.at(h) == p && currTruth == q){
					valid = false;
					break;
				} else if (g!=0 && graph.at(node)->truths.at(h) == p && currTruth == p){
					valid = true;
					pExist = true;
				} else if (g!=0 && graph.at(node)->truths.at(h) == q && currTruth == p){
					currTruth = q;
					valid = true;
					break;
				}
				if (pExist == false){
					valid = false;
					break;
				}
			}
			// put stuff outside the truth loop to compute
			if (valid == true && currTruth == q){
				return true;
			}
		}
		if (valid == true && currTruth == p){
			return true;
		}
	}
	// return true if all the paths's truths have have checked
	return false;
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

	char p = 'p';

	bool validity = checkG(graph, paths, p);

	cout << "Checking if X(p) is true\n";
	if (validity == true){
		cout << "valid\n";
		cout << endl;
	} else if (validity == false){
		cout << "not valid\n";
		cout << endl;
	}
	return 0;
}