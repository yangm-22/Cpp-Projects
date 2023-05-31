#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>

//A stack is an ADT in which elements add added and removed from only one end (i.e.,at the top of the stack)
using namespace std;

//prototypes for classes
class SNode;
class Stack; 
class RPNEvaluator;

//class implementation
class SNode {  //singly linked list node
 private:
  string elem; //linked list element value
  SNode * next; //next item in the list
  friend class Stack; //provide Stack access
};

//class implementation
class Stack {
  public:
    Stack(); //constructor method    
    bool empty(); //check if the stack is empty
    int Size(); //accessor method for the size of the stack
    void push(const string elem); //enters an item in the stack 
    string pop(); //retrieves an item in the stack
    void print(); //printing the values
  
  private: //cannot be changed
    int size; //size of the stack
    SNode * head; 
};

Stack::Stack() {  // constructor
  head = NULL;  //set head to NULL
  size = 0;
}

//check if the stack is empty
bool Stack::empty() {
    if (head == NULL) {
        return true; //return true if empty
    }
    else {
        return false; //return false if not empty
    }
}

//finding size of the stack
int Stack::Size() { 
    return size; 
}

//adding a new item to the stack
void Stack::push(const string elem) {
    SNode * cur = head; //setting cur to be head of the stack 
    if (cur == NULL) { //assigning head to cur if it is an empty list
        head = cur; //set head to cur
        head = new SNode; //make head a new SNode
        head->elem = elem; //set val of head to be val (passed in arugement)
        head->next = NULL; //set next of head to be NULL
        size++; //+1 to size
        return; 
    }
    while (cur->next != NULL) { //keep iterating thru stack until it reaches last item of the stack
        cur = cur->next;
    }
    SNode * new_node = new SNode; //making a new node of type SNode
    cur->next = new_node; //set the next item of cur to new_node
    new_node->elem = elem; //set elem of new_node to elem 
    new_node->next = NULL; //set next of new_node to NULL
    size++;
}

//removing top item of the stack 
string Stack::pop() {
    SNode * cur = head; //setting cur to be head of the stack 
    if (empty()) { //checking if stack is empty
        return "EMPTY"; //return "EMPTY" if the stack is empty
    }
    else if (size == 1) { //if the size of the stack is 1, remove item by running this code
        size--; //-1 from size of stack
        string top = cur->elem; //save the elem of the item being removed
        delete cur; //delete node
        head = NULL; //set head to NULL b/c the only item was just removed from the stack 
        return top; //return top which is the variable that stores the elem of the item that was just removed
    }
    else {
        string top = ""; //make a variable to store the elem of the item of stack being removed/popped
        while (cur->next->next != NULL) { //keep iterating thru stack until it reaches 2nd last item of the stack
            cur = cur->next;
        }
        top = cur->next->elem; //set top to be the elem of the last node in the stack
        delete cur->next; //delete the node that is being popped
        cur->next = NULL; //set cur->next to NULL
        size--;
        return top; //return the elem of the last item that was popped
    }
}

//printing the items in teh stack 
void Stack::print() {
    SNode * cur = head; //make a new node cur and set it to head
    while (cur->next != NULL) { //if next of cur is NOT NULL then continue to print using this format
        //elem stores the element that we want to print
        std::cout << cur->elem << "->";
        cur = cur->next; //iterating thru the list 
    }
    if (cur->next == NULL) { //if at the end of the list then print using this format
        std::cout << cur->elem << std::endl;
    }
}

//implementing class RPNEvaluator
class RPNEvaluator {
  public:
    RPNEvaluator(string equation); //constructor method 
    float Evaluate(); //evaluates the Reverse Polish Notation
  public:
    string eqn; //equation variable that was inputted
};

RPNEvaluator::RPNEvaluator(string equation) {  // constructor
  eqn = equation; 
}

float RPNEvaluator::Evaluate() { //evaluating the RPN input equation
    Stack stack; //make a new stack called stack
    for (int i=0 ; i < eqn.length() ; i++) {
        if (isdigit(eqn[i])) {
            string temp = ""; //intialize a new empty string called temp
            temp = eqn[i]; //converting character to a string to add it into the stack
            stack.push(temp); //adding temp onto the stack 
        }
        //checking if the elem is a valid operator 
        else if ((eqn[i] == '+') || (eqn[i] == '-') || (eqn[i] == '*') || (eqn[i] == '/')) {
            float num1 = 0; //initialize new variable called num1 and set it to 0
            float num2 = 0; //initialize new variable called num2 and set it to 0
            float answer = 0; //initialize a variable to store the answer of the RPN
            
            if (!stack.empty()) { //if stack is NOT empty...
                num2 = stof(stack.pop()); //set num2 to the top of stack that was popped and convert it from string to float type
            }
            else { //if stack is not properly formatted, output "Error: malformed expression"
                cout<< "Error: malformed expression" << endl;
                return -1;
            } 
            if (!stack.empty()) { //if stack is NOT empty...
                num1 = stof(stack.pop()); //set num1 to the top of stack that was popped and convert it from string to float type
            }
            else { //if stack is not properly formatted, output "Error: malformed expression"
                cout<< "Error: malformed expression" << endl;
                return -1;
            }

            if (eqn[i] == '+') { //if elem at eqn[i] is '+' then compute num1+num2 and set it to the variable answer
                answer = num1 + num2;
            }
            else if (eqn[i] == '-') { //if elem at eqn[i] is '-' then compute num1-num2 and set it to the variable answer
                answer = num1 - num2;
            }
            else if (eqn[i] == '*') { //if elem at eqn[i] is '*' then compute num1*num2 and set it to the variable answer
                answer = num1*num2;
            }
            else if (eqn[i] == '/') { //if elem at eqn[i] is '/' then compute num1/num2 and set it to the variable answer
                answer = num1/num2;
            }
            stack.push(to_string(answer)); //convert answer to string type and add the answer to the top of stack 
        }
    }
    float final_answer = stof(stack.pop()); //after the for loop runs, there should only be one item in the stack which is the final answer of the RPN input
    //cout<<"Is empty? "<<stack.empty()<<endl;
    cout<<"Answer: "<<final_answer<<endl; //output final_answer of RPN
    return final_answer; //return final_answer
}

int main() { //given main function in question
    std::string rpn_exp;
    std::cout << "Please enter an expression in RPN format: ";
    std::getline(std::cin, rpn_exp);
    RPNEvaluator rpn(rpn_exp);
    rpn.Evaluate();
    return EXIT_SUCCESS;
/*
    Stack S;
    S.push("1");
    S.push("1");
    S.push("1");
    S.push("1");
    S.pop();
*/
}

//5 2 + 8 3 - * 4 /
