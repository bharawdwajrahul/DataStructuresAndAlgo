// DSA 5005 - Computing Structures
// Fall 2022
// Project 3

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file

using namespace std;

// class to store one row's information
class DFrow
{
protected:
	// all the fields to store information of a row
	string name;
	char sex;
	int age;
	int height;
	int weight;
	string city;

public:
	DFrow(); // default constructor
	DFrow(string n, char c, int one, int two, int three, string ci); // non-default constructor
	// TODO: write getters for each of the fields
	string getname();
	char getsex();
	int getage();
	int getheight();
	int getweight();
	string getcity();
	// TODO: write setters for each of the fields

	void setname(string n);
	void setsex(char s);
	void setage(int a);
	void setheight(int h);
	void setweight(int w);
	void setcity(string c);
	void setDFrow(DFrow temp);			//helper method to copy one DFrow to another DFrow

	void display();			// TODO: write display method to display all the fields in the same order
	// 			refer to output sample for exact format

	// TODO: write destructor
	~DFrow();
};

DFrow::DFrow() {
	name = "";
	sex = ' ';				//initializing fields of DFrow with initial bare minimum values
	age = 0;
	height = 0;
	weight = 0;
	city = "";
}

DFrow::DFrow(string n, char c, int one, int two, int three, string ci) {
	name = n;
	sex = c;						//initiating all the fields of DFrow with respective passed parameters
	age = one;
	height = two;
	weight = three;
	city = ci;
}

void DFrow::display() {
	cout << name << " " << sex << " " << age << " " << height << " " << weight << " " << city;		//displying all the fields
}
int DFrow::getage() {
	return age;					//returning age
}

int DFrow::getheight() {	
	return height;				//returning height
}

int DFrow::getweight() {
	return weight;				//returing height
}

string DFrow::getname() {
	return name;				//returning name
}

char DFrow::getsex() {
	return sex;					//returning sex
}

string DFrow::getcity() {
	return city;			//returning city
}

void DFrow::setname(string n) {
	name = n;						//assigning field name with value of n
}
void DFrow::setsex(char s) {
	sex = s;						//assigning field sex with value of s
}
void DFrow::setage(int a) {
	age = a;						////assigning field age with value of a
}
void DFrow::setheight(int h) {
	height = h;						//assigning field height with value of h
}
void DFrow::setweight(int w) {
	weight = w;						//assigning field weight with value of w
}
void DFrow::setcity(string c) {
	city = c;						//assigning city name with value of c
}

void DFrow::setDFrow(DFrow temp) {
	name = temp.getname();			//assigning each field of DFrow with repective fiels of another DFrow(temp) with the help of respective getters 
	sex = temp.getsex();
	age = temp.getage();
	weight = temp.getweight();
	height = temp.getheight();
	city = temp.getcity();
}

DFrow::~DFrow() {
	//there is nothing to delete as there is no dynamically alloted variable 
}

// class to store the entire dataframe
class DataFrame
{
protected:
	vector<DFrow> data; // field storeing all the data
	vector<string> headers; // field to only the headers
	int nRows, nCols; // store the number of rows and cols

public:
	// Constructors
	DataFrame();
	DataFrame(int rows, int cols);

	// Overload the [] operator to access data in DF
	DFrow operator[](int i);

	// File reading Method
	void readCSV(string filename, string headerPresence);

	// Output Method
	void display();
	void displayrows();			//helper method to display rows from getRows method

	// Search Record
	DFrow searchRecord(string name);

	// Setters
	void setColName(int col, char* name); // change the name of a header/column
	void setdata(DFrow rowData);	//helper function to set the value for vector data

	// Getters
	int getNumberRows();                                              // returns the number of rows
	int getNumberCols();                                              // returns the number of columns
	DataFrame* getRows(int* rows, int rLen);                          // returns a data frame with a set of rLen number of rows
	string getHeader(int i);                                          // returns the header name given a index position

	// Find info of a given column
	double findAverage(int colNumber); // returns the average of the given column
	double findMax(int colNumber);     // returns the max of the given column
	double findMin(int colNumber);     // returns the min of the given column
	double frequency(int colNumber);   // displays the frequency of the unique values

	// Destructor
	~DataFrame();
};

