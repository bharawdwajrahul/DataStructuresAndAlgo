// Computing Structures Fall 2022
// Project 5

#include <iostream>
#include <stack>
#include <vector>

using namespace std;


//stack<int> _freeLocations;				//global stack to keep track of EMPTY nodes

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
protected:
	// Instance Variables
	DT* _info;
	int _left;
	int _right;

public:
	// Constructors and Destructor
	ArrayBTNode();
	ArrayBTNode(DT& info);
	~ArrayBTNode();

	// getter Methods
	DT* getinfo();
	int getleft();
	int getright();

	// setter Methods
	void setInfo(DT& info);
	void setInfoNull(); // Sets _info to Null
	void setLeft(int left);
	void setRight(int right);

	// Display Method
	// Outputs data in _info, _left, _right
	void display();

	// Overloaded Comparison Operators
	// Used for comparing _info field with other ArrayBTNodes
	bool operator<(const ArrayBTNode<DT>& x);
	bool operator>(const ArrayBTNode<DT>& x);
	bool operator==(const ArrayBTNode<DT>& x);
	bool operator>=(const ArrayBTNode<DT>& x);
	bool operator<=(const ArrayBTNode<DT>& x);
	bool operator!=(const ArrayBTNode<DT>& x);

	// TODO: Overloaded Ostream Operator - Uses display method to output ArrayBTNode contents
};

template <class DT>
ArrayBTNode<DT>::ArrayBTNode() {
	*_info = NULL;
	_left = -1;									//setting all the data fiels to their default values
	_right = -1;
}

template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT& info) {
	_info = info;
	_left = -1;									//setting all the data fiels to their default values except info
	_right = -1;
}

template <class DT>
void ArrayBTNode<DT>::setInfo(DT &info) {
	_info = &info;				//srtting pointer _info to address of info
}

template <class DT>
void ArrayBTNode<DT>::setInfoNull() {
	_info = NULL;				//srtting pointer _info to address of info
}

template <class DT>
void ArrayBTNode<DT>::setLeft(int left) {
	_left = left;					//setting _left to left(index of left child)
}

template <class DT>
void ArrayBTNode<DT>::setRight(int right) {
	_right = right;					//setting _right to right(index of right child)
}

template <class DT>
DT* ArrayBTNode<DT>::getinfo() {
	return _info;					//returning _info 
}

template <class DT>
int ArrayBTNode<DT>::getright() {
	return _right;					//returning _right node index
}

template <class DT>
int ArrayBTNode<DT>::getleft() {
	return _left;					//returning _left node index
}

template <class DT>
bool ArrayBTNode<DT>::operator < (const ArrayBTNode<DT>& x) {
	return ((*_info) < *(x.getinfo()));			//overloading < operator
}

template <class DT>
bool ArrayBTNode<DT>::operator > (const ArrayBTNode<DT>& x) {
	return ((*_info) > *(x.getInfo()));			//overloading > operator
}

template <class DT>
bool ArrayBTNode<DT>::operator == (const ArrayBTNode<DT>& x) {
	return ((*_info) == *(x.getinfo()));		//overloading == operator
}

template <class DT>
bool ArrayBTNode<DT>::operator >= (const ArrayBTNode<DT>& x) {
	return ((*_info) >= *(x.getinfo()));		//overloading >= operator
}

template <class DT>
bool ArrayBTNode<DT>::operator <= (const ArrayBTNode<DT>& x) {
	return ((*_info) <= *(x.getinfo()));		//overloading <= operator
}

template <class DT>
bool ArrayBTNode<DT>::operator != (const ArrayBTNode<DT>& x) {
	return ((*_info) != *(x.getinfo()));		//overloading != operator
}

template <class DT>
void ArrayBTNode<DT>::display() {
	cout << "Info: " << *_info;
	cout << "left: " << _left;
	cout << "right: " << _right;
}

