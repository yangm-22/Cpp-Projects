#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include <sstream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class LinkedBinaryTree;

//Builds and returns a binary expression tree from a string expression in postfix notation.
LinkedBinaryTree createExpressionTree(string postfix); 


typedef string Elem;
class LinkedBinaryTree { //create a class called LinkedBinaryTree
  protected: 
    struct Node { // a node of the tree
      Elem elt; // element value
      Node* par; // parent
      Node* left; // left child
      Node* right; // right child
      Node() : elt(), par(NULL), left(NULL), right(NULL) { } //constructor
    };
  public:
    class Position { // position in tree
      private:
        Node* v; // pointer to node
      public:
       Position(Node*_v = NULL) : v(_v) { } // constructor
       Elem& operator*() //get element
          { return v->elt; }
       Position left() const // get left child
         { return Position(v->left); }
       Position right() const // get right child
         { return Position(v->right); }
       Position parent() const // get parent child
          { return Position(v->par); }
       bool isRoot() const // root of tree?
         { return v->par == NULL; }
       bool isExternal() const // an external node?
          { return v->left == NULL && v-> right == NULL; }
        friend class LinkedBinaryTree; // give tree access
        void assignLeft(const Position& p) const { 
          v->left = p.v; //p = class, .v = defref p to get v (getting that is contained in class p)
          v->left->par = v; //making v point back to parent
        } 
        void assignRight(const Position& p) const { 
          v->right = p.v; 
          v->right->par = v; //making v point back to parent
        }
        Elem getElem() const { //getting the elem at v
          Elem element = v->elt;
          return element;
        }
        void deleteRight(const Position& p) const { //p is an object in Position class
          delete(p.v->right); //p.v gives you private node v (which is an instance to struct node)
          p.v->right = NULL;
        }
      }; typedef std::list<Position> PositionList; // list of positions

  public:
    LinkedBinaryTree(); // constructor
    ~LinkedBinaryTree(); // destructor
    int size() const; // number of nodes
    bool empty() const; // is tree empty?
    Position root() const; // get the root
    PositionList positions() const; // list of nodes
    void addRoot(); // add root to empty tree
    void expandExternal(const Position& p) {// expand external node
      Node* v = p.v; // p's node
      v->left = new Node; //  add a new left child
      v->left->par = v; // v is its parent
      v->right = new Node; //and a new right child
      v->right->par = v; // v is its parent
      n += 2; // two more node
    }
    //void destructor(Node* node);
    void printExpression();
    void printExpression(const Position& p); //PRINT EXPRESSION
    double evaluateExpression(double a, double b);
    double evaluateExpression(double a, double b, const Position& p);
    double getScore(); 
    void setScore(double s); //SET THIS TREE'S SCORE 
    //type function [operator used to compare] (arguements)
    bool operator < (const LinkedBinaryTree& tree) const {  // QUESTION 5
      //comaparing you are currently in vs. tree passed in
      return score < tree.score;
    }
    void sizeNodes(int increase) { //counting the number of nodes for each expression
      n += increase;
    }
    // housekeeping functions omitted... destructor, assignment operator, and copy constructor 
  protected: // local utilities 
    void preorder(Node* v, PositionList& pl) const; // preorder utilities 
  private:
    Node* _root; // pointer to the root
    int n; // number of nodes
    double score;
};


LinkedBinaryTree::LinkedBinaryTree() // constructor
  : _root(NULL), n(0) { }
int LinkedBinaryTree::size() const // number of nodes
  { return n; }
bool LinkedBinaryTree::empty() const // is tree empty?
  { return size() == 0; }
LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root
  { return Position(_root); }
void LinkedBinaryTree::addRoot() // add root to empty tree
  { _root = new Node; n = 1; }

/* //DESTRUCTOR METHOD
//commented out b/c the presence of the destructor messes up the sorting of the expressions
// order of "Exp ((1.2 + 1.2) > 9)"" and "Exp (((4 * 5) - 99.7) > 0.7)" are swapped (when compared to the test case) when destructor is included 
//destructor does not work with the given main function since it is called automatically before it gets a chance to create the final expression tree
LinkedBinaryTree::~LinkedBinaryTree() { //DESTRUCTOR
  if (_root != NULL) {
    destructor(_root); 
  }
}

void LinkedBinaryTree::destructor(Node* node) {
  if (node != NULL) {
    destructor(node->left);
    destructor(node->right);
    //delete node;
  }
}
*/

//QUESTION 1
void LinkedBinaryTree::printExpression() {
  printExpression(root());
}

void LinkedBinaryTree::printExpression(const Position& p) { //printing expression
  if (p.isExternal()) { //if p is an external node
    cout << p.getElem(); //print elem of p
  }
  else if (p.getElem() == "abs") { //if elem is "abs", print using this format...
    cout << p.getElem(); 
    cout << "(";
    printExpression(p.left());
    cout << ")";
  }
  else { //if elem is neither then print using this format...
    cout << "(";
    printExpression(p.left()); //print left expression 
    cout << " " << p.getElem() << " ";
    printExpression(p.right()); //print right expression 
    cout << ")";
  }
}

//QUESTION 2
double LinkedBinaryTree::evaluateExpression(double a, double b) {
  return evaluateExpression(a, b, root());
}

