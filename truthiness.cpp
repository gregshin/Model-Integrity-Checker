#include <iostream>
#include <vector>
#include <string>
#include <list> 
#include <iterator> 
#include <fstream>
#include <sstream>

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
// Find all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
void findAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index, vector<Node*> &graph, vector<Path*> &paths){ 
    // Mark the current node and store it in path[] 
    visited[u] = true; 
    path[path_index] = u; 
    path_index++; 
  
    // If current vertex is same as destination, then save 
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
				findAllPathsUtil(temp->name, d, visited, path, path_index, graph, paths);
			}
		}
    } 
    // Remove current vertex from path[] and mark it as unvisited 
    path_index--; 
    visited[u] = false; 
}
// finds all paths from 's' to 'd', num = # of vertices
void findAllPaths(int s, int d, int num, vector<Node*> &graph, vector<Path*> &paths){ 
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
    // Call the utility function to find all paths 
    findAllPathsUtil(s, d, visited, path, path_index, graph, paths); 
	//find all paths
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
			char currTruth = p;
			bool pExists = false;
			bool qExists = false;
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){

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
					qExists = true;
					currTruth = q;
					valid = true;
					// note: does not just return true because we need to check to sese if p exists at the same time
				}
			}
			// invalidation criteria
			// if it's the first node and p does not exist, path is invalid
			if (g==0 && pExists == false){
				valid = false;
				break;
			// if it's the first node and q exists, path is invalid
			} else if (g==0 && qExists == true){
				valid = false;
				break;
			// if p and q exist at the same time, path is invalid
			} else if (pExists == true && qExists == true){
				valid = false;
				break;
			// if neither p nor q exist in a node, path is invalid
			} else if (pExists != true && qExists != true){
				valid = false;
				break;
			// if the path is valid and q exists, return true
			} else if (valid == true && qExists == true){
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
		for (int g=0; g < paths.at(i)->path.size();g++){
			// setinel boolean for if the truths are valid at the node
			bool valid = false;
			char currTruth = p;
			bool pExists = false;
			bool qExists = false;
			int node = paths.at(i)->path.at(g);
			// check the corresponding node in graph and loop through the truths
			for (int h=0; h < graph.at(node)->truths.size(); h++){
			
				if (g==0 && graph.at(node)->truths.at(h) == q){
					qExists = true;
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
					valid = true;
					pExists = true;
				} else if (g!=0 && graph.at(node)->truths.at(h) == q && currTruth == p){
					qExists = true;
					currTruth = q;
					valid = true;
					// note: does not just return true because we need to check to sese if p exists at the same time
				}
			}
			// invalidation criteria
			// if it's the first node and p does not exist, path is invalid
			if (g==0 && pExists == false){
				valid = false;
				break;
			// if it's the first node and q exists, path is invalid
			} else if (g==0 && qExists == true){
				valid = false;
				break;
			// if p and q exist at the same time, path is invalid
			} else if (pExists == true && qExists == true){
				valid = false;
				break;
			// if neither p nor q exists in a node, path is invalid
			} else if (pExists != true && qExists != true){
				valid = false;
				break;
			// if the path is valid and q exists, return true
			} else if (valid == true && qExists == true){
				return true;
			// if p stays valid until the last node, return true
			} else if (g == graph.at(node)->truths.size()-1 && pExists == true && qExists == false){
				return true;
			}
		}
	}
	// return true if all the paths's truths have have checked
	return false;
}
// check R by calling W with reversed p and q
bool checkR(vector<Node*> &graph, vector<Path*> &paths, char p, char q){
	if (checkW(graph, paths, q, p)==true){
		return true;
	} else {
		return false;
	}
	return false;
}