DataFrame::DataFrame() {
	nRows = 0;				//assigning nRows and nCols with initial value of 0 
	nCols = 0;
	data = {};				//assigning data and headers vector with Null values
	headers = {};
}

DataFrame::DataFrame(int rows, int cols) {
	nRows = rows;			//non default constructor to assign nRows and nCols with values of rows and cols			
	nCols = cols;
	data = {};				//assigning data and headers vector with Null values
	headers = {};			
}

void DataFrame::readCSV(string filename, string headerPresence) {
	fstream fin;

	fin.open(filename, ios::in);	// opening the CSV file with fstream, ios::in allows input (read operations) from a stream

	int age, height, weight;
	string name, city;
	char sex;						//temporary variable to store values

	string temp;					//temprary variable to store a string
	string tempheader;				//temporary variable to store header

	int r = 1, c = 1;				//temporary variable to keep count of rows and coloumns respectively

	//DFrow temprow;

	while (!fin.eof()) {			//while it is not end of the file keep repeating
		if (headerPresence == "true") {			//checking for header presence
			if (r == 1) {
				//cout << "r value " << r << endl;
				if (c == nCols) {
					getline(fin, tempheader);			//getting the last header. i,e city in the CSV file
					headers.push_back(tempheader);
					c = 1;								//re assigning colomn cout to 1
					r++;								//incrementing row count as it is the last string of 1st row (colomn headers)
					//cout << "after r increment r = " << r << endl;
				}
				else {
					getline(fin, tempheader, ',');		//getting the first 5 headers which are separated by comma	
					headers.push_back(tempheader);		//push_back operation vector headers with value tempheader
					c++;								//incrementing colomn count
				}

			}
			else if (r > 1 && r <= nRows + 1) {				//r <= nRows + 1 becouse there are a total of 19 rows in csv file including header.
				//cout << "inside else statement" << endl;
				if (c == 1) {
					getline(fin, name, ',');				//if it is first colomn then storing the value in variable name
					c++;
				}
				else if (c == 2) {
					getline(fin, temp, ',');				//reading the value into temp string
					sex = temp[0];							//reading the first charecter of temp to sex(as sex is char variable and has only one letter)
					c++;									//increamenting colomn
				}
				else if (c == 3) {
					getline(fin, temp, ',');				//reading the value into temp string
					age = stoi(temp);						//converting temp into int and assigning it to age
					c++;									//increamenting colomn
				}
				else if (c == 4) {
					getline(fin, temp, ',');				//reading the value into temp string
					height = stoi(temp);					//converting temp into int and assigning it to height
					c++;									//increamenting colomn
				}
				else if (c == 5) {
					getline(fin, temp, ',');				//reading the value into temp string
					weight = stoi(temp);					//converting temp into int and assigning it to weight
					c++;									//increamenting colomn
				}
				else if (c == 6) {
					getline(fin, city);//getline(fin, tempDFrow[j].city);
					DFrow temprow(name, sex, age, height, weight, city);				//calling the non default constructor of DFrow to set the values
					data.push_back(temprow);				//push_back to vector data
					r++;									//incrementing row count
					//cout << "r: " << r << endl;
					c = 1;									//reassigning colomn value to 1
				}
				//cout << "inside while loop " << clmnName[0] << " with r: "<< r << endl;
				//break;
			}
			else {
				break;
			}

		}
		else {
			//cout << "Not true " << endl;
			if (c == 1) {
				getline(fin, name, ',');				//if it is first colomn then storing the value in variable name
				c++;
			}
			else if (c == 2) {
				getline(fin, temp, ',');				//reading the value into temp string
				sex = temp[0];							//reading the first charecter of temp to sex(as sex is char variable and has only one letter)
				c++;									//increamenting colomn
			}
			else if (c == 3) {
				getline(fin, temp, ',');				//reading the value into temp string
				age = stoi(temp);						//converting temp into int and assigning it to age
				c++;									//increamenting colomn
			}
			else if (c == 4) {
				getline(fin, temp, ',');				//reading the value into temp string
				height = stoi(temp);					//converting temp into int and assigning it to height
				c++;									//increamenting colomn
			}
			else if (c == 5) {
				getline(fin, temp, ',');				//reading the value into temp string
				weight = stoi(temp);					//converting temp into int and assigning it to weight
				c++;									//increamenting colomn
			}
			else if (c == 6) {
				getline(fin, city);//getline(fin, tempDFrow[j].city);
				DFrow temprow(name, sex, age, height, weight, city);				//calling the non default constructor of DFrow to set the values
				data.push_back(temprow);				//push_back to vector data
				r++;									//incrementing row count
				//cout << "r: " << r << endl;
				c = 1;									//reassigning colomn value to 1
			}
		}

		//getline(fin, line, ',');
		//cout << line << endl;
	}

}

