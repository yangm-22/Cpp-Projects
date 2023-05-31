#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;


// return true is op is a suported operation, otherwise return false
bool isOp(string op) {
  if (op == "+")
    return true;
  else if (op == "-")
    return true;
  else if (op == "*")
    return true;
  else if (op == "/")
    return true;
  else if (op == ">")
    return true;
  else if (op == "abs")
    return true;
  else
    return false;
}

int arity(string op) {
  if (op == "abs")
    return 1;
  else
    return 2;
}

typedef string Elem;

class LinkedBinaryTree {
 public:
  struct Node {
    Elem elt;
    string name;
    Node* par;
    Node* left;
    Node* right;
    Node() : elt(), par(NULL), name(""), left(NULL), right(NULL) {}
    int depth() {
      if (par == NULL) return 0;
      return par->depth() + 1;
    }
  };

  class Position {
   private:
    Node* v; //node at position

   public:
    Position(Node* _v = NULL) : v(_v) {}
    Elem& operator*() { return v->elt; }
    Position left() const { return Position(v->left); }
    void setLeft(Node* n) { v->left = n; }
    Position right() const { return Position(v->right); }
    void setRight(Node* n) { v->right = n; }
    Position parent() const  // get parent
    {
      return Position(v->par);
    }
    bool isRoot() const  // root of the tree?
    {
      return v->par == NULL;
    }
    bool isExternal() const  // an external node?
    {
      return v->left == NULL && v->right == NULL;
    }
    Elem getElem() const {
        return v->elt;
    }
    Node * getNode() {
        return v;
    }
    friend class LinkedBinaryTree;  // give tree access
  };
  typedef vector<Position> PositionList;

 public:
  LinkedBinaryTree() : _root(NULL), score(0), steps(0), generation(0) {}

  // copy constructor
  LinkedBinaryTree(const LinkedBinaryTree& t) {
    _root = copyPreOrder(t.root().v);
    score = t.getScore();
    steps = t.getSteps();
    generation = t.getGeneration();
  }

  // copy assignment operator
  LinkedBinaryTree& operator=(const LinkedBinaryTree& t) {
    if (this != &t) {
      // If tree already contains data, delete it
      if (_root != NULL) {
        PositionList pl = positions();
        for (auto& p : pl) delete p.v;
      }
      _root = copyPreOrder(t.root().v);
      score = t.getScore();
      steps = t.getSteps();
      generation = t.getGeneration();
    }
    return *this;
  }

  // destructor
  ~LinkedBinaryTree() {
    if (_root != NULL) {
      PositionList pl = positions();
      for (auto& p : pl) delete p.v;
    }
  }

  int size() const { return size(_root); }
  int size(Node* root) const;
  int depth() const;
  bool empty() const { return size() == 0; };
  Position root() const { return Position(_root); }
  PositionList positions() const; //gives you a list of all the nodes
  void addRoot() { _root = new Node; }
  void addRoot(Elem e) {
    _root = new Node;
    _root->elt = e;
  }
  void nameRoot(string name) { _root->name = name; }
  void addLeftChild(const Position& p, const Node* n);
  void addLeftChild(const Position& p);
  void addRightChild(const Position& p, const Node* n);
  void addRightChild(const Position& p);
  void printExpression() { printExpression(Position(_root)); }
  void printExpression(const Position& p);
  double evaluateExpression(double a, double b) {
    return evaluateExpression(a, b, Position(_root));
  };
  double evaluateExpression(double a, double b, const Position& p);
  long getGeneration() const { return generation; }
  void setGeneration(int g) { generation = g; }
  double getScore() const { return score; }
  void setScore(double s) { score = s; }
  double getSteps() const { return steps; }
  void setSteps(double s) { steps = s; }
  bool operator < (const LinkedBinaryTree& tree) const {  // QUESTION 5
      //comaparing you are currently in vs. tree passed in
      return (score) < (tree.score);
    }

 protected:                                        // local utilities
  void preorder(Node* v, PositionList& pl) const;  // preorder utility
  Node* copyPreOrder(const Node* root);
  double score;     // mean reward over 20 episodes
  double steps;     // mean steps-per-episode over 20 episodes
  long generation;
 private:
  Node* _root;  // pointer to the root
};

