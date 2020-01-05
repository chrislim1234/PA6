#include <iostream>
#include "os.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//------------------------------------------------------------------------------

/*
Constructor
	Dynamically allocate root data.
	set isFolder = true.
	dynamically allocate Mlist for our root data as well (since it's a directory type).
    push our newly created data object pointer to wd and dataStack from the top.
*/
OS::OS(){

    //create new root data, ad name, folder and childlist
    root_data = new Data();
    
    root_data->isFolder = true;
    
    root_data->childList = new MList();
    
    root_data->name = "root";
    
    //add to stack and work directory 
    wd.push_top(root_data);
        
    dataStack.push_top(root_data); 
    
    
    
}

/*
Destructor to clean-up memory, i will leave this for you to figure it out.
*/
OS::~OS(){

    //delete datstack memory
    
    Node* nd = dataStack.top();
    while (dataStack.isEmpty()==false) {
        //take top of stack until empty 
        nd=dataStack.top();
        if (nd->nodeData->isFolder==true) {
            //delete childlist if it is folder
            delete (nd->nodeData->childList);
            }
        //delete the node data
        delete (nd->nodeData);
        
        //delete node itself
        dataStack.pop_top();
    }
     
    
    
}

/*
Search a node in the current directory
	If one is found, return a pointer to that node
	If one is not found, return NULL
*/
Node* OS::search_item(string fname){
    
    //search for node, if its null return null, else return it
    MList* n =(wd.top()->nodeData->childList);
    Node* nd = n->search(n->top(),fname);
    if (nd==NULL) {
        return NULL;
        
    }
    else {
        return nd;
    }
    
    
    
}

/*
Delete a node in the current directory
	Note: this function only deletes (permanently) the node, not the Data obj the node points to
	If the item you want to delete doesn't exist in the current directly, do

		cout<<"Error: cannot find file or directory '"<<fname<<"'"<<endl;
*/
void OS::del(string fname){
    
    Node* nd = search_item(fname);
    MList* n = (wd.top()->nodeData->childList);
    
    //if node is null, say that you cant find it, else delete it
    if (nd==NULL) {
        cout<<"Error: cannot find file or directory '"<<fname<<"'"<<endl;
    }
    else {
        n->deleteNode(nd);
    }
    
    
    
}

/*
Create a file or a folder, use boolean isFolder to tell (true if folder, false if file)
Things to keep in mind:
	1). Don't forget to search for a node in the current directory with the same name first.
		if the name already exists, do:

				cout<<"Directory or file name '"<<fname<<"' already exists"<<endl;

	2). If you are creating a folder, make sure to allocate a memory for its MList object
		and set the boolean isFolder appropriately.
    3). At this point you should initialize the size of file and folder to 0
	4). Once the data object is created, add the pointer to that to dataStack from the "top" 
		and add the node to the current directory list from the "bottom".
	5). Once added, sort the current directory list by name.
*/
void OS::create_item(string fname, bool isFolder){
    
    //check if node exist, if it does say it already exists 
    Node* nd = search_item(fname);
    
    if ( nd != NULL) {
        cout<<"Directory or file name '"<<fname<<"' already exists"<<endl;
        return;
    }
    
    //create new data with data items
    Data* data = new Data();
    data->name = fname;
    data->isFolder = isFolder;
    data->text = "";
    data->size = 0;
    
    //add childlist if its folder
    if (isFolder==true) {
        data -> childList = new MList();
    }
    
    MList* n = (wd.top()->nodeData->childList);
    
    //add data into stack and to childList 
    
    n->push_bottom(data);
    dataStack.push_bottom(data);
    
    dataStack.sortByNameInsertion();
    n->sortByNameInsertion();
}