template <class DT>
ArrayBTNode<DT>::~ArrayBTNode() {
	//There is nothing to be destructed as there are no dynamically alloted pointers 
}

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT> > _tree;    // Vector of ArrayBTNodes used to create a tree
	int _rootIndex;            // Index of the root node in _tree
	int _numNodes;             // Number of nodes in the tree
	int _size;                 // Maximum size of the _tree array
	stack<int> _freeLocations; // Stack containing indexes of freeLocations in the _tree array

public:
// Constructors and Destructor
ArrayBST();
ArrayBST(int k); // initialize the vector with NULL nodes and fill the stack
~ArrayBST();

// Accessor Methods
bool isEmpty() const;
int Height();
int HeightofSubtree(int pos);	//helper method used in Height to calculate height of each subtree
int Size();
int rootIndex();
int maxSize();

// Mutator Methods
void setData(int index, DT& value);
void setLeft(int index, int value);
void setRight(int index, int value);

// Display methods and traversals
void display(ostream& os);
void displayPreOrder(ostream& os) ;
void PreOrderdisplaySubTree(int pos);		//helper method to dispay SubTree, used in  DisplayPreOrder method 
void displayInOrder(ostream& os);
void InOrderdisplaySubTree(int pos);		//helper method to display SubTree, used in displayInOrder method
void printRaw(); // Display the array and all of its contents

// BST Specific Methods
void insert(DT& object);
void _insert(DT& object, int pos);
bool find(DT& object);
bool _find(DT& object, int pos);			//helper method used in find method
int findIndex(DT& object);
int _findIndex(DT& object, int pos);		//helper method used in findIndex
//void remove(DT& object); // extra credit

// TODO: Overridden ostream operator for ArrayBST - this will call the pre order and in order methods
//friend ostream& operator << (ostream& s, ArrayBST<int> Tree);
friend ostream& operator << (ostream& s, ArrayBST<DT> Tree);
};



//ostream& operator << (ostream& s, GraphDB<int>* G) {
//	G->display();                       //calling display function of GraphDB 
//	//s << "Displaying myNodes:" << endl;
//	return s;
//}

//template <class DT>
ostream& operator << (ostream& s, ArrayBST<int> Tree) {
	Tree.displayPreOrder(s);			//calling displayPreOrder method
	cout << endl;
	Tree.displayInOrder(s);				//calling displayInOrder method
	//return s;
}

template <class DT>
ArrayBST<DT>::ArrayBST() {
	_tree = NULL;
	_rootIndex = NULL;
	_size = NULL;							//setting data field to their default value 
	_numNodes = NULL;
	_freeLocations = NULL;
}

template <class DT>
ArrayBST<DT>::ArrayBST(int k) {
	_rootIndex = NULL;
	ArrayBTNode<int> TempNode = ArrayBTNode<int>();		//initiating tempNode with default constructor which sets *_info to NULL and _lft and _right to -1

	_tree = vector<ArrayBTNode<DT> >(k, TempNode);						//initializing _tree vector with size k, and TempNode in all the positions

	_size = k;

	for (int i = 0; i < k; i++) {
		_freeLocations.push(i);											//pushing all the free index to stack
		//cout << i << endl;
	}

	//cout << "size: " << _tree.size() << endl;
}

template <class DT>
int ArrayBST<DT>::HeightofSubtree(int pos) {
	int leftheight;
	int rightheight;

	if (_tree[pos].getleft() != -1) {				//check if it has a left child
		leftheight++;								//leftheight
		HeightofLeftSubtree(_tree[pos].getleft());	//call HeightofLeftSubtree recurisively
	}

	if (_tree[pos].getright() != -1) {				//then if it has a right child
		rightheight++;								//increment rightheight
		PreOrderdisplaySubTree(_tree[pos].getright());	//if so then call the HeightofLeftSubtree recursively
	}

	return max(leftheight, rightheight);			//return the max between both the heights
}

