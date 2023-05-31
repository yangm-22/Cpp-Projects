#include <cstdlib>
#include <iostream>
using namespace std;
typedef std::string Elem;

class DNode {  // doubly linked list node
 private:
  Elem elem;                 // node element value
  int score;  //adding score of player
  DNode* prev;               // previous node in list
  DNode* next;               // next node in list
  friend class DLinkedList;  // allow DLinkedList access
};

class DLinkedList {  // doubly linked list
 public:
  DLinkedList();                 // constructor
  DLinkedList(const DLinkedList &dll2); //ADDING NEW COPY CONSTRUCTOR
  void operator = (const DLinkedList &dll2); //PART G USING OVERLOAD ASSIGNMENT
  ~DLinkedList();                // destructor
  bool empty() const;            // is list empty?
  const Elem& front() const;     // get front element
  const Elem& back() const;      // get back element
  void addFront(const Elem& e);  // add to front of list
  void addBack(const Elem& e);   // add to back of list
  void removeFront();            // remove from front
  void removeBack();             // remove from back
  DNode * getHead(); //getting the head of the list
  int Size(); //PART A
  int trueSize(DNode * cur);
  void AddScoreInOrder(Elem name, int score); //PART B
  void RemoveScore(int index); //PART C 
  bool UpdateScore(Elem name, int score); //PART D
  void Print(); //PART E
  void truePrint(DNode * cur);
  void OrderByName(); //PART H

 private:                        // local type definitions
  DNode* header;                 // list sentinels
  DNode* trailer;

 protected:                           // local utilities
  void add(DNode* v, const Elem& e);  // insert new node before v
  void remove(DNode* v);              // remove node v
};

DLinkedList::DLinkedList() {  // constructor
  header = new DNode;         // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;
}

//PART F 
DLinkedList::DLinkedList(const DLinkedList &dll2) {  // COPY CONSTRUCTOR
    DNode * cur = dll2.header; //set cur to equal head of dll2
    header = new DNode; //initialize header for dll2
    trailer = new DNode; //initialize trailer for dll2
    header->next = trailer; //set trailer to be next of header b/c it is an empty list
    trailer->prev = header; //set header to be prev of trailer b/c it is an empty list
    header->prev = NULL; //set the prev of header to be NULL b/c header is the start of the list
    trailer->next = NULL; //set the next of trailer to be NULL b/c trailer is the end of the list

    cur = cur->next; //set cur to equal cur->next to iterate thru list
    while (cur->next != NULL) {  //keeps on iterating 
        AddScoreInOrder(cur->elem, cur->score); //calls AddScoreInOrder method and pass in cur's elem and cur's score 
                                                //to add the score according to descending order (highest to lowest)
        cur = cur->next; //make cur equal to cur->next to continue to iterate thru list
    }
}

//PART G
void DLinkedList::operator = (const DLinkedList &dll2) { //overloading assignment (=) operator
    DNode * cur = dll2.header; //setting cur to be dll2 header
    header = new DNode; //making a header as type DNode
    trailer = new DNode; //making a trailer as type DNode
    header->next = trailer; //making a header next to be trailer
    trailer->prev = header; //making prev of trailer the header
    header->prev = NULL; //setting prev of header to NULL
    trailer->next = NULL; //setting next of trailer to NULL

    cur = cur->next; //proceeding to next of cur and setting it to cur
    while (cur->next != NULL) { //iterating thru cur until next of cur is NULL
        AddScoreInOrder(cur->elem, cur->score); //calling method AddScoreInOrder and passing parameters elem of cur and score of cur
        cur = cur->next; //iterating thru list by setting cur to be cur->next
    }

} 


DLinkedList::~DLinkedList() {  // destructor
  while (!empty()) {
    removeFront();  //  remove all but sentinels
  }
  delete header;  //  remove the sentinels
  delete trailer;
}

bool DLinkedList::empty() const {  // is list empty?
  return (header->next == trailer);
}

const Elem& DLinkedList::front() const {  // get front element
  return header->next->elem;
}