/*
Read or write a file according to the boolean isRead (true = read, false = write)
Things to keep in mind:
	1). make sure that a file "fname" exists in our current directly, if not

			cout<<"Error: cannot find file '"<<fname<<"'"<<endl;

	2). if it exists, make sure that it is a file type, not a folder type. If it is a folder type,

			cout<<"Error: '"<<fname<<"' is not a file"<<endl;

	3). read mode is simply just cout<<...text...<<endl;
	4). for write mode you need to allow user input, use these 3 lines below:

                cout<<"$> ";
				string input;
				getline(cin,input);

		then simply just set text to the input string.
	5). the size of the file should be based on the length of the input string.
*/
void OS::file(string fname, bool isRead){
    
    //search for node
    Node* nd = search_item(fname);
   
    
    //check if file can be found or if its not a file
    if( nd==NULL) {
        cout<<"Error: cannot find file '"<<fname<<"'"<<endl;
        return;
    }  
    
    else if (nd->nodeData->isFolder == true) {
         cout<<"Error: '"<<fname<<"' is not a file"<<endl;
         return;
    }
    
    //check if its read or write
    if (isRead==true) {
        cout<<nd->nodeData->text<<endl;
        return;
    }
    
    //take input and add to nodedata
    cout<<"$> ";
	string input;
	getline(cin,input); 
    
    nd->nodeData->text=input;
    nd->nodeData->size = input.size();
    
}


//Change directory
void OS::cd_dir(string fname){
	if(fname == ".."){
		//this option takes you up one directory (move the directory back one directory)
		//you should not be able to go back anymore if you are currently at root.
        
        //if its not root, pop top
        if (wd.top()->nodeData == root_data) {
            return;
        }
        else {
            wd.pop_top();
        }

	}
    else if(fname == "~"){
		//this option takes you directly to the home directory (i.e., root).
        Node* nd = wd.top();
        
        //pop until you get to root
        while ( nd->nodeData != root_data) {
            wd.pop_top();
            nd = wd.top();
        }
        
        


	}
    else{
		/*
			This option means that you are trying to access (go into) a directory
			1). check whether there exists a node with that name, if you cannot find it:

					cout<<"Error: cannot find directory '"<<fname<<"'"<<endl;

			2). if it does exist, check whether it is a folder type. If it is a file type:

					cout<<"Error: '"<<fname<<"' is not a directory"<<endl;
			
			3). after checking both things, you can safely move to another directory
		*/
        
        Node* nd = search_item(fname);
        
        //search if its null, say it can't be found and if its a file 
        //give erorr asking for directory 
        if (nd==NULL) {
            cout<<"Error: cannot find directory '"<<fname<<"'"<<endl;
            return;
        }
        
        else if (nd->nodeData->isFolder==false) {
            cout<<"Error: '"<<fname<<"' is not a directory"<<endl;
            return;
        }
        
        //move to next directory 
        wd.push_top(nd->nodeData);

	}
}

//Print list of item in the current directory, the way you print it will be according to the passed-in option
void OS::ls(string option){
    MList* n = (wd.top()->nodeData->childList);
	if (option == "-d"){
		//Default option - print the list of items in the current directory from top to bottom.
		//use a single space as delimiter.

        n->printTtB(" ");
        
        
	}
    
	else if(option == "-sort=name"){
		//Use Insertion Sort to sort items in the current directory and print from top to bottom (alphabetically A-Za-z).
		//use a single space as delimiter.

        n->sortByNameInsertion();
        
        
	}
    
    else if(option == "-r"){
		//Reverse print the list of items in the current directory (i.e., print form bottom to top).
		//use single space as delimiter.

        n->printBtT(" ");
        

	}else if(option == "-sort=size"){
		//Sort list by size and print the list of items in the current directory from top to bottom.
		//use single space as delimiter.

        n->printTtB(" ");
        
	}
	else{
		cout<<"usage: ls [optional: -r for reverse list, -sort=size to sort list by file size, -sort=name to soft list by name]";
	}
}

//Priting path from root to your current directory.
//use slash "/" as our delimiter.
//Example output: root/cs103/usc/viterbi/
void OS::present_working_dir(){
    

    //call printttb on wd
    wd.printBtT("/");
    
    
}