template <class DT>
int ArrayBST<DT>::Height() {
	int leftheight;
	int rightheight;

	if (isEmpty()) cout << "Height is 0" << endl; return 0;

	leftheight = HeightofSubtree(_tree[_rootIndex].getleft());
	rightheight = HeightofSubtree(_tree[_rootIndex].getright());

	return max(leftheight, rightheight) + 1;				//returns the max height between the two subtree + 1(for root)
}

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value) {
	_tree[index].setleft(value);				//setting left value for a node in _tree at location index
}

template <class DT>
void ArrayBST<DT>::setRight(int index, int value) {
	_tree[index].setright(value);				//setting right value for a node in _tree at location index
}

template <class DT>
void ArrayBST<DT>::setData(int index, DT& value) {
	_tree[index].setinfo(value);				// setting value for a node in _tree at location index
}


template <class DT>
int ArrayBST<DT>::Size() {
	int size;

	//return _size;
	size = (_size - _freeLocations.size());				//gives the number of Nodes that are filled
	return size;
}

template <class DT>
int ArrayBST<DT>::maxSize() {
	return _size;
}

template <class DT>
int ArrayBST<DT>::rootIndex() {
	return _rootIndex;							//returning _rootindex
}

template <class DT>
bool ArrayBST<DT>::isEmpty() const {
	//if ((_tree[_rootIndex].getinfo()) == NULL) return true;
	if (_rootIndex == NULL) return true;		//if _rootindex is set to null then return true
	else return false;
}

class EmptyTree {};

template <class DT>
bool ArrayBST<DT>::_find(DT& object, int pos) {
	if (*(_tree[pos].getinfo()) == object) {				//if object is found at the position 
		cout << "Number found at index " << pos << "." << endl << endl; //then print the statement
		return true;										//and return true
	} 

	if (*(_tree[pos].getinfo()) < object) {					//if object is greater then current node
		if ((_tree[pos]).getright() != -1) {				//check if it has a right child
			return _find(object, _tree[pos].getright());	//if so call _find recursively with right child
		}
		return false;										//if not found return false
	}
	else {													//if object is less then current node
		if ((_tree[pos]).getleft() != -1) {					//and it has left child
			return _find(object, _tree[pos].getleft());		//then call find recursively
		}
		return false;										//else return false
	}
}

template <class DT>
bool ArrayBST<DT>::find(DT& object) {
	try {
		if (isEmpty()) throw EmptyTree();					//check if the tree is empty if so throw EmptyTree error
		return _find(object, rootIndex());					//else call _find method with object to be found and rootindex
	}catch (EmptyTree notTree){ cout << "Number not found." << endl << endl; }	//catch Empty Tree error and display the message

}

template <class DT>
int ArrayBST<DT>::findIndex(DT& object) {
	try {
		if (isEmpty()) throw EmptyTree();					//check if the tree is empty if so throw EmptyTree error
		return _find(object, rootIndex());					//else call _find method with object to be found and rootindex
	}
	catch (EmptyTree notTree) { cout << "Number not found." << endl << endl; }	//catch Empty Tree error and display the message
}

template <class DT>
int ArrayBST<DT>::_findIndex(DT& object, int pos) {			//Same as _find function, modified to return location
	int foundloc;

	if (*(_tree[pos].getinfo()) == object) {				//if object is found at the position 
		//cout << "Number found at index " << pos << "." << endl << endl; //then print the statement
		foundloc = pos;
		return foundloc;										//and return foundloc
	}

	if (*(_tree[pos].getinfo()) < object) {					//if object is greater then current node
		if ((_tree[pos]).getright() != -1) {				//check if it has a right child
			return _findIndex(object, _tree[pos].getright());	//if so call _find recursively with right child
		}
		return -1;										//if not found return -1
	}
	else {													//if object is less then current node
		if ((_tree[pos]).getleft() != -1) {					//and it has left child
			return _findIndex(object, _tree[pos].getleft());		//then call find recursively
		}
		return -1;										//else return -1
	}
}




class ElementAlreadyExists {};

