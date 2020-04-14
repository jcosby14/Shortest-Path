#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <string>
#include "PriorityQueue.h"
using namespace std;

const int SIZE = 7;

//********************************
//Graph Class Header
//********************************
class Graph{
    //********************************
    //GNode Struct Implementation
    //********************************
	struct GNode{
    	int wt;            //Weight
    	int adj;           //Adjacency
    	GNode* next;       //Pointer to next GNode (or NULL)
    	
    	GNode():wt(-1),adj(-1),next(NULL){};
    	GNode(int weight, int adjacency):wt(weight),adj(adjacency),next(NULL){};
	};
	
//******************************************
//Graph Private Data Members and Functions
//******************************************
	GNode* adjList[SIZE];                      //adjacency list parallel array
	string names[SIZE];                        //names parallel array
	int distFromSrc[SIZE];                     //distance from source parallel array
	int changedby[SIZE];                       //who changed me parallel array
	
	void PrintPath(int src, int dest);
	void PrintPathHelper(int location, int src, int dest);
	
	void Reset();                              //reset the graph for another algorithm to run
	
//******************************************
//Graph Public Functions
//******************************************
public:
	Graph();                                   //Default Constructor
	~Graph();								   //Destructor
	void AddAdj(int index, int wt, int adj);   //Add adjacency
	string GetName(int i){ return names[i]; }  //Get name of given index
	void ShortestPath(int src, int dest);      //Find a shortest path from src to dest
};


//*****************************************************************************************
//Function:     Graph default constructor
//Purpose:      To create an empty graph
//Incoming:     N/A
//Outgoing:     A new graph
//Return:       N/A
//Authors:      Tay Cavett, Joshua Brown
//*****************************************************************************************
Graph::Graph(){
	for(int i = 0; i < SIZE; i++){  //loop through entire adjacency list
		adjList[i] = NULL;              //set all pointers to NULL
		distFromSrc[i] = INT_MAX;
		changedby[i] = INT_MIN;
	}
	                                //hardcoded all the names for our particular graph
	names[0] = "Empire State Building";		//0
	names[1] = "Penn Station";				//1
	names[2] = "Rector Street Station";		//2
	names[3] = "9/11 Memorial";				//3
	names[4] = "Wall Street Station";		//4
	names[5] = "Grand Army Plaza Station";	//5
	names[6] = "Grand Army Plaza";			//6
}

void Graph::Reset(){
	for(int i = 0; i < SIZE; i++){  //loop through entire adjacency list
		distFromSrc[i] = INT_MAX;
		changedby[i] = INT_MIN;
	}
}


//*****************************************************************************************
//Function:     Graph destructor
//Purpose:      To destroy the graph
//Incoming:     N/A
//Outgoing:     N/A
//Return:       N/A
//Authors:      Tay Cavett, Joshua Brown
//*****************************************************************************************
Graph::~Graph(){
	for(int i=0; i<SIZE; i++){         //loop through every node
		while(adjList[i]){                 //loop through all its adjacencies
			GNode* temp = adjList[i];          //temp var
			adjList[i] = temp->next;           //move to next adjacency (or NULL)
			delete temp;                       //delete the old previus adjacency (what temp points to)
		}
	}
}


//*****************************************************************************************
//Function:     Add Adjacency
//Purpose:      Add an adjacency to the specified index
//Incoming:     index: where to insert the adj
//              wt: the weight of the adj
//			    adj: the location of the adj
//Outgoing:	    The graph is updated with the adjacency
//Return:	    N/A
//Authors:	    Tay Cavett, Joshua Brown
//*****************************************************************************************
void Graph::AddAdj(int index, int wt, int adj){
	if(adjList[index] == NULL){                //if there is no adjacency for the current node,
		adjList[index] = new GNode(wt, adj);      //then add the new one to that node
	} else {                                   //if there is already at least one adjacency,
		GNode* temp = adjList[index];             //use a temp variable
		while(temp->next != NULL){                //to loop to the end of the adjacency "chain"
			temp = temp->next;
		}
		temp->next = new GNode(wt, adj);          //add the new adjacency to the end of the "chain"
	}
}


//*****************************************************************************************
//Function:     Shortest Path
//Purpose:      Find a shortest path from src to dest, using Dijkstra's algorithm.
//              Then print this path for the user.
//Incoming:     src: the index of the starting node
//              dest: the index of the destination node
//Outgoing:	    Printing the path to the screen
//Return:	    N/A-void function
//Authors:	    Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//*****************************************************************************************
void Graph::ShortestPath(int src, int dest){
	int eye = src;                 //"eyeball" index
	int eyedist = 0;               //distance the eye is from the src
	distFromSrc[src] = eyedist;    //update this distance in the distFromSrc parallel array
	
	PriorityQueue pq;              //initialize a priority queue
	
	
	while(eye != dest){                                        //loop until we reach the destination
		GNode* curr = adjList[eye];                                //temp variable for the adjecency we're currently "looking" at
		while(curr){                                               //loop through all adjacencies of the current eyeball
			if(curr->wt + eyedist <= distFromSrc[curr->adj]){          //if the distance to the current node is less than what is currently stored for that node,
				distFromSrc[curr->adj] = curr->wt + eyedist;               //then update that value
				pq.Enqueue(curr->adj, distFromSrc[curr->adj] );            //and add it to the priority queue
				changedby[curr->adj] = eye;                                //also update that the current eyeball "changed us"
			}
			curr = curr->next;                                         //once done with the current adjacency, move to the next one
		}                                                          //once done with all adjacencies for this eyeball,
		eye = pq.Dequeue(eyedist);                                 //move to the next one (the node with the shortest path is dequeued) and update our distance
	}
	
	cout << endl << endl << "A shortest path from " << names[src] << " to " << names[dest] << ":" << endl << endl;
	PrintPath(src, dest);  //print the path
	cout << endl << "This path takes approximately " << eyedist << " minutes to navigate." << endl << endl;
	
	Reset();               //reset the graph so we can find other shortest paths later
}


//*****************************************************************************************
//Function:     Print Path
//Purpose:      Print the shortest path that was found in "ShortestPath()" by using a
//              recursive helper function to traverse the "changedby" array in reverse
//              order, since that array points from dest to src and we want src to dest.
//Incoming:     src: the index of the starting node
//              dest: the index of the destination node
//Outgoing:	    Printing the path to the screen
//Return:	    N/A-void function
//Authors:	    Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//*****************************************************************************************
void Graph::PrintPath(int src, int dest){
	PrintPathHelper(dest, src, dest);
}


//*****************************************************************************************
//Function:     Print Path Helper
//Purpose:      Recursive helper to the "PrintPath()" function.
//Incoming:     location: variable to help iterate through the "changedby" array
//              src: the index of the starting node
//              dest: the index of the destination node
//Outgoing:	    Print a single location's name, depending on the current state of recursion
//Return:	    N/A-void function
//Authors:	    Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//*****************************************************************************************
void Graph::PrintPathHelper(int location, int src, int dest){
	if(location == src)                                        //if we've reached the source, we're done
		cout << names[location] << endl;                           //and we can print out the name of the location
	else{                                                      //if we haven't reached the source yet
		PrintPathHelper(changedby[location], src, dest);           //recurse down
		cout << "to" << endl;
		cout << names[location] << endl;                           //then print the name of the current location
	}
}


#endif