const Elem& DLinkedList::back() const {  // get back element
  return trailer->prev->elem;
}

void DLinkedList::add(DNode* x, const Elem& value) {
  DNode* newNode = new DNode;
  newNode->elem = value;
  newNode->next = x->next;
  newNode->prev = x;
  x->next->prev = newNode;
  x->next = newNode;
}

void DLinkedList::addFront(const Elem& e) {  // add to front of list
  add(header, e);
}

void DLinkedList::addBack(const Elem& e) {  // add to back of list
  add(trailer->prev, e);
}

void DLinkedList::remove(DNode* v) {  // remove node v
  DNode* u = v->prev;                 // predecessor
  DNode* w = v->next;                 // successor
  u->next = w;                        // unlink v from list
  w->prev = u;
  delete v;
}

void DLinkedList::removeFront() {  // remove from font
  remove(header->next);
}

void DLinkedList::removeBack() {  // remove from back
  remove(trailer->prev);
}

void listReverse(DLinkedList& L) {  // reverse a list
  DLinkedList T;                    // temporary list
  while (!L.empty()) {              // reverse L into T
    Elem s = L.front();
    L.removeFront();
    T.addFront(s);
  }
  while (!T.empty()) {  // copy T back to L
    Elem s = T.front();
    T.removeFront();
    L.addBack(s);
  }
}


DNode * DLinkedList::getHead() { //getting head of list 
  return header;
}

//PART A
int DLinkedList::Size() {
    return trueSize(header); //call trueSize method
}
int DLinkedList::trueSize(DNode * cur) { //calculates the size of the list
    if (cur->next == trailer) { //base case
        return 0; //exits method and returns size (sums together the return values of the previous recursion calls)
    }
    return trueSize(cur->next)+1; //adds one to the counter and iterates thru the list by calling cur->next
}

//PART B
//placing scores from highest to lowest
void DLinkedList::AddScoreInOrder(std::string name, int score) { //function that organizes scores from highest to lowest 
    DNode * new_node = new DNode; //make a new node called new_node of type DNode
    DNode * temp = new DNode; //make a temporary node called temp of type DNode
    new_node->elem = name; //set elem of new_node to be the arguement passed in called "name"
    new_node->score = score; //set score of new_node to be the arguement passed in called "score"
    //first score entered (empty list)
    if (header->next == trailer) { //checks if next node from header is the trailer and if it is then it will run thru this "if statement"
        new_node->next = trailer; //set next node of new node to point to trailer
        trailer->prev = new_node; //set prev node of trailer to be new_node
        header->next = new_node; //set the next of header to be new_node
        new_node->prev = header; //set prev of new_node to be header
    }
    //iterating thru array by comparing scores 
    else { //if the list is not empty then this else statement will run
        DNode * cur = header->next; //set cur to be the next node of header
        if (new_node->score >= cur->score) { //checking if new elem is greatest # in list
            new_node->next = cur; //set next of new_node to cur
            cur->prev = new_node; //set prev of cur to be new_node
            header->next = new_node; //set next of header to be new_node
            new_node->prev = header; //set prev of new_node to be header
        }
        else {
            while ((score < cur->score) && (cur != trailer)) { // iterate through the list to find out where to slot the new score entry
                cur = cur->next;
            }
            
            //cur is at node at which prev score is higher than new_node->elem AND lower than next score
            temp = cur->prev; //setting temp to be prev of cur
            new_node->prev = temp; //set prev of new_node to be temp
            new_node->next = cur; //set new_node of next to be cur
            cur->prev = new_node; //set prev of cur to new_node 
            temp->next = new_node; //set next of temp to be new_node
        }
    }
}

//PART C
void DLinkedList:: RemoveScore(int index) { //deleting a node
    DNode * cur = header->next; //set cur to be next of header
    for (int i=0 ; i<index ; i++) { //iterate thru list until i is equal to index
        cur = cur->next; //itertaing thru list
    }
    //rearraging the arrows of the nodes
    cur->prev->next = cur->next; //setting the next of the previous node of cur to be cur->next
    cur->next->prev = cur->prev; //setting the prev of next node of cur to be cur->prev
    delete cur; //deleting cur node
}

