#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "Graph.h"
using namespace std;


void BuildGraph(Graph &graph);
void Menu(Graph &g);


int main(){
	Graph g;               //initialize graph
	BuildGraph(g);         //fill graph with data from our real-world proposal
	
	
    int src = 0;
	int dest = 0;
	
	while(true){
		Menu(g); cout << endl;
		cout << "Choose a starting location(-1 to quit): ";
		cin >> src;
		if(src == -1)
			break;
		else if( !(src >= 0 && src < SIZE) ){
			cout << "Not a valid input. option 0 chosen by default." << endl << endl;
			src = 0;
		}
		cout << "Starting at " << g.GetName(src) << "." << endl;
		cout << "Now, choose a destination(-1 to quit): ";
		cin >> dest;
		if(dest == -1)
			break;
		else if( !(dest >= 0 && dest < SIZE) ){
			cout << "Not a valid input. option 6 chosen by default." << endl << endl;
			src = 6;
		}
		g.ShortestPath(src, dest);
	}
	
    return 0;
}


void BuildGraph(Graph &graph){
	graph.AddAdj(0,7,1);
	graph.AddAdj(0,20,3);
	graph.AddAdj(0,39,6);
	
	graph.AddAdj(1,22,4);
	graph.AddAdj(1,36,5);
	graph.AddAdj(1,27,2);
	
	graph.AddAdj(2,6,3);
	
	graph.AddAdj(3,10,4);
	graph.AddAdj(3,23,6);
	graph.AddAdj(3,20,0);
	
	graph.AddAdj(4,26,5);
	
	graph.AddAdj(5,1,6);
	
	graph.AddAdj(6,40,0);
}


void Menu(Graph &g){
	cout << "Menu" << endl;
	for(int i = 0; i < SIZE; i++)
		cout << "#" << i << ": " << g.GetName(i) << endl;
}
    