bool validity(vector<Node*> &graph, vector<Path*> &paths){
	// info for checking model validity
	char formula;
	char p;
	char q;
	bool validity;

	cout << "What formula would you like to check? (X, G, F, U, W, or R) ";
	cin >> formula;

	// use different truth functions for different user input
	switch(formula)
	{
		case 'X':
			cout << "What truth should be checked? ";
			cin >> p;
			cout << "Checking if X(" << p << ") is true\n";
			validity = checkX(graph, paths, p);
			break;
		case 'G':
			cout << "What truth should be checked? ";
			cin >> p;
			cout << "Checking if G(" << p << ") is true\n";
			validity = checkG(graph, paths, p);
			break;
		case 'F':
			cout << "What truth should be checked? ";
			cin >> p;
			cout << "Checking if F(" << p << ") is true\n";
			validity = checkF(graph, paths, p);
			break;
		case 'U':
			cout << "What is the first truth to be checked? ";
			cin >> p;
			cout << "What is the second truth to be checked? ";
			cin >> q;
			cout << "Checking if " << p << "U" << q << " is true\n";
			validity = checkU(graph, paths, p, q);
			break;
		case 'W':
			cout << "What is the first truth to be checked? ";
			cin >> p;
			cout << "What is the second truth to be checked? ";
			cin >> q;
			cout << "Checking if " << p << "W" << q << " is true\n";
			validity = checkW(graph, paths, p, q);
			break;
		case 'R':
			cout << "What is the first truth to be checked? ";
			cin >> p;
			cout << "What is the second truth to be checked? ";
			cin >> q;
			cout << "Checking if " << p << "R" << q << " is true\n";
			validity = checkW(graph, paths, p, q);
			break;
		default:
			cout << "Invalid formula";
			break;
	}
	return validity;
}

void nodesFromFile(int nodes, vector<Node*> &graph){
	for (int i=0;i<nodes;i++){
		graph.push_back(new Node);
		Node* temp = graph.at(i);
		temp->name = i;
	}
}

void truthsFromFile(vector<Node*> &graph, string truths){

    stringstream ss(truths);

    string token;
    string token2;

    while(!ss.eof()){

		stringstream num;
		stringstream truthTemp;
		int node;
		char truth;

        getline(ss, token, ':');

		num << token;
		num >> node;

		Node* temp = graph.at(node);

        getline(ss, token2, ',');

		truthTemp << token2;
		truthTemp >> truth;

		temp->truths.push_back(truth);
    }
}

void edgesFromFile(vector<Node*> &graph, string edges){
	stringstream ss(edges);

    string token;
    string token2;

	while (!ss.eof()){
		stringstream numTemp;
		stringstream numTemp2;
		int nodeNum = 0;
		int edgeNum = 0;

		getline(ss, token, ':');

		numTemp << token;
		numTemp >> nodeNum;

		Node* node = graph.at(nodeNum);

		getline(ss, token2, ',');

		numTemp2 << token2;
		numTemp2 >> edgeNum;

		Node* edge = graph.at(edgeNum);

		node->edges.push_back(edge);

	}
}

void graphFromFile (string fileName, vector<Node*> &graph){

    ifstream file;

    stringstream nodes;
    stringstream edges;
	stringstream truths;

    string variable;
    string value;
    int nodesNum;
	string allEdges;
	string allTruths;


    file.open(fileName);

    if (!file.is_open()){
        cout << "File cannot be opened";
        return;
    }

    while(!file.eof()){

        if(!file){
            break;
        }

        getline(file, variable, '=');
        getline(file, value, '\n');

        if (variable == "numNodes"){
            nodes << value;
            nodes >> nodesNum;
			nodesFromFile(nodesNum, graph);
        } else if (variable == "edges"){
            edges << value;
			edges >> allEdges;
			edgesFromFile(graph, allEdges);
        } else if (variable == "truths"){
			truths << value;
			truths >> allTruths;
			truthsFromFile(graph, allTruths);
		}
    }

    file.close();

    return;
}

// Graph Implementation in C++
int main()
{	
	// create vector to hold nodes
	vector<Node*> graph;
	// sentinal for first option
	bool validOption = false;

	while (validOption == false){
		int createType;

		cout << "1: Read from File\n2: Input manually?" << endl;
		cin >> createType;

		if (createType == 1){
			string fileName = "graph.txt";
			graphFromFile(fileName, graph);
			validOption = true;
		} else if (createType == 2){
			createNodes(graph);
			validOption = true;
		} else {
			cout << "Invalid option. Please try again" << endl;
		}
	}

	// for use in finding shortest path
	int size = graph.size();
	int pred[size]; 
	
	// define starting and ending nodes;
	int start;
	int dest;

	cout << "Starting node #? ";
	cin >> start;
	cout << endl;

	cout << "Destination node #? ";
	cin >> dest;
	cout << endl;

	// create vector to hold paths
	vector<Path*> paths;

	// find all paths
	findAllPaths(start, dest, size, graph, paths);

	bool valid = validity(graph, paths);

	if (valid == true){
		cout << "valid\n";
		cout << endl;
	} else if (valid == false){
		cout << "not valid\n";
		cout << endl;
	}
	return 0;
}