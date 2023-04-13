// Computing Structures Fall 2022
// DSA 5005
// Rahul Bharadwaj

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
template <class DT>
class Node
{
protected:
    int nodeNumber;  // field to store node's number
    string nodeInfo; // field to store node's information
    DT yearCreated;  // field to store the year of the node created
    string location; // field to store the location

public:
    Node(); // default constructor

    // getters
    string getNodeInfo();
    int getNodeNumber();
    DT getYearCreated();
    string getLocation();

    // setters
    void setNodeInfo(string newInfo, DT newYearCreated, string newLoc); // V2: updated
    void setNodeNumber(int newNum);
    void setYearCreated(DT newYearCreated);
    void setLocation(string newLocation);

    void display(); // display node details

    ~Node(); // destructor
};

template <class DT>
Node<DT>::Node()
{
	nodeNumber = 0;
	nodeInfo = "";
	yearCreated = 0;            //default constructor to initialize the protected variables/fiels of Node class with basic values  
	location = "";
}

template <class DT>
DT Node<DT>::getYearCreated() {
	return yearCreated;             //returning year created
}

template <class DT>
string Node<DT>::getLocation() {
	return location;        //returning location
}

template <class DT>
void Node<DT>::setYearCreated(DT newYearCreated) {
	yearCreated = newYearCreated;           //settign yearCreated to newYearCreated
}

template <class DT>
void Node<DT>::setLocation(string newLocation) {
	location = newLocation;             //assigning newLocation to location
}
template <class DT>
string Node<DT>::getNodeInfo()
{
	return nodeInfo;            //returning nodeinfo
}

template <class DT>
int Node<DT>::getNodeNumber()
{
	return nodeNumber;          //returning nodeNumber
}

template <class DT>
void Node<DT>::setNodeInfo(string newInfo, DT newYearCreated, string newLoc)
{
	nodeInfo = newInfo;
	yearCreated = newYearCreated;               //setting nodeInfo, YearCreated, location with respective parameters
	location = newLoc;
}

template <class DT>
void Node<DT>::setNodeNumber(int newNum)
{
	nodeNumber = newNum;            //assigning newNum to nodeNumber
}

template <class DT>
void Node<DT>::display()
{
	cout << nodeNumber << ": " << nodeInfo << ", " << yearCreated << ", " << location << endl;          //displying the fields of the class Node (fields of 1 node)
}

