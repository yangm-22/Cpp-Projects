#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

//A Deque, also known as a double-ended queue, is a data structure that supports 
//insertion and deletion operations at both the front and back of the queue
using namespace std;

//prototypes for classes
class Deque; 

//class implementation
class Deque {
public:
    Deque(int n): capacity(n), elemVector(n), frontIndex(0), backIndex(n-1), Size(0) {}
    void insertFront(std::string e); //PART B
    void insertBack(std::string e); //PART C
    void eraseFront(); //PART D
    void eraseBack(); //PART E
    std::string front(); //PART F
    std::string back(); //PART G
    int size(); //PART H
    bool empty(); //PART I
    void print(); //prints deque
    void printVector(); //prints vector
    
private:
    int capacity; //size limit 
    std::vector<std::string> elemVector; //vector of the elems of the vector
    int frontIndex; //first index
    int backIndex; //back index
    int Size; //size of the current # of items
};

//PART B
//inserting a new element e at the beginning of the deque
void Deque::insertFront(std::string e) {
    if (Size == capacity) { //checking if the number of elems in the deque is the same as capacity
        return; // deque at capacity
    }
    else {
        frontIndex = (frontIndex - 1 + capacity) % capacity; //calculating index to insert elem e at (at front of deque)
        elemVector[frontIndex] = e; //inserting elem e at front of deque
        Size++; //add 1 to the number of elems in deque
    }
}

//PART C
//inserting a new element e at the end of the deque
void Deque::insertBack(std::string e) {
    if (Size == capacity) { //checking if the number of elems in the deque is the same as capacity
        return; // deque at capacity
    }
    else {
        backIndex = (backIndex + 1) % capacity; //calculating index to insert elem e at at back of deque)
        elemVector[backIndex] = e; //inserting elem e at back of deque
        Size++; //add 1 to the number of elems in deque
    }
}

//PART D
//removing the first element of the deque (if it is not empty)
void Deque::eraseFront() {
    if (Size == 0) { //checking if deque is empty
        return; //if deque is empty, nothing to erase so return
    }
    frontIndex = (frontIndex + 1) % capacity; //calculating index of elem to remove (at front of deque)
    Size--; //subtract 1 from the number of elems in deque
}

//PART E
//removing the last element of the deque (if it is not empty)
void Deque::eraseBack() {
    if (Size == 0) { //checking if deque is empty
        return; //if deque is empty, nothing to erase so return
    }
    else {
        backIndex = (backIndex - 1 + capacity) % capacity; //calculating index of elem to remove (at back of deque)
        Size--; //subtract 1 from the number of elems in deque
    }
}

//PART F
//returning the first element of the deque
//if deque is empty, return “error: empty deque”
std::string Deque::front() {
    if (Size == 0) { //checking if deque is empty
        return "error: empty deque"; //if deque is empty, no elem to return so return message
    }
    else {
        string front = elemVector[frontIndex]; //assign variable front to the elem at frontIndex
        return front; //return front 
    }
}

//PART G
//returning the last element of the deque
//if deque is empty, return “error: empty deque”
std::string Deque::back() {
    if (Size == 0) { //checking if deque is empty
        return "error: empty deque"; //if deque is empty, no elem to return so return message
    }
    else {
        string back = elemVector[backIndex]; //assign variable back to the elem at backIndex
        return back; //return back
    }
}

//PART H
//returning the number of elements in deque
int Deque::size() {
    return Size; //return size of deque
}

//PART I
//returning true if the deque is empty and false otherwise
bool Deque::empty() {
    if (Size == 0) { //checking if deque is empty
        return true; //if deque is empty, return true
    }
    else {
        return false; //else return false since deque is not empty
    }
}

//print deque method
void Deque::print() {
    int cur = frontIndex; //set cur to the frontIndex
    if (Size == 0) { //check if siz eis empty and if it is then output "deque is empty"
        cout<<"deque is empty"<<endl;
        return;
    }
    for (int i=0 ; i<Size ; i++) { //iterate thru current size of deque
        if (i == Size-1) { //if i is at the last elem of the deque print using this format
            cout<<elemVector[cur]<<endl;
            return; 
        }
        else { //else print using this format
            cout<<elemVector[cur]<<"->";
            cur = (cur + 1) % capacity; //find the next index in the deque and set it to cur
        }
    }
}

//print vector method
void Deque::printVector() {
    for (int m=0 ; m<capacity ; m++) { //iterate thru vector until all printed using this format
        cout<<elemVector[m]<<" ";
    }
    cout<<endl;
}


/*
//MAIN FUNCTION
int main() {
    int n = 10; //set n to 10
    Deque D(n); //create new Deque called D and pass n as an arguement
    D.insertFront("1");
    D.insertFront("2");
    D.insertBack("3");
    D.insertBack("4");
    D.insertBack("5");
    D.insertFront("4");

    D.print();
    D.printVector();

    D.eraseBack();
    D.eraseFront();

    D.print();
    D.printVector();

    D.insertFront("8");
    D.insertBack("9");

    D.print();
    D.printVector();

    cout<<D.front()<<" "<<D.back()<< " " << D.size() << " " << D.empty() << endl;

    D.eraseFront();
    D.eraseFront();
    D.eraseFront();
    D.eraseFront();
    D.eraseFront();
    D.print();

    D.eraseFront();

    cout << D.front() <<endl;
    cout << D.back() << endl;
    cout<< D.size() << endl;
    cout<< D.empty() << endl;



    return 0;
}
*/
