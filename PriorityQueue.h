#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//********************************
//Priority Queue class header
//********************************
class PriorityQueue{
	//********************************
	//PQNode struct implementation
	//********************************
	struct PQNode{
		int index;		//index of the current node
		int distance;	//distance it is from the source
		

		PQNode():index(0), distance(0){};
		PQNode(int curr, int dist):index(curr), distance(dist){};
	};

//**************************************************
//Priority Queue Private Data Members and Functions
//**************************************************
	vector<PQNode> queue;		                                        //queue represented as a vector
	
	int Parent(int i){ return (i-1)/2;}                                 //get index of parent
    int Left(int i){ return (2*i + 1);}                                 //get index of left child
    int Right(int i){ return (2*i + 2);}                                //get index of right child
    
    bool HasLeft(int i){ return (Left(i) < (int)queue.size()); }        //is there a left child?
    bool HasRight(int i){ return (Right(i) < (int)queue.size()); }      //is there a right child?
    
    int PercolateDown(int hole);                                        //percolate the "hole" down
    int PercolateUp(int index);                                         //percolate a node up
    
    void DecreaseDist(int index, int dist);                             //decrease the distance of a node
	bool CheckIndex(int index);                                         //does the index exist in the queue

//********************************
//Priority Queue Public Functions
//******************************** 
public:
    PriorityQueue();
	void Enqueue(int index, int dist);                                   //enqueue (insert)
	int Dequeue(int &distance);                                         //dequeue (remove min)
};

PriorityQueue::PriorityQueue(){
	
}


//*****************************************************************************************
//Function:     Percolate Down
//Purpose:      Move the "hole" down the list to prep for Dequeue
//Incoming:     hole: index of the hole
//Outgoing:     Updated tree with hole moved down
//Return:       The new index of where the hole now is
//Author:       Jalyn Cosby, Whittney Schwarz
//Modified by:  Joshua Brown
//*****************************************************************************************
int PriorityQueue::PercolateDown(int hole){
    while (HasLeft(hole) || HasRight(hole)){                                    //continue looping while the hole still has any children
    
    	if(HasLeft(hole) && HasRight(hole)){                                        //If there are two children,
    		if(queue[Left(hole)].distance <= queue[Right(hole)].distance){              //and if the left child is smaller than the right child,
    			if(queue[queue.size()-1].distance >= queue[Left(hole)].distance){           //and only if the last node in the tree can fit where the child is,
                    iter_swap(queue.begin() + hole, queue.begin() + Left(hole));                //then swap the hole node with the child node
                    hole = Left(hole);                                                          //and update the index value for the hole.
                } else                                                                      //If the last node can't fit where the child is,
                    break;                                                                      //then we've already found a sutiable postion for it and we can break the loop.
                
            } else {                                                                    //If the right child is smaller than the left child,
                if(queue[queue.size()-1].distance >= queue[Right(hole)].distance){          //and only if the last node in the tree can fit where the child is,
                    iter_swap(queue.begin() + hole, queue.begin() + Right(hole));               //then swap the hole node with the child node
                    hole = Right(hole);                                                         //and update the index value for the hole.
                } else                                                                      //If the last node can't fit where the child is,
                    break;                                                                      //then we've already found a sutiable postion for it and we can break the loop.
            }
        } else {                                                                    //If there is only a left child,
            if(queue[queue.size()-1].distance >= queue[Left(hole)].distance){           //and only if the last node in the tree can fit where the child is,
                iter_swap(queue.begin() + hole, queue.begin() + Left(hole));                //then swap the hole node with the child node
                hole = Left(hole);                                                          //and update the index value for the hole.
            } else                                                                      //If the last node can't fit where the child is,
                break;                                                                      //then we've already found a sutiable postion for it and we can break the loop.
        }
    }
    return hole;                                                                //return the index of where the hole now is, so it can be filled in the Dequeue function
}


//*****************************************************************************************
//Function:     Percolate Up
//Purpose:      Move a node up the tree to fix the heap-order property
//Incoming:     index: index of the node to be percolated
//Outgoing:     Updated tree with the node moved up
//Return:       Updated index of where the hole is
//Author:       Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//Source:		https://www.geeksforgeeks.org/binary-heap/
//*****************************************************************************************
int PriorityQueue::PercolateUp(int index){
    while(index >= 0 && queue[Parent(index)].distance > queue[index].distance){ //loop until we've either reached the top, or found a suitable postion for the node
		iter_swap(queue.begin() + index, queue.begin() + Parent(index));            //continue swapping the current node with its parent
		index = Parent(index);                                                      //update the index of the new current node
	}
	return index;                                                               //return the index of where the node now is
}


