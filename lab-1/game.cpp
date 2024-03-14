#include "game.h"
#include <cmath>
#include <string>
using namespace std;

// implement classes' member functions here...

// add player to linked list if in quadrant 1

LinkedList::LinkedList()
{
  head = new Node(0, 0); 
  head->next = nullptr; 
}

LinkedList::~LinkedList()
{
  //TODO: Change
  head = nullptr;
}


void LinkedList::spawn(double x, double y)
{
  // don't add player if out of bounds
  if ((x < 0) || (y < 0) || (x > 500) || (y > 500) || (x == 0) || (y == 0))
  {
    cout << "failure" << endl;
  }
  // add player to front of linked list
  else
  {
    Node *newNode = new Node(x, y); 
    
    if(head->next == nullptr){
      head->next = newNode; 
    }
    else{
      newNode->next = head->next; 
      head->next = newNode; 
    }
    
    numPlayers += 1;

    cout << "success" << endl;
  }
}

// move players t steps
void LinkedList::time(double t)
{
  Node *curr{head->next};
  Node *prev{nullptr};

  while (curr != nullptr)
  {
    double tempX = curr->x;
    double angle = atan2(curr->y, tempX); 
    curr->x -= t * cos(angle);
    curr->y -= t * sin(angle);

    // delete player if not in first quadrant
    if ((curr->x < 0) || (curr->y < 0))
    {
      if(numPlayers == 1){
        head->next = nullptr; 
        curr = nullptr; 
      }
      else{
        prev->next = curr->next;
      }

      numPlayers--;
    }

    prev = curr;
    curr = curr->next;
  }

  cout << "num of players: " << numPlayers << endl;
}

// delete players < 1 from (0, 0)
void LinkedList::lunch()
{
  Node *curr{head->next};
  Node *prev{nullptr};

  while (curr != nullptr)
  {
    double d = sqrt(pow(curr->x, 2) + pow(curr->y, 2));

    // remove player from linked list
    if (d < 1)
    {
      prev->next = curr->next;
      numPlayers--;
    }

    prev = curr;
    curr = curr->next;
  }

  cout << "num of players: " << numPlayers << endl;
}

// output number of players
void LinkedList::num()
{
  cout << "num of players " << numPlayers << endl;
}

// print coordinates of players with distance less than d
void LinkedList::prt(double d)
{
 
  bool players = false;
  Node *curr{head->next};

  // loop through linked list
  while (curr != nullptr)
  {
    double dis = sqrt(pow(curr->x, 2) + pow(curr->y, 2));

    if (dis < d)
    {
      cout << curr->x << " " << curr->y << " ";
      players = true;
    }

    curr = curr->next;
  }

  cout << endl; 

  if (!players)
  {
    cout << "no players found" << endl;
  }
  
}

// check for winner then terminate program
void LinkedList::over()
{
  // check if linked list is empty
  if (head->next == nullptr)
  {
    cout << "wolf wins" << endl;
  }
  else
  {
    cout << "players win" << endl;
  }
}