template <class DT>
void ArrayBST<DT>::_insert(DT& object, int pos) {
	if (*(_tree[pos].getinfo()) == object) {
		//_tree[pos].setInfo(object);					//rewritting the info value with the same value
		return;
	}

	else if (*(_tree[pos].getinfo()) < object) {		//if object is greater than the current node
		if (_tree[pos].getright() != -1){				//and it has right child
			_insert(object, _tree[pos].getright());		//call _insert recursively
		}
		else {
			int temp;									//if not add the node as the right child

			temp = _freeLocations.top();
			_freeLocations.pop();

			_tree[temp].setInfo(object);
			_tree[pos].setRight(temp);
		}
	}

	else {
		if ((_tree[pos]).getleft() != -1) {			//if object is less than current node and it does have a left child
			_insert(object, _tree[pos].getleft());	//then call _insert recursively
		}
		else {
			int temp;								//if not add the node as the left child

			temp = _freeLocations.top();
			_freeLocations.pop();

			_tree[temp].setInfo(object);
			_tree[pos].setLeft(temp);
		}
	}

}

template <class DT>
void ArrayBST<DT>::insert(DT& object) {
	if (isEmpty()) {					//check if the tree is empty
		//cout << "inside 1st Insert" << endl;
		_rootIndex = _freeLocations.top();		//then insert object as root node
		_freeLocations.pop();

		_tree[_rootIndex].setInfo(object);

		cout << endl;

	}
	else if (_freeLocations.empty()) cout << "Cannot insert data, BST Full." << endl << endl; //else check the Empty stack and if it is empty then dispay the satement
	else {
		//if (find(object)) return;
		_insert(object, rootIndex());															//else call _insert method
		cout << endl;
	} 
	
	
}


template <class DT>
void ArrayBST<DT>::printRaw() {
	for (int i = 0; i < _size; i++) {					//looping through and printing the row
		if (*(_tree[i].getinfo()) != NULL) {
			cout << "Index " << i << ": ";
			cout << "Info: " << *(_tree[i].getinfo()) << ", ";
			cout << "Left: " << _tree[i].getleft() << ", ";
			cout << "Right: " << _tree[i].getright() << endl;
		}
		else continue;
	}
	cout << "Free Indexes: " << endl;
	if (_freeLocations.empty()) cout << "None";		//checking if stack is empty

	else {
		stack<int> i = _freeLocations;				//if not print the stack
		while (!i.empty()) {
			cout << i.top();
			i.pop();

			if (!i.empty()) {
				cout << ", ";
			}
		}
		//for (stack<int> i = _freeLocations; !i.empty(); i.pop()) {
		//	cout << i.top() << ", ";
		//}
	}

	cout << endl << endl;

}

template <class DT>
void ArrayBST<DT>::display(ostream& os) {
	//same as print raw method
	for (int i = 0; i < _size; i++) {
		if (*(_tree[i].getinfo()) != NULL) {
			os << "Index " << i << ": ";
			os << "Info: " << *(_tree[i].getinfo()) << ", ";
			os << "Left: " << _tree[i].getleft() << ", ";
			os << "Right: " << _tree[i].getright() << endl;
		}
		else continue;
	}
	cout << "Free Indexes: " << endl;
	if (_freeLocations.empty()) cout << "None";

	else {
		stack<int> i = _freeLocations;
		while (!i.empty()) {
			cout << i.top();
			i.pop();

			if (!i.empty()) {
				cout << ", ";
			}
		}
		//for (stack<int> i = _freeLocations; !i.empty(); i.pop()) {
		//	cout << i.top() << ", ";
		//}
	}

	cout << endl << endl;
}

//template <class DT>
//void ArrayBST<DT>::PreOrderdisplayRightSubTree(int pos) {
//	cout << *(_tree[pos].getinfo());
//
//}