void DataFrame::display() {
	if (headers.size() != 0) {				//if header vector size is not equal to 0 then display both headers vector and data vector by looping through it
		for (int i = 0; i < nCols;i++) {
			cout << " " << headers[i];
		}
		cout << endl;
		for (int j = 0; j < data.size();j++) {
			data[j].display();				//calling display method of DFrow class
			cout << endl;
		}
		cout << endl;
	}
	else {								//else just print out the rows stored in data vector
		for (int j = 0; j < data.size();j++) {
			data[j].display();			////calling display method of DFrow class
			cout << endl;
		}
		cout << endl;
	}

}

double DataFrame::findAverage(int colNumber) {
	int a[nRows];					//int array to store all initiger values of repective colomn
	int Total = 0;					//variable to calculate the total
	double result;					//double variable result to find average and returning it 
	
	if (colNumber == 3) {
		for (int i = 0; i < data.size(); i++) {		//looping through all the rows(data vector)
			a[i] = data[i].getage();				//calling get age method of DFrow and assigning it to a[i]
			Total = Total + a[i];					//adding the current element to the already existing total
		}
		result = Total / data.size();				//total divided by number of rows
		return result;								//returning variable result
	}
	else if (colNumber == 4) {						//same as the above condition except for the getter used 
		for (int i = 0; i < data.size(); i++) {
			a[i] = data[i].getheight();				//calling getheight of DFrow class and assigning it to a[i]
			Total = Total + a[i];
		}
		result = Total / data.size();
		return result;
	}
	else if (colNumber == 5) {
		for (int i = 0; i < data.size(); i++) {		//same as the above condition except for the getter used
			a[i] = data[i].getweight();				//calling getweight of DFrow class and assigning it to a[i]
			Total = Total + a[i];
		}
		result = Total / data.size();
		return result;
	}
}

double DataFrame::findMax(int colNumber) {
	int a[nRows];				//int array to store all initiger values of repective colomn
	int Max = 0;				//Max variable to store the max value, initialized to 0

	if (colNumber == 3) {
		for (int i = 0; i < data.size(); i++) {		//looping through the data vector
			a[i] = data[i].getage();				//calling get age method of DFrow and assigning it to a[i]
			if (a[i] > Max) {						//comparing if the current value is greater than max
				Max = a[i];							//if so assigning max to current value
			}
			else continue;							//else continue
		}
		return Max;									//return max
	}
	else if (colNumber == 4) {			
		for (int i = 0; i < data.size(); i++) {		//same as above except for getter which is used
			a[i] = data[i].getheight();
			if (a[i] > Max) {
				Max = a[i];
			}
			else continue;
		}
		return Max;
	}
	else if (colNumber == 5) {
		for (int i = 0; i < data.size(); i++) {		//same as above except for getter which is used
			a[i] = data[i].getweight();
			if (a[i] > Max) {
				Max = a[i];
			}
			else continue;
		}
		return Max;
	}
}

double DataFrame::findMin(int colNumber) {
	int a[nRows];								//int array to store all initiger values of repective colomn
	double Min;									//Min variable to store the min value

	if (colNumber == 3) {
		Min = data[0].getage();					//assgning min to the first value of the age coloumn
		for (int i = 0; i < data.size(); i++) {		//looping through the vector data
			a[i] = data[i].getage();			//assigning a[i] to age at current position with the help of getage method from DFrow class
			if (a[i] < Min) {					//comparing if a[i] is less than Min
				Min = a[i];						//if so Min is assigned to current value of a[i]
			}
			else continue;
		}
		return Min;								//returning Min
	}
	else if (colNumber == 4) {					//Same as above, but for the height colomn and its respective getter is used
		Min = data[0].getheight();
		for (int i = 0; i < data.size(); i++) {
			a[i] = data[i].getheight();
			if (a[i] < Min) {
				Min = a[i];
			}
			else continue;
		}
		return Min;
	}
	else if (colNumber == 5) {					//Same as above, but for the weight colomn and its respective getter is used
		Min = data[0].getweight();
		for (int i = 0; i < data.size(); i++) {
			a[i] = data[i].getweight();
			if (a[i] < Min) {
				Min = a[i];
			}
			else continue;
		}
		return Min;
	}
}

