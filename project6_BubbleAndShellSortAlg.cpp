//Computing Structures
//Fall 2022
//Project 6
//Author: Rahul Bharadwaj

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
    // we want to retain the ordering of arr for shell sort 
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//function to find the inversions
int Inversions(int* arr,int numElements) {
    int* count = new int[numElements];      //an array count to store the number of element greater than that
    int TotalComparisions = 0;              //variable Total Comparisions to store the total comparission of the all elements

    for (int i = 0; i < numElements; i++) {     //looping through
        count[i] = 0;                           //and initiating count of each elment to 0
    }

    for (int i = 0; i < numElements - 1; i++) {     //looping from the first element to the last but one element(as last element will not have any element on its right to be compared)
        for (int j = i + 1; j < numElements; j++) { //loopinng through the respective next element to the last element
            if (arr[i] > arr[j]) {                  //if the element is greater than it's element on the right
                count[i] = count[i] + 1;            //incrementing count by 1
            }
            else
                continue;                           //else just continue
        }
    }

    for (int i = 0; i < numElements; i++) {        //loop through
        TotalComparisions = TotalComparisions + count[i];   //and add count of each element to TotalComparisions
    }

    return TotalComparisions;                       //Return total comparision

}

//function to calculate the MaximumDisplacement/Chebyshev
int MaximumDisplacement(int* arr, int* arrSorted, int numElements) {
    int* displacementOfEachElement = new int[numElements];  //array called displacementOfEachElement to store desplacement of each element
    int maximumdisplacement = 0;
    
    for (int i = 0; i < numElements; i++) {                 //loop throuth first element to the last in the array
        if(arr[i] == arrSorted[i]) {                        //if the element in the position i in both sorted and partially sorted array is same then
            displacementOfEachElement[i] = 0;               //then set displacementOfEachElement for that element to 0 
        }

        else {
            int positionInSortedArray;                      //else if they are not equal

            for (int j = 0; j < numElements; j++) {         //loop through sorted array
                if (arrSorted[j] == arr[i])                 //and check if the element at position j in sorted array is same as element in partially sorted array same
                    positionInSortedArray = j;              //then set positionInSortedArray to j
                else
                    continue;                               //else just continue
            }

            int diff;                                       //variable diff to store the difference between the positions in sorted and partially sorted array for a particular element

            diff = positionInSortedArray - i;               //callculate the difference and assighn it to diff

            if (diff < 0) {                                 //if diff is negetive
                diff = diff * -1;                           //then multiply it with -1 to make it positive
            }

            displacementOfEachElement[i] = diff;            //and assign displacementOfEachElement to i
        }

    }

    for (int i = 0; i < numElements; i++) {                 //loop through to check the max in array displacementOfEachElement
        maximumdisplacement = max(maximumdisplacement, displacementOfEachElement[i]);   //assign max between maximumdisplacement and displacementOfEachElement to maximumdisplacement
    }

    return maximumdisplacement;                             //return maximumdisplacement

}

//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

    // generate n random elements with the seed s, within the lower and upper range 
    // store the randomly generated UNIQUE set of elements in an array 'A'
    //int *A = new int[n];
    int A[n];
    int j = 0;
    srand(s); // using seed s

    int range = u - l + 1;

    std::unordered_set<int> numbers;

    while (numbers.size() < n && j < n) {
        int randomNum = rand() % range + l;
        if (numbers.find(randomNum) != numbers.end()) {
            continue;
        }
        else {
            numbers.insert(randomNum);
            //A[j] = randomNum;
            //j++;
        }
        
    }

    unordered_set<int>::iterator c1;                    //iterator to parse through the unordered set
    for (c1 = numbers.begin();c1 != numbers.end();++c1) {   //parsing through unordered set
            A[j] = *c1;                                     //copying each value to a array
            j++;                                            //incrementing j
    }

    // you may use the unordered set to help generate unique elements

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    // display the array A
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 
    int* Asorted;
    Asorted = bubbleSort(A, n, n*n );

    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array 
    for (int i = 0; i < n; i++) {
        cout << Asorted[i] << " ";
    }
    cout << endl << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    int* bubResult;
    bubResult = bubbleSort(A, n, D);


    // display bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    for (int i = 0; i < n; i++) {
        cout << bubResult[i] << " ";
    }
    cout << endl << endl;

    // find both the quality metrics for bubResult
    cout << "Number of inversions in bubResult: " << Inversions(bubResult, n) << endl;
    cout << "Chebyshev distance in bubResult: " << MaximumDisplacement(bubResult, Asorted, n) << endl << endl;


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    int* shellResult;
    shellResult = shellSort(A, n, D);

    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    for (int i = 0; i < n; i++) {
        cout << shellResult[i] << " ";
    }
    cout << endl << endl;

    // display shellResult

    // find both the quality metrics for shellResult
        // find both the quality metrics for bubResult
    cout << "Number of inversions in shellResult: " << Inversions(shellResult, n) << endl;
    cout << "Chebyshev distance in shellResult: " << MaximumDisplacement(shellResult, Asorted, n) << endl << endl;


    return 0;
}