template <class DT>
Node<DT>::~Node() {
	//cout << "Node object is deleted...." << endl;
    //Node destructer cannot have anything as there is no dynamically alloted variable or a object assosiated with it.
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store one edge's details
template <class DT>
class Edge
{
protected:
    Node<DT>* u;     // field to store source node pointer
    Node<DT>* v;     // field to store destination node pointer
    string edgeInfo; // field to store edge information
    DT yearsKnown;   // u and v - years known

public:
    Edge(); // default constructor
    // getters
    Node<DT>* getu();
    Node<DT>* getv();
    string getEdgeInfo();
    DT getYearsKnown();

    // setters
    void setu(Node<DT>* newu);
    void setv(Node<DT>* newv);
    void setEdgeInfo(string newInfo, DT newYearsKnown); // V2: updated
    void setYearsKnown(DT newYear);                     // V2: updated

    void display(); // display edge details

    ~Edge(); // destructor
};

template <class DT>
Edge<DT>::Edge()
{
	u = NULL;                           //default constructor to initialize the protected variables/fiels of Edge class with basic values
	v = NULL;
	edgeInfo = "";
    yearsKnown = 0;
}

template <class DT>
DT Edge<DT>::getYearsKnown() {
	return yearsKnown;              //returning yearsKnown
}

template <class DT>
void Edge<DT>::setYearsKnown(DT newYear) {
	yearsKnown = newYear;           //assigning newYear to yearsKnown
}

template <class DT>
Node<DT>* Edge<DT>::getu()
{
	return u;           //returning u
}

template <class DT>
Node<DT>* Edge<DT>::getv()
{
	return v;           //returning v
}

template <class DT>
string Edge<DT>::getEdgeInfo()
{
	return edgeInfo;        //returnign edgeInfo
}

template <class DT>
void Edge<DT>::setu(Node<DT>* newu)
{
	u = newu;           //assigning newu to u
}

template <class DT>
void Edge<DT>::setv(Node<DT>* newv)
{
	v = newv;           //assigning newv to v
}

template <class DT>
void Edge<DT>::setEdgeInfo(string newInfo, DT newYearsKnown)
{
	edgeInfo = newInfo;         //assigning newInfo to edgeInfo
}

template <class DT>
void Edge<DT>::display()
{
	if ((u != NULL) && (v != NULL))
		cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << edgeInfo << ", " << yearsKnown << endl;  //displaying the fields of Edge class (fields of one Edge)
}

template <class DT>
Edge<DT>::~Edge() {
    //Edge Destructer cannot have anything as there is no dynamically alloted variable or object. 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph
template <class DT>
class GraphDB
{
	friend ostream& operator << (ostream& s, GraphDB<DT> G);
    // TODO: ostream operator for displaying myNodes and myEdges
protected:
    Node<DT>* myNodes; // array of nodes
    Edge<DT>* myEdges; // array of edges
    int numNodes;      // number of nodes
    int numEdges;      // number of edges
    int maxEdges;      // store the max number of edges (array size)

public:
    GraphDB(int nNodes, int nEdges); // non-default constructor
    // setters
    void setNode(Node<DT>& newNode);
    void setEdge(Edge<DT>& newEdge);
    void setNodeInfo(int u, string newInfo);
    void setEdgeInfo(int u, int v, string newInfo);

    // getters
    Node<DT>* getNode(int nodeNum);
    string getNodeInfo(int nodeNum);
    Edge<DT>* getEdgeInfo(int u, int v);

    // operations
    bool isAnEdge(int u, int v);     // is this edge existent
    void addEdge(Edge<DT>& newEdge); // add an edge
    void deleteEdge(int u, int v);   // delete the edge
    void display();                  // display the contents of the two arrays
    int* findNeighbours(int u);      // returns an integer array of neighbours' nodeNum

    ~GraphDB(); // destructor
};

template <class DT>
GraphDB<DT>::GraphDB(int nNodes, int nEdges)
{
	numNodes = nNodes;          //assigning numNodes with nNodes
	maxEdges = nEdges;          //assigning maxEdges with nEdges
	myNodes = new Node<DT>[numNodes]; // allocating memory for the myNodes array
	myEdges = new Edge<DT>[maxEdges]; // allocating memory for the myEdges array
	numEdges = 0; // to keep count of the number of edges currently present
}

// display for the nodes and edges of graphDB
template <class DT>
void GraphDB<DT>::display()
{
	// cout << "numNodes: " << numNodes << endl;
	// cout << "maxEdges: " << maxEdges << endl;
	// cout << "numEdges: " << numEdges << endl;

	cout << "Displaying myNodes: " << endl;
	for (int i = 0; i < numNodes; i++)
		myNodes[i].display(); // calling the Node class display

	cout << "Displaying myEdges: " << endl;
	for (int i = 0; i < numEdges; i++)
		myEdges[i].display(); // calling the Edge class display

	return;
}

// setter for node object
template <class DT>
void GraphDB<DT>::setNode(Node<DT>& newNode) {
    //seeting myNodes[newNode number] fields by funnelling data from there respective getters from Node class
	myNodes[newNode.getNodeNumber()].setNodeNumber(newNode.getNodeNumber());
	myNodes[newNode.getNodeNumber()].setNodeInfo(newNode.getNodeInfo(), newNode.getYearCreated(), newNode.getLocation());
	myNodes[newNode.getNodeNumber()].setLocation(newNode.getLocation());
	myNodes[newNode.getNodeNumber()].setYearCreated(newNode.getYearCreated());
	// myNodes[newNode.getNodeNumber()] = newNode;

}

// getter for a specific node from myNodes
template <class DT>
Node<DT>* GraphDB<DT>::getNode(int nodeNum)
{
	return &myNodes[nodeNum];           //returning address of myNodes[nodeNum]
}

template <class DT>
void GraphDB<DT>::setEdge(Edge<DT>& newEdge)
{
	numEdges++;
	// cout << "numEdges: " << numEdges << endl;
	if (numEdges >= maxEdges) // to allocate new memory
	{
		Edge<int>* tempArrayEdges = new Edge<int>[maxEdges + (maxEdges / 2)]; // create a new temp array

		// cout << "--- Increasing the size of array by " << (maxEdges/2); 
		// cout << " new maxEdges: " << maxEdges + (maxEdges/2) << endl;

		for (int i = 0; i < maxEdges; i++) // copy old values - deep copy
			tempArrayEdges[i] = myEdges[i];

		delete[] myEdges; // delete the pointer to the old values

		myEdges = tempArrayEdges; // re point the pointer to the new memory location

		maxEdges = maxEdges + (maxEdges / 2); // update the value of maxEdges
	}

	// copying the newEdge to the array
	myEdges[numEdges - 1].setu((newEdge.getu()));
	myEdges[numEdges - 1].setv((newEdge.getv()));
	myEdges[numEdges - 1].setEdgeInfo(newEdge.getEdgeInfo(), newEdge.getYearsKnown());
	myEdges[numEdges - 1].setYearsKnown(newEdge.getYearsKnown());

}


template <class DT>
void GraphDB<DT>::deleteEdge(int u, int v)
{
	if (isAnEdge(u, v)) // check if the edge exists
	{
		for (int i = 0; i < numEdges; i++)
		{
            // loop through and find the edge for both u = u, v = v and u = v, v = u  
			if ((myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) || (myEdges[i].getu()->getNodeNumber() == v && myEdges[i].getu()->getNodeNumber() == u))
			{
				// setting the values to NULL (edge to be deleted)
				Node<int>* t = NULL; // temp dummy node
				myEdges[i].setu(t);
				myEdges[i].setv(t);
				myEdges[i].setEdgeInfo("", 0);
				myEdges[i].setYearsKnown(0);

				for (int j = i; j < numEdges - 1; j++) // left shift all the edges
				{
					myEdges[j].setu(myEdges[j + 1].getu());
					myEdges[j].setv(myEdges[j + 1].getv());
					myEdges[j].setEdgeInfo(myEdges[j + 1].getEdgeInfo(), myEdges[j + 1].getYearsKnown());
					myEdges[j].setYearsKnown(myEdges[j + 1].getYearsKnown());
				}
				numEdges = numEdges - 1; // decrement the numEdges
                //cout << numEdges << endl;

                if (numEdges <= (maxEdges/2)) // to allocate new memory
                {
                    Edge<int>* tempArrayEdges = new Edge<int>[maxEdges - (maxEdges / 2)]; // create a new temp array, to decrease the size of the array to half.

                    for (int i = 0; i < numEdges; i++) // copy old values - deep copy
                        tempArrayEdges[i] = myEdges[i];

                    delete[] myEdges; // delete the pointer to the old values

                    myEdges = tempArrayEdges; // re point the pointer to the new memory location

                    maxEdges = maxEdges - (maxEdges / 2); // update the value of maxEdges
                    //cout << "max size: " << maxEdges << "numEdges Size: " << numEdges << endl;
                }
				break;
			}
		}
	}
	else
	{
		cout << "Edge does not exist to be deleted" << endl; // this could be an exception
	}
}

// set the information of node u
template <class DT>
void GraphDB<DT>::setNodeInfo(int u, string newInfo)
{
	for (int i = 0; i < numNodes; i++) // loop through the myNodes array
	{
		if (myNodes[i].getNodeNumber() == u) // check nodeNum
		{
			myNodes[i].setNodeInfo(newInfo);            //setting node info with newInfo
		}
	}
}


// set the information of edge u-v
template <class DT>
void GraphDB<DT>::setEdgeInfo(int u, int v, string newInfo)
{
	for (int i = 0; i < numEdges; i++) // loop through the myEdges array
	{
		if ((myEdges[i].getu()->getNodeNumber() == u &&
			myEdges[i].getv()->getNodeNumber() == v) || (myEdges[i].getu()->getNodeNumber() == v && myEdges[i].getu()->getNodeNumber() == u)) // check nodeNums //condition is same as deleteEdge and isEdge methods
		{
			myEdges[i].setEdgeInfo(newInfo, 0);         //setting Node info
		}
	}
}

// check the existence of an edge
template <class DT>
bool GraphDB<DT>::isAnEdge(int u, int v)
{
	for (int i = 0; i < numEdges; i++) // loop through the myEdges array
	{
        if ((myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v) || (myEdges[i].getu()->getNodeNumber() == v && myEdges[i].getu()->getNodeNumber() == u)) // check nodeNums //same as deleteEdge method
		{
			return true; // return true if found
		}
	}
	return false; // else false
}

template <class DT>
int* GraphDB<DT>::findNeighbours(int u) {
	int j = -1;             //counter variable to keep track of neighboring nodes
	int a[numNodes];
	for (int i = 0; i < numEdges;i++) {
		if (myEdges[i].getu()->getNodeNumber() == u) {          //checking if u is the first node in the edge
            j++;
            a[j] = myEdges[i].getv()->getNodeNumber();          //recording the second node(Neighboring node)
			
		}
		else if (myEdges[i].getv()->getNodeNumber() == u) {      //checking if u is the second node in the edge.
			//cout << "j is " << j << endl;
            j++;
            a[j] = myEdges[i].getu()->getNodeNumber();      //recording the first node(Neighboring node)
			
		}
		else {
			continue;
		}
	}
    //cout << "j =" << j << endl;
    //displaying the array of neighboring nodes
    if (j >= 0) {
        cout << "Neighbours of " << u << ": ";
        for (int i = 0; i <= j;i++) {
            cout << a[i] << " ";
        }
        cout << endl << endl;
    }
    else {
        cout << "No Neighbours exist" << endl << endl;              //message to display if there exists no neigbours
    }
    return a;               // a is variable of an array which stores the address of first element of the array. 
}

template <class DT>
GraphDB<DT>::~GraphDB() {
	delete[] myEdges;
	delete[] myNodes;                     //destructer to delete all the dynamically alloted arrays
    //cout << "Destructed....." << endl << endl;
}

template <class DT>
void GraphDB<DT>::addEdge(Edge<DT>& newEdge)            //addEdge mehod which has same functionality of setEdge method
{
    numEdges++;
    // cout << "numEdges: " << numEdges << endl;
    if (numEdges >= maxEdges) // to allocate new memory
    {
        Edge<int>* tempArrayEdges = new Edge<int>[maxEdges + (maxEdges / 2)]; // create a new temp array

        // cout << "--- Increasing the size of array by " << (maxEdges/2); 
        // cout << " new maxEdges: " << maxEdges + (maxEdges/2) << endl;

        for (int i = 0; i < maxEdges; i++) // copy old values - deep copy
            tempArrayEdges[i] = myEdges[i];

        delete[] myEdges; // delete the pointer to the old values

        myEdges = tempArrayEdges; // re point the pointer to the new memory location

        maxEdges = maxEdges + (maxEdges / 2); // update the value of maxEdges
    }

    // copying the newEdge to the array
    myEdges[numEdges - 1].setu((newEdge.getu()));
    myEdges[numEdges - 1].setv((newEdge.getv()));
    myEdges[numEdges - 1].setEdgeInfo(newEdge.getEdgeInfo(), newEdge.getYearsKnown());
    myEdges[numEdges - 1].setYearsKnown(newEdge.getYearsKnown());

}

template <class DT>
string GraphDB<DT>::getNodeInfo(int nodeNum) {
    return myNodes[nodeNum].getNodeInfo();                                         //returning nodeinfo of myNodes[nodeNum]
}

template <class DT>
Edge<DT>* GraphDB<DT>::getEdgeInfo(int u, int v) {
    for (int i = 0; i <= numEdges; i++) {                                         //To traverse through the myEdges array
        if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v || myEdges[i].getu().getNodeNumber() == v && myEdges[i].getv().getNodeNumber() == u) { //same condition as in deleteEdge and isEdge method to find whether the edge exists.
            return &myEdges[i];         //returns the myEdges[i] adress. NOTE: Even though the name says getEdgeInfo with Edge* data type: we can't send the address of EdgeInfo of myEdges[i] 
        }
        else {
            continue;
        }
    }
}

//overloading << operator to call display method of graphDB class
ostream& operator << (ostream& s, GraphDB<int>* G) {
	G->display();                       //calling display function of GraphDB 
	//s << "Displaying myNodes:" << endl;
	return s;
}

class ExceptionNoNode {};                   //ExceptionNoNode class to call exceptions if the edge is being added to non existent node.

//function to display the int array recieved from findNeighbor method
//void displayarray(int* Toarray) {
//    /*sizeof(Toarray) gives size in bytes, ex: for elements{1,2,3} sizeof returns(int size in bytes)4 * 3(no of elements) = 12, 
//    which intern divided by sizeof(first element) which is nothing but 4(int byte size) gives the actual size i,e 12/4 = 3 in above example */
//    cout << "inside to array" << endl;
//    for (int i = 0; i < sizeof(Toarray) / sizeof(Toarray[0]); i++) {
//        cout << "for loop of to array" << endl;
//        cout << Toarray[i] << " ";              //displaying the elements.
//    }
//    cout << endl << endl;
//}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{

    // you can start with the same main function from project 1
    // you can start with the same main function from project 1
    int numNodes; // temp variable to store numNodes from input
    int maxEdges; // temp variable to store numEdges from input
    int nodeNumber; //temp variable to store number of a particular node
    string nodeString;  //temp variable to store sting of a node
    string nodelocation; //temp variable to store location of the node
    int nodeYear;   //temp variable to store nodeYear

    int nodeNeighbor;       //temp variable for node Neighbor

    int U, V;       //variable to store the Nodes of the edges
    string newedgeInfo;     //temp variable to store edge info
    int newYearsknown;      // temp variable to store Years known

    GraphDB<int>* masterGraph;          //creating masterGraph pointer object of GraphDB class



    cin >> numNodes >> maxEdges;        //reading numNodes and maxEdges.

    masterGraph = new GraphDB<int>(numNodes, maxEdges);         //dynamically initializing the masterGraph object by calling non default constructer of GraphDB class

    cout << "numNodes: " << numNodes << endl;
    cout << "maxEdges: " << maxEdges << endl << endl;

    Node<int> tempNode;                 //statically created tempNode which automatically gets deleted once the job is done
    for (int i = 0; i < numNodes; i++) {
        cin >> nodeNumber >> nodeString >> nodeYear >> nodelocation;
        tempNode.setNodeNumber(nodeNumber);                         //Calling setNodenumber using tempNode and passing nodeNumber as parameter
        tempNode.setNodeInfo(nodeString, nodeYear, nodelocation);   //Calling setNodeInfo and passing nodeString, nodeYear, Nnodelocation as parameters
        masterGraph->setNode(tempNode);
        //tempNode.display();             //Extra line just to check if it's working
    }

    char command;
    Edge<int> tempEdge;             //statically created Edge objects which gets deleted automatically

    //while (!cin.eof())
    while (cin >> command)
    {
        //cin >> command;
        //cout << " inside while loop" << endl;
        switch (command)
        {
            //cout << "inside switch" << endl;
        case 'I': {
            //cout << "inside I" << endl;
            cin >> U >> V >> newedgeInfo >> newYearsknown;

            try {
                cout << "Inserting " << U << " " << V << ": " << newedgeInfo << ", " << newYearsknown << endl;
                bool truthU = false;                //Boolean variable for U exists and initiated to false at start
                bool truthV = false;                //Boolean variable for V exists and initiated to false at start
                for (int i = 0; i < numNodes; i++) {                    //looping through the Nodes
                    if (masterGraph->getNode(i)->getNodeNumber() == U) { //checking if u of an edge is equal to given u
                        truthU = true;              //if so then set truthU to true
                    }
                    else if (masterGraph->getNode(i)->getNodeNumber() == V)             //checking if v of an edge is equal to given u
                    {
                        truthV = true;              //if so setting truthV to true
                    }
                    else
                        continue;
                }

                if (truthU == false || truthV == false) throw ExceptionNoNode();            //if either for the set values are false then throw an exception
                //cout << "Inserting " << U << " " << V << ": " << newedgeInfo << ", " << newYearsknown << endl;
                tempEdge.setu(masterGraph->getNode(U));                     //if both are true then set the values of the Edge accordingly
                tempEdge.setv(masterGraph->getNode(V));
                tempEdge.setEdgeInfo(newedgeInfo, newYearsknown);
                tempEdge.setYearsKnown(newYearsknown);
                //cout << "after tempEdge" << endl;

                masterGraph->setEdge(tempEdge);     //setting tempEdge to my Edges array.
                //break;
            }
            catch (ExceptionNoNode NoNode) {
                cout << "Node not a part of the graph";             //catching the exception and displying the message
                cout << endl;
            }

            cout << endl;
            break;
            //cout << "Inserting " << U << " " << V << ": " << newedgeInfo << ", " << newYearsknown << endl << endl;
            //tempEdge.setu(masterGraph->getNode(U));
            //tempEdge.setv(masterGraph->getNode(V));
            //tempEdge.setEdgeInfo(newedgeInfo, newYearsknown);

            //masterGraph->setEdge(tempEdge);     //setting tempEdge to my Edges array.
            //break;
        }
        case 'R': {
            cin >> U >> V; // read in the edge details
            cout << "Removing the item " << U << " " << V << endl;
            masterGraph->deleteEdge(U, V); // delete the edge in myEdges array
            cout << endl;

            break;
        }

        case 'D': {
            //cout << "inside D" << endl;
            //masterGraph->display(); // call display of graphDB
            //cout << endl;
            cout << masterGraph;            //calling operator overloader for masterGraph
            cout << endl;
            break;
        }
        case 'E': {
            cin >> U >> V; // read in the edge details

            bool flag = masterGraph->isAnEdge(U, V);            //checking if the edge exists between U and V
            if (flag == true)
                cout << "Edge exists between " << masterGraph->getNode(U)->getNodeInfo() << " and " << masterGraph->getNode(V)->getNodeInfo() << endl << endl;
            // cout << "true" << endl;
            else
                cout << "No edge exists between " << masterGraph->getNode(U)->getNodeInfo() << " and " << masterGraph->getNode(V)->getNodeInfo() << endl << endl;
            break;
        }
        case 'N': {
             cin >> nodeNeighbor;                          //taking in nodeNumber
             //cout << "nodeNeighbor is: " << nodeNeighbor << endl;
             //cout << "Neighbours of " << nodeNeighbor << ": ";
             //displayarray(masterGraph->findNeighbours(nodeNeighbor));       //calling findNeighbours method inside displyarray function
             masterGraph->findNeighbours(nodeNeighbor);                       //calling findNeighbours method of class GraphDB
             break;
                ////    /*cout << "Neighbours of " << nodeNumber << ": ";
                ////    for (int i = 0; i <= j;i++) {
                ////        cout << a[i] << " ";
                ////    }
                ////    cout << endl << endl;*/
        }

        default:
            break;
        }
    }

    delete masterGraph;         //calling destructer for masterGraph, ALL OTHER objects are staticlly created and hence destructer need not to be called
    
    return 0;
}