DFrow DataFrame::operator[](int i) {
	return data[i];											//overloading operator to access vector data at position i
}

void DataFrame::setdata(DFrow rowData) {
	data.push_back(rowData);								//takes a single row data (from parameter) and pushes it to the data vector of dataFrame class
}

DataFrame* DataFrame::getRows(int* rows, int rLen) {
	DataFrame* temp = new DataFrame();						//creating a temporary dataframe to sore the values and return
	
	for (int i = 0;i < rLen;i++) {
		temp->setdata(data[rows[i]]);						//setting the data for the temp data with helper method setdata
		//temp->setdata(data[rows[i]]);
		//temp[i] = data[rows[i]];
	}

	return temp;											//returning temp
}

void DataFrame::displayrows() {								//helper method to display the required rows
	for (int j = 0; j < data.size();j++) {
		//cout << j << endl;
		data[j].display();									//displaymethod of DFrow class to display each row
		cout << endl;
	}
	cout << endl << endl;
	return;
}

double DataFrame::frequency(int colNumber) {
	vector<int> count;				//vector of int to hold the count of each category
	vector<string> categories;		//vector of string to hold the categories in string and char colomns
	vector<int> intcategories;		//vector of int to store the categories in int colomns
	string tempstring;				//temparary variable of string
	int tempint;					//temporary variable of int
	bool tempbool;					//temporary variable of bool

	if (colNumber == 1) {			//if colNumber is 1(Name)
		for (int i = 0; i < data.size();i++) {	//then loop through the data vector
			tempbool = false;		//assigning tempbool to false initially for each itteration
			tempstring = data[i].getname();	//getting the name and storing it in tempstring

			for (int j = 0;j < categories.size();j++) {		//looping through the categories vactor
				if (categories[j] == tempstring) {			//and chech if the current value is already recorded once
					count[j] = count[j] + 1;				//if so increase the paralel count by 1
					tempbool = true;						//and trninf tempbool to true
				}
			}

			if (tempbool == false) {				//if tempbool remains falls even after looping through the vector categories
				categories.push_back(tempstring);	//then assisgn the tempstring its own new position in categories vector
				count.push_back(1);					//and assign it's parllel counter with value 1
			}
			else
				continue;
		}

		for (int k = 0; k < categories.size();k++) {				//looping through the category vector and printing its value and it's parallel count
			cout << categories[k] << ": " << count[k] << endl;
		}
	}

	if (colNumber == 2) {
		for (int i = 0; i < data.size();i++) {						//same as above for colomn sex, except the respective getter from DFrow class is used
			tempbool = false;
			tempstring = data[i].getsex();

			for (int j = 0;j < categories.size();j++) {
				if (categories[j] == tempstring) {
					count[j] = count[j] + 1;
					tempbool = true;
				}
			}

			if (tempbool == false) {
				categories.push_back(tempstring);
				count.push_back(1);
			}
			else
				continue;
		}

		for (int k = 0; k < categories.size();k++) {
			cout << categories[k] << ": " << count[k] << endl;
		}
	}

	if (colNumber == 6) {							//same as above for colomn city, except the respective getter from DFrow class is used
		for (int i = 0; i < data.size();i++) {
			tempbool = false;
			tempstring = data[i].getcity();

			for (int j = 0;j < categories.size();j++) {
				if (categories[j] == tempstring) {
					count[j] = count[j] + 1;
					tempbool = true;
				}
			}

			if (tempbool == false) {
				categories.push_back(tempstring);
				count.push_back(1);
			}
			else
				continue;
		}

		for (int k = 0; k < categories.size();k++) {
			cout << categories[k] << ": " << count[k] << endl;
		}
	}

	if (colNumber == 3) {
		for (int i = 0; i < data.size();i++) {			//same as above for colomn age, except the respective getter from DFrow class is used, and respective temporary int variables to hold the value
			tempbool = false;
			tempint = data[i].getage();

			for (int j = 0;j < intcategories.size();j++) {
				if (intcategories[j] == tempint) {
					count[j] = count[j] + 1;
					tempbool = true;
				}
			}

			if (tempbool == false) {
				intcategories.push_back(tempint);
				count.push_back(1);
			}
			else
				continue;
		}

		for (int k = 0; k < intcategories.size();k++) {
			cout << intcategories[k] << ": " << count[k] << endl;
		}
	}

	if (colNumber == 4) {
		for (int i = 0; i < data.size();i++) {			//same as above for colomn height, except the respective getter from DFrow class is used, and respective temporary int variables to hold the value
			tempbool = false;
			tempint = data[i].getheight();

			for (int j = 0;j < intcategories.size();j++) {
				if (intcategories[j] == tempint) {
					count[j] = count[j] + 1;
					tempbool = true;
				}
			}

			if (tempbool == false) {
				intcategories.push_back(tempint);
				count.push_back(1);
			}
			else
				continue;
		}

		for (int k = 0; k < intcategories.size();k++) {
			cout << intcategories[k] << ": " << count[k] << endl;
		}
	}

	if (colNumber == 5) {
		for (int i = 0; i < data.size();i++) {			//same as above for colomn weight, except the respective getter from DFrow class is used, and respective temporary int variables to hold the value
			tempbool = false;
			tempint = data[i].getweight();

			for (int j = 0;j < intcategories.size();j++) {
				if (intcategories[j] == tempint) {
					count[j] = count[j] + 1;
					tempbool = true;
				}
			}

			if (tempbool == false) {
				intcategories.push_back(tempint);
				count.push_back(1);
			}
			else
				continue;
		}

		for (int k = 0; k < intcategories.size();k++) {
			cout << intcategories[k] << ": " << count[k] << endl;
		}
	}

	return 0;
}