template <class DT>
void ArrayBST<DT>::PreOrderdisplaySubTree(int pos) {
	cout << *(_tree[pos].getinfo()) << " ";			//print the current node

	if (_tree[pos].getleft() != -1) {				//check if it has a left child
		PreOrderdisplaySubTree(_tree[pos].getleft());	//call PreOrderdisplaySubTree recurisively
	}
	
	if (_tree[pos].getright() != -1) {				//then if it has a right child
			PreOrderdisplaySubTree(_tree[pos].getright());	//if so then call the PreOrderdisplaySubTree recursively
	}
	else return;
	
}

template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream& os)  {
	try {
		if (isEmpty()) throw EmptyTree();		//check if the tree is empty then throw a exception

		else {
			cout << "Pre Order Traversal: " << endl;	
			//PreOrderdisplaySubTree(rootIndex());
			cout << *(_tree[_rootIndex].getinfo()) << " ";		//if not then display the root
			if (_tree[_rootIndex].getleft() != -1) {			//and check if the root has left child
				PreOrderdisplaySubTree(_tree[_rootIndex].getleft());		//if so call PreOrderdisplaySubTree method with left child
			}
			if (_tree[_rootIndex].getright() != -1) {				//then check if the root has a right node
				PreOrderdisplaySubTree(_tree[_rootIndex].getright());	//if so then call PreOrderdisplaySubTree method with right child
			}
			else {
				cout << endl;
				return;
			}

		}
	}
	catch (EmptyTree NoTree) {}

}

template <class DT>
void ArrayBST<DT>::InOrderdisplaySubTree(int pos) {
	if (_tree[pos].getleft() != -1) {			//same as PreOrderdisplaySubTree just the pattern is different to print Inorder
		InOrderdisplaySubTree(_tree[pos].getleft());
	}

	cout << *(_tree[pos].getinfo()) << " ";
	

	if (_tree[pos].getright() != -1) {
		InOrderdisplaySubTree(_tree[pos].getright());
	}
	
	else return;

}

template <class DT>
void ArrayBST<DT>::displayInOrder(ostream& os) {			//same logic as preorder just the pattern is different to print in INorder 
	try {
		if (isEmpty()) throw EmptyTree();

		else {
			cout << "In Order Traversal: " << endl;

			if (_tree[_rootIndex].getleft() != -1) {
				InOrderdisplaySubTree(_tree[_rootIndex].getleft());
			}

			cout << *(_tree[_rootIndex].getinfo()) << " ";

			if (_tree[_rootIndex].getright() != -1) {
				InOrderdisplaySubTree(_tree[_rootIndex].getright());
			}

			else return;

		}
	}catch(EmptyTree noTREE){}

}


template <class DT>
ArrayBST<DT>::~ArrayBST() {
	//there is nothing to be destructed as there is no dynamically created variable
}

////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	cin >> inputSize;				//reading input size

	cout << "Number of maximum nodes: " << inputSize << endl << endl;	//displaying input size

	//cout << "before initialization" << endl;
	// Create a BST of the size inputSize
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);	

	//cout << "after initialization" << endl;
	// TODO: input loop for commands

	char command;
	//int number;

	while (cin >> command) {
		switch (command)
		{
		case 'I': {
			int *number = new int;
			cin >> *number;
			cout << "Inserting " << *number << endl;
			myBST.insert(*number);						//calling insert method with value to be inserted
			//cout << "Hello after I" << endl;
			break;
		}


		case 'A': {
			cout << "Raw Data:" << endl;
			myBST.printRaw();			//calling printRaw method
			//cout << "after print" << endl;
			break;
		}


		case 'F': {
			int NumberToBeFound;
			cin >> NumberToBeFound;
			cout << "Finding " << NumberToBeFound << endl;

			if (myBST.find(NumberToBeFound)) {		//if the the element is found 
				break;								//then break
			}
			else cout << "Number not found." << endl << endl; break;	//else display the message and break out
			
		}


		case'O': {
			cout << "Information in Tree: " << endl;
			cout << myBST;						//calling overloaded << operator
			cout << endl << endl;
			break;
		}


		case'R': {
			//please find this in project5_extra
			break;
		}


		default:
			break;
		}
	}

	//cout << myBST.rootIndex() << endl;

	return 0;
}