//**********************************************************************************
//Function:     Decrease Distance
//Purpose:      Update a certain node's distance value, then fix the heap-order property
//Incoming:     index: the index of the node to be changed
//              dist: the NEW integer distance of the node from the source
//Outgoing:     Updated tree with the new value changed
//Return:       N/A-void function
//Author:       Joshua Brown, Jalyn Cosby
//**********************************************************************************
void PriorityQueue::DecreaseDist(int index, int dist){
    if(index >= 0 && index < (int)queue.size()){    //only if the index is a valid node in the vector
        queue[index].distance = dist;                   //update the distance at that node
        PercolateUp(index);                             //percolate up the updated node to ensure heap-order property is maintained
    } else                                          //otherwise, error
        cout << "Err: \"" << index << "\" is not a valid index" << endl;
}


//**********************************************************************************
//Function:     Check Index
//Purpose:      Check if a certain index exists somewhere in the queue
//Incoming:     index: the value of the index to be checked
//Outgoing:     N/A
//Return:       If we found the index or not
//Author:       Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//**********************************************************************************
bool PriorityQueue::CheckIndex(int index){
	bool retval = false;                       //default to false unless we find the index in the queue
	for(int i = 0; i < queue.size(); i++){     //loop through the entire queue
		if(queue[i].index == index){               //if the current node's index is equal to the one we're searching for
			retval = true;                             //then set the return value to true
			break;                                     //break the loop so as to not waste more time
		}
	}
	return retval;                             //return whether or not we found the index in the queue
}


//*****************************************************************************************
//Function:     Enqueue (Insert Function)
//Purpose:      Inserts a new node at the end of the queue, then percolates it up
//              to maintain the heap-order property. If a node already exists with the
//              given index, then we simply decrease the distance of that node.
//Incoming:     index: the index of the node being enqueued
//              distance: the total distance that node is from the source
//Outgoing:     updated queue with the new item inserted/updated
//Return:       N/A-void function
//Author:       Joshua Brown, Tay Cavett, Jalyn Cosby, Whittney Schwarz
//*****************************************************************************************
void PriorityQueue::Enqueue(int index, int dist){
    if(CheckIndex(index))               //if the index already exists within the queue,
        DecreaseDist(index, dist);          //then we update the distance corresponding to that index
    else{                               //otherwise, we enque a new node containing the data
        PQNode temp(index, dist);          //create a node containing the data
        
    	queue.push_back(temp);             //push that node to the back of the queue
    	
    	PercolateUp(queue.size()-1);       //percolate up the new node to ensure heap-order property is maintained
    }
}


//**********************************************************************************
//Function:     Dequeue (Remove Min Function)
//Purpose:      Removes node at top(minimum)
//Incoming:     &distance: a pass-by-reference parameter to get the distance of the dequeued node
//Outgoing:     Updated queue with the node removed
//Return:       The index of the node to be removed (distance is passed by reference)
//Author:       Jalyn Cosby, Whittney Schwarz
//Modified by:	Joshua Brown
//**********************************************************************************
int PriorityQueue::Dequeue(int &distance){
	int retval = INT_MIN;                    //initially set the return value to INT_MIN, in case we are unable to dequeue
	int hole = 0;                            //the "hole" will always be the root (first item in vector)
	
	if (queue.size() > 0){                   //Only if we have items in the queue, are we able to dequeue anything.
        
        retval = queue[0].index;                 //set the return value to the index of the current node
        distance = queue[0].distance;            //set the parameter for the distance of the current node (to be passed back by reference)
        
        if(queue.size() == 1)                    //If there is only one item in the queue,
            queue.pop_back();                        //we only need to remove that one item, no need to percolate.
        else{                                    //Otherwise,
            hole = PercolateDown(hole);                             //we need to percolate the hole down
    		queue[hole].index = queue[queue.size()-1].index;        //then fill the hole with the index data copied from the last node in the vector
    		queue[hole].distance = queue[queue.size()-1].distance;  //and copy the distance data as well
    		queue.pop_back();                                       //then simply remove the last node from the vector now that we've copied all its data
        }
	}
	return retval;                           //return the index (passing back distance by reference)
}




#endif	
