// Project 4
// Fall 2022
// Computing Structures

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list

using namespace std;

int height = 1;       //global counter variable initited to 1 (minimum height)

int LCAheight1 = 1;   //global counter variable for LCA initiated to 1
int LCAheight2 = 1;

class GL; // prototype for class GL

//int countCheck = 0;

//class nodeSearch {              //additional helper class used for Search Duplicates
//public:
//    int count;
//    char charecter;
//};

bool found = false;             //global found variable used in SearchDuplicates method

//list<nodeSearch> LL;            //list of nodeSearch class called LL, used in SearchDuplicates method
//list<nodeSearch>::iterator l1;


list<char> repeatedChar;          //list of char used in searchDuplicates(recordRepeted function) to store the characters which occured twice. 
list<char> allChar;             //list of char used in searchDuplicates to store all the characters in the expression.
list<char>::iterator c1;        //iterator to allChar list
list<char>::iterator c2;        //iterator to repeatedChar list


// node class to store char and generalized linked list called down
class node
{
protected:
    char* charVariable; // single char variable pointer (not an array)
    GL* down;           // going down to the next level

public:
    node(); // default constructor

    // setters
    void setCharVariable(char var);
    void setDown(GL* d);

    // getters
    char* getChar();
    GL* getDown();

    // display
    void displayChar();
};

node::node() {
    charVariable = new char;
    down = NULL;
}

void node::setCharVariable(char var) {
    //cout << var << " with address:   " << &var << endl;
    *charVariable = var;
    //cout << var << " with address:   " << &charVariable << "    and *charVar  ====  " << *charVariable << endl;
}

void node::setDown(GL* d) {
    down = d;
}

void node::displayChar() {
    cout << *charVariable << " ";
}

char* node::getChar() {
    return charVariable;
}