//PART D 
bool DLinkedList:: UpdateScore(std::string name, int score) {  //Elem = std::string
    DNode * cur = header->next; //set cur to be next of header
    while (cur->elem != name) { //comparing names until we reach the name that we want
        if (cur->next == trailer) { //if the next node from cur is trailer then return false
            return false;
        }
        cur = cur->next; //iterating thru the list
    }

    if (cur->elem == name) { //if score change was successful return True
        cur->prev->next = cur->next; //setting the next of the previous node form cur to be cur->next
        cur->next->prev = cur->prev; //setting the prev of the next node to be cur->prev
        AddScoreInOrder(cur->elem, score); //passing in elem at cur and the new score into AddScoreInOrder method to sort the list
        delete cur; //delete cur node
        return true; //return true is changed successfully
    }
    else { //if score change was UNsuccessful return False
        return false;
    }
}





//PART E
void DLinkedList::Print() { //print method that uses a helper class called truePrint and passing in the header
    truePrint(header);
}
void DLinkedList::truePrint(DNode * cur) { //helper method for Print() method
    if (empty()) { //if the list is empty then exit the method
        return;
    }
    if (cur == header) { //if cur is header then proceed to cur->next
        cur = cur->next;
    }
    if (cur->next == trailer) { //if cur->next is trailer (last item in list) then print it in this format
        std::cout << "{" << cur->elem << "," << cur->score << "}" << std::endl; 
        return; //return when done
    }
    std::cout << "{" << cur->elem << "," << cur->score << "}->" ; //print items in this format if it has not reached the end of the list
    truePrint(cur->next); //recursion call and send in cur->next as parameter
}

//PART H
void DLinkedList::OrderByName() { //method that prints the list alphabetically
    DNode * cur = header->next; //set cur to be header next
    DNode * cur2 = header->next; //set cur2 to be header next as well
    //DNode * temp;
    //make a tail to see when cur 2 should stop
    DNode * end = trailer->prev; //set the end node to be prev of trailer

    while (cur->next != trailer) { //while loop runs as long as next node from cur is not trailer (end of list)
        cur2 = header->next;
        while (cur2 != end) {
            if (cur2->elem > cur2->next->elem) {
                string tempName = cur2->next->elem;
                int tempScore = cur2->next->score;
                cur2->next->elem = cur2->elem;
                cur2->next->score = cur2->score;
                cur2->elem = tempName;
                cur2->score = tempScore;
                
                /*temp = cur2;
                cur2->elem = cur2->next->elem;
                cur2->score = cur2->next->score;
                cur2->next->elem = temp->elem;
                cur2->next->score = temp->score; */
            }
            cur2 = cur2->next; 
        } 
        cur = cur->next; 
        end = end->prev;
    }
}


int main() {
    DLinkedList scores;
    scores.Print();
    scores.AddScoreInOrder("Jeff", 7);
    scores.AddScoreInOrder("Jen", 9);
    scores.AddScoreInOrder("Ilya", 3);
    scores.AddScoreInOrder("Sara", 10);
    scores.AddScoreInOrder("Sam", 11);
    //scores.Print();

    // Test size function
    cout << "Number of scores is " << scores.Size() << endl; 
    scores.Print();
    // Test remove function
    scores.RemoveScore(3);
    cout << "Number of scores is now " << scores.Size() << endl; 

    scores.Print();
    // Test update function
    if (scores.UpdateScore("Jeff",6))
    scores.Print();
    // Test copy construcor
    DLinkedList scores_copy_1(scores); 
    scores.UpdateScore("Jen",5); 
    scores.Print();
    scores_copy_1.Print();
    // Test assignment operator overload 
    DLinkedList scores_copy_2;
    scores_copy_2 = scores_copy_1;  
    scores_copy_1.UpdateScore("Jen",5); 
    scores_copy_1.Print(); 
    scores_copy_2.Print();
    // Test OrderByName function 
    scores_copy_2.OrderByName(); 
    scores_copy_2.Print();
    
}
