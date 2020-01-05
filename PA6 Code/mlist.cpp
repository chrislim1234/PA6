#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){
    
 //set top and bottom to null   
 ntop = NULL;
 nbottom = NULL;

}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
   
  //use clear functiojn  
  clear();
    
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
    
    
   //recursive function checking if empty
   //if it is not empty pop top;
   if (isEmpty()==false) {
       pop_top();
       clear();
     }

}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
      
    //if top and bottom is null, then it is empty
    
    if (ntop==NULL && nbottom==NULL) {
              return true;
      }
      
    else {
          return false;
      }

}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
    
    
        //create new node with data item
    
        Node* temp = new Node();
      
        temp->nodeData = d_item;
        temp->prev = NULL;
        
        //3 case scenarios, #1 is if empty
        //#2 is if one item
        //#3 is regular
        if(isEmpty()==true)
        {
            ntop = temp;
            nbottom = temp;
            
        }
        else if (ntop==nbottom) {
            nbottom = ntop;
            ntop->prev = temp;
            temp->next = ntop;
            ntop = temp;  
        }
        else    
        {
            temp->next = ntop;
            ntop->prev = temp;
            ntop = temp;
        }

}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
    
        //same as push top but from bottom

        Node* temp = new Node();
      
        temp->nodeData = d_item;
        //temp->prev = nbottom;
        temp->next = NULL;

        if(isEmpty()==true)
        {
            ntop = temp;
            nbottom = temp;
        }
        else if (ntop==nbottom)
        {
            ntop = nbottom;
            nbottom->next = temp;
            temp->prev = nbottom;
            nbottom = temp;
            
        }
        else {
            nbottom->next = temp;
            temp->prev= nbottom;
            nbottom = temp;
        }
    
    
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
    
    
        //create a temp to delete node
        //reset ntop and nbottom aftewards

        Node* temp;
      
        if(isEmpty()==true)
        {
            return;
            }
        else if (ntop==nbottom) {
            temp = ntop;
            delete temp;
            ntop = NULL;
            nbottom = NULL;
            }
         else {
                temp = ntop;
                ntop = ntop->next;
                ntop->prev = NULL;
                delete temp;
            }
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
    
    
       //same as poptop but for bottom

        Node* temp;
      
        if(isEmpty()==true)
        {
            return;
            }
        else if (ntop==nbottom) {
            delete nbottom;
            ntop = NULL;
            nbottom = NULL;
            }
         else {
                temp = nbottom;
                nbottom = nbottom->prev;
                nbottom->next = NULL;
                delete temp;
            }
        
    
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){

    //recursive and check if name is equal to node
    //in list

    if (start==NULL) {
        return NULL;
    }
    
    else if (name.compare(start->nodeData->name)==0) {
        return start;
    
    }
    else {
        return search(start->next, name);
    }
    
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){
    
    //if empty, or one node, fails

    if (a==NULL || b==NULL || a==b) {
        return;
    }
    
    //create temp for a, remove it, insert temp
    //and then remove b
    
    Node* temp = a->prev;
    removeNode(a);
    insertAfter(a,b);
    removeNode(b);
    
    //this makes sure scenario in which a is next to b,
    //and temp isn't moved, insert a or temp
    if (temp!=b) {
        insertAfter(b,temp);
    }
    else {
        insertAfter(b,a);
    }
    

}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){
    
    //four secnarios, empty, one item, a is top, a is bottom
    
    if (isEmpty()==true) {
        return;
    }
    
    if (ntop==nbottom) {
        ntop=NULL;
        nbottom=NULL;
    }
     
    

    else if (nbottom == a) {
        nbottom = a->prev;
        (a->prev)->next = NULL;
    }
    
    else if (ntop==a ) {
        ntop = a->next;
       ( a->next) -> prev = NULL; 
    }
    
    //regular shifts to link a prev and a next
    
    if (a->next!=NULL)  {
        (a->next)->prev = a->prev;
    }
    if (a->prev!=NULL) {
        (a->prev)->next = a->next;
    }
       
    //delete a 
    
    delete a;
    a = NULL;
    
    

}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){
    
    //three scenarios, empty, one item, and else
    
    if (isEmpty()==true) {
        return;
    }
    
    else if (ntop==nbottom) {
        ntop = NULL;
        nbottom = NULL;
    }

    else {
        
        //check if a is top or bottom
        
        if(ntop==a) {
            ntop = a->next;
        }

        else if (nbottom ==a) {
            nbottom = a->prev;
        }
        
        //regular shifts same as delete 
        
        if (a->prev!=NULL) {   
            (a->prev)->next = a->next;
        }
        
        if (a->next!=NULL) {
            (a->next)->prev = a->prev;
        }
        
    } 
        
    
    //lose all of a's links
    a->prev =NULL;
    a->next = NULL;
    
}


	/*Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){

    
    //check for b being null (would happen when b is ntop)
    if (b!=NULL) {
        a->next = b->next;
        a->prev = b;
        b->next = a;
    }
    
    else  {
        a->next = ntop;
        ntop = a;
        a->prev=b;
        
    }
    
    //check for b being bottom
    if (nbottom == b) {
        nbottom = a;
        a->prev=b;
    }
    
    //regular 
    if (a->next!=NULL) {
        (a->next)->prev = a;
        a->prev=b;
    }
      
    
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){

    //quits when its empty or when list is done with
    if (isEmpty()==true || start==NULL) {
        return;
    }
    
    //declare variable
    Node* head = start;
    Node* temp;
    string str = start->nodeData->name;
    size_t size1 = start->nodeData->size;
    
    //go through list using head and its next function
    while (head !=NULL) {
        //check if alphabetical and if name is smaller
        if (mode==true && 0<str.compare(head->nodeData->name)) {
            str = head->nodeData->name;
            //swap node if head is smaller and start
            swapNode(head,start);
            //bring head back to start
            temp = start;
            start = head;
            head = temp;
            
        }
        
        if (mode==false && size1>(head->nodeData->size)) {
            //the same but based on size
            size1 = head->nodeData->size;
            swapNode(head,start);
            temp = start;
            start = head;
            head = temp;
        }
        
        head = head->next;
        
    }
    //recursive so it goes through the entire list
    sortSelection(start->next, mode);

}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){

    if (isEmpty()==true || start==NULL) {
        return;
    }
    
    
    Node* head=start->prev;
    
    //use while loop to find node whcih is not bigger than start
    while ((head != NULL) && 0>(start->nodeData->name).compare(head->nodeData->name)) {
        head = head ->prev; 
    }
    
    //remove node if itst true, and insert before start
    removeNode(start);
    insertAfter(start,head);
    
    //recursive go through whole list
    sortInsertion(start->next);       
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
    
    //fail if node is null, if folder, print name, if file include size

    if(n==NULL) {
        return;
    }
    else if (n->nodeData->isFolder) {
        cout<<n->nodeData->name<<delim;
        
    }
    else {
        cout<<n->nodeData->name<<"("<<n->nodeData->size<<")"<<delim;
    }
    
    
    //recursive up
    traverseToTop(n->prev, delim);
    

}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
    
    //same as above but the opposite direction

    if(n==NULL) {
        return;
    }
    else if (n->nodeData->isFolder) {
        cout<<n->nodeData->name<<delim;
        
    }
    else {
        cout<<n->nodeData->name<<"("<<n->nodeData->size<<")"<<delim;
    }
    
    
    //recursive down
    traverseToBottom(n->next, delim);
     
    
    
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}