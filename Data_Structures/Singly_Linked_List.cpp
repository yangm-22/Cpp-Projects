#include <cstdlib>
#include <iostream>
using namespace std;

template <typename E>  // forward declaration of SLinkedList
class SLinkedList;

template <typename E>
class SNode {  // singly linked list node
 private:
  E elem;                       // linked list element value
  SNode<E>* next;               // next item in the list
  friend class SLinkedList<E>;  // provide SLinkedList access
};

template <typename E>
class SLinkedList {  // a singly linked list
 public:
  SLinkedList();              // empty list constructor
  ~SLinkedList();             // destructor
  bool empty() const;         // is list empty?
  const E& front() const;     // return front element
  void addFront(const E& e);  // add to front of list
  void removeFront();         //  remove front of list
  SNode<E>* getHead();             //getting the head of the list
  //SNode of type E b/c there is a template
  void countNodes(SNode<E>* cur,int &count); // counting nodes
  void printNodes();
  void appendNodes(SLinkedList <E> &sll); //passing sll by reference
  void revList(SNode <E>* cur); //reversing the list
 private:
  SNode<E>* head;  // head of the list
};

template <typename E>
SLinkedList<E>::SLinkedList()  // constructor
    : head(NULL) {}

template <typename E>
bool SLinkedList<E>::empty() const {  // is list empty?
  return head == NULL;
}

template <typename E>
const E& SLinkedList<E>::front() const {  // return front element
  return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList() {  // destructor
  while (!empty()) removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e) {  // add to front of list
  SNode<E>* v = new SNode<E>;                // create new node
  v->elem = e;                               // store data
  v->next = head;                            // head now follows v
  head = v;                                  // v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront() {  // remove front item
  if (head == NULL) return;
  SNode<E>* old = head;  // save current head
  head = old->next;      // skip over old head
  delete old;            // delete the old head
}

//get head
template <typename E>
SNode<E> * SLinkedList<E>::getHead() {
  return head;
}

//adding recursive function to the SLinkedList class that counts and returns the number of nodes
template <typename E>
void SLinkedList<E>::countNodes(SNode <E>* cur, int &count) {
  if (cur == NULL) { //base case that returns 
    return; 
  }
  count++; //adding 1 to count 
  //std::cout << count << std::endl;
  countNodes(cur->next, count); //recursive call
}

//printing node elements in order
template <typename E>
void SLinkedList<E>::printNodes() {
  SNode <E>* cur = head; //within scope of function so can just call head instead of sll.getHead()
  while (cur->next != NULL) {
    //elem stores the element that we want to print
    std::cout << cur->elem << "->"; 
    cur = cur->next;
  }
  if (cur->next == NULL) { //end of the printing  
    std::cout << cur->elem << std::endl; //printing last item of list
  }
}


//appending another singly linked list to the end of a list object
template <typename E>
void SLinkedList<E>::appendNodes(SLinkedList <E> &sll) {
  //copy element and redirect arrows
  //getting the tail of sll and the head of sll2
  SNode <E>* cur1 = head; //class we are adding to so we have access to head so we can use that instead of getHead() which is for stuff outside of the current class
  while (cur1->next != NULL) { //b/c if you go to the NULL you cannot access the next
    cur1 = cur1->next;
  }
  SNode <E>* cur2 = sll.getHead();

  //making a new node
  while (cur2 != NULL) { //continue until list 2 reaches NULL (end of list 2)
    SNode <E>* new_node = new SNode <E>; //making new node
    new_node->elem = cur2->elem; //new_node elem assigned to elem of node in list 2
    new_node->next = NULL; //assign new_node next to NULL
    cur1->next = new_node; //assign next of last node in list 1 to new_node
    cur1 = cur1->next; //assign cur1 to cur1 next to proceed in list 1
    cur2 = cur2->next; //assign cur2 to cur2 next to proceed in list 2

    //std::cout << cur1->elem << std::endl;
  } 
}

//reversing a list
template <typename E>
void SLinkedList<E>::revList(SNode <E>* cur) {
  //STEP 2: sets last item of the list to the head
  if (cur->next == NULL) { //base case
    head = cur; 
    return;
  }
  //STEP 1: it'll iterate thru the SLL until it reaches the base case
  revList(cur->next); //recursive step that goes twds base case

  //STEP 3: goes to next previous call of the function 
  // 1->2->3->4->5->NULL
  //head = 5
  cur->next->next = cur; //cur->next->next => 1->2->3->__->5->4 (3 still points to 4)
  cur->next = NULL;  //cur->next = NULL => 1->2->__->__->5->4->3->NULL (2 still points to 3)
}




int main() {
  SLinkedList<std::string> sll;
  int count = 0;
  //declaring variable 
  //node that uses string 
  //of they didnt use namespace you would have to do std::string
  //SNode <string> * cur = sll.getHead(); //start at head 
  sll.addFront("four");
  sll.addFront("three");
  sll.addFront("two");
  sll.addFront("one");

  sll.countNodes(sll.getHead(),count);
  std::cout << "List 1 has " << count << " nodes: " << std::endl;
  //std::cout << count << std::endl;
  sll.printNodes();

  count = 0; //reset count to 0 to count sll2
  SLinkedList<std::string> sll2;
  sll2.addFront("seven");
  sll2.addFront("six");
  sll2.addFront("five");
  sll2.countNodes(sll2.getHead(),count);
  std::cout << "List 2 has " << count << " nodes:" << std::endl;
  sll2.printNodes();


  count = 0; //reset count to 0 to count new sll after appending new nodes
  sll.appendNodes(sll2);
  sll.countNodes(sll.getHead(),count);
  std::cout << "After appending list 2 to list 1, list 1 has " << count << " nodes:" << std::endl;
  sll.printNodes();
  //std::cout << sll.front() << std::endl;

  std::cout << "After reversing list 1, it looks like this: " << std::endl;
  sll.revList(sll.getHead());
  sll.printNodes();


}