GL* node::getDown() {
    return down;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class Generalized List
class GL
{
protected:
    list<node> head; // head of the list - each object is of type node class

public:
    GL();                                         // default constructor
    void buildGL(string l);                       // to build the generalized list
    bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
    int LCAdistance(char char1, char char2);      // find the LCA distance of two char in the expression
    int LCAdistanceChar1(char char1);             //helper methods for LCA distance
    int LCAdistanceChar2(char char2);             //helper methods for LCA distance
    int heightOfGL();                             // return the height of the GL using the GL
    void searchDuplicates();                      // print all the duplicates in the GL
    void display();                               // display list
};

GL::GL() {
    
}

void GL::display() {

    list<node>::iterator i1;
    for (i1 = head.begin();i1 != head.end();++i1)
    {
        //cout << (*i1) << " ";
        if (*(i1->getChar()) != NULL) {             //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
            i1->displayChar();                      //if so calling dispayChar method of node class
        }
        else {
            (i1->getDown())->display();            //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned to call the display method of GL recursively 
        }
        
    }
    //cout << endl;
}

void GL::buildGL(string l) {
    string tempString;

    int op = 0;             //variable to keep the count of open brackets
    int loc;                //variable to record the closed bracket location
    int loc1;               //variable to record the open bracket location

    //char tempchar[l.length()];

    for (int j = 1; j < l.length() - 1;j++) {           //j starts from 1 and ends at l.lenght() - 1 because we know that first and last charecters of the string are open and close parantheses respectively.
        if (j > loc1 && j < loc) continue;              //to make sure the elements which are already inserted through recurssion do not get inserted once again.
        else if (l[j] != '(' && l[j] != ')') {
            node temp;
            temp.setCharVariable(l[j]);
            temp.setDown(NULL);
            head.push_back(temp);
            //cout << j << l[j] << endl;

        }
        else if (l[j] == '(') {                              //checking if l[j] is a open bracket
            node temp;
            temp.setCharVariable(NULL);
            GL* tempGL = new GL;
            for (int i = j; i < l.length() - 1;i++) {         //looping through from the open bracket till the end of the string
                if (l[i] == '(') {                           //if l[i] is a open (
                    op++;                                   //then incrementing the bracket counter
                }
                else if (l[i] == ')') {                     //if l[i] is closed bracket
                    op--;                                   //then decrementing the bracket counter
                }

                //else continue;

                if (l[i] == '(' && op == 1) {               //if the l[i] is a bracket and it is infact first bracket (op == 1) 
                    loc1 = i;                               //Then record the location
                }

                else if (l[i] == ')' && op == 0) {          //l[i] is a closed bracket and infact it is the last closed bracket(op == 0)
                    loc = i;                                //then record the location
                    break;                                  //if we have found the last closed bracket then break out of the second loop
                }
            }

            tempString = l.substr(loc1, (loc - loc1) + 1);          //recoring tempstring from loc1( " from (" ) with size (loc - loc1 + 1) which indicates till the closed bracket 
            //cout << l[loc1] << "   " << tempString << endl;
            tempGL->buildGL(tempString);                            //recursivelly calling buildGLwith tempString 
            temp.setDown(tempGL);                                   //setting down pointer of temp to tempGL
            head.push_back(temp);                                   //and pushing temp node to head
        }

        else continue;                                              //else continue ( to ignore close '(' ) 
     }
    //cout << endl;

}

bool GL::findCharInExpression(char findThisChar) {
    //bool tempbool = false;

    list<node>::iterator i1;
    for (i1 = head.begin();i1 != head.end();++i1)
    {
        //cout << (*i1) << " ";
        if (*(i1->getChar()) != NULL) {                 //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
            if (*(i1->getChar()) == findThisChar) {     //checking if char stored inside the node is equal to findThisCHar 
                return true;                            //if so return true (if this line is executed, it is the end of this method, i,e compiler return backs to the main function)
                //tempbool = true;
                //break;
            }
            else
                continue;                               //if char stored inide this node is not equal to findThisChar then continue for the next node in the list  
        }
        else {
            (i1->getDown())->findCharInExpression(findThisChar);  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the findCharInExpression method of GL recursively 
        }

    }
    return false;
}

int GL::heightOfGL() {
    
    list<node>::iterator i1;

    for (i1 = head.begin();i1 != head.end();++i1)
    {
        //cout << (*i1) << " ";
        if (*(i1->getChar()) != NULL) {   //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
            continue;
                //break;
        }                              //if char stored inide this node is not equal to findThisChar then continue for the next node in the list  
        else {
            height++;
            (i1->getDown())->heightOfGL();  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the findCharInExpression method of GL recursively 
        }

    }

    return height;

}

//helper function recordRepeted to store the char that are found multiple times, only once
void recordRepeted(char A) {
    bool temp = false;          //initiating temp to false

    for (c2 = repeatedChar.begin();c2 != repeatedChar.end();++c2) { //iterating through repeatedChar list
        if (A == *c2) {                                         //and checking if the character passed (parameter) is equal to character in repeatedChar
            temp = true;                                        //if so then setting temp to true
        }
        else continue;                                          //else continue
    }

    if (temp != true) {                                         //if temp is not equal to true, even after the iteraton of all the character in repeatedChar
        repeatedChar.push_back(A);                                //then pushback the character ( passed parameter) to repeatedChar
    }   
    else return;                                                //else (if it already exists in repeatedChar, then just return to caller)
}

void GL::searchDuplicates() {
    //list<int> count;
    //list<char> repeatedChar;

    list<node>::iterator i1;
    //list<int>::iterator iInt;
    //list<char>::iterator iChar;

    for (i1 = head.begin();i1 != head.end();++i1) {                 //itterating through the head list
        if (*(i1->getChar()) != NULL) {                             //if the node has a charecter in it
            for (c1 = allChar.begin();c1 != allChar.end();++c1) {   //theniterate through allChar list
                if (*(i1->getChar()) == *c1) {                      //if the Charecter in head already exists in allChar list
                    recordRepeted(*(i1->getChar()));                //then call recordRepeted function with that charecter
                    found = true;                                   //and turn found to true
                }
                else continue;                                      //else continue to check the next charecter in allChar list
            }
            if (found != true) {                                    //if found is not equal to true
                allChar.push_back(*(i1->getChar()));                //then push it to the allChar list
            }
            else continue;                                          //else just continue to the next char in head
        }
        else {
            (i1->getDown())->searchDuplicates();                    //if there dosen't exist a charecter in the node then call searchDuplicate recursively with GL poinet strored in Down
        }
    }



    //nodeSearch temp;

    //for (i1 = head.begin();i1 != head.end();++i1) {         //itterating through the head list
    //    found = false;                                      //initiating found to false for every itteration
    //    if (*(i1->getChar()) != NULL) {                     //if the node has a charecter in it
    //        for (l1 = LL.begin(); l1 != LL.end(); ++l1) {   //then loop through the LL list with nodeSearch as each node
    //            if (*(i1->getChar()) == (l1->charecter)) {  //checking if charecter in head is same as character in LL
    //                //cout << LL.size() << " Before a2" << endl;
    //                l1->count = l1->count + 1;              //then increment the corresponding count
    //                //cout << *(i1->getChar()) << " 2nd TIME" << endl;
    //                //cout << LL.size() << " after a2" << endl;
    //                found = true;                           //then set found to true
    //            }
    //            //else continue;
    //        }
    //        if (found != true) {                    //after coming out of for loop of LL traversal, checking if found is false         
    //            //nodeSearch temp;                    //if so then creating a temp node of nodeSearch class 
    //            //cout << LL.size() << " Before 1st time " << endl;
    //            //cout << *(i1->getChar()) << " 1st TIME" << endl;
    //            temp.charecter = *(i1->getChar());  //setting character to current head character
    //            temp.count = 1;                     //and setting count to 1
    //            LL.push_back(temp);                 //and pushing back the temp to LL
    //            //cout << LL.size() << " After 1st time " << endl;
    //        }
    //    }
    //    else {
    //        //countCheck++;
    //        //cout << "Check counter " << countCheck << endl;
    //        (i1->getDown())->searchDuplicates();        //if the char is NULL in current head then call searchDuplicates recursively with GL pointed by getDown
    //    }
    //}


}

int GL::LCAdistanceChar1(char char1) {
    list<node>::iterator i1;
    list<node>::iterator i2;


    for (i1 = head.begin();i1 != head.end();++i1)
    {
        //cout << (*i1) << " ";
        if (*(i1->getChar()) != NULL) {   //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
            if (*(i1->getChar()) == char1) {    //if char1 matches with a char in head 
                //break;                          //then break
                return LCAheight1;                 //return LCAheight1 if the charecter is found
            }
            else continue;                         //if not just contiune

            //break;
        }                              
        else {
            //cout << "Hello INCREMENT is getting executed" << endl;
            //LCAheight1++;
            //(i1->getDown())->LCAdistanceChar1(char1);  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the LCAdistanceChar1 method of GL recursively 
            i2 = i1;                             //if we encounter a NULL pointer in char then record that address to i2
            continue;                            //and conitnue
            //cout << "Hello DECREMENT is getting executed" << endl;
            //LCAheight1--;
        }

    }

    //cout << "Increment is getting executed" << endl;
    LCAheight1++;                               //after parsing through thw whole node increment LCAheight1
    (i2->getDown())->LCAdistanceChar1(char1);   //and call the down pointer with recorded i2 to call LCAdistanceChar1 recursively


    //return LCAheight1;    //return LCAheight1
    //cout << "Hello DECREMENT is getting executed" << endl;
    //LCAheight1--;
}

int GL::LCAdistanceChar2(char char2) {

    list<node>::iterator i1;
    list<node>::iterator i2;

    for (i1 = head.begin();i1 != head.end();++i1)
    {
        //cout << (*i1) << " ";
        if (*(i1->getChar()) != NULL) {   //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
            if (*(i1->getChar()) == char2) {    //if char2 matches with a char in head 
                //break;                        //then break
                return LCAheight2;              //if the charecter is found return LCAheight2
            }
            else continue;                      //if it is not the charecter we are looking for, else just continue
            //break;
        }                                
        else {
            //cout << "Hello INCREMENT is getting executed" << endl;
            //LCAheight2++;                       //increment LCAheight2
            //(i1->getDown())->LCAdistanceChar2(char2);  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the LCAdistanceChar2 method of GL recursively
            //LCAheight2--;

            i2 = i1;                            //if we encounter a null pointer record the location to i2
            continue;                           //and continue
        }

    }

    //return LCAheight2;                  //return LCAheight2
    //cout << "Hello DECREMENT is getting executed" << endl;
    //LCAheight2--;

    //cout << "Increment is getting executed" << endl;
    LCAheight2++;                                //after iterating through the whole level and if the charecter is still not found then increment LCAheight2 
    (i2->getDown())->LCAdistanceChar2(char2);    //and call LCAdistanceChar2 recursively with with recored address i2 and down pointer stored within it
}

int GL::LCAdistance(char char1, char char2) {

    int LCAchar1;                   //variables to store the returned LCA values of char1
    int LCAchar2;                   //variables to store the returned LCA values of char2

    LCAchar1 = LCAdistanceChar1(char1); //calling helper method LCAdistanceChar1 with char1 
    LCAchar2 = LCAdistanceChar2(char2); //calling helper method LCAdistanceChar2 with char2

    //if (LCAchar1 > LCAchar2)
    //    return LCAchar1;
    //else
    //    return LCAchar2;

    if (LCAchar1 == LCAchar2) {             //if char1 and char2 both lie in the same level
        return (LCAchar1 - LCAchar2) + 1;   //then retun 1   example:- (4-4) + 1
    }
    //else if (LCAchar1 == LCAchar2 && LCAchar1 > 1) {
    //    return LCAchar1 - 1;
    //}
    else if (LCAchar1 > LCAchar2)           //if char1 has a larger LCA
       return (LCAchar1 - LCAchar2) + 1;    //then subtract LCAchar2 from LCAchar1 (which gives the level difference between both charecters) and add 1 to it which gives the LCA of both the char
    else if (LCAchar2 > LCAchar1)           //this is same logic as above just cahr2 has more LCA than char1
        return (LCAchar2 - LCAchar1) + 1;

    //list<node>::iterator i1;

    //for (i1 = head.begin();i1 != head.end();++i1)
    //{
    //    //cout << (*i1) << " ";
    //    if (*(i1->getChar()) != NULL) {   //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
    //        if (*(i1->getChar()) == char1) {
    //            break;
    //        }
    //        //break;
    //    }                              //if char stored inide this node is not equal to findThisChar then continue for the next node in the list  
    //    else {
    //        LCAheight1++;
    //        (i1->getDown())->LCAdistance(char1, char2);  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the findCharInExpression method of GL recursively 
    //    }

    //}


    //for (i1 = head.begin();i1 != head.end();++i1)
    //{
    //    //cout << (*i1) << " ";
    //    if (*(i1->getChar()) != NULL) {   //checking if node that i1 is pointing to has a charecter in it, this is achieved by calling getChar method and dereferencing the returned ponter and maching it to not null 
    //        if (*(i1->getChar()) == char2) {
    //            break;
    //        }
    //        //break;
    //    }                              //if char stored inide this node is not equal to findThisChar then continue for the next node in the list  
    //    else {
    //        LCAheight2++;
    //        (i1->getDown())->LCAdistance(char1, char2);  //if there is No charecter present, then getting Down pointer by calling getDown mehod of node class and using the GL pointer returned, to call the findCharInExpression method of GL recursively 
    //    }

    //}
}

int main()
{
    int numExpressions; // number of expressions
    char option;        // command from the input file
    int count = 0;

    // read the number of expressions given
    cin >> numExpressions;
    cout << "Number of expressions: " << numExpressions << endl << endl;

    string Expression[numExpressions];

    GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects

    node temp;

    for (int i = 0; i < numExpressions;i++) {
        cin >> Expression[i];               // read one line/expression at a time and call the buildGL method for each expression[i]
        expressions[i].buildGL(Expression[i]);
        //expressions[i].display();
        //cout << endl;
        
    }

    // read one line/expression at a time and call the buildGL method for each expression[i]

    // read in and process all the options using switch case
    char command;        //variable to record the command in input file
    int exp;            //variable to store expression
    char Chartobefound;  //variable to sotre Char to be found
    char lcaChar1;      //variables to read char1 and char2 for LCA method respectively
    char lcaChar2;

    while (cin >> command)
    {
        switch (command)
        {
        case 'D': {
            cout << "Displaying all expressions : " << endl;
            for (int i = 0; i < numExpressions;i++) {   //looping through the expressions
                cout << "Expression " << i << " : ";
                expressions[i].display();               //and calling display for each 1 of them
                cout << endl;
            }
            cout << endl;
            break;
        }

        case 'F': {
            cin >> exp >> Chartobefound;        //reading expression and charecter to be found
            cout << "Find " << Chartobefound << " in " << exp << ": ";
            bool tempbool;                      //variable to recieve the return value
            tempbool = expressions[exp].findCharInExpression(Chartobefound);    //calling findCharInExpression with expressions[exp] and recieving the value returned in tempbool 

            if (tempbool == true) {
                cout << "found" << endl << endl;    //if tempbool is true print found
            }
            else
                cout << "not found" << endl << endl;    //else print false 
            break;
        }

        case 'H': {
            cin >> exp;
            height = 1;             //re initiating height to it's original value, because we don't want the value of prior H command get carried on to the new H command
            cout << "Height of expression " << exp << " : " << expressions[exp].heightOfGL() << endl << endl; // calling heightofGL method for expresssions[exp] incsid cout(print statement)
            break;
        }

        case 'L': {
            cin >> exp >> lcaChar1 >> lcaChar2;             //reading exp and char1 and char2

            //Intitalizing LCAheight1 and LCAheight2 to its original values, as we don't want the values from previous L command to be carried on
            LCAheight1 = 1;
            LCAheight2 = 1;

            int heighestDistance;
            cout << "LCA distance between " << lcaChar1 << " and " << lcaChar2 << " in expression " << exp << " : "; //printing in required format
            heighestDistance = expressions[exp].LCAdistance(lcaChar1, lcaChar2);    //calling LCAdistance and storing the return value in heighestDistance
            cout << heighestDistance << endl;       //printing heighest distance
            cout << endl;
            break;
        }
        case 'U': {
            cin >> exp;
            bool tempNone = true;       //intialized to true, for no duplicates
            // re initiating found and LL to it's original value, because we don't want the value of prior U command get carried on to the new U command
            found = false;
            //LL.clear();

            allChar.clear();            //clearing the allChar linkedList from previous U command
            repeatedChar.clear();         //claearing the repeatedChar linkedList from previous U command
            
            cout << "Duplicates in " << exp << " : ";
            expressions[exp].searchDuplicates();    //calling searchDuplicates method with  expressions[exp] GL

            /*for (l1 = LL.begin(); l1 != LL.end(); ++l1) {
                if ((l1->count) > 1) {
                    cout << l1->charecter << " ";
                    tempNone = false;
                }
                else continue;
            }*/

            for (c2 = repeatedChar.begin(); c2 != repeatedChar.end(); ++c2) {   //itterating through the repeatedChar list
                cout << *c2 << " ";                                             //then printing the charecter
                tempNone = false;                                               //if there exists a charecter in repetedChar to be printed then tempNone is set to false
            }

            if (tempNone == true) {                                             //if tempNone is true, i,e there was no chareceter to be printed in repeatedChar lsit 
                cout << "None";                                                 //then print None
            }
            cout << endl << endl;
            break;
        }

        default:
            break;
        }
    }



    return 0;
} // main
