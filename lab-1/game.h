#include <iostream>

using namespace std;

// define your classes here...

class Node
{
public:
  //member variables
  double x; 
  double y;
  Node *next;
  
  //initialize constructor
  Node(double x, double y) : x{x}, y{y}, next{nullptr} {}
};

class LinkedList
{
  private:
    //member variables 
    int numPlayers = 0;
    Node *head;

  public:
    //constructor, destructor, member functions 
    LinkedList();
    ~LinkedList();
    void spawn(double x, double y);
    void time(double d);
    void lunch();
    void num();
    void prt(double t);
    void over();
};