// add the tree rooted at node child as this tree's left child
void LinkedBinaryTree::addLeftChild(const Position& p, const Node* child) {
  Node* v = p.v;
  v->left = copyPreOrder(child);  // deep copy child
  v->left->par = v;
}

// add the tree rooted at node child as this tree's right child
void LinkedBinaryTree::addRightChild(const Position& p, const Node* child) {
  Node* v = p.v;
  v->right = copyPreOrder(child);  // deep copy child
  v->right->par = v;
}

void LinkedBinaryTree::addLeftChild(const Position& p) {
  Node* v = p.v;
  v->left = new Node;
  v->left->par = v;
}

void LinkedBinaryTree::addRightChild(const Position& p) {
  Node* v = p.v;
  v->right = new Node;
  v->right->par = v;
}

// return a list of all nodes
LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const {
  PositionList pl;
  preorder(_root, pl);
  return PositionList(pl);
}

void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const {
  pl.push_back(Position(v));
  if (v->left != NULL) preorder(v->left, pl);
  if (v->right != NULL) preorder(v->right, pl);
}

int LinkedBinaryTree::size(Node* v) const {
  int lsize = 0;
  int rsize = 0;
  if (v->left != NULL) lsize = size(v->left);
  if (v->right != NULL) rsize = size(v->right);
  return 1 + lsize + rsize;
}

int LinkedBinaryTree::depth() const {
  PositionList pl = positions();
  int depth = 0;
  for (auto& p : pl) depth = std::max(depth, p.v->depth());
  return depth;
}

LinkedBinaryTree::Node* LinkedBinaryTree::copyPreOrder(const Node* root) {
  if (root == NULL) return NULL;
  Node* nn = new Node;
  nn->elt = root->elt;
  nn->left = copyPreOrder(root->left);
  if (nn->left != NULL) nn->left->par = nn;
  nn->right = copyPreOrder(root->right);
  if (nn->right != NULL) nn->right->par = nn;
  return nn;
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


//function reorganizes the data of postfix into a tree data structure (creates the expression tree)
LinkedBinaryTree createExpressionTree(string postfix) { //function so don't need :: (NOT method)
  std::stack<LinkedBinaryTree> newStack; //creates a new stack of type LinkedBinaryTree so each item in stack is a tree
  string tok; //used for tokenizing
  stringstream ss(postfix); //string must be of type stringstream to be able to tokenize (use tok)
  
  while (getline(ss, tok, ' ')) { //getline(input, output, deliminator)
    if (tok == "*" || tok == "+" || tok == "-" || tok == ">" || tok == "/"){ 
      LinkedBinaryTree newTree; //making instance of linked binary tree
      newTree.addRoot(); // adding a root
      *(newTree.root()) = tok; // set root to be elem of token

      //save trees to stack and pop out
      LinkedBinaryTree right = newStack.top();
      newStack.pop();
      LinkedBinaryTree left = newStack.top();
      newStack.pop();

      newTree.addRightChild(newTree.root(), right.root().getNode()); //add new Right node
      newTree.addLeftChild(newTree.root(), left.root().getNode()); //add new Left node

      newStack.push(newTree); //push tree onto stack
    }

      //cout << tok << endl;
    else if (tok == "abs") { //checks if tok is "abs"
      LinkedBinaryTree newTree;
      newTree.addRoot(); //making the root
      *(newTree.root()) = tok; //setting root to new value

      LinkedBinaryTree left = newStack.top(); //finding top of stack
      newStack.pop(); //popping first item of stack

      newTree.addLeftChild(newTree.root(), left.root().getNode()); //add new Left node
      newStack.push(newTree); //push tree onto stack
    }

    else {
      LinkedBinaryTree newTree;
      newTree.addRoot();
      *(newTree.root()) = tok;
      newStack.push(newTree);
    }
  }
    LinkedBinaryTree answer = newStack.top(); //final tree is located on top of stack
    newStack.pop();
    return answer; 
}


int main(){

  // Read postfix expressions into vector 
  //createExpressionTree("22 22 09 29 10");
  vector<LinkedBinaryTree> trees; 
  ifstream exp_file("expressions.txt"); 
  string line;
  while (getline(exp_file, line)) {
    trees.push_back(createExpressionTree(line));
  }


  for (auto& t : trees) {
        t.printExpression(t.root());
        cout << endl;
  }

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

  return 0;

}
