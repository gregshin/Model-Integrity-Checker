#include <iostream>
#include <vector>
#include <string>
#include <list> 
#include <iterator> 
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void test(){
    string str = "1,2,3,4,5,6";
    vector<int> vect;

    stringstream ss(str);

    for (int i; ss >> i;) {
        vect.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    vector<int>::iterator ptr; 
    for (ptr = vect.begin(); ptr < vect.end(); ptr++) {
        cout << *ptr << " ";
    }
}

void parseTruths (string truths){

    vector<string> results;

    stringstream ss(truths);

    string token;
    string token2;

    
    while(ss){
        getline(ss, token, ':');
        getline(ss, token2, ',');

        cout << token << "\n";
        cout << token2 << endl;
    }
    cout << "parse truth end" << endl;
}
void parseEdges (string edges){

    vector<string> results;

    stringstream ss(edges);

    string token;
    string token2;

    
    while(ss){
        getline(ss, token, ':');
        getline(ss, token2, ',');

        cout << token << "\n";
        cout << token2 << endl;
    }
    cout << "parse truth end" << endl;
}


void readFile (string fileName){

    ifstream file;

    stringstream nodes;
    stringstream edges;
    stringstream truths;

    string variable;
    string value;
    int nodesNum;


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
        } else if (variable == "edges"){
            edges << value;
            parseEdges(value);
        } else if (variable == "truths"){
            truths << value;
            // parseTruths(value);
        }
    }

    file.close();
    return;
}

int main(){

    string fileName = "graph.txt";

    readFile(fileName);

    // parseString();
    // test();

    // parseTruths();

    return 0;
}