//evaluate expression passing variables a and b of type double and p (position) by reference as arguements
double LinkedBinaryTree::evaluateExpression(double a, double b, const Position& p) {
  if (p.getElem() == "abs") { //check if the elem is "abs"
    double yABS = evaluateExpression(a,b,p.left()); //call evaluateExpression
    if (yABS < 0) {  //if the value is negative the convert it to a positive value by multiplying by (-1)
      double absVal = yABS*(-1);
      return absVal; //return the absolute value
    }
    else { //if the value is already positive then just return the original value
      return yABS; 
    }
  }
  else if (!(p.isExternal())) { //if p is not an external node
    //recursively evaluating expression 
    double x = evaluateExpression(a,b,p.left()); //assign left number to x
    double y = evaluateExpression(a,b,p.right()); //assign right number to y
    double result;

    //perform operations
    if (p.getElem() == "+") { //if elem is "+"
      result = x + y; //add x and y
    }
    else if (p.getElem() == "-") { //if elem is "-"
      result = x - y; //subtract y from x
    }
    else if (p.getElem() == "*") { //if elem is "*"
      result = x * y; //multiply x by y
    }
    else if (p.getElem() == "/") { //if elem is "/"
      result = x / y; //if there is no error then calculate x/y
    }
    else if (p.getElem() == ">") { //if elem is ">"
      if (x > y) { //if x>y then return 1
        result = 1;
      }
      else { //if NOT x>y then return -1
        result = -1; 
      }
    }

    return isnan(result) || !isfinite(result) ? 0 : result; //0 if divide by 0 
  }
  else {
    if (p.getElem() == "a") { //checking if the elem is the variable a
      return a;
    }
    else if (p.getElem() == "b") { //checking if the elem is the variable b
      return b;
    }
    else {
      return stod(p.getElem()); //converting string to float
    }
  }
  //return 0;
}


//QUESTION 3
double LinkedBinaryTree::getScore() { //gets the score
  return score; //returning the score obtained
}

//QUESTION 4
void LinkedBinaryTree::setScore(double s) { //sets the score to s
  score = s; //setting the score
}



//function reorganizes the data of postfix into a tree data structure (creates the expression tree)
LinkedBinaryTree createExpressionTree(string postfix) { //function so don't need :: (NOT method)
  std::stack<LinkedBinaryTree> newStack; //creates a new stack of type LinkedBinaryTree so each item in stack is a tree
  string tok; //used for tokenizing
  stringstream ss(postfix); //string must be of type stringstream to be able to tokenize (use tok)
  
  while (getline(ss, tok, ' ')) { //getline(input, output, deliminator)
    LinkedBinaryTree newTree; //making instance of linked binary tree

      //cout << tok << endl;
    if (tok == "abs") { //checks if tok is "abs"
      newTree.addRoot(); //making the root
      *(newTree.root()) = tok; //setting root to new value

      LinkedBinaryTree num1 = newStack.top(); //finding top of stack
      newStack.pop(); //popping first item of stack

      newTree.expandExternal(newTree.root()); // growing branches of tree
      newTree.sizeNodes(num1.size()-2); //increase size of total nodes in expression by 1
      newTree.root().assignLeft(num1.root()); //passing in position of root 

      newStack.push(newTree); //pushing tree into stack
    }
    else if ((tok == "+") || (tok == "-") || (tok == "*") || (tok == "/") ||  (tok == ">") ) {
      newTree.addRoot(); //making the root
      *(newTree.root()) = tok; //setting root to new value
      LinkedBinaryTree num2 = newStack.top(); //finding top of stack
      newStack.pop(); //popping first item of stack
      LinkedBinaryTree num1 = newStack.top(); 
      newStack.pop(); //popping first item of stack
      //assign L and R of root 
      newTree.expandExternal(newTree.root()); // growing branches of tree
      //assigning right and left child branches of root
      newTree.root().assignRight(num2.root()); //passing in position of root 
      newTree.root().assignLeft(num1.root());
      newTree.sizeNodes(num1.size() + num2.size() - 2); //increase size of total nodes in expression by 1

      newStack.push(newTree); //pushing tree into stack
    }
    else { //if it is a # (operand)
      newTree.addRoot(); //making the root
      *(newTree.root()) = tok; //setting root to new value
      newStack.push(newTree); //pushing tree into stack
    }
  }
  LinkedBinaryTree answer = newStack.top(); //assign answer to the top of the stack
  return answer; 
}



int main() {

  // Read postfix expressions into vector 
  //createExpressionTree("22 22 09 29 10");
  vector<LinkedBinaryTree> trees; 
  ifstream exp_file("expressions.txt"); 
  string line;
  while (getline(exp_file, line)) {
    trees.push_back(createExpressionTree(line));
  }
  /*
  for (auto& t : trees) {
        t.printExpression(t.root());
        cout << endl;

*/
// Read input data into 2D vector 
  vector<vector<double> > inputs; 
  ifstream input_file("input.txt"); 
  while (getline(input_file, line)) {
    vector<double> ab_input;
    stringstream ss(line);
    string str;
    while (getline(ss, str, ' ')) {
      ab_input.push_back(stod(str));
    }
    inputs.push_back(ab_input);
  }

  // Evaluate expressions on input data
  for (auto& t : trees) {
    double sum = 0;
    for (auto& i : inputs) {
      sum += t.evaluateExpression(i[0], i[1]);
    }
    //cout<<sum/inputs.size()<<endl;
    t.setScore(sum/inputs.size());
  }

// Sort trees by their score 
  sort(trees.begin(), trees.end());
  
  for (auto& t : trees) { 
    cout << "Exp ";
  t.printExpression();
  cout << " Score " << t.getScore() << endl;

  }
 //*/
}