class ExceptionNoRecord {};					//ExceptionNoRecord class to call if there exists no record asosiated with the name.

DFrow DataFrame::searchRecord(string name) {
	DFrow temp;								//temporary variable to store DFrow
	try {
		bool found = false;					//bool variable found initialized to false
		for (int i = 0; i < data.size();i++) {		//looping throught the colomn
			if (name == data[i].getname()) {	//if the given name(parameter) mataches name at the respective location
				temp.setDFrow(data[i]);			//temp variable is assigned with values of DFrow data[i] with the help of helper method setDFrow
				found = true;					//boolean value for found is turned to false
			}
			else
				continue;
		}

		if (found == false) throw ExceptionNoRecord();		//even after looping through all the rows in data vector if we don't get a match with the given name, then found would have remained false and we throw an exception
		//return temp;
	}
	catch (ExceptionNoRecord NoRecord) {				//catching the exception thrown
	//	//catching the exception
	}
	return temp;										//returning temp
}

void DataFrame::setColName(int col, char* name) {
	headers[col] = *name;						//header in headers vector at position col assigned to *name value of name 
}

int DataFrame::getNumberRows() {
	return nRows;				//returning number of rows
}

int DataFrame::getNumberCols() {
	return nCols;				//returning number of colomns
}

string DataFrame::getHeader(int i) {
	return headers[i];			//returning value stored at position i in vector headers
}

DataFrame::~DataFrame() {
	//there is nothing to delete as there are no dynamically alotted pointers
}



// main function
int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	//char command;

	int r = 1, c = 1;
	

	cin >> numRows >> numCols >> headerBool >> fileName;

	//cout << "Hello" << endl;

	//string clmnName[numCols];
	//int cn = 0;						//temporary variable to keep track of coloumn name count
	DataFrame* d = new DataFrame(numRows, numCols);

	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	
	// TODO: read the commands from the input file (redirected input)
char command;
string commandtemp;
int tempColNum;
double tempresult;
int fromrow, torow, len, rowrecord;				//temporary variable to store from and to row for R command and len to store the rowlength and row record to record to the arrray
DataFrame* tempDF;								//tempDF  DataFrame to catch the return from the getRows method
string category;
DFrow temprow;

