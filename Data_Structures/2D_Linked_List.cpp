#include <cstdlib>
#include <iostream>
using namespace std;
//QUESTION
//given a singly linked list of integer nodes sorted in increasing order
//output the minimum integer which is greater than or equal to x
//INPUT: n = number of elements in the list
//first = index of the first element
// integer x

//nexti = −1 then it is the tail of the list and does not point to any other cell
//output the minimum value that is greater than or equal to x, or -1 if there is no such number

//making a class
class SLinkedList;

//function declarations
SLinkedList makeSLL(int n, int first, int x, int **arr, int &output);
//int linkedList(int n, int first, int x, int **arr);

class SNode {  // singly linked list node
 private:
  int val;                       // linked list element value
  SNode* next;               // next item in the list
  friend class SLinkedList;  // provide SLinkedList access
};

class SLinkedList {
    public:
        SLinkedList();              // empty list constructor
        void addVal(int val); //method to add values
        void printNodes(); //method to print the nodes
        SNode * getHead(); //used to get the head of the list
    private:
        SNode* head;
};

SLinkedList::SLinkedList() : head(NULL) {} //constructor

//retriving the head from the list 
SNode * SLinkedList::getHead() {
    return head;
};

//adding a new node at the beginning 
void SLinkedList::addVal(int val) {
    SNode * new_node = new SNode; //making new node
    SNode * cur = head; //setting cur to point to head
    if (cur == NULL) { //assigning head to cur if it is an empty list
        head = cur; //set head to cur
        head = new SNode; //make head a new SNode
        head->val = val; //set val of head to be val (passed in arugement)
        head->next = NULL; //set next of head to be NULL
        return; 
    }
    while (cur->next != NULL) { //finding the end of list
        cur = cur->next; 
    }
    cur->next = new_node; //adding new_node to the end of list
    new_node->val = val; //assigning value to new_node to val
    new_node->next = NULL; //assigning next value of new_node to NULL
};


//printing nodes
void SLinkedList::printNodes() {
    SNode * cur = head;
    while (cur->next != NULL) { //if next of cur is NOT NULL then continue to print using this format
        //elem stores the element that we want to print
        std::cout << cur->val << "->";
        cur = cur->next; //iterating thru the list 
    }
    if (cur->next == NULL) { //if at the end of the list then print using this format
        std::cout << cur->val << std::endl;
    }
}

SLinkedList makeSLL(int n, int first, int x, int **arr, int &output) { //making a SLL
    SLinkedList sll; //creates a class of sll
    int curIndex = first; //set curIndex to first
    int flag = -1; //-1 is default (no number greater or equal to x)
    while (curIndex != -1) { //while curIndex is not -1 then it continues to iterate thru while loop
        sll.addVal(arr[0][curIndex-1]); //call addVal method and pass in parameters (first column which is the values)
        if ((arr[0][curIndex-1] >= x) && flag==-1) { //if the value at that index is greater or equal to x and if the flag is still -1
            output = arr[0][curIndex-1]; //sets output to be the number that is greater or equal to x
            flag = 0; //flag set to 0 b/c there is a number greater or equal to x
        }
        curIndex = arr[1][curIndex-1]; //set curIndex to be the index (second column)
    }
    return sll; //return sll
}









int main() {
    int n;
    int first;
    int x;
    int output;
    std::cin >> n >> first >> x ;
    int **arr = new int*[2]; 
    arr[0] = new int[n]; //node's value (element)
    arr[1] = new int [n]; //index

    for (int i=0 ; i<n ; i++) {
        std::cin >> arr[0][i] >> arr[1][i]; //arr[col][row]
    }

    SLinkedList sll = makeSLL(n, first, x, arr, output);
    cout << endl << "SLL: " << endl;
    sll.printNodes(); cout << endl;

    //int output = makeSLL(n, first, x, arr);
    std::cout << "Output: " << output << std::endl; 

    return 0;
}
/*
5 3 80
97 -1 
58 5 
16 2 
81 1 
79 4
*/