while (cin >> command) {						//while there still exsists a command in the input file
	switch (command)							//swith to respective case
	{
	case 'A': {
		cin >> commandtemp;
		if (commandtemp == "Name") {				//checking if given input string is Name
			cout << "Average for Name cannot be found since it is nan" << endl;	//if so display appropriate message as Avg can't be calculated for string variables
			break;
		}
		else if (commandtemp == "Sex") {					//checking if given input string is Sex
			cout << "Average for Sex cannot be found since it is nan" << endl;	//if so display appropriate message as Avg can't be calculated for char variables
		}
		else if (commandtemp == "Age") {					//checking if given input string is Sex
			tempColNum = 3;									//then assigning temColNum with 3
			tempresult = d->findAverage(tempColNum);		//and using tempColNum calling findAverage method and store the return value in tempresult
			cout << "Average of Age is " << tempresult << endl;	//displying the Avg
		}
		else if (commandtemp == "Height(in)") {			//checking if given input string is Height(in)
			tempColNum = 4;								//then assigning temColNum with 4
			tempresult = d->findAverage(tempColNum);	//and using tempColNum calling findAverage method and store the return value in tempresult
			cout << "Average of Height(in) is " << tempresult << endl;	//displying the Avg
		}
		else if (commandtemp == "Weight(lbs)") {		//checking if given input string is Weight(lbs)
			tempColNum = 5;								//then assigning temColNum with 5
			tempresult = d->findAverage(tempColNum);	//and using tempColNum calling findAverage method and store the return value in tempresult
			cout << "Average of Weight(lbs) is " << tempresult << endl; //displying the Avg
		}
		else if (commandtemp == "City") {			//checking if given input string is City
			cout << "Average for City cannot be found since it is nan" << endl;	//if so display appropriate message as Avg can't be calculated for string variables
		}
		break;
	}
	case 'F': {
		cin >> commandtemp;						//reading the name to be found, with commandtemp variable

		temprow = d->searchRecord(commandtemp);	//calling searchRecord of DataFrame class with the given string and assisgning it to temprow
		cout << "Record found: " << endl << "	";
		temprow.display();						//and displaying temprow by calling display function of DFrow class
		cout << endl << endl;
		break;
	}
	case 'Q': {
		cin >> category;

		if (category == "Name") {				//checking if given input string is Name
			//cout << "Average for Name cannot be found since it is nan" << endl;
			tempColNum = 1;						//then assigning tempColNum to 1
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
			//break;
		}
		else if (category == "Sex") {		//checking if given input string is Name
			//cout << "Average for Sex cannot be found since it is nan" << endl;
			tempColNum = 2;						//then assigning tempColNum to 2
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
		}
		else if (category == "Age") {
			tempColNum = 3;						//then assigning tempColNum to 3
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
			//tempresult = d->findAverage(tempColNum);
			//cout << "Average of Age is " << tempresult << endl;
		}
		else if (category == "Height(in)") {	//checking if given input string is Height(in)
			tempColNum = 4;						//then assigning tempColNum to 4
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
			//tempresult = d->findAverage(tempColNum);
			//cout << "Average of Height(in) is " << tempresult << endl;
		}
		else if (category == "Weight(lbs)") {	//checking if given input string is Weight(lbs)
			tempColNum = 5;						//then assigning tempColNum to 5
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
			//tempresult = d->findAverage(tempColNum);
			//cout << "Average of Weight(lbs) is " << tempresult << endl;
		}
		else if (category == "City") {			//checking if given input string is City
			tempColNum = 6;						//then assigning tempColNum to 6
			d->frequency(tempColNum);			//calling frequency method of DataFrame class with tempColNum
			//cout << "Average for City cannot be found since it is nan" << endl;
		}


		break;
	}
	case 'X': {
		cin >> commandtemp;				//reading in the given string
		if (commandtemp == "Name") {	//checking if given input string is Name
			cout << "Max for Name cannot be found since it is nan" << endl;	//if so displying ther appropriate message
			break;
		}
		else if (commandtemp == "Sex") {	//checking if given input string is Sex
			cout << "Max for Sex cannot be found since it is nan" << endl; //if so displying ther appropriate message
		}
		else if (commandtemp == "Age") {	//checking if given input string is Age
			tempColNum = 3;					//if so, then setting tempColNum to 3
			tempresult = d->findMax(tempColNum); //and calling findMax method of DataFrame class with tempColNum and storing the return value in tempresult
			cout << "Max of Age is " << tempresult << endl;
		}
		else if (commandtemp == "Height(in)") {		//checking if given input string is Height(in)
			tempColNum = 4;							//if so, then setting tempColNum to 4
			tempresult = d->findMax(tempColNum);	//and calling findMax method of DataFrame class with tempColNum and storing the return value in tempresult
			cout << "Max of Height(in) is " << tempresult << endl; //displaying tempresult which stores Height(in)
		}
		else if (commandtemp == "Weight(lbs)") {	//checking if given input string is Weight(lbs)
			tempColNum = 5;							//if so, then setting tempColNum to 5
			tempresult = d->findMax(tempColNum);	//and calling findMax method of DataFrame class with tempColNum and storing the return value in tempresult
			cout << "Max of Weight(lbs) is " << tempresult << endl;	//displaying tempresult which stores Weight(lbs)
		}
		else if (commandtemp == "City") {			//checking if given input string is City
			cout << "Max for City cannot be found since it is nan" << endl;	//if so displying ther appropriate message
		}
		break;				//breaking out of the case
	}
	case 'I': {
		cin >> commandtemp;
		if (commandtemp == "Name") {		//checking if given input string is Name
			cout << "Min for Name cannot be found since it is nan" << endl << endl; //if so displying ther appropriate message
			break;
		}
		else if (commandtemp == "Sex") {			//checking if given input string is Sex
			cout << "Min for Sex cannot be found since it is nan" << endl<< endl;	//if so displying ther appropriate message
		}
		else if (commandtemp == "Age") {			//checking if given input string is Age
			tempColNum = 3;							//if so then assigning tempColNum to 3
			tempresult = d->findMin(tempColNum);	//calling findMin method of DataFrame class with tempColNum and assigning the return value to tempresult
			cout << "Min of Age is " << tempresult << endl << endl;
		}
		else if (commandtemp == "Height(in)") {		//checking if given input string is Height(in)
			tempColNum = 4;							//if so then assigning tempColNum to 4
			tempresult = d->findMin(tempColNum);	//calling findMin method of DataFrame class with tempColNum and assigning the return value to tempresult
			cout << "Min of Height(in) is " << tempresult << endl << endl;
		}
		else if (commandtemp == "Weight(lbs)") {	//checking if given input string is Weight(lbs)
			tempColNum = 5;							//if so then assigning tempColNum to 5
			tempresult = d->findMin(tempColNum);	//calling findMin method of DataFrame class with tempColNum and assigning the return value to tempresult
			cout << "Min of Weight(lbs) is " << tempresult << endl << endl;
		}
		else if (commandtemp == "City") {			//checking if given input string is City
			cout << "Min for City cannot be found since it is nan" << endl << endl;	//if so displying ther appropriate message
		}
		break;			//breaking out of the case
	}
	case 'R': {
		//cout << "inside R" << endl;
		cin >> fromrow >> torow;							//reading from row and torow
		rowrecord = fromrow;								//fromrow is the staring point of the row requested
		len = torow - fromrow;
		int temprow[len];									//array called temprow to store the values of fromrow to row for R command, which will further be passed as a parameter for getRows method 
		for (int i = 0; i < len; i++) {
			temprow[i] = rowrecord;							//storing exact inidex of each row which is needed, for example R 10 15.....temprow = {10, 11, 12, 13, 14}
			rowrecord++;
		}

		tempDF = d->getRows(temprow, len);					//calling getrows method with temprow array and length and storing the return value in tempDF 
			//cout << "for i: " << i << endl;
		tempDF->displayrows();								//helper method to display the rows needed
		//for (int i = 0; i < len ;i++) {
		//	tempDF[i].display();
		//}
		//cout << "end of R" << endl;
		//cout << endl;
		//delete[] tempDF;
		break;
	}
	case 'D':{
		d->display();									//calling display method of DataFrame class
		break;
	}
	default:
		break;
	}
}

delete d;			//deleting dynamically created DataFrame pointer variable d

	return 0;
}
